#ifndef _ENEMY_SCAFFOLDING_H_
#define _ENEMY_SCAFFOLDING_H_
//=============================================================================
//
// 敵の櫓 [enemy_scaffolding.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "enemy.h"

//=============================================================================
// 櫓クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CEnemy_Scaffolding : public CEnemy
{
public:
	enum PARTS
	{
		PARTS_SHIP = 0,
		PARTS_BATTERY,		// 砲台
		PARTS_MAX
	};
	CEnemy_Scaffolding(PRIORITY Priority = PRIORITY_ENEMY);					// コンストラクタ
	~CEnemy_Scaffolding();													// デストラクタ
	static CEnemy_Scaffolding *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);							// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理

private:
	void Attack(void) override;		// 攻撃処理
};
#endif