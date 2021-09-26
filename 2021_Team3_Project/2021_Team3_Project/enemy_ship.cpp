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
#include "enemy_bullet.h"
#include "character_box.h"
#include "collision.h"
#include "map.h"
#include "enemy_ship.h"
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
#define SHIP_NUM		(0)										// 船のナンバー
#define RAY_NUM			(1)										// レイの数
#define RAY_HIT_RANGE	(600.0f)								// 範囲
#define RAY_ANGLE		(D3DXToRadian(360.0f / 4.0f))			// 角度
// 船体の位置
#define SHIP_POS		(D3DXVECTOR3(pShip->GetMtxWorld()._41, pShip->GetMtxWorld()._42, pShip->GetMtxWorld()._43))
// 砲台の位置
#define BATTERY_POS		(D3DXVECTOR3(pBattery->GetMtxWorld()._41, pBattery->GetMtxWorld()._42, pBattery->GetMtxWorld()._43))
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Ship::CEnemy_Ship(PRIORITY Priority) : CEnemy(Priority)
{
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Ship::~CEnemy_Ship()
{
}
//=============================================================================
// 生成関数
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Ship * CEnemy_Ship::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CEnemy_Shipポインタ
	CEnemy_Ship *pEnemy_Ship = nullptr;

	// nullcheck
	if (pEnemy_Ship == nullptr)
	{
		// メモリ確保
		pEnemy_Ship = new CEnemy_Ship;

		// !nullcheck
		if (pEnemy_Ship != nullptr)
		{
			// 初期化処理
			pEnemy_Ship->Init(pos, rot);

			// ボックス生成
			//CCharacter_Box::Create(pos, rot, pEnemy_Ship);
		}
	}
	// ポインタを返す
	return pEnemy_Ship;
}
//=============================================================================
// 初期化関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CEnemy_Ship::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデルの情報を渡す
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_ENEMY_SHIP);
	}

	// 体力設定
	SetLife(MAX_LIFE);

	// サイズ設定
	SetSize(SIZE);

	// 攻撃判定設定
	SetAttackDecision(ATTACK_DECISION_CIRCLE);

	// 初期化関数
	CEnemy::Init(pos, rot);

	// レイの情報
	CCharacter::RAY_DATA Ray_Data = { RAY_ANGLE, RAY_HIT_RANGE, RAY_NUM };

	// レイの情報設定
	SetRay_Data(Ray_Data);
	return S_OK;
}
//=============================================================================
// 終了関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Ship::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}
//=============================================================================
// 更新関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Ship::Update(void)
{
	// 更新処理
	CEnemy::Update();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 状態取得
	int nState = GetState();

	// 古い座標保存
	SetPosOld(pos);	

	// 攻撃判定取得
	bool bAttack = Get_bAttackDecision();

	// 攻撃判定がtrueの場合
	if (bAttack == true)
	{
		// 攻撃処理
		Attack();

		// 移動処理
		Move();
	}

	// 死亡状態
	if (nState == STATE_DEAD)
	{
		// 終了
		Uninit();

		return;
	}

	// レイの当たり判定
	RayCollision();
}
//=============================================================================
// 描画関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Ship::Draw(void)
{
	// 描画関数
	CEnemy::Draw();
}
//=============================================================================
// 移動処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Ship::Move(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	// CGameのポインタ
	CGame *pGame = nullptr;

	// nullcheck
	if (pGame == nullptr)
	{
		// CGameの情報取得
		pGame = (CGame*)CManager::GetModePtr();

		// !nullcheck
		if (pGame != nullptr)
		{
			// CPlayerのポインタ
			CPlayer *pPlayer = nullptr;

			// nullcheck
			if (pPlayer == nullptr)
			{
				// プレイヤーの情報取得
				pPlayer = pGame->GetPlayer();

				// !nullcheck
				if (pPlayer != nullptr)
				{
					// プレイヤーの位置を取得
					D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

					// 角度算出
					float fAngle = atan2f(PlayerPos.x - pos.x, PlayerPos.z - pos.z);

					// 目的の角度
					D3DXVECTOR3 rotDest = ZeroVector3;

					// 目的の角度
					rotDest.y = fAngle;

					// 目的の角度
					rotDest.y += D3DXToRadian(ANGLE_180);

					while (rotDest.y - rot.y > D3DXToRadian(ANGLE_180))
					{
						rotDest.y -= D3DXToRadian(ANGLE_360);
					}
					while (rotDest.y - rot.y < D3DXToRadian(-ANGLE_180))
					{
						rotDest.y += D3DXToRadian(ANGLE_360);
					}

					// 旋回
					rot += (rotDest - rot)*ROT_SPEED;

					// 移動
					D3DXVECTOR3 move = ZeroVector3;

					// 移動量加算（求めた角度をもとに移動する）
					move.x = sinf(fAngle)*MOVE_VALUE;
					move.z = cosf(fAngle)*MOVE_VALUE;

					// 位置設定
					SetMove(move);

					// 向き設定
					SetRot(rot);
				}
			}
		}
	}
}
//=============================================================================
// 攻撃処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Ship::Attack(void)
{
	// アタック処理
	CEnemy::Attack();

	// カウントが60以上になった場合
	if (GetAttackCount() >= ATTACK_COUNT)
	{
		// 砲台のポインタ取得
		CModelAnime *pBattery = GetModelAnime(PARTS_BATTERY);

		// 弾生成
		CEnemy_Bullet::Create(BATTERY_POS, ZeroVector3);

		// 0に
		GetAttackCount() = ZERO_INT;
	}
}
//=============================================================================
// レイの当たり判定処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Ship::RayCollision(void)
{
	//// モデルの情報取得
	//CModelAnime *pShip = GetModelAnime(SHIP_NUM);

	//// 位置取得
	//D3DXVECTOR3 pos = SHIP_POS;

	//// 向き取得
	//D3DXVECTOR3 rot = GetRot();

	//// マップのポインタ取得
	//CMap *pMap = GET_MAP_PTR;

	//// !nullcheck
	//if (pShip != nullptr)
	//{
	//	// !nullcheck
	//	if (pMap != nullptr)
	//	{
	//		// レイの情報
	//		CCollision::RAY_INFO Ray_Info;

	//		// レイの当たり判定
	//		Ray_Info = CCollision::RayCollision(pos, GET_MAP_PTR, rot.y, RAY_HIT_RANGE, RAY_NUM);

	//		// trueの場合
	//		if (Ray_Info.bHit == true)
	//		{
	//			// 戻す
	//			pos -= (D3DXVECTOR3(sinf(Ray_Info.VecDirection.y), ZERO_FLOAT, cosf(Ray_Info.VecDirection.y)));

	//			// 位置設定
	//			SetPos(pos);

	//			return;
	//		}
	//	}
	//}
}