#ifndef _TORPEDO_H_
#define _TORPEDO_H_
//=============================================================================
// 魚雷[torpedo.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"

//=============================================================================
// 弾クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CTorpedo : public CModel
{
public:
	CTorpedo(PRIORITY Priority = PRIORITY_CHARACTER);			// コンストラクタ
	~CTorpedo();												// デストラクタ
	static CTorpedo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
private:
	void Move(void);											// 移動
	void Collision(void);										// 当たり判定
	void FanDecision(void);										// 扇の判定
	void RayCollision(void);									// レイの当たり判定

	float m_fAngle;			// 角度
	bool m_bAttackDecision;	// 攻撃判定用
	bool m_bMove;			// 移動判定
};
#endif