#ifndef _BOSS_FADE_H_
#define _BOSS_FADE_H_
//=============================================================================
// ボスフェード [boss_fade.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "scene2d.h"

//=============================================================================
// フェードクラス
//=============================================================================
class CBoss_Fade : public CScene2D
{
public:
	//=========================================================================
	//列挙型定義
	//=========================================================================
	enum FADE_MODE
	{
		FADE_MODE_NONE = 0,	//何もない状態
		FADE_MODE_IN,		//フェードイン状態
		FADE_MODE_OUT,		//フェードアウト状態
		FADE_MODE_MAX
	};

	CBoss_Fade(PRIORITY Priority = PRIORITY_FADE);					// コンストラクタ
	~CBoss_Fade();													// デストラクタ
	static CBoss_Fade *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 生成処理関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理　
	void Draw(void);												// 描画処理
	
private:
	D3DXCOLOR m_colorFade;						//フェード色
	FADE_MODE m_FadeMode;						//フェードモード判定用
};
#endif