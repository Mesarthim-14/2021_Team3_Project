#ifndef _TITLE_SKY_H_
#define _TITLE_SKY_H_
//=============================================================================
// タイトルマップ [title_sky.h]
// Author : Konishi Yuuto
//=============================================================================

//=============================================================================
// インクルード
// Author : Konishi Yuuto
//=============================================================================
#include "model.h"

//=============================================================================
// マップクラス
// Author : Konishi Yuuto
//=============================================================================
class CTitleSky : public CModel
{
public:
	CTitleSky(PRIORITY Priority = PRIORITY_MODEL);				// コンストラクタ
	~CTitleSky();												// デストラクタ
	static CTitleSky *Create(void);								// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// 初期化処理
	void Draw(void);											// 描画処理
private:
};
#endif