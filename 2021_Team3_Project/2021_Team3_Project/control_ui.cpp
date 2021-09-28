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
#include "control_ui.h"
#include "player.h"
#include "modelanime.h"
#include "mode_base.h"

//=============================================================================
// マクロ定義
// Author : Konishi Yuuto
//=============================================================================
#define END_TIME	(240)									// 終了の時間

//=============================================================================
// コンストラクタ
// Author : Konishi Yuuto
//=============================================================================
CControlUi::CControlUi(PRIORITY Priority) : CBillboard(Priority)
{
	m_pModelPtr = nullptr;
	m_nCounter = 0;
	m_fHeight = 0.0f;
}

//=============================================================================
// デストラクタ
// Author : Konishi Yuuto
//=============================================================================
CControlUi::~CControlUi()
{
}

//=============================================================================
// 初期化処理関数
// Author : Konishi Yuuto
//=============================================================================
HRESULT CControlUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CBillboard::Init(pos, size);

	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Konishi Yuuto
//=============================================================================
void CControlUi::Uninit(void)
{
	// 終了処理
	CBillboard::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Konishi Yuuto
//=============================================================================
void CControlUi::Update(void)
{
	m_nCounter++;

	// 車輪の上に設定
	D3DXVECTOR3 pos = m_pModelPtr->GetMtxPos();
	pos.y = pos.y + m_fHeight;
	SetPos(pos);

	// 更新処理
	CBillboard::Update();

	// 一定時間で
	if (m_nCounter >= END_TIME)
	{
		// 終了処理
		Uninit();

		return;
	}
}

//=============================================================================
// 描画処理関数
// Author : Konishi Yuuto
//=============================================================================
void CControlUi::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

	// かぶさらないようにする　(Zバッファ)
	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	// 描画処理
	CBillboard::Draw();

	// かぶさらないようにする　(Zバッファ)
	pDevice->SetRenderState(D3DRS_ZENABLE, true);
}