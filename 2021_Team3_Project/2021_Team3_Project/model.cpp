//=============================================================================
//
// モデルクラス処理 [model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "game.h"
#include "xfile.h"
#include "shadow.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ALPHA_NUM_MAX		(1.0f)		// 透明度の最大数

//=============================================================================
// コンストラクタ
//=============================================================================
CModel::CModel(PRIORITY Priority) : CScene(Priority)
{
	m_pos = ZeroVector3;
	m_rot = ZeroVector3;
	m_move = ZeroVector3;
	m_size = ZeroVector3;
	m_scale = MODEL_DEFAULT_SIZE;
	m_apTexture = nullptr;
	m_nTexPattern = 0;
	m_nLife = 0;
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fAlphaNum = 0.0f;
	m_pShadow = nullptr;
	m_State = STATE_NORMAL;
	m_RayData = { ZERO_FLOAT,ZERO_FLOAT,ZERO_INT };
}

//=============================================================================
// デストラクタ
//=============================================================================
CModel::~CModel()
{
}

//=============================================================================
// クリエイト処理
//=============================================================================
CModel * CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//モデルクラスのポインタ変数
	CModel *pModel = nullptr;

	//メモリ確保
	pModel = new CModel;

	// nullcheck
	if (pModel != nullptr)
	{
		//初期化処理呼び出し
		pModel->Init(pos, rot);
	}
	//メモリ確保に失敗したとき
	else
	{
		return nullptr;
	}

	return pModel;
}

//=============================================================================
//モデルクラスの初期化処理
//=============================================================================
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 位置の初期化
	m_pos = pos;

	// サイズ初期化
	m_rot = rot;

	return S_OK;
}

//=============================================================================
//モデルクラスの終了処理
//=============================================================================
void CModel::Uninit(void)
{
	//オブジェクトの破棄
	Release();

	// 影の終了処理
	HasPtrDelete();
}

//=============================================================================
// モデルクラスの更新処理
//=============================================================================
void CModel::Update(void)
{
	// 寿命を減らす
	m_nLife--;

	// 座標の更新
	m_pos += m_move;
}

//=============================================================================
// モデルクラスの描画処理
//=============================================================================
void CModel::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	D3DMATERIAL9 matDef;					//現在のマテリアル保持用

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 拡大率を反映
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得する
	pDevice->GetMaterial(&matDef);

	D3DXMATERIAL*pMat;		//マテリアルデータへのポインタ

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_Model.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_Model.dwNumMat; nCntMat++)
	{
		//マテリアルのアンビエントにディフューズカラーを設定
		pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (m_Model.apTexture[nCntMat] != nullptr)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, m_Model.apTexture[nCntMat]);
		}
		else
		{
			pDevice->SetTexture(0, nullptr);
		}
		
		//モデルパーツの描画
		m_Model.pMesh->DrawSubset(nCntMat);

		pDevice->SetTexture(0, nullptr);
	}

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	// 影の描画
	ShadowDraw(m_rot);
}

//=============================================================================
// 影の描画
//=============================================================================
void CModel::ShadowDraw(D3DXVECTOR3 rot)
{
	if (m_pShadow)
	{
		// 影の生成
		m_pShadow->CreateShadow(m_rot, ZeroVector3, m_mtxWorld);

		// 影の描画処理
		m_pShadow->VolumeDraw();
	}
}

//=============================================================================
// モデル情報の設定
//=============================================================================
void CModel::HasPtrDelete(void)
{
	if (m_pShadow)
	{
		// 影の終了処理
		m_pShadow->Uninit();
		delete m_pShadow;
		m_pShadow = nullptr;
	}
}

//=============================================================================
// モデル情報の設定
//=============================================================================
void CModel::BindModel(CXfile::MODEL model)
{
	m_Model.pMesh = model.pMesh;
	m_Model.pBuffMat = model.pBuffMat;
	m_Model.dwNumMat = model.dwNumMat;
	m_Model.apTexture = model.apTexture;
}

//=============================================================================
// 影の設定
//=============================================================================
void CModel::SetShadowInfo(CXfile::MODEL model)
{
	// nullcheck
	if (!m_pShadow)
	{
		// 影の生成
		m_pShadow = CShadow::Create(model.pMesh);
	}
}

//=============================================================================
// 透明度の減算
//=============================================================================
void CModel::SubAlpha(float fAlpha)
{
	if (m_fAlphaNum < ALPHA_NUM_MAX)
	{
		m_fAlphaNum += fAlpha;
	}
	else
	{
		m_fAlphaNum = ALPHA_NUM_MAX;
	}
}