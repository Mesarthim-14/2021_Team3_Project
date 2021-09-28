#ifndef _ENEMY_NORAMLBULLET_H_
#define _ENEMY_NORAMLBULLET_H_
//=============================================================================
// プレイヤーの弾 [enemy_bullet.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "enemy_bullet.h"

//=============================================================================
// 弾クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CEnemy_Normal_Bullet : public CEnemy_Bullet
{
public:
	CEnemy_Normal_Bullet(PRIORITY Priority = PRIORITY_MODEL);				// コンストラクタ
	~CEnemy_Normal_Bullet();												// デストラクタ
	static CEnemy_Normal_Bullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);							// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理
private:
};
#endif