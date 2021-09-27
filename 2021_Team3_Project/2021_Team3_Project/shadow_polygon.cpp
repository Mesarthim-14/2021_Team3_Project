//=============================================================================CShadowPolygon
//
// シャドウポリゴンクラス [shadow_polygon.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "game.h"
#include "light.h"
#include "shadow_polygon.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CShadowPolygon::CShadowPolygon(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CShadowPolygon::~CShadowPolygon()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CShadowPolygon * CShadowPolygon::Create(void)
{
	// メモリ確保
	CShadowPolygon *pPolygon = new CShadowPolygon(PRIORITY_SHADOW);

	// !nullcheck
	if (pPolygon)
	{
		// 初期化処理
		pPolygon->Init();

		return pPolygon;
	}

	return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CShadowPolygon::Init(void)
{
	// 初期化処理
	CScene2D::Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	// 色の設定
	SetCol(D3DCOLOR_RGBA(0, 0, 0, 0x7f));

	return S_OK;
}

//=============================================================================
// 影の描画
//=============================================================================
void CShadowPolygon::Draw(void)
{
	// レンダラーポインタ取得
	CRenderer *pRenderer = CManager::GetRenderer();

	// ステンシルテスト
	pRenderer->SetStencilTest();

	// ポリゴンの描画
	CScene2D::Draw();

	// ステンシルリセット
	pRenderer->ReSetStateStencil();
}