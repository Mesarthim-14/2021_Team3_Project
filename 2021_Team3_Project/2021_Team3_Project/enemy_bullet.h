#ifndef _ENEMY_BULLET_H_
#define _ENEMY_BULLET_H_
//=============================================================================
// プレイヤーの弾 [enemy_bullet.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "bullet.h"

//=============================================================================
// 弾クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CEnemy_Bullet : public CBullet
{
public:
	enum STATE	// 状態
	{
		STATE_UP = 0,
		STATE_DOWN,
	};
	CEnemy_Bullet(PRIORITY Priority = PRIORITY_CHARACTER);		// コンストラクタ
	~CEnemy_Bullet();											// デストラクタ
	static CEnemy_Bullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
private:
	void Move(void);											// 移動処理
	void Collision(void);										// 当たり判定処理
	void AttackPoint_Crate(void);								// 攻撃地点生成
	CEnemy_Bullet *m_pEnemy_Bullet;								// CEnemy_Bulletのポインタ
	D3DXVECTOR3 m_PlayerPos;									// プレイヤーの位置
	STATE m_State;												// 状態
};
#endif