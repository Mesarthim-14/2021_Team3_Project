//=============================================================================
//
// エネミークラス [enemy.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "player.h"
#include "game.h"
#include "fade.h"
#include "resource_manager.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define MIN_LIFE	(0)									// ライフの最小
#define FAN_LENGTH	(5000.0f)							// 扇の長さ
#define FAN_DIR		(D3DXVECTOR3(1.0f, 0.0f, 0.0f))		// 弧線方向
#define ANGLE_90	(D3DXToRadian(90.0f))				// 90度
#define ANGLE_270	(D3DXToRadian(270.0f))				// 270度
#define ANGLE_0		(D3DXToRadian(0.0f))				// 0度
#define ANGLE_360	(D3DXToRadian(360.0f))				// 360度
#define FAN_COS		(cosf(D3DXToRadian(180.0f / 2.0f)))	// cosfに
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy::CEnemy(PRIORITY Priority) : CCharacter(Priority)
{
	m_Attack_Decision_Type	= ATTACK_DECISION_FAN;
	m_bAttack_Decision		= false;
	m_AttackCount = 0;
}

//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// オブジェクト生成
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// メモリ確保
	CEnemy *pEnemy = new CEnemy;

	// 初期化処理
	pEnemy->Init(pos, rot);

	return pEnemy;
}

//=============================================================================
// 初期化処理
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CCharacter::Init(pos, rot);			// 座標、角度

	return S_OK;
}

//=============================================================================
// 終了処理
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::Uninit(void)
{
	// 終了処理
	CCharacter::Uninit();
}

//=============================================================================
// 更新処理
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::Update(void)
{
	// 更新処理
	CCharacter::Update();

	// 攻撃判定処理が扇の場合
	if (m_Attack_Decision_Type == ATTACK_DECISION_FAN)
	{
		// 扇の攻撃判定
		FanDecision();
	}
	// 攻撃判定処理が扇の場合
	if (m_Attack_Decision_Type == ATTACK_DECISION_CIRCLE)
	{
		// 扇の攻撃判定
		CircleDecision();
	}

	// 体力の設定
	if (GetLife() <= MIN_LIFE)
	{
		// 状態設定
		SetState(CCharacter::STATE_DEAD);
	}

	// 状態処理
	UpdateState();
}

//=============================================================================
// 描画処理
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::Draw(void)
{
	// 描画処理
	CCharacter::Draw();
}

//=============================================================================
// エネミーの状態
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::UpdateState(void)
{
	// 状態取得
	int nState = GetState();

	// 死亡状態
	if (nState == STATE_DEAD)
	{
		// 死亡
		Death();
	}
}
//=============================================================================
// 扇形の判定処理
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::FanDecision(void)
{
	// プレイヤーのポインタ取得
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// 位置取得
	D3DXVECTOR3 Pos = GetPos();

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// プレイヤーの位置座標取得
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

		// ベクトル
		D3DXVECTOR3 Vec = ZeroVector3;

		// 点と扇のベクトル
		Vec.x = PlayerPos.x - Pos.x;
		Vec.z = PlayerPos.z - Pos.z;

		// 長さ算出
		float fVec_Length = sqrtf((Vec.x * Vec.x) + (Vec.z * Vec.z));

		// 長さの比較
		if (fVec_Length > FAN_LENGTH)
		{
			// 攻撃判定をtrueに
			m_bAttack_Decision = false;
			// 処理の終了
			return;
		}

		// 向き取得
		D3DXVECTOR3 Rot = GetRot();

		// 向き
		float fRot = ZERO_FLOAT;

		// 前を向いてるか後ろを向いてるか
		if (Rot.y > ANGLE_90 && Rot.y < ANGLE_270 || Rot.y < ANGLE_90 && Rot.y > -ANGLE_90)
		{
			// 向き
 			fRot = Rot.y - ANGLE_90;
		}
		//右を向いてるか左を向いてるか
		if (Rot.y > ANGLE_0 && Rot.y < ANGLE_360 || Rot.y < ANGLE_0 && Rot.y > -ANGLE_0)
		{
			// 向き
			fRot = Rot.y + ANGLE_90;
		}

		// 回転
		D3DXVECTOR3 Rotate_ArcDir = ZeroVector3;

		// ベクトルを回転させる
		Rotate_ArcDir.x = FAN_DIR.x * cosf(fRot) + FAN_DIR.z * -sinf(fRot);
		Rotate_ArcDir.z = FAN_DIR.x * sinf(fRot) + FAN_DIR.z * cosf(fRot);

		// 単位ベクトル
		D3DXVECTOR3 Normal_Vec = ZeroVector3;

		// 単位ベクトルにする
		Normal_Vec.x = Vec.x / fVec_Length;
		Normal_Vec.z = Vec.z / fVec_Length;

		// 内積計算
		float fdot = Normal_Vec.x * Rotate_ArcDir.x + Normal_Vec.z * Rotate_ArcDir.z;

		// 扇の範囲をcosにする
		float fcos = FAN_COS;

		// 点が扇の範囲内にあるかを比較する
		if (fcos > fdot)
		{
			// 攻撃判定をtrueに
			m_bAttack_Decision = false;
		}
		// 点が扇の範囲内にあるかを比較する
		if (fcos < fdot)
		{
			// 攻撃判定をtrueに
			m_bAttack_Decision = true;
		}
	}
}
//=============================================================================
// 円形の判定処理
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::CircleDecision(void)
{
	// プレイヤーのポインタ取得
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// 位置取得
	D3DXVECTOR3 Pos = GetPos();

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// 位置取得
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

		// 円の判定
		if (CCollision::CollisionCircularAndCircular(Pos, PlayerPos, FAN_LENGTH, ZERO_FLOAT) == true)
		{
			// 攻撃判定がfalseの場合
			if (m_bAttack_Decision == false)
			{
				// 攻撃判定をtrueに
				m_bAttack_Decision = true;
			}
		}
		else
		{
			// 攻撃判定がtrueの場合
			if (m_bAttack_Decision == true)
			{
				// 攻撃判定をfalseに
				m_bAttack_Decision = false;
			}
		}
	}
}

//=============================================================================
// 死んだときの処理
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::Death(void)
{
}

//=============================================================================
// 攻撃の処理
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::Attack(void)
{
	m_AttackCount++;
}

//=============================================================================
// 移動の処理
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::Move(void)
{
}
