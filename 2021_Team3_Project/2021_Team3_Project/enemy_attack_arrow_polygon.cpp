//=============================================================================
// 敵の攻撃矢印 [enemy_attack_arrow_polygon.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "character.h"
#include "enemy_attack_arrow_polygon.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define DOWN_COUNT	(30)								// カウント
#define UP_COUNT	(60)								// カウント
#define MOVE		(3.0f)								// 移動量
#define COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 色
#define POINT_SIZE	(D3DXVECTOR3(300.0f,0.0f,400.0f))	// サイズ
#define UP_POS		(D3DXVECTOR3(pos.x,700.0f,pos.z))	// 位置
#define DOWN_POS	(D3DXVECTOR3(pos.x,200.0f,pos.z))	// 位置
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Attack_Arrow_Polygon::CEnemy_Attack_Arrow_Polygon(PRIORITY Priority) : CBillboard(Priority)
{
	m_nCount		= ZERO_INT;
	m_pBullet		= nullptr;
	m_bCollision	= false;
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Attack_Arrow_Polygon::~CEnemy_Attack_Arrow_Polygon()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Attack_Arrow_Polygon * CEnemy_Attack_Arrow_Polygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CBullet *pBullet)
{
	// CEnemy_Attack_Arrow_Polygonのポインタ
	CEnemy_Attack_Arrow_Polygon *pEnemy_Attack_Point_Polygon = nullptr;

	// nullcheck
	if (pEnemy_Attack_Point_Polygon == nullptr)
	{
		// メモリ確保
		pEnemy_Attack_Point_Polygon = new CEnemy_Attack_Arrow_Polygon;

		// !nullcheck
		if (pEnemy_Attack_Point_Polygon != nullptr)
		{
			// 代入
			pEnemy_Attack_Point_Polygon->m_pBullet = pBullet;

			// 初期化処理
			pEnemy_Attack_Point_Polygon->Init(pos, size);
		}
	}
	// ポインタを返す
	return pEnemy_Attack_Point_Polygon;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CEnemy_Attack_Arrow_Polygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CBillboard::Init(pos, size);

	// // Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ATTACK_ARROW));

	// 向き設定
	SetRot(ZeroVector3);

	// 色設定
	SetColor(COLOR);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Arrow_Polygon::Uninit(void)
{
	// !nullcheck
	if (m_pBullet != nullptr)
	{
		m_pBullet = nullptr;
	}

	// 終了処理
	CBillboard::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Arrow_Polygon::Update(void)
{
	// 更新処理
	CBillboard::Update();

	// 移動処理
	Move();

	// 当たり判定
	Collision();

	// 死亡状態の場合
	if (m_pBullet->GetState() == CModel::STATE_DEAD)
	{
		// 終了
		Uninit();

		return;
	}
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Arrow_Polygon::Draw(void)
{
	// 描画処理
	CBillboard::Draw();
}
//=============================================================================
// 当たり判定処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Arrow_Polygon::Collision(void)
{
	//プレイヤーのポインタ取得
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// 位置
	D3DXVECTOR3 pos = GetPos();

	// 位置取得
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	// サイズ取得
	D3DXVECTOR3 PlayerSize = pPlayer->GetSize();

	// プレイヤーと重なっていたら
	if (pos.x < PlayerPos.x + PlayerSize.x / DIVIDE_2 &&
		pos.x > PlayerPos.x - PlayerSize.x / DIVIDE_2 &&
		pos.z < PlayerPos.z + PlayerSize.z / DIVIDE_2 &&
		pos.z > PlayerPos.z - PlayerSize.z / DIVIDE_2)
	{
		// falseの場合
		if (m_bCollision == false)
		{
			// trueに
			m_bCollision = true;

			// 位置設定
			SetPos(UP_POS);
		}
	}
	// 重なっていない場合
	else
	{
		// falseの場合
		if (m_bCollision == true)
		{
			// trueに
			m_bCollision = false;

			// 位置設定
			SetPos(DOWN_POS);
		}
	}
}
//=============================================================================
// 移動処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Arrow_Polygon::Move(void)
{
	// 移動
	D3DXVECTOR3 move = ZeroVector3;

	// インクリメント
	m_nCount++;

	// 30以下の場合
	if (m_nCount < DOWN_COUNT)
	{
		move.y += -MOVE;
	}
	// 60以下の場合
	if (m_nCount < UP_COUNT && m_nCount > DOWN_COUNT)
	{
		move.y += MOVE;
	}
	// 60以上の場合
	if (m_nCount > UP_COUNT)
	{
		// 0に
		m_nCount = ZERO_INT;
	}

	// 移動量設定
	SetMove(move);
}