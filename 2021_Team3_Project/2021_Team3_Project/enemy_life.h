//=============================================================================
// 敵ライフゲージ [enemy_life.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _ENEMY_LIFE_H_
#define _ENEMY_LIFE_H_
//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "gage_3d.h"
#include "enemy.h"
#include "gage_3d_back.h"
//=============================================================================
// 敵ライフクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CEnemy_Life :public CGage_3D
{
public:
	CEnemy_Life(PRIORITY nPriority = PRIORITY_UI);										// コンストラクタ
	~CEnemy_Life();																	// デストラクタ
	static CEnemy_Life *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy *pEnemy);	// 生成処理関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);								// 初期化処理関数
	void Uninit(void);																// 終了処理関数
	void Update(void);																// 更新処理関数
	void Draw(void);																// 描画処理関数

private:
	CEnemy *m_pEnemy;					// CEnemyのポインタ
};
#endif