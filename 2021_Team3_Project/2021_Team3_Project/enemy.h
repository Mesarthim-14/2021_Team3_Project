#ifndef _ENEMY_H_
#define _ENEMY_H_
//=============================================================================
//
// エネミークラスヘッダー [enemy.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character.h"
#include "modelanime.h"

//=============================================================================
// エネミークラス
//=============================================================================
class CEnemy : public CCharacter
{
public:
	struct Vec2
	{
		float x;
		float z;
	};
	//=============================================================================
	//　モーション状態の列挙型
	//=============================================================================
	enum ENEMY_MOTION_STATE
	{
		ENEMY_MOTION_NONE = -1,
		ENEMY_MOTION_IDOL,			// アイドルモーション
		ENEMY_MOTION_MAX			// モーション最大数
	};

	enum ENEMY_ATTACK_DECISION_TYPE
	{
		ATTACK_DECISION_FAN = -1,	// 扇
		ATTACK_DECISION_CIRCLE,		// 円
		ATTACK_DECISION_MAX
	};

	CEnemy(PRIORITY Priority = PRIORITY_ENEMY);					// コンストラクタ
	~CEnemy();													// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	void UpdateState(void);										// プレイヤーの状態
	void FanDecision(void);										// 扇の判定
	void CircleDecision(void);									// 円の判定
	static CEnemy*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// クリエイト

	virtual void Death(void);									// 死んだときの処理
	virtual void Attack(void);									// 攻撃の処理
	virtual void Move(void);									// 移動の処理

	// セッター
	void SetAttackDecision(ENEMY_ATTACK_DECISION_TYPE Attck_Decision_Type) {m_Attack_Decision_Type = Attck_Decision_Type;}	// 攻撃判定設定処理

	// ゲッター
	ENEMY_ATTACK_DECISION_TYPE GetAttackDecision(void) { return m_Attack_Decision_Type; }	// 攻撃判定取得処理
	bool Get_bAttackDecision(void) { return m_bAttack_Decision; }							// 攻撃判定取得処理
private:
	ENEMY_ATTACK_DECISION_TYPE m_Attack_Decision_Type;			// 攻撃判定の種類
	bool m_bAttack_Decision;									// 攻撃判定用
};
#endif