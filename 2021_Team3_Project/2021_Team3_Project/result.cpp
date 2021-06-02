//=============================================================================
//
// リザルトクラス処理 [result.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"
#include "joypad.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CResult::CResult()
{
	m_pScene2D = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{
	// 終了処理
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult::Init(void)
{
	//2Dオブジェクトの生成
	m_pScene2D = CScene2D::Create(
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	// !nullcheck
	if (m_pScene2D != nullptr)
	{
		// 終了処理
		m_pScene2D->Uninit();
		m_pScene2D = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CResult::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	// コントローラのstartを押したときか、エンターキーを押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_TITLE);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{
}
