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
#include "scene3d.h"
//=============================================================================
// マップクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CByte_Effect : public CScene3D
{
public:
	// 列挙型
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_UP,
		TYPE_DOWN,
		TYPE_MAX
	}TYPE;
	CByte_Effect(PRIORITY Priority = PRIORITY_3D_UI);											// コンストラクタ
	~CByte_Effect();																			// デストラクタ
	static CByte_Effect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, TYPE type);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);											// 初期化処理
	void Uninit(void);																			// 終了処理
	void Update(void);																			// 更新処理
	void Draw(void);																			// 描画処理

	static void CrateEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXVECTOR3 rot);					// エフェクト生成処理関数
private:
	void Move(void);	// 移動処理関数

	D3DXVECTOR3 m_rot;		// 向き
	D3DXVECTOR3 m_SavePos;	// 位置保存用
	TYPE m_Type;			// 種類
	bool bEndByte;			// 終了
};
#endif