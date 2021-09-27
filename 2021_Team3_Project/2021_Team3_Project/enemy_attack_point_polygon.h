//=============================================================================
// 敵の攻撃地点 [enemy_attack_point_polygon.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _ENEMY_ATTACK_POINT_POLYGON_H_
#define _ENEMY_ATTACK_POINT_POLYGON_H_
//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "scene3D.h"
#include "bullet.h"
//=============================================================================
// マップクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CEnemy_Attack_Point_Polygon : public CScene3D
{
public:
	CEnemy_Attack_Point_Polygon(PRIORITY Priority = PRIORITY_UI);													// コンストラクタ
	~CEnemy_Attack_Point_Polygon();																					// デストラクタ
	static CEnemy_Attack_Point_Polygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CBullet *pBullet);				// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);																// 初期化処理
	void Uninit(void);																								// 終了処理
	void Update(void);																								// 更新処理
	void Draw(void);																								// 描画処理
private:
	void Collision(void);			// 当たり判定
	void UpdateRot(void);			// 向きの処理
	CBullet *m_pBullet;	// CEnemy_Bulletのポインタ
	bool m_bCollision;				// 当たり判定
};
#endif