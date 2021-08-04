//=============================================================================
// プレイヤーのライフ [player_lufe.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _PLAYER_LIFE_H_
#define _PLAYER_LIFE_H_
//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "scene2d.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define MAX_LIFE	(100)
//=============================================================================
// マップクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CPlayer_Life : public CScene
{
public:
	CPlayer_Life(PRIORITY Priority = PRIORITY_UI);					// コンストラクタ
	~CPlayer_Life();												// デストラクタ
	static CPlayer_Life *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
	CScene2D *m_apScene2d[MAX_LIFE];	// CScene2Dのポインタ
};
#endif