//=============================================================================
// 通常敵の弾 [enemy_normal_bullet.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "character.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "enemy_normal_bullet.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Normal_Bullet::CEnemy_Normal_Bullet(PRIORITY Priority) : CEnemy_Bullet(Priority)
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Normal_Bullet::~CEnemy_Normal_Bullet()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Normal_Bullet * CEnemy_Normal_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CEnemy_Normal_Bulletのポインタ
	CEnemy_Normal_Bullet *pEnemy_Noraml_Bullet = nullptr;

	// nullcheck
	if (pEnemy_Noraml_Bullet == nullptr)
	{
		// メモリ確保
		pEnemy_Noraml_Bullet = new CEnemy_Normal_Bullet;

		// !nullcheck
		if (pEnemy_Noraml_Bullet != nullptr)
		{
			// 初期化処理
			pEnemy_Noraml_Bullet->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pEnemy_Noraml_Bullet;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CEnemy_Normal_Bullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// XFile名設定
	SetXFileNum(CXfile::XFILE_NUM_BULLET);

	// プレイヤーのポインタ取得
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// 位置座標取得
		SetTargetPos(pPlayer->GetPos());
	}

	// 初期化処理
	CEnemy_Bullet::Init(pos, rot);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Normal_Bullet::Uninit(void)
{
	// 終了処理
	CEnemy_Bullet::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Normal_Bullet::Update(void)
{
	// 更新処理
	CEnemy_Bullet::Update();

	// 移動処理
	Projectile_motion();

	// 当たり判定
	Collision();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Normal_Bullet::Draw(void)
{
	// 描画処理
	CEnemy_Bullet::Draw();
}