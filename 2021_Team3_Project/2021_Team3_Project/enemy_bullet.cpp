//=============================================================================
// 敵の弾 [enemy_bullet.cpp]
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
#include "model_box.h"
#include "enemy_attack_arrow_polygon.h"
#include "enemy_attack_point_polygon.h"
#include "enemy_bullet.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define MOVE_VALUE			(30.0f)								// 移動量
#define MOVE_VALUE_Y		(60.0f)								// 移動量
#define POS_Y_MAX			(4000.0f)							// Y最大値
#define PARENT_NUM			(0)									// 親のナンバー
#define DAMAGE				(10)								// ダメージ
#define GRAVITY				(-1.0f)								// 重力
#define DIVIDE_2F			(2.0f)								// ÷2
#define ANGLE				(D3DXToRadian(45.0f))				// 角度
#define POW_VALUE			(2.0f)								// 累乗値
// 攻撃地点のサイズ
#define ARROW_SIZE	(D3DXVECTOR3(500.0f,300.0f,0.0f))
#define POINT_SIZE	(D3DXVECTOR3(300.0f,0.0f,400.0f))
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Bullet::CEnemy_Bullet(PRIORITY Priority)
{
	m_TargetPos = ZeroVector3;
	m_State = STATE_UP;
	m_StartPos = ZeroVector3;
	m_bInitVelocity = true;
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Bullet::~CEnemy_Bullet()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Bullet * CEnemy_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CEnemy_Bulletのポインタ
	CEnemy_Bullet *pEnemy_Bullet = nullptr;

	// nullcheck
	if (pEnemy_Bullet == nullptr)
	{
		// メモリ確保
		pEnemy_Bullet = new CEnemy_Bullet;

		// !nullcheck
		if (pEnemy_Bullet != nullptr)
		{
			// 初期化処理
			pEnemy_Bullet->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pEnemy_Bullet;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CEnemy_Bullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CBullet::Init(pos, rot);

	// 代入
	m_StartPos = pos;

	// 箱生成
	CModel_Box::Create(pos, rot, this);

	// 攻撃地点生成
	AttackPoint_Crate(this);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Bullet::Uninit(void)
{
	// 終了処理
	CBullet::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Bullet::Update(void)
{
	// 更新処理
	CBullet::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Bullet::Draw(void)
{
	// 描画処理
	CBullet::Draw();
}
//=============================================================================
// 移動処理
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Bullet::Move(void)
{
	// 位置座標取得
	D3DXVECTOR3 pos = GetPos();

	// 移動量
	D3DXVECTOR3 move = ZeroVector3;

	// 角度
	float fAngle = atan2f((pos.x - m_TargetPos.x), (pos.z - m_TargetPos.z));

	// 0以上の場合
	if ((int)fAngle != ZERO_INT)
	{
		// 弾の移動
		move.x = -sinf(fAngle) *MOVE_VALUE;
		move.z = -cosf(fAngle) *MOVE_VALUE;
	}
	// UPの場合
	if (m_State == STATE_UP)
	{
		// 1000以下の場合
		if (pos.y < POS_Y_MAX)
		{
			// UPに
			m_State = STATE_UP;
		}
	}
	// 1000以上の場合
	if (pos.y > POS_Y_MAX)
	{
		// DOWNに
		m_State = STATE_DOWN;
	}
	// UPの場合
	if (m_State == STATE_UP)
	{
		// 上昇
		move.y = MOVE_VALUE_Y;
	}
	// DOWNの場合
	if (m_State == STATE_DOWN)
	{
		// 落下
		move.y = -MOVE_VALUE_Y / DIVIDE_2;
	}

	// 移動量設定
	SetMove(move);
}
//=============================================================================
// 当たり判定処理
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Bullet::Collision(void)
{
	// 船の位置取得
	D3DXVECTOR3 pos = GetPos();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// プレイヤーのポインタ取得
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// nullptrでない場合
	if (pPlayer != nullptr)
	{
		// プレイヤー位置座標取得
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

		// プレイヤーサイズ取得
		D3DXVECTOR3 PlayerSize = pPlayer->GetSize();

		// 判定
		if (CCollision::CollisionRectangleAndRectangle(pos, PlayerPos, size, PlayerSize) == true)
		{
			// ヒット処理
			pPlayer->Hit(DAMAGE);

			// 状態設定
			Death();
		}
	}
}
//=============================================================================
// 攻撃地点生成
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Bullet::AttackPoint_Crate(CBullet * pBullet)
{
	// 矢印生成
	CEnemy_Attack_Arrow_Polygon::Create(m_TargetPos, ARROW_SIZE, pBullet);

	// 攻撃地点生成
	CEnemy_Attack_Point_Polygon::Create(m_TargetPos, POINT_SIZE, pBullet);
}
//=============================================================================
// 斜方投射処理
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Bullet::Projectile_motion(void)
{
	// 距離
	D3DXVECTOR3 Dist = ZeroVector3;

	// 距離算出
	Dist.x = m_StartPos.x - m_TargetPos.x;
	Dist.y = m_StartPos.y - m_TargetPos.y;
	Dist.z = m_StartPos.z - m_TargetPos.z;

	// 水平方向の距離
	float fX = sqrtf((Dist.x * Dist.x) + (Dist.z * Dist.z));

	// 垂直方向
	float fY = Dist.y;

	// 斜方投射の公式を初速度について解く
	float fSpeed = sqrtf(-GRAVITY * powf(fX, POW_VALUE) / (2 * powf(cosf(ANGLE), POW_VALUE) * (fX * tanf(ANGLE) + fY)));

	// ベクトル
	D3DXVECTOR3 Vec = ZeroVector3;

	// 正規化
	D3DXVec3Normalize(&Vec, &(D3DXVECTOR3(m_TargetPos.x - m_StartPos.x, fX * tanf(ANGLE), m_TargetPos.z - m_StartPos.z)));

	// 速度
	Vec *= fSpeed;

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// falseの場合
	if (m_bInitVelocity == false)
	{
		// 重力
		move.y += GRAVITY;
	}
	// trueの場合
	if (m_bInitVelocity == true)
	{
		// 力 =速度 * 質量
		move = Vec;

		// 発射時重力を/2
		move.y += GRAVITY / DIVIDE_2F;

		// false1に
		m_bInitVelocity = false;
	}
	// 移動量
	SetMove(move);
}