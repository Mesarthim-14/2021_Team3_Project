//=======================================================================================
//
// チュートリアルクラス [tutorial.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "tutorial.h"
#include "scene2d.h"
#include "manager.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"

//=======================================================================================
// コンストラクタ
//=======================================================================================
CTutorial::CTutorial()
{
	m_pScene = nullptr;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CTutorial::~CTutorial()
{
	// 終了処理
	Uninit();
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CTutorial::Init(void)
{
	// nullcheck
	if (m_pScene == nullptr)
	{
		// インスタンス生成
		m_pScene = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}
	
	// サウンドのポインタ
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
	//pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CTutorial::Uninit(void)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		m_pScene = nullptr;
	}
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CTutorial::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	// コントローラのstartを押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}

	//エンターキーを押したとき
	if (pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}

}

//=======================================================================================
// 描画処理
//=======================================================================================
void CTutorial::Draw(void)
{

}
