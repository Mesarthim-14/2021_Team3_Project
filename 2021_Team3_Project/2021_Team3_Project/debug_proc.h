//=============================================================================
// デバッグプロシージャ [debug_proc.h]
// Author : SugawaraTsukasa
//=============================================================================
#ifndef _DEBUG_PROC_H_
#define _DEBUG_PROC_H_
//=============================================================================
// クラス
// Author : SugawaraTsukasa
//=============================================================================
class CDebugProc
{
public:
	CDebugProc();						// コンストラクタ
	~CDebugProc();						// デストラクタ
	void Init(void);					// 初期化処理関数
	void Uninit(void);					// 終了処理関数
	static void Print(char *fmt, ...);	// 書き込み処理関数
	static void Draw(void);				// 描画処理関数
private:
	static LPD3DXFONT m_pFont;			// フォント
	static char m_astr[1024];			// 文字数
};
#endif
