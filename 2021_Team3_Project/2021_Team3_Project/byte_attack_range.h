//=============================================================================
// ボス噛みつき範囲 [byte_attack_range.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _BYTE_ATTACK_RANGE_H_
#define _BYTE_ATTACK_RANGE_H_
//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "scene3d.h"
//=============================================================================
// マップクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CByte_Attack_Range : public CScene3D
{
public:
	CByte_Attack_Range(PRIORITY Priority = PRIORITY_UI);						// コンストラクタ
	~CByte_Attack_Range();														// デストラクタ
	static CByte_Attack_Range *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);							// 初期化処理
	void Uninit(void);															// 終了処理
	void Update(void);															// 更新処理
	void Draw(void);															// 描画処理

private:
	void Collision(void);	// 当たり判定
	int m_nCount;			// カウント
	bool m_bAddColor;		// 色を加算するか
};
#endif