//=============================================================================
// 敵の攻撃地点 [enemy_attack_point_polygon.cpp]
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
#include "player.h"
#include "game.h"
#include "enemy_attack_point_polygon.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define ADD_ROT		(D3DXToRadian(1.0f))				// 向き加算値
#define ANGLE_MAX	(D3DXToRadian(360.0f))				// 角度の最大
#define ANGLE_MIN	(D3DXToRadian(0.0f))				// 角度の最小
#define COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 色
#define ALPHA		(100)								// 透過値
#define SIZE		(D3DXVECTOR3(300.0f,0.0f,400.0f))	// サイズ
#define UP_POS		(D3DXVECTOR3(pos.x,500.0f,pos.z))	// 位置
#define DOWN_POS	(D3DXVECTOR3(pos.x,10.0f,pos.z))		// 位置
#define PARENT_NUM	(0)									// 親のナンバー
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Attack_Point_Polygon::CEnemy_Attack_Point_Polygon(PRIORITY Priority) : CScene3D(Priority)
{
	m_pBullet		= nullptr;
	m_bCollision	= false;
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Attack_Point_Polygon::~CEnemy_Attack_Point_Polygon()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Attack_Point_Polygon * CEnemy_Attack_Point_Polygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CBullet *pBullet)
{
	// CEnemy_Attack_Point_Polygonのポインタ
	CEnemy_Attack_Point_Polygon *pEnemy_Attack_Point_Polygon = nullptr;

	// nullcheck
	if (pEnemy_Attack_Point_Polygon == nullptr)
	{
		// メモリ確保
		pEnemy_Attack_Point_Polygon = new CEnemy_Attack_Point_Polygon;

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
HRESULT CEnemy_Attack_Point_Polygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CScene3D::Init(pos, size);

	// // Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ATTACK_POINT));

	// 向き設定
	SetRot(ZeroVector3);

	// 色設定
	SetColor(COLOR);

	// 透過値設定
	SetAlpha(true);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Point_Polygon::Uninit(void)
{
	// !nullcheck
	if (m_pBullet != nullptr)
	{
		m_pBullet = nullptr;
	}

	// 終了処理
	CScene3D::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Point_Polygon::Update(void)
{
	// 更新処理
	CScene3D::Update();

	// 向き処理
	UpdateRot();

	// 当たり判定
	Collision();

	// 死亡状態の場合
	if (m_pBullet->GetState() == CModel::STATE_DEAD)
	{
		// 終了処理
		Uninit();

		return;
	}
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Point_Polygon::Draw(void)
{
	// 描画処理
	CScene3D::Draw();
}
//=============================================================================
// 向き処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Point_Polygon::UpdateRot(void)
{
	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	// 向き加算
	rot.y += ADD_ROT;

	// 360以上の場合
	if (rot.x >= ANGLE_MAX)
	{
		// 向きを元に戻す
		rot.y = ANGLE_MIN;
	}

	// 向き設定
	SetRot(rot);
}
//=============================================================================
// 当たり判定処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Point_Polygon::Collision(void)
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