//=============================================================================
// ライフゲージの背景 [gage_3d_back.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "boss_life_back.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COL		(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))// 色
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Life_Back::CBoss_Life_Back(PRIORITY Priority) : CScene2D(Priority)
{
	m_pEnemy = nullptr;
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Life_Back::~CBoss_Life_Back()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Life_Back * CBoss_Life_Back::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy *pEnemy)
{
	// CBoss_Life_Backのポインタ
	CBoss_Life_Back *pBoss_Life_Back = nullptr;

	// nullcheck
	if (pBoss_Life_Back == nullptr)
	{
		// メモリ確保
		pBoss_Life_Back = new CBoss_Life_Back;

		// !nullcheck
		if (pBoss_Life_Back != nullptr)
		{
			// 代入
			pBoss_Life_Back->m_pEnemy = pEnemy;

			// 初期化処理
			pBoss_Life_Back->Init(pos, size);
		}
	}
	// ポインタを返す
	return pBoss_Life_Back;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBoss_Life_Back::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CScene2D::Init(pos, size);

	// 色設定
	SetCol(COL);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Life_Back::Uninit(void)
{
	// !nullcheck
	if (m_pEnemy != nullptr)
	{
		// nullptrに
		m_pEnemy = nullptr;
	}

	// 終了処理
	CScene2D::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Life_Back::Update(void)
{
	// 更新処理
	CScene2D::Update();

	// 死亡状態の場合
	if (m_pEnemy->GetState() == CEnemy::STATE_DEAD)
	{
		// 終了
		Uninit();

		return;
	}
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Life_Back::Draw(void)
{
	// 描画処理
	CScene2D::Draw();
}