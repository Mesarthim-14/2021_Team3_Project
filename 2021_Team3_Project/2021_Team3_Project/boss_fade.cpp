//=============================================================================
// ボスフェード処理 [boss_fade.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "boss_fade.h"

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define FADE_RATE (0.02f)	// α値変動係数

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Fade::CBoss_Fade(PRIORITY Priority = PRIORITY_FADE)
{
	m_FadeMode	= FADE_MODE_NONE;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
}

//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Fade::~CBoss_Fade()
{
}
//=============================================================================
// 初期化処理
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Fade * CBoss_Fade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CBoss_Fadeのポインタ
	CBoss_Fade *pBoss_Fade = nullptr;

	// nullcheck
	if (pBoss_Fade == nullptr)
	{
		// メモリ確保
		pBoss_Fade = new CBoss_Fade;

		// !nullcheck
		if (pBoss_Fade != nullptr)
		{
			// 初期化処理
			pBoss_Fade->Init(pos, size);
		}
	}
	// ポインタを返す
	return pBoss_Fade;
}

//=============================================================================
// 初期化処理
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBoss_Fade::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// フェードアウト状態
	m_FadeMode = FADE_MODE_OUT;

	CScene2D::Init(pos, size);
	return S_OK;
}

//=============================================================================
// 終了処理
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Fade::Uninit(void)
{
	// 終了処理
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Fade::Update(void)
{
	// 更新処理
	CScene2D::Update();

	// ゲーム取得
	CGame *pGame = CManager::GetGame();

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

				// falseに
				pGame->SetbBoss(false);

				// 終了
				Uninit();

				return;
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

				// ボス戦か取得
				bool bBoss = pGame->GetbBoss();

				// trueの場合
				if (bBoss == true)
				{
					m_FadeMode = FADE_MODE_IN;
				}
			}
		}

		//透明度の設定
		SetColor(m_colorFade);
	}
}

//=============================================================================
// 描画処理
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Fade::Draw(void)
{
	// 描画処理
	CScene2D::Draw();
}