#ifndef _ENEMYSHIP_H_
#define _ENEMYSHIP_H_
//=============================================================================
//
// 敵の船 [enemy_ship.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "enemy.h"

//=============================================================================
// 敵船クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CEnemy_Ship : public CEnemy
{
public:
	enum PARTS
	{
		PARTS_SHIP = 0,
		PARTS_BATTERY,		// 砲台
		PARTS_MAX
	};
	CEnemy_Ship(PRIORITY Priority = PRIORITY_ENEMY);				// コンストラクタ
	~CEnemy_Ship();													// デストラクタ
	static CEnemy_Ship *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

private:
	void Move(void);												// 移動処理
	void Attack(void) override;										// 攻撃処理
};
#endif