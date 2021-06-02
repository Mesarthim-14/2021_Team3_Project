//=============================================================================
//
// 階層構造用のモデルクラス処理 [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "modelanime.h"
#include "manager.h"
#include "renderer.h"
#include "resource_manager.h"
#include "xfile.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CModelAnime::CModelAnime()
{
	//各メンバ変数のクリア
	memset(&m_model, 0, sizeof(m_model));
	m_pos = ZeroVector3;
	m_rot = ZeroVector3;
	m_posAnime = ZeroVector3;
	m_rotAnime = ZeroVector3;
	m_pParent = nullptr;
	ZeroMemory(m_OldMtxWorld, sizeof(m_OldMtxWorld));
	ZeroMemory(m_mtxWorld, sizeof(m_mtxWorld));
}

//=============================================================================
// デストラクタ
//=============================================================================
CModelAnime::~CModelAnime()
{
}

//=============================================================================
// クリエイト処理
//=============================================================================
CModelAnime * CModelAnime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//階層モデルクラスのポインタ変数
	CModelAnime *pModelAnime = nullptr;

	//インスタンス生成
	pModelAnime = new CModelAnime;

	// !nullcheck
	if (pModelAnime != nullptr)
	{
		//初期化処理呼び出し
		pModelAnime->Init(pos, rot);
	}
	//失敗していた場合
	else
	{
		return nullptr;
	}

	return pModelAnime;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CModelAnime::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//位置の設定
	m_pos = pos;

	//向きの設定
	m_rot = rot;

	return S_OK;
}

//=============================================================================
// 描画処理
//=============================================================================
void CModelAnime::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxParent;
	D3DMATERIAL9 matDef;						//現在のマテリアル保持用
	D3DXMATERIAL*pMat;							//マテリアルデータへのポインタ

	// 剣の軌跡の古いデータ
	m_OldMtxWorld1[4] = m_OldMtxWorld1[3];
	m_OldMtxWorld1[3] = m_OldMtxWorld1[2];
	m_OldMtxWorld1[2] = m_OldMtxWorld1[1];
	m_OldMtxWorld1[1] = m_OldMtxWorld1[0];
	m_OldMtxWorld1[0] = m_OldMtxWorld;
	m_OldMtxWorld = m_mtxWorld;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//アニメーションの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotAnime.y, m_rotAnime.x, m_rotAnime.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//アニメーションの位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_posAnime.x, m_posAnime.y, m_posAnime.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//親が存在する場合
	if (m_pParent != nullptr)
	{
		//親情報を設定
		mtxParent = m_pParent->GetMtxWorld();
	}
	//親が存在しない場合
	else
	{
		//デバイス情報を設定
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//親のマトリクスと掛け合わせる
	m_mtxWorld *= mtxParent;

	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得する
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_model.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_model.dwNumMat; nCntMat++)
	{
		//マテリアルのアンビエントにディフューズカラーを設定
		pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (m_model.apTexture[nCntMat] != nullptr)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, m_model.apTexture[nCntMat]);
		}
		else
		{
			// テクスチャ設定
			pDevice->SetTexture(0, nullptr);
		}

		//モデルパーツの描画
		m_model.pMesh->DrawSubset(nCntMat);

		// 透明度戻す
		pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
	}

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
//階層モデルクラスの親情報の設定処理
//=============================================================================
void CModelAnime::SetParent(CModelAnime * pParent)
{
	m_pParent = pParent;
}

//=============================================================================
//階層モデルクラスの位置設定処理
//=============================================================================
void CModelAnime::SetPosAnime(const D3DXVECTOR3 posAnime)
{
	m_posAnime = posAnime;
}

//=============================================================================
//モデル情報を取得
//=============================================================================
void CModelAnime::SetModel(CXfile::MODEL model)
{
	m_model = model;
}

//=============================================================================
//階層モデルクラスの位置取得処理
//=============================================================================
D3DXVECTOR3 CModelAnime::GetPos(void) const
{
	return m_pos;
}

//=============================================================================
//階層モデルクラスのアニメーション位置の取得
//=============================================================================
D3DXVECTOR3 CModelAnime::GetPosAnime(void) const
{
	return m_posAnime;
}

//=============================================================================
//階層モデルクラスの向きの設定処理
//=============================================================================
void CModelAnime::SetRotAnime(const D3DXVECTOR3 rotAnime)
{
	m_rotAnime = rotAnime;
}

//=============================================================================
//階層モデルクラスの向きの取得処理
//=============================================================================
D3DXVECTOR3 CModelAnime::GetRot(void) const
{
	return m_rot;
}

//=============================================================================
//階層モデルクラスのアニメーション向きの取得
//=============================================================================
D3DXVECTOR3 CModelAnime::GetRotAnime(void) const
{
	return m_rotAnime;
}

//=============================================================================
//階層モデルクラスのマトリクス情報の取得処理
//=============================================================================
D3DXMATRIX CModelAnime::GetMtxWorld(void)
{
	return m_mtxWorld;
}

//=============================================================================
// 古い座標の情報
//=============================================================================
D3DXMATRIX CModelAnime::GetOldMtxWorld(void)
{
	return m_OldMtxWorld;
}