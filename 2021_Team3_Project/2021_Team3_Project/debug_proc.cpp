//=============================================================================
// デバッグプロシージャ [debug_proc.cpp]
// Author : SugawaraTsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : SugawaraTsukasa
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "debug_proc.h"
//=============================================================================
// 静的メンバ変数宣言
// Author : SugawaraTsukasa
//=============================================================================
LPD3DXFONT CDebugProc::m_pFont = nullptr;
char CDebugProc::m_astr[1024] = {};

//=============================================================================
// コンストラクタ
// Author : SugawaraTsukasa
//=============================================================================
CDebugProc::CDebugProc()
{
}

//=============================================================================
// デストラクタ
// Author : SugawaraTsukasa
//=============================================================================
CDebugProc::~CDebugProc()
{
}

//=============================================================================
//初期化処理関数
// Author : SugawaraTsukasa
//=============================================================================
void CDebugProc::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// レンダラー取得
	pDevice = CManager::GetRenderer()->GetDevice();

	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
}

//=============================================================================
// 終了処理関数
// Author : SugawaraTsukasa
//=============================================================================
void CDebugProc::Uninit(void)
{
	// m_pFontがNULLでない場合
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//=============================================================================
// 書き込み処理関数
// Author : SugawaraTsukasa
//=============================================================================
void CDebugProc::Print(char * fmt, ...)
{
	va_list list;
	// 可変長引数の取得
	va_start(list, fmt);
	// 可変長引数のリストを書き込む
	vsprintf(m_astr, fmt, list);
	va_end(list);
}

//=============================================================================
// 描画処理関数
// Author : SugawaraTsukasa
//=============================================================================
void CDebugProc::Draw(void)
{
	RECT rect = { SCREEN_WIDTH - 500, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	// テキスト描画
	m_pFont->DrawText(NULL, m_astr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
