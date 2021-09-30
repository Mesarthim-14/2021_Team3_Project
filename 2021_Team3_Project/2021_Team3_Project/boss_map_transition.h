#ifndef _BOSS_MAP_TRANSITION_H_
#define _BOSS_MAP_TRANSITION_H_
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
class CBoss_Map_Transition : public CModel
{
public:
	CBoss_Map_Transition(PRIORITY Priority = PRIORITY_MODEL);								// コンストラクタ
	~CBoss_Map_Transition();															// デストラクタ
	static CBoss_Map_Transition *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);						// 初期化処理
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理
private:
};
#endif