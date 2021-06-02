#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// プレイヤークラスヘッダー [player.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character.h"
#include "modelanime.h"

//=============================================================================
//　モーション状態の列挙型
//=============================================================================
enum PARTS_NUM
{
	PARTS_NUM_NONE = -1,
	PARTS_NUM_WAIST,			// [0]腰
	PARTS_NUM_MAX,				// モーション最大数
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
		PLAYER_STATE_MAX			// 最大数
	};

	//=============================================================================
	//　モーション状態の列挙型
	//=============================================================================
	enum MOTION_STATE
	{
		MOTION_NONE = -1,
		MOTION_IDOL,				// アイドルモーション
		MOTION_MAX,					// モーション最大数
	};

	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);			// コンストラクタ
	~CPlayer();													// デストラクタ

	static CPlayer*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// クリエイト

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
	void UpdateState(void);										// プレイヤーの状態
	void UpdateMotionState(void);								// モーション状態
	void PlayerControl(void);									// プレイヤーの制御
	void UpdateRot(void);										// 角度の更新処理

	void Death(void);											// 死亡関数
	void Move(void);											// 移動処理
	void Attack(void);											// 攻撃の関数

private:
	D3DXVECTOR3 m_rotDest;							// 回転(目標値)
	bool m_bMove;									// 歩いているフラグ
};
#endif