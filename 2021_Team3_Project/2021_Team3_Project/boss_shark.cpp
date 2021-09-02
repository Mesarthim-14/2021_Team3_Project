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
#include "boss_shark.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define MAX_LIFE		(100)									// 体力
#define MOVE_VALUE		(10.0f)									// 移動量
#define ROT_SPEED		(0.01f)									// 旋回速度
#define ANGLE_180		(180)									// 180度
#define ANGLE_360		(360)									// 360度
#define SIZE			(D3DXVECTOR3 (700.0f,900.0f,700.0f))	// サイズ
#define ATTACK_COUNT	(300)									// 攻撃間隔

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Shark::CBoss_Shark(PRIORITY Priority) : CEnemy(Priority)
{
	m_nAttackCount = ZERO_INT;
	m_MotionState = MOTION_STATE_IDLE;
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

			// ボックス生成
			CCharacter_Box::Create(pos, rot, pBoss_Shark);
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

	// 攻撃処理
	Attack();
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

	// カウントが300以上の場合
	if (m_nAttackCount >= ATTACK_COUNT)
	{
		// 噛みつき攻撃
		ByteAttack();

		// 0に
		m_nAttackCount = ZERO_INT;
	}
}
//=============================================================================
// 噛みつき攻撃処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::ByteAttack(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 噛みつきモーション
	m_MotionState = MOTION_STATE_BYTE;

	// 噛みつきエフェクト
	CByte_Effect::CrateEffect(pos, SIZE);
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
		SetMotion(MOTION_STATE_IDLE);
	}
	if (m_MotionState == MOTION_STATE_BYTE)
	{
		// モーション設定
		SetMotion(MOTION_STATE_BYTE);
	}
}
