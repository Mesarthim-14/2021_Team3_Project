//=============================================================================
//
// エネミークラス [enemy.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
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
// コンストラクタ
//=============================================================================
CEnemy::CEnemy(PRIORITY Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// オブジェクト生成
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
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CCharacter::Init(pos, rot);			// 座標、角度

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	// 終了処理
	CCharacter::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update(void)
{
	// 更新処理
	CCharacter::Update();

	// モーション状態
	UpdateMotionState();

	// 体力の設定
	if (GetLife() <= 0)
	{
		// 死亡時の処理
		Death();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	// 描画処理
	CCharacter::Draw();
}

//=============================================================================
// エネミーの状態
//=============================================================================
void CEnemy::UpdateState(void)
{
}

//=============================================================================
// 死んだときの処理
//=============================================================================
void CEnemy::Death(void)
{
	// 終了処理
	Uninit();
}

//=============================================================================
// 攻撃の処理
//=============================================================================
void CEnemy::Attack(void)
{
}

//=============================================================================
// 移動の処理
//=============================================================================
void CEnemy::Move(void)
{
}

//=============================================================================
// モーション状態の更新
//=============================================================================
void CEnemy::UpdateMotionState(void)
{
}