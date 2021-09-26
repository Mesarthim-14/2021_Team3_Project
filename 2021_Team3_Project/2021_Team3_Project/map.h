#ifndef _MAP_H_
#define _MAP_H_
//=============================================================================
// マップ [map.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"

//=============================================================================
// マップクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CMap : public CModel
{
public:
	enum TYPE 
	{
		TYPE_NORMAL = 0,
		TYPE_BOSS
	};
	CMap(PRIORITY Priority = PRIORITY_MAP);								// コンストラクタ
	~CMap();															// デストラクタ
	static CMap *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);						// 初期化処理
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理
	void RayCollision(void);											// レイの当たり判定
private:
	TYPE m_Type;	// 種類
};
#endif