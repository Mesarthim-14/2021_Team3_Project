//=============================================================================
// マップ [bullet.cpp]
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
#include "renderer.h"
#include "game.h"
#include "model.h"
#include "boss_map_transition.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Map_Transition::CBoss_Map_Transition(PRIORITY Priority) : CModel(Priority)
{

}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Map_Transition::~CBoss_Map_Transition()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Map_Transition * CBoss_Map_Transition::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CBoss_Map_Transitionのポインタ
	CBoss_Map_Transition *pMap = nullptr;

	// nullcheck
	if (pMap == nullptr)
	{
		// メモリ確保
		pMap = new CBoss_Map_Transition;

		// !nullcheck
		if (pMap != nullptr)
		{
			// 初期化処理
			pMap->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pMap;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBoss_Map_Transition::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル
		CXfile::MODEL model;

		// モデル情報取得
		model = pXfile->GetXfile(CXfile::XFILE_NUM_BOSS_MAP_TRANSITION);

		// モデルの情報を渡す
		BindModel(model);
	}

	// 初期化処理
	CModel::Init(pos, rot);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Map_Transition::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Map_Transition::Update(void)
{
	// 更新処理
	CModel::Update();

}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Map_Transition::Draw(void)
{
	// 描画処理
	CModel::Draw();
}