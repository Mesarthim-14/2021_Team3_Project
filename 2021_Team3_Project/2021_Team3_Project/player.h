#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// プレイヤークラスヘッダー [player.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character.h"
#include "modelanime.h"
#include "effect.h"

//=============================================================================
//　モーション状態の列挙型
//=============================================================================
enum PARTS_NUM
{
	PARTS_NUM_NONE = -1,
	PARTS_NUM_WAIST,			// [0]腰
	PARTS_NUM_MAX				// モーション最大数
};

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer : public CCharacter
{
public:
	//=============================================================================
	//　状態の列挙型
	//=============================================================================
	enum PLAYER_STATE
	{
		PLAYER_STATE_NONE = 0,		// 初期置
		PLAYER_STATE_NORMAL,		// 通常状態
		PLAYER_STATE_DEAD,			// 死亡状態
		PLAYER_STATE_MAX			// 最大数
	};

	//=============================================================================
	//　モーション状態の列挙型
	//=============================================================================
	enum MOTION_STATE
	{
		MOTION_NONE = -1,
		MOTION_IDOL,				// アイドルモーション
		MOTION_MAX					// モーション最大数
	};

	//=============================================================================
	//　パッドの種類の列挙型
	//=============================================================================
	enum PAD_TYPE
	{
		PAD_TYPE_1P = 0,
		PAD_TYPE_2P,
		PAD_TYPE_MAX
	};

	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);			// コンストラクタ
	~CPlayer();													// デストラクタ

	static CPlayer*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// クリエイト

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
	void UpdateState(void);										// プレイヤーの状態
	void PlayerControl(void);									// プレイヤーの制御
	void UpdateRot(void);										// 角度の更新処理

	void Death(void);											// 死亡関数
	void Move(void);											// 移動処理
	void Pad2Move(void);										// 2コントローラーの移動
	void Attack(void);											// 攻撃の関数
	void Pad2Attack(void);										// 2コントローラーの攻撃
	void KeyboardMove(void);									// キーボード移動
	void Collision(void);										// 当たり判定
	void CrossCollision(void);									// 外積当たり判定
	void RayCollision(void);									// レイの当たり判定

	void CreateSmoke(void);			//煙生成関数
	void CreateWoodEP(void);			//木材生成関数
	void CreateSplash(void);			//水しぶき生成関数
	void CreateExplosion(void);		//爆発生成関数
	void CreateWave(void);			//波生成関数

	void Knock_Back(void);										// ノックバック処理
  
private:
	D3DXVECTOR3 m_rotDest;							// 回転(目標値)
	int m_nAttackCount_R;							// 右攻撃カウント
	int m_nAttackCount_L;							// 左攻撃カウント
	int m_nRockHitCount;							// 岩にヒットしたカウント
	PAD_TYPE m_PadType;								// パッドタイプ
	D3DXVECTOR3 m_Reflection_Vec;					// 反射ベクトル
	float m_fRefrectionVec;							// 反射ベクトル
	bool m_bBack;									// 後ろに移動しているか
	CEffect *m_pEffect;								//エフェクトのポインタ
	bool m_bMove;									// 歩いているフラグ
	bool m_bKnock_Back;								// ノックバック
};
#endif