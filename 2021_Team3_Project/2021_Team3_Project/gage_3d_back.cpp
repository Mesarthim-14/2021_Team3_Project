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
#include "gage_3d_back.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define POS		(D3DXVECTOR3(pos.x,pos.y + size.y,pos.z))		// 位置
#define COL		(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))				// 色
#define SIZE	(D3DXVECTOR3(810.0f,40.0f,0.0f))				// 背景サイズ
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CGage_3D_Back::CGage_3D_Back(PRIORITY Priority) : CBillboard(Priority)
{
	m_pEnemy = nullptr;
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CGage_3D_Back::~CGage_3D_Back()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CGage_3D_Back * CGage_3D_Back::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy *pEnemy)
{
	// CGage_3D_Backのポインタ
	CGage_3D_Back *pGage_3D_Back = nullptr;

	// nullcheck
	if (pGage_3D_Back == nullptr)
	{
		// メモリ確保
		pGage_3D_Back = new CGage_3D_Back;

		// !nullcheck
		if (pGage_3D_Back != nullptr)
		{
			// 代入
			pGage_3D_Back->m_pEnemy = pEnemy;

			// 初期化処理
			pGage_3D_Back->Init(pos, SIZE);
		}
	}
	// ポインタを返す
	return pGage_3D_Back;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CGage_3D_Back::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CBillboard::Init(pos, size);

	// 向き設定
	SetRot(ZeroVector3);

	// 色設定
	SetColor(COL);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_3D_Back::Uninit(void)
{
	// !nullcheck
	if (m_pEnemy != nullptr)
	{
		// nullptrに
		m_pEnemy = nullptr;
	}

	// 終了処理
	CBillboard::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_3D_Back::Update(void)
{
	// 更新処理
	CBillboard::Update();

	// 位置取得
	D3DXVECTOR3 pos = m_pEnemy->GetPos();

	// サイズ取得
	D3DXVECTOR3 size = m_pEnemy->GetSize();

	// 位置設定
	SetPos(POS);

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
void CGage_3D_Back::Draw(void)
{
	// 描画処理
	CBillboard::Draw();
}