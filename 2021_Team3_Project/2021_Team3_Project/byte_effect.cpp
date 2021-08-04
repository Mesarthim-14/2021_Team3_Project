//=============================================================================
// 噛みつきエフェクト [byte_effect.cpp]
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
#include "byte_effect.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COL	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Effect::CByte_Effect(PRIORITY Priority) : CBillboard(Priority)
{

}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Effect::~CByte_Effect()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Effect * CByte_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CGage_3D_Backのポインタ
	CByte_Effect *pGage_3D_Back = nullptr;

	// nullcheck
	if (pGage_3D_Back == nullptr)
	{
		// メモリ確保
		pGage_3D_Back = new CByte_Effect;

		// !nullcheck
		if (pGage_3D_Back != nullptr)
		{
			// 初期化処理
			pGage_3D_Back->Init(pos, size);
		}
	}
	// ポインタを返す
	return pGage_3D_Back;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CByte_Effect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CBillboard::Init(pos, size);

	// 向き設定
	SetRot(ZeroVector3);

	// 色設定
	SetColor(COL);

	// 透過値設定
	SetAlpha(true);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Effect::Uninit(void)
{

	// 終了処理
	CBillboard::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Effect::Update(void)
{
	// 更新処理
	CBillboard::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Effect::Draw(void)
{
	// 描画処理
	CBillboard::Draw();
}