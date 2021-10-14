//=============================================================================
//
// フェード処理 [fade.cpp]
// Author : konishi Yuuto
//
//=============================================================================
#include "fade.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FADE_RATE (0.02f)	// α値変動係数

//=============================================================================
// コンストラクタ
//=============================================================================
CFade::CFade()
{
	m_pPolygon = nullptr;
	m_FadeMode = FADE_MODE_NONE;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_modeNext = CManager::MODE_TYPE_TITLE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CFade::Init(void)
{
	m_FadeMode = FADE_MODE_OUT;

	if (!m_pPolygon)
	{
		//ポリゴンクラスを生成
		m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

		if (m_pPolygon)
		{
			//色を設定
			m_pPolygon->SetColor(m_colorFade);
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CFade::Uninit(void)
{
	if (m_pPolygon != nullptr)
	{
		//ポリゴンクラスの終了処理呼び出し
		m_pPolygon->Uninit();

		//メモリの破棄
		delete m_pPolygon;

		//メモリのクリア
		m_pPolygon = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CFade::Update(void)
{
	if (m_pPolygon != nullptr)
	{
		if (m_FadeMode != FADE_MODE_NONE)
		{
			//フェードイン処理
			if (m_FadeMode == FADE_MODE_IN)
			{
				//α値の減算
				m_colorFade.a -= FADE_RATE;

				//α値が0.0fより小さくなったらフェード更新終了
				if (m_colorFade.a <= 0.0f)
				{
					m_colorFade.a = 0.0f;
					m_FadeMode = FADE_MODE_NONE;
				}
			}

			//フェードアウト処理
			else if (m_FadeMode == FADE_MODE_OUT)
			{
				//α値の加算
				m_colorFade.a += FADE_RATE;

				//α値が1.0fより大きくなったらフェードインへ移行
				if (m_colorFade.a >= 1.0f)
				{
					m_colorFade.a = 1.0f;
					m_FadeMode = FADE_MODE_IN;

					CManager::SetMode(m_modeNext);
				}
			}

			//透明度の設定
			m_pPolygon->SetColor(m_colorFade);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CFade::Draw(void)
{
	if (m_pPolygon != nullptr)
	{
		if (m_FadeMode != FADE_MODE_NONE)
		{
			// ポリゴンクラスの描画処理呼び出し
			m_pPolygon->Draw();
		}
	}
}

//=============================================================================
// フェード呼び出し
//=============================================================================
void CFade::SetFade(CManager::MODE_TYPE mode)
{
	m_FadeMode = FADE_MODE_OUT;
	m_modeNext = mode;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//黒い画面（透過）
}

//=============================================================================
// フェード情報
//=============================================================================
CFade::FADE_MODE CFade::GetFade(void)
{
	return m_FadeMode;
}