//=============================================================================
//
// タイトルストーリー処理 [title_story.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "title_story.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"
#include "texture.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"
#include "camera.h"
#include "camera_title.h"
#include "light.h"
#include "player.h"
#include "water.h"
#include "title_map.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BG_POS						(HALF_SCREEN_POS)
#define BG_SIZE						(SCREEN_SIZE)
#define SENTENCE_0_POS				(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 160.0f, 0.0f))
#define SENTENCE_0_SIZE				(D3DXVECTOR3(750.0f, 100.0f, 0.0f))
#define SENTENCE_1_POS				(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 280.0f, 0.0f))
#define SENTENCE_1_SIZE				(D3DXVECTOR3(750.0f, 100.0f, 0.0f))
#define SENTENCE_2_POS				(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 400.0f, 0.0f))
#define SENTENCE_2_SIZE				(D3DXVECTOR3(750.0f, 100.0f, 0.0f))
#define SENTENCE_3_POS				(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 530.0f, 0.0f))
#define SENTENCE_3_SIZE				(D3DXVECTOR3(750.0f, 100.0f, 0.0f))

#define CREATE_SENTENCE_INTER		(120)
#define SENTENCE_FADE_OUT_NUM		(0.05f)

//=============================================================================
// static宣言
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CTitleStory::CTitleStory()
{
	m_pObject2D.clear();
	m_nSentenceNum = 0;
	m_nTimeCounter = 0;
	m_bEnd = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitleStory::~CTitleStory()
{
	// 終了処理
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitleStory::Init(void)
{
	// 背景の生成
	CreateBg();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitleStory::Uninit(void)
{
	for (auto &object : m_pObject2D)
	{
		// 終了処理
		object->Uninit();
	}

	// オブジェクト削除
	m_pObject2D.clear();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitleStory::Update(void)
{
	if (!m_bEnd)
	{
		m_nTimeCounter++;

		if (m_nTimeCounter >= CREATE_SENTENCE_INTER)
		{
			// 文章の生成
			(this->*m_CreateSentence.at(m_nSentenceNum))();

			// 生成する関数を進める
			m_nSentenceNum++;
			m_nTimeCounter = 0;
		}

		// 文章のスキップ
		SkipSentence();
	}
	else
	{
		// モード遷移
		ModeTransition();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitleStory::Draw(void)
{

}

//=============================================================================
// モード遷移
//=============================================================================
void CTitleStory::ModeTransition(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	// コントローラのstartを押したときか、エンターキーを押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}
}

//=============================================================================
// 文章スキップ
//=============================================================================
void CTitleStory::SkipSentence(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();

	// ボタンが押されたら
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_B, 0)
		|| pKey->GetTrigger(DIK_B))
	{
		while (!m_bEnd)
		{
			// 文章の生成
			(this->*m_CreateSentence.at(m_nSentenceNum))();

			// 生成する関数を進める
			m_nSentenceNum++;
		}
	}
}

//=============================================================================
// 背景の生成
//=============================================================================
void CTitleStory::CreateBg(void)
{
	// テクスチャのポイン取得
	CTexture *pTexture = GET_TEXTURE_PTR;

	// メモリ確保
	CScene2D *pTitleLogo = CScene2D::Create(BG_POS, BG_SIZE);
	pTitleLogo->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_STORY_BG));

	// オブジェクト追加
	m_pObject2D.push_back(pTitleLogo);
}

//=============================================================================
// 文章の生成
//=============================================================================
void CTitleStory::CreateSentence0(void)
{
	// テクスチャのポイン取得
	CTexture *pTexture = GET_TEXTURE_PTR;

	// メモリ確保
	CScene2D *pTitleLogo = CScene2D::Create(SENTENCE_0_POS, SENTENCE_0_SIZE, SENTENCE_FADE_OUT_NUM);
	pTitleLogo->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_STORY_SENTENCE0));

	// オブジェクト追加
	m_pObject2D.push_back(pTitleLogo);
}

//=============================================================================
// 文章の生成
//=============================================================================
void CTitleStory::CreateSentence1(void)
{
	// テクスチャのポイン取得
	CTexture *pTexture = GET_TEXTURE_PTR;

	// メモリ確保
	CScene2D *pTitleLogo = CScene2D::Create(SENTENCE_1_POS, SENTENCE_1_SIZE, SENTENCE_FADE_OUT_NUM);
	pTitleLogo->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_STORY_SENTENCE1));

	// オブジェクト追加
	m_pObject2D.push_back(pTitleLogo);
}

//=============================================================================
// 文章の生成
//=============================================================================
void CTitleStory::CreateSentence2(void)
{
	// テクスチャのポイン取得
	CTexture *pTexture = GET_TEXTURE_PTR;

	// メモリ確保
	CScene2D *pTitleLogo = CScene2D::Create(SENTENCE_2_POS, SENTENCE_2_SIZE, SENTENCE_FADE_OUT_NUM);
	pTitleLogo->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_STORY_SENTENCE2));

	// オブジェクト追加
	m_pObject2D.push_back(pTitleLogo);
}

//=============================================================================
// 文章の生成
//=============================================================================
void CTitleStory::CreateSentence3(void)
{
	// テクスチャのポイン取得
	CTexture *pTexture = GET_TEXTURE_PTR;

	// メモリ確保
	CScene2D *pTitleLogo = CScene2D::Create(SENTENCE_3_POS, SENTENCE_3_SIZE, SENTENCE_FADE_OUT_NUM);
	pTitleLogo->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_STORY_SENTENCE3));

	// オブジェクト追加
	m_pObject2D.push_back(pTitleLogo);

	m_bEnd = true;
}