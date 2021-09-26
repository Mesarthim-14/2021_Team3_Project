//=============================================================================CShadow
//
// シャドウクラス [shadow.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "game.h"
#include "light.h"
#include "shadow_volume.h"
#include "shadow_polygon.h"

//=============================================================================
// static初期化
//=============================================================================
CShadowPolygon *CShadow::m_pPolygon = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CShadow::CShadow()
{
	m_pShadowVolume = nullptr;
	D3DXMatrixIdentity(&m_ModelMtxWorld);
}

//=============================================================================
// デストラクタ
//=============================================================================
CShadow::~CShadow()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CShadow * CShadow::Create(LPD3DXMESH pSrcMesh)
{
	// メモリ確保
	CShadow *pShadow = new CShadow;

	// !nullcheck
	if (pShadow)
	{
		// 初期化処理
		pShadow->Init(pSrcMesh);
	}

	return pShadow;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CShadow::Init(LPD3DXMESH pSrcMesh)
{
	// nullcheck
	if (!m_pShadowVolume)
	{
		// 影の生成
		m_pShadowVolume = CShadowVolume::Create(pSrcMesh);
	}

	// nullcheck
	if (!m_pPolygon)
	{
		m_pPolygon = CShadowPolygon::Create();
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CShadow::Uninit(void)
{
	if (m_pShadowVolume)
	{
		// シャドウボリューム終了処理
		m_pShadowVolume->Uninit();
		delete m_pShadowVolume;
		m_pShadowVolume = nullptr;
	}
}

//=============================================================================
// 影の描画処理
//=============================================================================
void CShadow::VolumeDraw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

	// レンダラーポインタ取得
	CRenderer *pRenderer = CManager::GetRenderer();

	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_ModelMtxWorld);

	// シャドウの描画
	if (m_pShadowVolume)
	{
		// ステンシル設定
		pRenderer->SetStateStencil();

		// シャドウボリュームの描画
		m_pShadowVolume->Draw();

		// 状態を元に戻す
		pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
	}
}

//=============================================================================
// 影の生成処理
//=============================================================================
void CShadow::CreateShadow(D3DXVECTOR3 rot, D3DXVECTOR3 ShipRot, D3DXMATRIX ModelMtxWorld)
{
	// 影の生成
	if (m_pShadowVolume)
	{
		m_pShadowVolume->CreateShadow(rot, ShipRot);
	}

	// ワールド座標を受け取る
	m_ModelMtxWorld = ModelMtxWorld;
}

//=============================================================================
// 影の生成処理
//=============================================================================
void CShadow::CreateShadow(D3DXVECTOR3 rot, D3DXMATRIX ModelMtxWorld)
{
	// 影の生成
	if (m_pShadowVolume)
	{
		m_pShadowVolume->CreateShadow(rot);
	}

	// ワールド座標を受け取る
	m_ModelMtxWorld = ModelMtxWorld;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CShadow::PolygonUninit(void)
{
	if (m_pPolygon)
	{
		// ポリゴン終了処理
		m_pPolygon->Uninit();
		m_pPolygon = nullptr;
	}
}