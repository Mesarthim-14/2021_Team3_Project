//=============================================================================
// 移動の操作UIクラス [rotate_ui.cpp]
// Author : Konishi Yuuto
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Konishi Yuuto
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "rotate_ui.h"
#include "player.h"
#include "modelanime.h"
#include "mode_base.h"

//=============================================================================
// マクロ定義
// Author : Konishi Yuuto
//=============================================================================
#define SIZE		(D3DXVECTOR3(300.0f, 300.0f,0.0f))		// サイズ
#define ADD_POS_Y	(500.0f)								// 車輪の上に表示

//=============================================================================
// コンストラクタ
// Author : Konishi Yuuto
//=============================================================================
CRotateUi::CRotateUi(PRIORITY Priority) : CControlUi(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Konishi Yuuto
//=============================================================================
CRotateUi::~CRotateUi()
{
}

//=============================================================================
// インスタンス生成
// Author : Konishi Yuuto
//=============================================================================
CRotateUi * CRotateUi::Create(CModelAnime *pPtr)
{
	// CRotateUiのポインタ
	CRotateUi *pRotateUi = new CRotateUi;

	// !nullcheck
	if (pRotateUi)
	{
		pRotateUi->SetModelPtr(pPtr);

		// 初期化処理
		pRotateUi->Init(pPtr->GetMtxPos(), SIZE);

		// ポインタを返す
		return pRotateUi;
	}

	return nullptr;
}

//=============================================================================
// 初期化処理関数
// Author : Konishi Yuuto
//=============================================================================
HRESULT CRotateUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CControlUi::Init(pos, size);

	// テクスチャポインタ
	CTexture *pTexture = GET_TEXTURE_PTR;
	BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_MOVE_UI));

	// アニメーション情報設定
	D3DXVECTOR2 TexInfo = pTexture->GetSparateTexInfo(CTexture::SEPARATE_TEX_MOVE_UI);
	bool bLoop = pTexture->GetSparateTexLoop(CTexture::SEPARATE_TEX_MOVE_UI);
	InitAnimation(TexInfo, bLoop);

	// 高さの設定
	SetHeight(ADD_POS_Y);

	return S_OK;
}