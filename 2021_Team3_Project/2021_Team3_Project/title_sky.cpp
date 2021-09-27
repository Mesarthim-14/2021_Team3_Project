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
#include "title_sky.h"

//=============================================================================
// マクロ定義
// Author : Konishi Yuuto
//=============================================================================
#define POS				(D3DXVECTOR3(5000.0f, 0.0f, -20000.0f))
#define ROT				(D3DXVECTOR3(0.0f, D3DXToRadian(45.0f), 0.0f))
#define SKY_SCALE_NUM	(25.0f)
#define SKY_SCALE		(D3DXVECTOR3(SKY_SCALE_NUM, SKY_SCALE_NUM, SKY_SCALE_NUM))

//=============================================================================
// コンストラクタ
// Author : Konishi Yuuto
//=============================================================================
CTitleSky::CTitleSky(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// インクルードファイル
// Author : Konishi Yuuto
//=============================================================================
CTitleSky::~CTitleSky()
{
}

//=============================================================================
// インクルードファイル
// Author : Konishi Yuuto
//=============================================================================
CTitleSky * CTitleSky::Create(void)
{
	// CBulletのポインタ
	CTitleSky *pSky = new CTitleSky;

	// !nullcheck
	if (pSky != nullptr)
	{
		// 初期化処理
		pSky->Init(POS, ROT);
		pSky->SetScale(SKY_SCALE);

		// ポインタを返す
		return pSky;
	}

	return nullptr;
}

//=============================================================================
// 初期化処理関数
// Author : Konishi Yuuto
//=============================================================================
HRESULT CTitleSky::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_TITLE_SKY);

		// モデルの情報を渡す
		BindModel(model);
	}

	// 初期化処理
	CModel::Init(pos, rot);

	return S_OK;
}

//=============================================================================
// 描画処理
// Author : Konishi Yuuto
//=============================================================================
void CTitleSky::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	// 描画処理
	CModel::Draw();

	// ライト効果を付ける
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}