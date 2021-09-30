//=============================================================================
// プレイヤーのライフ [player_lufe.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "game.h"
#include "player.h"
#include "player_life.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define MIN_LIFE	(0)								// ライフの最小
#define MUT_2		(2.0f)							// ×2		
#define LENGTH		(70.0f)							// 半径
#define ROT			(D3DXToRadian(-3.6f * nCnt))	// 向き
#define SIZE		(D3DXVECTOR3(20.0f,20.0f,0.0f))	// サイズ
#define RED			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))// 赤色
#define BLACK		(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))// 黒色
#define ANGLE_90	(D3DXToRadian(90.0f))			// 角度90
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Life::CPlayer_Life(PRIORITY Priority) : CScene(Priority)
{
	memset(m_apScene2d, 0, sizeof(m_apScene2d));
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Life::~CPlayer_Life()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Life * CPlayer_Life::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPlayer_Lifeのポインタ
	CPlayer_Life *pPlayer_Life = nullptr;

	// nullcheck
	if (pPlayer_Life == nullptr)
	{
		// メモリ確保
		pPlayer_Life = new CPlayer_Life(PRIORITY_UI);

		// !nullcheck
		if (pPlayer_Life != nullptr)
		{
			// 位置
			pPlayer_Life->Init(pos, size);
		}
	}
	// ポインタを返す
	return pPlayer_Life;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CPlayer_Life::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 最大数分繰り返す
	for (int nCnt = MIN_LIFE; nCnt < MAX_LIFE; nCnt++)
	{
		// 弧度
		float fRadian = (float)nCnt / MAX_LIFE;

		// 弧度計算
		fRadian = fRadian * D3DX_PI * MUT_2;

		// 位置座標
		D3DXVECTOR3 Life_pos = ZeroVector3;

		// 座標を求める
		Life_pos.x = pos.x - cosf(fRadian - ANGLE_90) * LENGTH;
		Life_pos.y = pos.y + sinf(fRadian - ANGLE_90) * LENGTH;

		// 生成
		m_apScene2d[nCnt] = CScene2D::Create(Life_pos, SIZE);

		// 向きの設定
		m_apScene2d[nCnt]->SetRotation(ROT);

		// 位置
		m_apScene2d[nCnt]->SetCol(RED);

	}
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Life::Uninit(void)
{
	// 最大数繰り返す
	for (int nCnt = MIN_LIFE; nCnt < MAX_LIFE; nCnt++)
	{
		// !nullcheck
		if (m_apScene2d[nCnt] != nullptr)
		{
			// 終了
			m_apScene2d[nCnt]->Uninit();

			// nullptrに
			m_apScene2d[nCnt] = nullptr;
		}
	}

	// 破棄
	Release();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Life::Update(void)
{
	// CPlayerのポインタ
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// ダメージを食らっていたら
		if (pPlayer->GetHitFlag() == true)
		{
			// ライフ取得
			int nLife = pPlayer->GetLife();

			// 最大数分繰り返す
			for (int nCnt = MIN_LIFE; nCnt < MAX_LIFE; nCnt++)
			{
				// nLife以下の場合
				if (nCnt <= nLife)
				{
					// 位置
					m_apScene2d[nCnt]->SetCol(RED);
				}
				// nLifeより大きい場合
				if (nCnt > nLife)
				{
					// 位置
					m_apScene2d[nCnt]->SetCol(BLACK);
				}
			}

			// プレイヤーのフラグ変更
			pPlayer->SetHitFlag(false);
		}
	}
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Life::Draw(void)
{
}