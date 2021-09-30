//=============================================================================
// ボスの弾 [boss_bullet.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "character.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "enemy_bullet.h"
#include "boss_bullet.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define ADD_ROT			(D3DXVECTOR3(D3DXToRadian(1.5f),0.0f,0.0f))		// 向き加算
#define MAX_ANGLE		(D3DXToRadian(270.0f))							// 最大角度
#define RAND_POS_MAX	(5000)											// 最大
#define RAND_POS_MIN	(0)												// 最小
#define RANDOM_POS_MUT	(10)											// 10倍
#define MUT_2			(2)												// 2倍
#define BULLET_NUM		(20)											// 弾の発射数
#define ANGLE_180		(D3DXToRadian(90.0f))							// 角度90
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Bullet::CBoss_Bullet(PRIORITY Priority) : CEnemy_Bullet(Priority)
{
	m_fAngle = ZERO_FLOAT;
	m_Type	 = TYPE_NORMAL;
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Bullet::~CBoss_Bullet()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Bullet * CBoss_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,TYPE type)
{
	// CBoss_Bulletのポインタ
	CBoss_Bullet *pBoss_Bullet = nullptr;

	// nullcheck
	if (pBoss_Bullet == nullptr)
	{
		// メモリ確保
		pBoss_Bullet = new CBoss_Bullet;

		// !nullcheck
		if (pBoss_Bullet != nullptr)
		{
			// 代入
			pBoss_Bullet->m_Type = type;

			// 初期化処理
			pBoss_Bullet->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pBoss_Bullet;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBoss_Bullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 向き
	D3DXVECTOR3 Rot = rot;

	// XFile名設定
	SetXFileNum(CXfile::XFILE_NUM_TORPEDO);

	// プレイヤーのポインタ取得
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// ターゲット位置取得
		D3DXVECTOR3 Targetpos = pPlayer->GetPos();

		// TYPE_RANDOMの場合
		if (m_Type == TYPE_RANDOM)
		{
			// ランダム位置
			D3DXVECTOR3 randpos = ZeroVector3;

			// ランダム
			randpos.x = float(rand() % RAND_POS_MAX *RANDOM_POS_MUT * MUT_2 - RAND_POS_MAX *RANDOM_POS_MUT / MUT_2);
			randpos.z = float(rand() % RAND_POS_MAX *RANDOM_POS_MUT * MUT_2 - RAND_POS_MAX *RANDOM_POS_MUT / MUT_2);

			// 除算
			randpos.x = randpos.x / RANDOM_POS_MUT;
			randpos.z = randpos.z / RANDOM_POS_MUT;

			// 位置ランダム加算
			Targetpos += randpos;
		}
		// ターゲット位置設定
		SetTargetPos(Targetpos);

		// 角度
		m_fAngle = atan2f((Targetpos.x - pos.x), (Targetpos.z - pos.z));
	}
	// 向き
	Rot.y = m_fAngle;

	// 180度加算
	Rot.x = ANGLE_180;

	// 初期化処理
	CEnemy_Bullet::Init(pos, Rot);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Bullet::Uninit(void)
{
	// 終了処理
	CEnemy_Bullet::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Bullet::Update(void)
{
	// 更新
	CEnemy_Bullet::Update();

	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	// 向きの角度が180より低い場合
	if (rot.x < MAX_ANGLE)
	{
		// 向き加算
		rot.x += ADD_ROT.x;

		// 向き設定
		SetRot(rot);
	}

	// 斜方投射処理
	Projectile_motion();

	// 当たり判定
	Collision();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Bullet::Draw(void)
{
	// 描画処理
	CEnemy_Bullet::Draw();
}
//=============================================================================
// 弾生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Bullet::CreateBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// プレイヤーに飛ぶ弾生成
	Create(pos, rot, TYPE_NORMAL);

	// 10回生成
	for (int nCount = ZERO_INT; nCount < BULLET_NUM; nCount++)
	{
		// ランダム弾生成
		Create(pos, rot, TYPE_RANDOM);
	}
}