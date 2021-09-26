#ifndef _MAP_H_
#define _MAP_H_
//=============================================================================
// タイトルマップ [titlr_map.h]
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
class CTitleMap : public CModel
{
public:
	CTitleMap(PRIORITY Priority = PRIORITY_MAP);				// コンストラクタ
	~CTitleMap();												// デストラクタ
	static CTitleMap *Create(void);								// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// 初期化処理

private:
};
#endif