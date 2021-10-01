//=============================================================================
// 攻撃操作UIクラス [atack_ui.cpp]
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
#include "attack_ui.h"
#include "player.h"
#include "modelanime.h"
#include "mode_base.h"

//=============================================================================
// マクロ定義
// Author : Konishi Yuuto
//=============================================================================
#define SIZE		(D3DXVECTOR3(200.0f, 200.0f,0.0f))		// サイズ
#define ADD_POS_Y	(930.0f)								// 車輪の上に表示

//=============================================================================
// コンストラクタ
// Author : Konishi Yuuto
//=============================================================================
CAttackUi::CAttackUi(PRIORITY Priority) : CControlUi(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Konishi Yuuto
//=============================================================================
CAttackUi::~CAttackUi()
{
}

//=============================================================================
// インスタンス生成
// Author : Konishi Yuuto
//=============================================================================
CAttackUi * CAttackUi::Create(CModelAnime *pPtr)
{
	// CAttackUiのポインタ
	CAttackUi *pAttackUi = new CAttackUi;

	// !nullcheck
	if (pAttackUi)
	{
		pAttackUi->SetModelPtr(pPtr);

		// 初期化処理
		pAttackUi->Init(pPtr->GetMtxPos(), SIZE);

		// ポインタを返す
		return pAttackUi;
	}

	return nullptr;
}

//=============================================================================
// 初期化処理関数
// Author : Konishi Yuuto
//=============================================================================
HRESULT CAttackUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CControlUi::Init(pos, size);

	// テクスチャポインタ
	CTexture *pTexture = GET_TEXTURE_PTR;
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_R1));

	// 高さの設定
	SetHeight(ADD_POS_Y);

	return S_OK;
}