//=============================================================================
// 敵の船 [enemy_ship.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "game.h"
#include "player.h"
#include "character_box.h"
#include "byte_effect.h"
#include "motion.h"
#include "boss_bullet.h"
#include "byte_attack_range.h"
#include "boss_shark.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define MAX_LIFE			(500)														// 体力
#define ROT_SPEED			(0.04f)														// 旋回速度
#define ANGLE_180			(D3DXToRadian(180))											// 180度
#define ANGLE_90			(D3DXToRadian(90))											// 90度
#define ANGLE_360			(D3DXToRadian(360))											// 90度
#define SIZE				(D3DXVECTOR3(16000.0f,5000.0f,16000.0f))						// サイズ
#define BYTE_SIZE			(D3DXVECTOR3(3000.0f,3000.0f,0.0f))							// 噛みつきエフェクトサイズ
#define BYTE_RANGE_SIZE		(D3DXVECTOR3(10000.0f,0.0f,10000.0f))						// 噛みつき範囲サイズ
#define ATTACK_COUNT		(300)														// 攻撃間隔
#define BYTE_COUNT			(500)														// 噛みつき攻撃
#define BYTE_KEY_MAX		(1)															// 噛みつき攻撃Keyの最大
#define BYTE_FRAME			(15)														// エフェクト生成Frame
#define BYTE_FRAME_MAX		(45)														// 噛みつき攻撃Frameの最大
#define BULLET_ROT			(D3DXVECTOR3(D3DXToRadian(90.0f),0.0f,D3DXToRadian(180.0f)))// 向き
#define MUT_2				(2)															// 2倍
#define RANGE_LENGTH		(13000.0f)													// 攻撃範囲位置算出用
#define RANGE_Y				(100.0f)													// 範囲のY座標
#define BYTE_LENGTH			(5000.0f)													// 長さ
#define BULLET_CNT			(1000)														// 弾発射カウント
#define BULLET_KEY_MAX		(3)															// 弾発射キー最大
#define BULLET_KEY			(2)															// 弾発射キー最大
#define BULLET_FRAME		(0)															// 弾フレーム
#define BULLET_FRAME_MAX	(40)														// 弾フレーム最大
#define BYTE_Y				(2000.0f)													// 位置
// 顎の位置
#define CHIN_POS		(D3DXVECTOR3(pChin->GetMtxWorld()._41, pChin->GetMtxWorld()._42, pChin->GetMtxWorld()._43))
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Shark::CBoss_Shark(PRIORITY Priority) : CEnemy(Priority)
{
	m_MotionState	= MOTION_STATE_IDLE;
	m_bEnd			= false;
	m_bEnemyCreate	= false;
	m_bRot			= false;
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Shark::~CBoss_Shark()
{
}
//=============================================================================
// 生成関数
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Shark * CBoss_Shark::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CBoss_Sharkポインタ
	CBoss_Shark *pBoss_Shark = nullptr;

	// nullcheck
	if (pBoss_Shark == nullptr)
	{
		// メモリ確保
		pBoss_Shark = new CBoss_Shark;

		// !nullcheck
		if (pBoss_Shark != nullptr)
		{
			// 初期化処理
			pBoss_Shark->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pBoss_Shark;
}
//=============================================================================
// 初期化関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBoss_Shark::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデルの情報を渡す
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_BOSS_SHARK);
	}

	// 体力設定
	SetLife(MAX_LIFE);

	// サイズ設定
	SetSize(SIZE);

	// 攻撃判定設定
	SetAttackDecision(ATTACK_DECISION_CIRCLE);

	// タイプ設定
	SetType(TYPE_BOSS);

	// 影の使用
	SetUseShadow();

	// 影の回転を反映させる
	SetShadowRotCalculation();

	// 初期化関数
	CEnemy::Init(pos, rot);

	return S_OK;
}
//=============================================================================
// 終了関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}
//=============================================================================
// 更新関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::Update(void)
{
	// 更新処理
	CEnemy::Update();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// モーション更新
	ModelAnimeUpdate();

	// モーション処理
	MotionUpdate();

	// 古い座標保存
	SetPosOld(pos);

	// 向き更新
	UpdateRot();

	// 攻撃処理
	Attack();

	// falseの場合
	if (m_bEnemyCreate == false)
	{
		// 敵生成
		Enemy_Create();
	}
	// 死亡処理
	Death();
}
//=============================================================================
// 描画関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::Draw(void)
{
	// 描画関数
	CEnemy::Draw();
}

//=============================================================================
// 攻撃処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::Attack(void)
{
	// エネミーの攻撃
	CEnemy::Attack();

	// 攻撃カウント取得
	int nAttackCount = GetAttackCount();

	// ライフ取得
	int nLife = GetLife();

	// カウントが300以上の場合
	if (nAttackCount == ATTACK_COUNT)
	{
		// 位置取得
		D3DXVECTOR3 pos = GetPos();

		// 向き取得
		D3DXVECTOR3 rot = GetRot();

		// 攻撃範囲位置
		D3DXVECTOR3 RangePos = ZeroVector3;

		// 座標を求める
		RangePos.x = pos.x - cosf(rot.y + ANGLE_90) * RANGE_LENGTH;
		RangePos.z = pos.z + sinf(rot.y + ANGLE_90) * RANGE_LENGTH;
		RangePos.y = RANGE_Y;

		// 攻撃範囲生成
		CByte_Attack_Range::Create(RangePos, BYTE_RANGE_SIZE);

		// falseに
		m_bRot = true;
	}
	// カウントが500以上の場合
	if (nAttackCount == BYTE_COUNT)
	{
		// 噛みつき攻撃
		ByteAttack();

		// ライフが半分より大きいの場合
		if (nLife > MAX_LIFE / DIVIDE_2)
		{
			// 0に
			GetAttackCount() = ZERO_INT;
		}
	}
	// ライフが半分以下の場合
	if (nLife <= MAX_LIFE / DIVIDE_2)
	{
		// 攻撃カウント
		if (nAttackCount == BULLET_CNT)
		{
			// 弾発射攻撃
			m_MotionState = MOTION_STATE_SHARK_BULLET;

			// 0に
			GetAttackCount() = ZERO_INT;
		}
	}
}
//=============================================================================
// 死亡処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::Death(void)
{
	// 状態取得
	int nState = GetState();

	// 死亡状態
	if (nState == STATE_DEAD)
	{
		// trueに
		m_bEnd = true;
	}
}
//=============================================================================
// 噛みつき攻撃処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::ByteAttack(void)
{
	// 噛みつきモーション
	m_MotionState = MOTION_STATE_BYTE;

	CSound *pSound = GET_SOUND_PTR;
//	pSound->Play(CSound::SOUND_BGM_RESULT);

}
//=============================================================================
// サメの弾攻撃処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::SharkBulletAttack(void)
{
	// 顎のポインタ取得
	CModelAnime *pChin = GetModelAnime(PARTS_CHIN);

	// 弾生成
	CBoss_Bullet::CreateBullet(CHIN_POS, BULLET_ROT);
}
//=============================================================================
// モーション処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::MotionUpdate(void)
{
	// アイドルモーション
	if (m_MotionState == MOTION_STATE_IDLE)
	{
		// モーション設定
		SetMotion(m_MotionState);
	}
	// 噛みつきモーション
	if (m_MotionState == MOTION_STATE_BYTE)
	{
		// モーション設定
		SetMotion(m_MotionState);

		// 位置取得
		D3DXVECTOR3 pos = GetPos();

		// モーション取得
		CMotion *pMotion = GetMotion();

		// キー取得
		int nKey = pMotion->GetKey();

		// フレーム取得
		int nFrame = pMotion->GetCountMotion();
		
		// キーとカウントが最大になったら
		if (nKey == BYTE_KEY_MAX && nFrame == BYTE_FRAME)
		{
			// 顎のポインタ取得
			CModelAnime *pChin = GetModelAnime(PARTS_CHIN);

			// 向き取得
			D3DXVECTOR3 rot = GetRot();

			// 攻撃範囲位置
			D3DXVECTOR3 RangePos = ZeroVector3;

			// 座標を求める
			RangePos.x = CHIN_POS.x - cosf(rot.y + ANGLE_90) * BYTE_LENGTH;
			RangePos.z = CHIN_POS.z + sinf(rot.y + ANGLE_90) * BYTE_LENGTH;
			RangePos.y = CHIN_POS.y;

			// 180度加算
			rot.y += ANGLE_180;

			// 噛みつきエフェクト生成
			//CByte_Effect::CrateEffect(RangePos, BYTE_SIZE, rot);
		}
		// キーとカウントが最大になったら
		if (nKey == BYTE_KEY_MAX && nFrame >= BYTE_FRAME_MAX - 1)
		{
			// アイドルモーションに
			m_MotionState = MOTION_STATE_IDLE;

			// falseに
			m_bRot = false;
		}
	}
	// 弾発射攻撃
	if (m_MotionState == MOTION_STATE_SHARK_BULLET)
	{
		// falseに
		m_bRot = true;

		// モーション設定
		SetMotion(m_MotionState);

		// 位置取得
		D3DXVECTOR3 pos = GetPos();

		// モーション取得
		CMotion *pMotion = GetMotion();

		// キー取得
		int nKey = pMotion->GetKey();

		// フレーム取得
		int nFrame = pMotion->GetCountMotion();

		// キーとカウントが最大になったら
		if (nKey == BULLET_KEY && nFrame == BULLET_FRAME)
		{
			// 弾発射攻撃
			SharkBulletAttack();
		}
		// キーとカウントが最大になったら
		if (nKey == BULLET_KEY_MAX && nFrame >= BULLET_FRAME_MAX - 1)
		{
			// アイドルモーションに
			m_MotionState = MOTION_STATE_IDLE;

			// falseに
			m_bRot = false;
		}
	}
}
//=============================================================================
// 向き更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::UpdateRot(void)
{
	// プレイヤー取得
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// falseの場合
		if (m_bRot == false)
		{
			// プレイヤーの位置取得
			D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

			// 位置取得
			D3DXVECTOR3 pos = GetPos();

			// 向き取得
			D3DXVECTOR3 rot = GetRot();
			// 角度
			float fRot = atan2f((PlayerPos.x - pos.x), (PlayerPos.z - pos.z));

			// 目的の角度
			D3DXVECTOR3 rotDest = ZeroVector3;

			// 目的の角度
			rotDest.y = fRot;

			// 角度補間
			while (rotDest.y - rot.y > ANGLE_180)
			{
				rotDest.y -= ANGLE_360;
			}
			while (rotDest.y - rot.y < -ANGLE_180)
			{
				rotDest.y += ANGLE_360;
			}

			// 旋回
			rot += (rotDest - rot)*ROT_SPEED;

			// 向き設定
			SetRot(rot);
		}
	}
}
//=============================================================================
// 敵生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::Enemy_Create(void)
{
	// ライフ取得
	int nLife = GetLife();

	// ライフ半分以下の場合
	if (nLife <= MAX_LIFE / DIVIDE_2)
	{
		// ゲームのポインタ取得
		CGame *pGame = (CGame*)CManager::GetModePtr();

		// 敵生成
		pGame->Boss_Enemy_Create();

		// trueの場合
		m_bEnemyCreate = true;
	}
}
