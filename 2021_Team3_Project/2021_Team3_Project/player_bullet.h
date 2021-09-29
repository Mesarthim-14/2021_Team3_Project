#ifndef _PLAYER_BULLET_H_
#define _PLAYER_BULLET_H_
//=============================================================================
// プレイヤーの弾 [player_bullet.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "bullet.h"

//=============================================================================
// 弾クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CPlayer_Bullet : public CBullet
{
public:
	CPlayer_Bullet(PRIORITY Priority = PRIORITY_MODEL);		// コンストラクタ
	~CPlayer_Bullet();											// デストラクタ
	static CPlayer_Bullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

private:
	void Collision(void);										// 当たり判定
};
#endif