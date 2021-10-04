//=============================================================================
//
// リザルトクラス処理 [result.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "result_clear.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"
#include "joypad.h"
#include "resource_manager.h"
#include "texture.h"
#include "result_story.h"
#include "sound.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CResultClear::CResultClear()
{
	m_pObject2D = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CResultClear::~CResultClear()
{
	// 終了処理
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResultClear::Init(void)
{
	// オブジェクト生成
	Create2DObject();

	CSound *pSound = GET_SOUND_PTR;
	pSound->Play(CSound::SOUND_BGM_RESULT_CLEAR);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CResultClear::Uninit(void)
{
	if (m_pObject2D)
	{
		m_pObject2D->Uninit();
		m_pObject2D = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CResultClear::Update(void)
{
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	if (m_pObject2D)
	{
		if (m_pObject2D->GetEnd())
		{
			// コントローラのstartを押したときか、エンターキーを押したとき
			if (mode == CFade::FADE_MODE_NONE)
			{
				CFade *pFade = CManager::GetFade();
				pFade->SetFade(CManager::MODE_TYPE_TITLE);
			}
		}
		else
		{
			CInputKeyboard* pKey = CManager::GetKeyboard();

			// コントローラのstartを押したときか、エンターキーを押したとき
			if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
				|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
			{
				CFade *pFade = CManager::GetFade();
				pFade->SetFade(CManager::MODE_TYPE_TITLE);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CResultClear::Draw(void)
{
}

//=============================================================================
// 2Dオブジェクト生成
//=============================================================================
void CResultClear::Create2DObject(void)
{
	// テクスチャのポイン取得
	CTexture *pTexture = GET_TEXTURE_PTR;

	// 背景
	CScene2D *pScene2D = CScene2D::Create(HALF_SCREEN_POS, SCREEN_SIZE);
	pScene2D->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_RESULT_STORY_BACK));

	// メモリ確保
	m_pObject2D = CResultStory::Create();
	m_pObject2D->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_RESULT_STORY));
}