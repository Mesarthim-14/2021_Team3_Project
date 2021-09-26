//=============================================================================
// タイトルマップ [title_map.cpp]
// Author : Konishi Yuuto
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Konishi Yuuto
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "renderer.h"
#include "game.h"
#include "model.h"
#include "title_map.h"

//=============================================================================
// マクロ定義
// Author : Konishi Yuuto
//=============================================================================
#define POS		(D3DXVECTOR3(-100000.0f, 0.0f, -15000.0f))
#define ROT		(D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f))

//=============================================================================
// コンストラクタ
// Author : Konishi Yuuto
//=============================================================================
CTitleMap::CTitleMap(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// インクルードファイル
// Author : Konishi Yuuto
//=============================================================================
CTitleMap::~CTitleMap()
{
}

//=============================================================================
// インクルードファイル
// Author : Konishi Yuuto
//=============================================================================
CTitleMap * CTitleMap::Create(void)
{
	// CBulletのポインタ
	CTitleMap *pMap = new CTitleMap;

	// !nullcheck
	if (pMap != nullptr)
	{
		// 初期化処理
		pMap->Init(POS, ROT);

		// ポインタを返す
		return pMap;
	}

	return nullptr;
}

//=============================================================================
// 初期化処理関数
// Author : Konishi Yuuto
//=============================================================================
HRESULT CTitleMap::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_TITLE_MAP);

		// モデルの情報を渡す
		BindModel(model);
	}

	// 初期化処理
	CModel::Init(pos, rot);

	return S_OK;
}