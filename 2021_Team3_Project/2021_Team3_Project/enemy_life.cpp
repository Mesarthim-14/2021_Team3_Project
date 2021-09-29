//=============================================================================
// 敵ライフゲージ [enemy_life.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "enemy_life.h"
#include "gage_3d_back.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define POS			(D3DXVECTOR3(pos.x,pos.y + size.y,pos.z))		// 位置
#define SIZE		(D3DXVECTOR3(800.0f,30.0f,0.0f))				// サイズ
#define COL			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))				// 色
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Life::CEnemy_Life(PRIORITY nPriority) : CGage_3D(nPriority)
{
	m_pEnemy		= nullptr;
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Life::~CEnemy_Life()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Life * CEnemy_Life::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy * pEnemy)
{
	// CEnemy_Lifeのポインタ
	CEnemy_Life * pEnemy_Life = nullptr;

	// nullcheck
	if (pEnemy_Life == nullptr)
	{
		// メモリ確保
		pEnemy_Life = new CEnemy_Life;

		// !nullcheck
		if (pEnemy_Life != nullptr)
		{
			// 代入
			pEnemy_Life->m_pEnemy = pEnemy;

			// 初期化処理
			pEnemy_Life->Init(pos, SIZE);

			// 背景生成
			CGage_3D_Back::Create(pos, size, pEnemy);
		}
	}
	// ポインタを返す
	return pEnemy_Life;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CEnemy_Life::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ライフ取得
	int nLife = m_pEnemy->GetLife();

	// ライフの最大値設定
	SetMaxGageNum(nLife);

	// 初期化処理
	CGage_3D::Init(pos, size);

	// ライフの値設定
	SetGageNum(nLife);

	// 色設定
	SetColor(COL);

	// アルファブレンド
	SetAlpha(true);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Life::Uninit(void)
{
	// !nullcheck
	if (m_pEnemy != nullptr)
	{
		// nullptrに
		m_pEnemy = nullptr;
	}

	// 終了処理
	CGage_3D::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Life::Update(void)
{
	// 更新処理
	CGage_3D::Update();

	// 位置取得
	D3DXVECTOR3 pos = m_pEnemy->GetPos();

	// サイズ取得
	D3DXVECTOR3 size = m_pEnemy->GetSize();

	// 位置設定
	SetPosition(POS);

	// ヒット判定取得
	bool bHit = m_pEnemy->GetHit();
	// trueの場合
	if (bHit == true)
	{
		// ライフ取得
		int nLife = m_pEnemy->GetLife();

		// ゲージの値設定
		SetGageNum(nLife);

		// ヒット設定
		m_pEnemy->SetHit(false);
	}
	// 死亡状態の場合
	if (m_pEnemy->GetState() == CEnemy::STATE_DEAD)
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
void CEnemy_Life::Draw(void)
{
	// 更新処理
	CGage_3D::Draw();
}