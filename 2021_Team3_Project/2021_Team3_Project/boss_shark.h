#ifndef _BOSS_SHARK_H_
#define _BOSS_SHARK_H_
//=============================================================================
//
// ボスサメ [boss_shark.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "enemy.h"

//=============================================================================
// エネミークラス
// Author : Sugawara Tsukasa
//=============================================================================
class CBoss_Shark : public CEnemy
{
public:
	enum PARTS
	{
		PARTS_BODY = 0,		// 体
		PARTS_HEAD,			// 頭
		PARTS_CHIN,			// 顎
		PARTS_UNDER_BODY,	// 下半身
		PARTS_MAX
	};
	enum MOTION_STATE
	{
		MOTION_STATE_IDLE = 0,
		MOTION_STATE_BYTE,
		MOTION_STATE_SHARK_BULLET
	};
	CBoss_Shark(PRIORITY Priority = PRIORITY_ENEMY);				// コンストラクタ
	~CBoss_Shark();													// デストラクタ
	static CBoss_Shark *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

	bool GetEnd(void) { return m_bEnd; }							// 終了取得
private:
	void Attack(void)override;										// 攻撃処理
	void Death(void)override;										// 死亡処理
	void ByteAttack(void);											// 噛みつき攻撃
	void SharkBulletAttack(void);									// サメの弾攻撃
	void MotionUpdate(void);										// モーション処理
	void UpdateRot(void);											// 向き更新
	void Enemy_Create(void);										// 敵生成処理

	MOTION_STATE m_MotionState;	// モーションの状態
	bool m_bEnd;				// 終了
	bool m_bEnemyCreate;		// 敵生成
	bool m_bRot;				// 向き判定
};
#endif