#ifndef _BOSS_BULLET_H_
#define _BOSS_BULLET_H_
//=============================================================================
// ボスの弾 [boss_bullet.h]
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
class CBoss_Bullet : public CEnemy_Bullet
{
public:
	enum TYPE
	{
		TYPE_NORMAL = 0,
		TYPE_RANDOM
	};
	CBoss_Bullet(PRIORITY Priority = PRIORITY_MODEL);							// コンストラクタ
	~CBoss_Bullet();															// デストラクタ
	static CBoss_Bullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,TYPE type);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);								// 初期化処理
	void Uninit(void);															// 終了処理
	void Update(void);															// 更新処理
	void Draw(void);															// 描画処理
	static void CreateBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 弾生成
private:
	float m_fAngle;	// 角度
	TYPE m_Type;	// 種類
};
#endif