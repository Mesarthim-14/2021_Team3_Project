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
#define FADE_RATE	(0.01f)												// α値変動係数
#define POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,0.0f))	// 位置
#define SIZE		(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT,0.0f))			// サイズ
#define COL			(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f))						// 色
#define αMIN		(0.0f)													// α値の最小
#define αMAX		(1.0f)													// α値の最大
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Fade::CBoss_Fade(PRIORITY Priority) : CScene2D(Priority)
{
	m_FadeMode	= FADE_MODE_NONE;
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
	m_FadeMode = FADE_MODE_IN;

	CScene2D::Init(POS, SIZE);

	// 色設定
	SetCol(COL);

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
	CGame *pGame = (CGame*)CManager::GetModePtr();

	// 色取得
	D3DXCOLOR col = GetColor();

	if (m_FadeMode != FADE_MODE_NONE)
	{
		//フェードイン処理
		if (m_FadeMode == FADE_MODE_OUT)
		{
			//α値の減算
			col.a -= FADE_RATE;

			//α値が0.0fより小さくなったらフェード更新終了
			if (col.a <= αMIN)
			{
				// 0.0fに
				col.a = αMIN;

				// ボス戦の判定設定
				pGame->SetbBossTransition(false);

				// ボス戦の判定設定
				pGame->SetbBoss(true);

				// 終了
				Uninit();

				return;
			}
		}

		//フェードアウト処理
		else if (m_FadeMode == FADE_MODE_IN)
		{
			//α値の加算
			col.a += FADE_RATE;

			//α値が1.0fより大きくなったらフェードインへ移行
			if (col.a >= αMAX)
			{
				// ボス戦の判定設定
				pGame->CreateBossMap();

				// 1.0fに
				col.a = αMAX;

				// OUTに
				m_FadeMode = FADE_MODE_OUT;
			}
		}
		// 透明度の設定
		SetCol(col);
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