//=============================================================================
// 敵の櫓 [enemy_ship.cpp]
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
#include "enemy_normal_bullet.h"
#include "enemy_life.h"
#include "enemy_scaffolding.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define MAX_LIFE		(100)									// 体力
#define MOVE_VALUE		(10.0f)									// 移動量
#define ROT_SPEED		(0.01f)									// 旋回速度
#define ANGLE_180		(180)									// 180度
#define ANGLE_360		(360)									// 360度
#define SIZE			(D3DXVECTOR3 (1500.0f,6000.0f,1500.0f))	// サイズ
#define ATTACK_COUNT	(120)									// 攻撃間隔

// 砲台の位置
#define BATTERY_POS		(D3DXVECTOR3(pBattery->GetMtxWorld()._41, pBattery->GetMtxWorld()._42, pBattery->GetMtxWorld()._43))
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Scaffolding::CEnemy_Scaffolding(PRIORITY Priority) : CEnemy(Priority)
{
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Scaffolding::~CEnemy_Scaffolding()
{
}
//=============================================================================
// 生成関数
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Scaffolding * CEnemy_Scaffolding::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CEnemy_Shipポインタ
	CEnemy_Scaffolding *pEnemy_Scaffolding = nullptr;

	// nullcheck
	if (pEnemy_Scaffolding == nullptr)
	{
		// メモリ確保
		pEnemy_Scaffolding = new CEnemy_Scaffolding;

		// !nullcheck
		if (pEnemy_Scaffolding != nullptr)
		{
			// 初期化処理
			pEnemy_Scaffolding->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pEnemy_Scaffolding;
}
//=============================================================================
// 初期化関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CEnemy_Scaffolding::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデルの情報を渡す
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_ENEMY_SCAFFOLDING);
	}

	// 体力設定
	SetLife(MAX_LIFE);

	// サイズ設定
	SetSize(SIZE);

	// 初期化関数
	CEnemy::Init(pos, rot);
	return S_OK;
}
//=============================================================================
// 終了関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Scaffolding::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}
//=============================================================================
// 更新関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Scaffolding::Update(void)
{
	// 更新処理
	CEnemy::Update();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 古い座標保存
	SetPosOld(pos);

	// 攻撃処理
	Attack();

	// 状態取得
	int nState = GetState();

	// 死亡状態
	if (nState == STATE_DEAD)
	{
		// 終了
		Uninit();

		return;
	}
}
//=============================================================================
// 描画関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Scaffolding::Draw(void)
{
	// 描画関数
	CEnemy::Draw();
}
//=============================================================================
// 攻撃処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Scaffolding::Attack(void)
{
	// インクリメント
	CEnemy::Attack();

	// 攻撃判定取得
	bool bAttack = Get_bAttackDecision();

	// 攻撃判定がtrueの場合
	if (bAttack == true)
	{
		// カウントが60以上になった場合
		if (GetAttackCount() >= ATTACK_COUNT)
		{
			// 砲台のポインタ取得
			CModelAnime *pBattery = GetModelAnime(PARTS_BATTERY);

			// 弾生成
			CEnemy_Normal_Bullet::Create(BATTERY_POS, ZeroVector3);

			// 0に
			GetAttackCount() = ZERO_INT;
		}
	}
}