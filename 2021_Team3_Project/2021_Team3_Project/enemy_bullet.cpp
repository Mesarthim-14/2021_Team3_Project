//=============================================================================
// プレイヤー弾 [player_bullet.cpp]
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
#include "enemy_bullet.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define MOVE_VALUE_X	(40.0f)								// 移動量
#define MOVE_VALUE_Y	(60.0f)								// 移動量
#define POS_Y_MAX		(4000.0f)							// Y最大値
#define PARENT_NUM		(0)									// 親のナンバー
#define DAMAGE			(100)								// ダメージ
#define ANGLE_90		(D3DXToRadian(90))					// 90度
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Bullet::CEnemy_Bullet(PRIORITY Priority)
{
	m_PlayerPos = ZeroVector3;
	m_State		= STATE_UP;
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
	CEnemy_Bullet *pPlayer_Bullet = nullptr;

	// nullcheck
	if (pPlayer_Bullet == nullptr)
	{
		// メモリ確保
		pPlayer_Bullet = new CEnemy_Bullet;

		// !nullcheck
		if (pPlayer_Bullet != nullptr)
		{
			// 初期化処理
			pPlayer_Bullet->Init(pos, rot);

			// 箱生成
			CModel_Box::Create(pos, rot, pPlayer_Bullet);
		}
	}
	// ポインタを返す
	return pPlayer_Bullet;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CEnemy_Bullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CBullet::Init(pos, rot);

	// プレイヤーのポインタ取得
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// 位置座標取得
	m_PlayerPos = pPlayer->GetPos();

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

	// 移動処理
	Move();

	// 当たり判定
	Collision();
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
	float fAngle = atan2f((pos.x - m_PlayerPos.x), (pos.z - m_PlayerPos.z));

	// 0以上の場合
	if ((int)fAngle != ZERO_FLOAT)
	{
		// 弾の移動
		move.x = -sinf(fAngle) *MOVE_VALUE_X;
		move.z = -cosf(fAngle) *MOVE_VALUE_X;
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

	// プレイヤー位置座標取得
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	// プレイヤーサイズ取得
	D3DXVECTOR3 PlayerSize = pPlayer->GetSize();

	// 判定
	if (CCollision::CollisionRectangleAndRectangle(pos, PlayerPos, size, PlayerSize) == true)
	{
		// 状態設定
		SetState(CModel::STATE_DEAD);

		// 終了
		Uninit();

		return;
	}
}