//=============================================================================
// 敵の攻撃矢印 [enemy_attack_arrow_polygon.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _ENEMY_ATTACK_ARROW_POLYGON_H_
#define _ENEMY_ATTACK_ARROW_POLYGON_H_
//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "billboard.h"
#include "bullet.h"
//=============================================================================
// マップクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CEnemy_Attack_Arrow_Polygon : public CBillboard
{
public:
	CEnemy_Attack_Arrow_Polygon(PRIORITY Priority = PRIORITY_UI);										// コンストラクタ
	~CEnemy_Attack_Arrow_Polygon();																		// デストラクタ
	static CEnemy_Attack_Arrow_Polygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CBullet *pBullet);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);													// 初期化処理
	void Uninit(void);																					// 終了処理
	void Update(void);																					// 更新処理
	void Draw(void);																					// 描画処理
private:
	void Collision(void);			// 当たり判定
	void Move(void);				// 移動
	CBullet *m_pBullet;				// CBulletのポインタ
	int m_nCount;					// カウント
	bool m_bCollision;				// 当たり判定
};
#endif