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
	CEnemy_Bullet(PRIORITY Priority = PRIORITY_MODEL);						// コンストラクタ
	~CEnemy_Bullet();														// デストラクタ
	static CEnemy_Bullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);							// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理

	void Move(void);														// 移動処理
	void Collision(void);													// 当たり判定処理
	void AttackPoint_Crate(CBullet * pBullet);								// 攻撃地点生成
	void Projectile_motion(void);											// 斜方投射処理
	void SetTargetPos(D3DXVECTOR3 targetpos) { m_TargetPos = targetpos; }	// ターゲット位置設定
	void SetStartPos(D3DXVECTOR3 startpos) { m_StartPos = startpos; }		// スタート地点設定
private:

	D3DXVECTOR3 m_TargetPos;									// プレイヤーの位置
	STATE m_State;												// 状態
	D3DXVECTOR3 m_StartPos;										// 初期位置
	bool m_bInitVelocity;										// 初速
};
#endif