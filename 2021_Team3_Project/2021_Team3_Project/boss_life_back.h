//=============================================================================
// ボスライフゲージの背景 [boss_life_back.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _BOSS_LIFE_BACK_H_
#define _BOSS_LIFE_BACK_H_
//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "scene2d.h"
#include "enemy.h"
//=============================================================================
// ライフゲージ背景クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CBoss_Life_Back : public CScene2D
{
public:
	CBoss_Life_Back(PRIORITY Priority = PRIORITY_3D_UI);									// コンストラクタ
	~CBoss_Life_Back();																	// デストラクタ
	static CBoss_Life_Back *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy *pEnemy);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);										// 初期化処理
	void Uninit(void);																		// 終了処理
	void Update(void);																		// 更新処理
	void Draw(void);																		// 描画処理
private:
	CEnemy *m_pEnemy;					// CEnemyのポインタ
};
#endif