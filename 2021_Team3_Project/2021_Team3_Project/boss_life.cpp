//=============================================================================
// ボスライフゲージ [boss_life.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "boss_life_back.h"
#include "boss_life.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define POS			(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.05f,0.0f))	// サイズ
#define SIZE		(D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.025f,0.0f))	// サイズ
#define COL			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))								// 色
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Life::CBoss_Life(PRIORITY nPriority) : CGage_2D(nPriority)
{
	m_pEnemy = nullptr;
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Life::~CBoss_Life()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Life * CBoss_Life::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy * pEnemy)
{
	// CBoss_Lifeのポインタ
	CBoss_Life * pBoss_Life = nullptr;

	// nullcheck
	if (pBoss_Life == nullptr)
	{
		// メモリ確保
		pBoss_Life = new CBoss_Life;

		// !nullcheck
		if (pBoss_Life != nullptr)
		{
			// 代入
			pBoss_Life->m_pEnemy = pEnemy;

			// 初期化処理
			pBoss_Life->Init(POS, SIZE);
		}
	}
	// ポインタを返す
	return pBoss_Life;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBoss_Life::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ライフ取得
	int nLife = m_pEnemy->GetLife();

	// ライフの最大値設定
	SetMaxGageNum(nLife);

	// 初期化処理
	CGage_2D::Init(pos, size);

	// ライフの値設定
	SetGageNum(nLife);

	// 色設定
	SetColor(COL);

	// 位置設定
	SetPosition(pos);

	// ライフ背景生成
	CBoss_Life_Back::Create(pos, SIZE, m_pEnemy);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Life::Uninit(void)
{
	// !nullcheck
	if (m_pEnemy != nullptr)
	{
		// nullptrに
		m_pEnemy = nullptr;
	}

	// 終了処理
	CGage_2D::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Life::Update(void)
{
	// 更新処理
	CGage_2D::Update();

	// ヒット判定取得
	bool bHit = m_pEnemy->GetHit();

	// trueの場合
	if (bHit == true)
	{
		// ライフ取得
		int nLife = m_pEnemy->GetLife();

		// ゲージの値設定
		SetGageNum(nLife);

		// ライフ取得
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
void CBoss_Life::Draw(void)
{
	// 更新処理
	CGage_2D::Draw();
}