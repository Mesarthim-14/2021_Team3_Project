#ifndef _ENEMY_H_
#define _ENEMY_H_
//=============================================================================
//
// エネミークラスヘッダー [enemy.h]
// Author : Konishi Yuuto
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
	//　モーション状態の列挙型
	//=============================================================================
	enum ENEMY_MOTION_STATE
	{
		ENEMY_MOTION_NONE = -1,
		ENEMY_MOTION_IDOL,			// アイドルモーション
		ENEMY_MOTION_MAX,			// モーション最大数
	};

	CEnemy(PRIORITY Priority = PRIORITY_ENEMY);				// コンストラクタ
	~CEnemy();													// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	void UpdateState(void);										// プレイヤーの状態
	static CEnemy*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// クリエイト

	virtual void UpdateMotionState(void);						// モーション状態
	virtual void Death(void);									// 死んだときの処理
	virtual void Attack(void);									// 攻撃の処理
	virtual void Move(void);									// 移動の処理

private:
};
#endif