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
	//=============================================================================
	// XZの構造体
	//=============================================================================
	struct Vec2
	{
		float x;
		float z;
	};
	//=============================================================================
	//　敵の種類
	//=============================================================================
	enum TYPE
	{
		TYPE_NORMAL = 0,
		TYPE_BOSS
	};
	//=============================================================================
	//　判定の種類
	//=============================================================================
	enum ATTACK_DECISION_TYPE
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
	void Hit(int nDamage);										// ヒット処理
	static CEnemy*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// クリエイト

	virtual void Death(void);									// 死んだときの処理
	virtual void Attack(void);									// 攻撃の処理
	virtual void Move(void);									// 移動の処理

	// セッター
	void SetAttackDecision(ATTACK_DECISION_TYPE Attck_Decision_Type) {m_Attack_Decision_Type = Attck_Decision_Type;}	// 攻撃判定設定処理
	void SetType(TYPE type) { m_Type = type; }
	void SetHit(bool bHit) { m_bHit = bHit; }
	// ゲッター
	ATTACK_DECISION_TYPE GetAttackDecision(void)	{ return m_Attack_Decision_Type; }		// 攻撃判定取得処理
	bool Get_bAttackDecision(void)						{ return m_bAttack_Decision; }		// 攻撃判定取得処理
	int &GetAttackCount(void)							{ return m_AttackCount; }			// 攻撃のカウント
	bool GetHit(void) { return m_bHit; }													// ヒット判定取得
private:
	ATTACK_DECISION_TYPE m_Attack_Decision_Type; // 攻撃判定の種類
	bool m_bAttack_Decision;					 // 攻撃判定用
	int m_AttackCount;							 // 攻撃カウント
	TYPE m_Type;								 // 敵の種類
	bool m_bHit;								 // ヒットした場合
};
#endif