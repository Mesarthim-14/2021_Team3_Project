//=============================================================================
//
// 3Dメッシュ生成クラス [mesh_3d.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "mesh_3d.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MESH_3D_FILENAME		("data/Text/mesh_3d.txt")

//=============================================================================
// 前方宣言
//=============================================================================
CMesh3d::MESH_3D CMesh3d::m_Mesh3D[MESH_TYPE_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CMesh3d::CMesh3d(PRIORITY Priority) :CSceneBase(Priority)
{
	m_pIdxBuff = nullptr;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nNumVertex = 0;
	m_nNumIndex = 0;
	m_nNumPolygon = 0;
	m_OneSize = ZeroVector2;
	m_MeshNum = MESH_TYPE_NONE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMesh3d::~CMesh3d()
{
	// インデックスバッファの開放
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CMesh3d::Draw(void)
{
	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXVECTOR3 rot = GetRot();
	D3DXMatrixRotationYawPitchRoll(
		&mtxRot,
		rot.y,
		rot.x,
		rot.z);

	D3DXMatrixMultiply(
		&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// 位置を反映
	D3DXVECTOR3 pos = GetPos();
	D3DXMatrixTranslation(
		&mtxTrans,
		pos.x,
		pos.y,
		pos.z);

	D3DXMatrixMultiply(
		&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームにバインド
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームにバインド
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// 頂点フォーマットの設定
	pDevice->SetTexture(0, GetTexture());

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);

	// 頂点フォーマットの設定
	pDevice->SetTexture(0, nullptr);
}

//=============================================================================
// ファイル読み込み
//=============================================================================
HRESULT CMesh3d::ReadFile(void)
{
	FILE *pFile = nullptr;		//FILEポインタ
	char aHeadData[1024];
	char aParticleName[1024];
	int nParticleIndex = 0;	// モデルのインデックス

							// ファイルオープン
	pFile = fopen(MESH_3D_FILENAME, "r");

	if (pFile != nullptr)
	{
		do
		{
			//一列読み込んでモード情報を抽出
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aParticleName);

			if (strcmp(aParticleName, "MESH3DSET") == 0)
			{
				//インデックスを最初に戻す
				nParticleIndex = 0;

				//END_MOTIONSETを読み込むまで繰り返す
				while (strcmp(aParticleName, "END_MESH3DSET") != 0)
				{
					//一列読み込んでモード情報を抽出
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aParticleName);

					if (strcmp(aParticleName, "MESHSET") == 0)
					{
						//END_PARTSSETを読み込むまで繰り返す
						while (strcmp(aParticleName, "END_MESHSET") != 0)
						{
							//一列読み込んでモード情報を抽出
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aParticleName);

							if (strcmp(aParticleName, "WIDTH") == 0)
							{
								// サイズの設定
								sscanf(aHeadData, "%*s %*s %d", &m_Mesh3D[nParticleIndex].CylinderNum.nNumX);
							}
							if (strcmp(aParticleName, "HEIGHT") == 0)
							{
								// サイズの設定
								sscanf(aHeadData, "%*s %*s %d", &m_Mesh3D[nParticleIndex].CylinderNum.nNumY);
							}

							if (strcmp(aParticleName, "SIZE") == 0)
							{
								// サイズの設定
								sscanf(aHeadData, "%*s %*s %f %f",
									&m_Mesh3D[nParticleIndex].size.x,
									&m_Mesh3D[nParticleIndex].size.y);
							}
						}

						//インデックスを１つ進める
						nParticleIndex++;
					}
				}
			}

		} while (strcmp(aParticleName, "END_SCRIPT") != 0);

		//ファイルクローズ
		fclose(pFile);

		return S_OK;
	}
	else
	{
		//失敗した場合メッセージボックスを表示
		MessageBox(nullptr, "メッシュファイルを開くのに失敗しました", "警告", MB_OK | MB_ICONEXCLAMATION);

		return	E_FAIL;
	}
}