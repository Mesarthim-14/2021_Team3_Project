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
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define RESULT_BG_POS						(HALF_SCREEN_POS)
#define RESULT_BG_SIZE						(SCREEN_SIZE)

//=============================================================================
// コンストラクタ
//=============================================================================
CResult::CResult()
{
	m_pObject2D.clear();
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
	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	for (auto apObject : m_pObject2D)
	{
		// 終了処理
		apObject->Uninit();
	}
	m_pObject2D.clear();
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

//=============================================================================
// 2Dオブジェクト生成
//=============================================================================
void CResult::Create2DObject(void)
{
	// テクスチャのポイン取得
	CTexture *pTexture = GET_TEXTURE_PTR;

	// メモリ確保
	CScene2D *pResultLogo = CScene2D::Create(RESULT_BG_POS, RESULT_BG_SIZE);
	pResultLogo->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_RESULT_BG));

	// オブジェクト追加
	m_pObject2D.push_back(pResultLogo);
}
