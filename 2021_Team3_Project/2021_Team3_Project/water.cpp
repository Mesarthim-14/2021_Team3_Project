//=============================================================================
//
// 地面フィールドクラス [ground.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "water.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"
#include "game.h"
#include "manager.h"
#include "light.h"
#include "game.h"
#include "camera.h"
#include "player.h"
#include "wave.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define WATER_WIDTH					(150)			// 分割数
#define WATER_HEIGHT				(150)			// 分割数
#define WATER_WIDTH_SIZE			(120000.0f)		// サイズ
#define WATER_HEIGHT_SIZE			(120000.0f)		// サイズ

#define WATER_GRAVITY				(0.01f)			// 水に掛かる重力
#define WAVE_TIME_INTER				(1.0f)			// 波の速度
#define WAVE_HEIGHT					(30)			// 波の間隔 30
#define WATER_POWER					(1.2f)			// 振れ幅 5.0f

//=========================================================================
// 静的変数の初期化
//=========================================================================
LPD3DXEFFECT CWater::m_pEffect = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CWater::CWater(PRIORITY Priority) : CMeshField(Priority)
{
	D3DXMatrixIdentity(&m_mtxWorld);
	m_fFileTime = 0.0f;
	m_pWave = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CWater::~CWater()
{
}

//=============================================================================
// ポリゴン生成
//=============================================================================
CWater * CWater::Create(void)
{
	// メモリ確保
	CWater *pWater = new CWater;

	// nullchack
	if (pWater != nullptr)
	{
		// 初期化処理
		pWater->Init();
	}

	return pWater;
}

//=============================================================================
// シェーダ生成
//=============================================================================
HRESULT CWater::LoadShaderFile(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;
	ID3DXBuffer *error = 0;

	// エフェクトファイルの読み込み
	D3DXCreateEffectFromFile(pDevice, "hlsl.fx", NULL, NULL,
		0, NULL, &m_pEffect, &error);

	return S_OK;
}

//=============================================================================
// シェーダファイルのアンロード
//=============================================================================
void CWater::UnLoadShaderFile(void)
{
	// シェーダエフェクト
	if (m_pEffect)
	{
		m_pEffect->Release();
		m_pEffect = nullptr;
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CWater::Init(void)
{
	// 情報の設定
	D3DXVECTOR3 size = D3DXVECTOR3(WATER_WIDTH_SIZE, 0.0f, WATER_HEIGHT_SIZE);
	INT_VERTEX_2D PieceNum = { WATER_WIDTH , WATER_HEIGHT };

	// メッシュ情報の設定
	SetInfo(size, PieceNum);

	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	m_pNoiseVolumeTexture = pTexture->GetVolumeTexture(CTexture::VOLUME_TEX_NOISE);
	m_pEnvironmentTexture = pTexture->GetCubeTexture(CTexture::CUBE_TEX_OCEAN);

	// 頂点の設定
	CreateVerterx();
	
	// nullcheck
	if (!m_pWave)
	{
		// インスタンス生成
		m_pWave = CWave::Create(WAVE_TIME_INTER, WATER_POWER, WAVE_HEIGHT);
	}

	// マトリクスの設定
	SetMatrix();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CWater::Uninit(void)
{
	// 波の揺れ
	if (m_pWave)
	{
		delete m_pWave;
		m_pWave = nullptr;
	}

	// 終了処理
	CMeshField::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CWater::Update(void)
{
	if (m_pWave)
	{
		// 波の処理
		Wave();
		m_pWave->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CWater::Draw(void)
{
	// nullcheck
	if (m_pEffect)
	{
		LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;	//デバイス情報の取得
		D3DXMATRIXA16 matSuimen;							// 水面の描画
		D3DXMATRIX mtxRot, mtxTrans, mtxScale;				// マトリクス

		// レンダーステートの設定
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			// 裏面を（左回り）をカリング

		//ワールドマトリックスの初期化	
		D3DXMatrixIdentity(&m_mtxWorld);

		m_pEffect->OnResetDevice();

		// ライトの方向
		D3DXVECTOR3 LightDir = CManager::GetModePtr()->GetLight()->GetLightDir();
		m_pEffect->SetValue("lightDir1", (void*)(FLOAT*)&D3DXVECTOR3(0.577f, -0.577f, 0.577f), sizeof(D3DXVECTOR3));

		// カメラ位置をセット
		D3DXVECTOR3 CameraPos = CManager::GetModePtr()->GetCamera()->GetposV();
		D3DXMATRIX matView = CManager::GetModePtr()->GetCamera()->GetMtxView();
		D3DXMATRIX matProj = CManager::GetModePtr()->GetCamera()->GetMtxProj();
		m_pEffect->SetValue("CameraPos", (void*)(FLOAT*)CameraPos, sizeof(D3DXVECTOR3));

		// プライヤーの座標
		D3DXVECTOR3 PlayerPos = CManager::GetModePtr()->GetPlayer()->GetPos();
		m_pEffect->SetValue("PlayerPos", (void*)(FLOAT*)CameraPos, sizeof(D3DXVECTOR3));

		D3DXMatrixIdentity(&matSuimen);

		// 水面回転を反映
		D3DXVECTOR3 rot = GetRot();
		D3DXMatrixRotationYawPitchRoll(
			&mtxRot,
			rot.y,
			rot.x,
			rot.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// 水面の中心とプレイヤーの中心
		D3DXVECTOR3 pos = GetPos();
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// マトリクスの設定
		D3DXMatrixMultiply(&matSuimen, &matSuimen, &m_mtxWorld);

		// 行列を設定 
		D3DXMATRIX matWorldViewProj = matSuimen * matView * matProj;
		D3DXMATRIX matWorldPlayer = m_MatPlayer * matView * matProj;

		// シェーダに値を渡す
		m_pEffect->SetValue("WorldViewProjectionPlayer", (void*)(FLOAT*)matWorldPlayer, sizeof(D3DXMATRIX));
		m_pEffect->SetValue("WorldViewProjection", (void*)(FLOAT*)matWorldViewProj, sizeof(D3DXMATRIX));
		m_pEffect->SetValue("LightDirection", (void*)(FLOAT*)D3DXVECTOR3(-1, 1, -1), sizeof(D3DXVECTOR3));
		m_pEffect->SetValue("DiffuseColor", (void*)(FLOAT*)D3DXVECTOR4(0.7f, 0.7f, 0.7f, 0.7f), sizeof(D3DXVECTOR4));

		// タイムを送る
		m_pEffect->SetFloat("Time", m_fFileTime);
		m_fFileTime += 0.01f;

		// そのテクニックだけに必要なパラメーターを設定
		m_pEffect->SetValue("NoiseTex", (void*)&m_pNoiseVolumeTexture, sizeof(LPDIRECT3DBASETEXTURE9));
		m_pEffect->SetValue("skyBoxTex", (void*)&m_pEnvironmentTexture, sizeof(LPDIRECT3DBASETEXTURE9));

		// テクニックを設定
		D3DXHANDLE hTechnique = m_pEffect->GetTechniqueByName("Ocean");
		UINT numPasses;
		m_pEffect->SetTechnique(hTechnique);
		m_pEffect->Begin(&numPasses, 0);

		for (UINT nCount = 0; nCount < numPasses; nCount++)
		{
			m_pEffect->BeginPass(nCount);

			// 頂点の数
			LPDIRECT3DVERTEXBUFFER9 VtxBuff = GetVtxBuff();
			LPDIRECT3DINDEXBUFFER9 IdxBuff = GetIdxBuff();
			int nNumVertex = GetNumVertex();
			int nNumPolygon = GetNumPolygon();

			// 頂点バッファをデータストリームにバインド
			pDevice->SetStreamSource(0, VtxBuff,
				0, sizeof(VERTEX_3D));

			// インデックスバッファをデータストリームにバインド
			pDevice->SetIndices(IdxBuff);

			// 頂点情報
			pDevice->SetFVF(FVF_VERTEX_3D);

			// ポリゴンの描画
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,
				0,
				0,
				nNumVertex,
				0,
				nNumPolygon);

			m_pEffect->EndPass();
		}

		m_pEffect->End();
	}
}

//=============================================================================
// 波の処理
//=============================================================================
void CWater::Wave(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();		// バッファ
	VERTEX_3D *pVtx = nullptr;

	// メッシュ情報取得
	D3DXVECTOR3 OneSize = GetOneSize();
	D3DXVECTOR3 AllSize = GetSize();
	INT_VERTEX_2D PieceNum = GetPieceNum();

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 横のカウント
	for (int nCntV = 0; nCntV < PieceNum.x + 1; nCntV++)
	{
		// 縦のカウント
		for (int nCntH = 0; nCntH < PieceNum.y + 1; nCntH++)
		{
			// 頂点の変更
			pVtx[(nCntV * (PieceNum.y + 1)) + nCntH].pos.y += m_pWave->Wave(nCntV, nCntH);
		}
	}

	// 頂点データをアンロックする
	pVtxBuff->Unlock();

	// 頂点バッファの設定
	BindVtxBuff(pVtxBuff);
}

//=============================================================================
// マトリクスの設定
//=============================================================================
void CWater::SetMatrix(void)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	// 水面回転を反映
	D3DXVECTOR3 rot = GetRot();
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 水面の中心とプレイヤーの中心
	D3DXVECTOR3 pos = GetPos();
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	// 水面の中心とプレイヤーの中心
	D3DXMatrixTranslation(&m_MatPlayer,
		-10000.0f, 0.0f, 5000.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// マトリクスの設定
	D3DXMatrixMultiply(&m_MatPlayer, &m_MatPlayer, &m_mtxWorld);
}