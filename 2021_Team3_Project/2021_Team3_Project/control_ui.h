#ifndef _CONTROL_UI_H_
#define _CONTROL_UI_H_
//=============================================================================
// 操作UIクラス [control_ui.h]
// Author : Konishi Yuuto
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "billboard.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CModelAnime;

//=============================================================================
// クラス定義
// Author : Konishi Yuuto
//=============================================================================
class CControlUi : public CBillboard
{
public:
	CControlUi(PRIORITY Priority = PRIORITY_UI);					// コンストラクタ
	~CControlUi();													// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

	// Set関数
	void SetModelPtr(CModelAnime* pPtr) { m_pModelPtr = pPtr; }		// モデルのポインタ設定
	void SetHeight(float fHeight)		{ m_fHeight = fHeight; }	// 高さの設定
private:
	CModelAnime* m_pModelPtr;	// モデルのポインタ
	int m_nCounter;				// タイムのカウンター
	float m_fHeight;			// 表示する高さ
};
#endif