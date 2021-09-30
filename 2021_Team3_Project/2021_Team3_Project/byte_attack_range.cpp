//=============================================================================
// ボス噛みつき範囲 [byte_attack_range.cpp]
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
#include "game.h"
#include "player.h"
#include "collision.h"
#include "byte_attack_range.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COL			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))	// 色
#define DAMAGE		(10)								// ダメージ
#define ATTACK_KEY	(265)								// 攻撃キー
#define COL_MAX		(1.0f)								// 色最大
#define COL_MIN		(0.1f)								// 色の最小
#define ADD_COL		(0.05f)								// 色の加算値
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Attack_Range::CByte_Attack_Range(PRIORITY Priority) : CScene3D(Priority)
{
	m_nCount	= ZERO_INT;
	m_bAddColor = false;
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Attack_Range::~CByte_Attack_Range()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Attack_Range * CByte_Attack_Range::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CByte_Attack_Rangeのポインタ
	CByte_Attack_Range *pByte_Attack_Range = nullptr;

	// nullcheck
	if (pByte_Attack_Range == nullptr)
	{
		// メモリ確保
		pByte_Attack_Range = new CByte_Attack_Range;

		// !nullcheck
		if (pByte_Attack_Range != nullptr)
		{
			// 初期化処理
			pByte_Attack_Range->Init(pos, size);
		}
	}
	// ポインタを返す
	return pByte_Attack_Range;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CByte_Attack_Range::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化
	CScene3D::Init(pos, size);

	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_RED));

	// 色設定
	SetColor(COL);

	// 透過値設定
	SetAlpha(true);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Attack_Range::Uninit(void)
{
	// 終了処理
	CScene3D::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Attack_Range::Update(void)
{
	// インクリメント
	m_nCount++;

	// 色
	D3DXCOLOR col = GetColor();

	// falseの場合
	if (m_bAddColor == false)
	{
		// 減算
		col.a -= ADD_COL;

		// 最小以下の場合
		if (col.a < COL_MIN)
		{
			// 最小値に
			col.a = COL_MIN;

			// trueに
			m_bAddColor = true;
		}
	}
	// trueの場合
	if (m_bAddColor == true)
	{
		// 増算
		col.a += ADD_COL;

		// 最小以下の場合
		if (col.a > COL_MAX)
		{
			// 最小値に
			col.a = COL_MAX;

			// trueに
			m_bAddColor = false;
		}
	}

	// 色設定
	SetColor(col);

	// 265になったら
	if (m_nCount >= ATTACK_KEY)
	{
		// 当たり判定処理
		Collision();

		// 終了
		Uninit();
		return;
	}
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Attack_Range::Draw(void)
{
	// 描画処理
	CScene3D::Draw();
}
//=============================================================================
// 当たり判定処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Attack_Range::Collision(void)
{
	// プレイヤーのポインタ取得
	CPlayer * pPlayer = GET_PLAYER_PTR;

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// 位置取得
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

		// サイズ取得
		D3DXVECTOR3 PlayerSize = pPlayer->GetSize();

		// 矩形判定
		if (PlayerPos.x - (PlayerSize.x / 2) < pos.x + (size.x / 2) &&
			PlayerPos.x + (PlayerSize.x / 2) > pos.x - (size.x / 2) &&
			PlayerPos.z - (PlayerSize.z / 2) < pos.z + (size.z / 2) &&
			PlayerPos.z + (PlayerSize.z / 2) > pos.z - (size.z / 2))
		{
			// ヒット
			pPlayer->Hit(DAMAGE);
		}
	}
}