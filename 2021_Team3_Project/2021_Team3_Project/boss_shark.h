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
		MOTION_STATE_BYTE
	};
	CBoss_Shark(PRIORITY Priority = PRIORITY_ENEMY);				// コンストラクタ
	~CBoss_Shark();													// デストラクタ
	static CBoss_Shark *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
	void Attack(void);												// 攻撃処理
	void ByteAttack(void);											// 噛みつき攻撃
	void MotionUpdate(void);										// モーション処理

	int m_nAttackCount;												// 攻撃カウント
	MOTION_STATE m_MotionState;										// モーションの状態
};
#endif