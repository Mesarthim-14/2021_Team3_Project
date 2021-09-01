//=============================================================================
// ライフゲージの背景 [gage_3d_back.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _GAGE_3D_BACK_H_
#define _GAGE_3D_BACK_H_
//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "billboard.h"
#include "enemy.h"
//=============================================================================
// マップクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CGage_3D_Back : public CBillboard
{
public:
	CGage_3D_Back(PRIORITY Priority = PRIORITY_3D_UI);										// コンストラクタ
	~CGage_3D_Back();																		// デストラクタ
	static CGage_3D_Back *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy *pEnemy);		// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);										// 初期化処理
	void Uninit(void);																		// 終了処理
	void Update(void);																		// 更新処理
	void Draw(void);																		// 描画処理
private:
	CEnemy *m_pEnemy;					// CEnemyのポインタ
};
#endif