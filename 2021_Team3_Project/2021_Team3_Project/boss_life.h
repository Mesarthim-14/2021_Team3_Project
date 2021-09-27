//=============================================================================
// ボスライフゲージ [boss_life.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _BOSS_LIFE_H_
#define _BOSS_LIFE_H_
//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "gage_2d.h"
#include "enemy.h"
//=============================================================================
// ゲージクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CBoss_Life :public CGage_2D
{
public:
	CBoss_Life(PRIORITY nPriority = PRIORITY_UI);									// コンストラクタ
	~CBoss_Life();																	// デストラクタ
	static CBoss_Life *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy *pEnemy);	// 生成処理関数
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);						// 初期化処理関数
	virtual void Uninit(void);														// 終了処理関数
	virtual void Update(void);														// 更新処理関数
	virtual void Draw(void);														// 描画処理関数
private:
	CEnemy *m_pEnemy;	// CEnemyのポインタ
};
#endif