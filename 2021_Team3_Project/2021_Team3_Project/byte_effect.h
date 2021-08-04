//=============================================================================
// ボス噛みつきエフェクト [byte_effect.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _BYTE_EFFECT_H_
#define _BYTE_EFFECT_H_
//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "billboard.h"
//=============================================================================
// マップクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CByte_Effect : public CBillboard
{
public:
	CByte_Effect(PRIORITY Priority = PRIORITY_3D_UI);				// コンストラクタ
	~CByte_Effect();												// デストラクタ
	static CByte_Effect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
};
#endif