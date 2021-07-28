//=============================================================================
// 岩 [rock.cpp]
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
#include "model_box.h"
#include "game.h"
#include "player.h"
#include "rock.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define GRAVITY		(0.1f)									// 重力
#define SIZE		(D3DXVECTOR3 (1400.0f,1400.0f,1400.0f))	// サイズ
#define POS_Y_MIN	(0.0f)									// Y座標最小値
#define MIN_MOVE	(D3DXVECTOR3(0.0f,0.0f,0.0f))			// 移動量の最小
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CRock::CRock(PRIORITY Priority) : CModel(Priority)
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CRock::~CRock()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CRock * CRock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CRockのポインタ
	CRock *pRock = nullptr;

	// nullcheck
	if (pRock == nullptr)
	{
		// メモリ確保
		pRock = new CRock;

		// !nullcheck
		if (pRock != nullptr)
		{
			// 初期化処理
			pRock->Init(pos, rot);

			// 箱生成
			CModel_Box::Create(pos, rot, pRock);
		}
	}
	// ポインタを返す
	return pRock;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CRock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_ROCK);

		// モデルの情報を渡す
		BindModel(model);
	}

	// サイズ設定
	SetSize(SIZE);

	// 初期化処理
	CModel::Init(pos, ZeroVector3);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CRock::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CRock::Update(void)
{
	// 更新処理
	CModel::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CRock::Draw(void)
{
	// 描画処理
	CModel::Draw();
}