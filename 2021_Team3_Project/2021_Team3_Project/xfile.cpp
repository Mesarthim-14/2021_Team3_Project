//=============================================================================
//
// Xファイルの管理クラス [xfile.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "xfile.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CXfile::CXfile()
{
	memset(m_aXfile, 0, sizeof(m_aXfile));
	memset(m_pFileName, 0, sizeof(m_pFileName));
	memset(m_nMaxParts, 0, sizeof(m_nMaxParts));

	for (int nCount = 0; nCount < HIERARCHY_XFILE_NUM_MAX; nCount++)
	{
		// 初期化処理
		m_apHierarchyModel[nCount].clear();
	}

	for (int nCount = 0; nCount < HIERARCHY_XFILE_NUM_MAX; nCount++)
	{
		// 初期化処理
		m_apModelFile[nCount].clear();
	}

	// Xファイルネームを取得
	m_aXfileName =
	{
		{ "data/Model/Bullet/bullet.x" },		// 弾
		{ "data/Model/box/box.x" },				// 箱
		{"data/Model/Map/Map.x"},				// マップ
	};

	m_aHierarchyXfileName =
	{
		{ "data/Text/Player/motion_Player.txt" },		// プレイヤー
		{ "data/Text/Enemy/motion_Enemy_Ship.txt" },	// 敵船
	};
}

//=============================================================================
// デストラクタ
//=============================================================================
CXfile::~CXfile()
{
	m_aXfileName.clear();

	m_aHierarchyXfileName.clear();
}

//=============================================================================
// インスタンス生成
//=============================================================================
CXfile * CXfile::Create(void)
{
	// メモリ確保
	CXfile *pXfile = new CXfile;

	return pXfile;
}

//=============================================================================
// Xファイルロード
//=============================================================================
HRESULT CXfile::ModelLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (size_t nCount = 0; nCount < m_aXfileName.size(); nCount++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(m_aXfileName.at(nCount).data(),
			D3DXMESH_SYSTEMMEM,
			pDevice,
			nullptr,
			&m_aXfile[nCount].pBuffMat,
			nullptr,
			&m_aXfile[nCount].dwNumMat,
			&m_aXfile[nCount].pMesh);
	}

	for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
	{
		//マテリアル情報の解析
		D3DXMATERIAL *materials = (D3DXMATERIAL*)m_aXfile[nCount].pBuffMat->GetBufferPointer();
		LPDIRECT3DTEXTURE9 pTexture = nullptr;

		for (int nCntMat = 0; nCntMat < (int)m_aXfile[nCount].dwNumMat; nCntMat++)
		{
			// ファイルネームの取得
			char cData[128] = {};

			sprintf(cData, "data/model/Texture/%s", materials[nCntMat].pTextureFilename);

			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, cData, &pTexture);

		}

		// テクスチャ情報取得
		m_aXfile[nCount].apTexture.push_back(pTexture);

	}

	return S_OK;
}

//=============================================================================
// Xファイルアンロード
//=============================================================================
void CXfile::ModelUnLoad(void)
{
	for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
	{
		//メッシュの破棄
		if (m_aXfile[nCount].pMesh != nullptr)
		{
			m_aXfile[nCount].pMesh->Release();
			m_aXfile[nCount].pMesh = nullptr;
		}
		//マテリアルの破棄
		if (m_aXfile[nCount].pBuffMat != nullptr)
		{
			m_aXfile[nCount].pBuffMat->Release();
			m_aXfile[nCount].pBuffMat = nullptr;
		}

		// テクスチャの破棄
		for (size_t nCntTexture = 0; nCntTexture < m_aXfile[nCount].apTexture.size(); nCntTexture++)
		{
			if (m_aXfile[nCount].apTexture.at(nCntTexture) != nullptr)
			{
				m_aXfile[nCount].apTexture.at(nCntTexture)->Release();
				m_aXfile[nCount].apTexture.at(nCntTexture) = nullptr;
			}
		}

		// テクスチャの配列クリア
		m_aXfile[nCount].apTexture.clear();
	}
}

//=============================================================================
// 階層構造のモデルファイル読み込み
//=============================================================================
HRESULT CXfile::HierarchyReadFile(void)
{
	FILE *pFile = nullptr;		//FILEポインタ

	// ファイルの名前を設定
	SetHierarchyFileName();

	for (int nModelCnt = 0; nModelCnt < HIERARCHY_XFILE_NUM_MAX; nModelCnt++)
	{
		// ファイルオープン
		pFile = fopen(m_pFileName[nModelCnt].c_str(), "r");

		string aHeadData;
		string aModeName;

		int nModelIndex = 0;	// モデルのインデックス
		int nMotionType = 0;	// モーションのタイプ
		int nKeyNum = 0;		// キー番号
		int nMotionNum = 0;		// モーション番号

		if (pFile != nullptr)
		{
			do
			{
				// 文字列をクリアする
				aHeadData.clear();

				//一列読み込んでモード情報を抽出
				getline((ifstream)pFile, aHeadData);

				aModeName = aHeadData;

				if (aHeadData.find("MODEL_FILENAME") != string::npos)
				{
					// モデルファイルの構造体
					MODELFILE aModelFile = {};

					aModelFile.aFileName = CLibrary::split(aHeadData, ' ', 2);

					if (aModelFile.aFileName.c_str() != NULL)
					{
						// ファイル情報確保
						m_apModelFile[nModelCnt].push_back(aModelFile);

						//インデックスを１つ進める
						nModelIndex++;
					}
				}

				if (aModeName.compare(string("CHARACTERSET")) == 0)
				{
					//インデックスを最初に戻す
					nModelIndex = 0;

					//END_MOTIONSETを読み込むまで繰り返す
					while (aModeName.compare(string("END_CHARACTERSET")) != 0)
					{
						//一列読み込んでモード情報を抽出
						getline((ifstream)pFile, aHeadData);

						// 文字の分解
						aModeName = CLibrary::split(aHeadData, ' ', 0);

						if (aModeName.compare(string("PARTSSET")) == 0)
						{
							//END_PARTSSETを読み込むまで繰り返す
							while (aModeName.compare(string("END_PARTSSET")) != 0)
							{
								//一列読み込んでモード情報を抽出
								getline((ifstream)pFile, aHeadData);
								aModeName = CLibrary::split(aHeadData, ' ', 0);

								if (aModeName.find(string("PARENT")) == 0)
								{
									//親子情報の設定
									sscanf(aHeadData.c_str(), "%*s %*s %d", &m_apModelFile[nModelCnt].at(nModelIndex).nParent);

								}
								//if (strcmp(aModeName, "POS") == 0)
								if (aModeName.find(string("POS")) == 0)
								{
									//位置の設定
									sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_apModelFile[nModelCnt].at(nModelIndex).offsetPos.x,
										&m_apModelFile[nModelCnt].at(nModelIndex).offsetPos.y, &m_apModelFile[nModelCnt].at(nModelIndex).offsetPos.z);
								}
								//if (strcmp(aModeName, "ROT") == 0)
								if (aModeName.find(string("ROT")) == 0)
								{
									//向きの設定
									sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_apModelFile[nModelCnt].at(nModelIndex).offsetRot.x,
										&m_apModelFile[nModelCnt].at(nModelIndex).offsetRot.y, &m_apModelFile[nModelCnt].at(nModelIndex).offsetRot.z);
								}
							}

							//インデックスを１つ進める
							nModelIndex++;

							// パーツ数を数える
							m_nMaxParts[nModelCnt]++;

						}
					}
				}

			} while (aModeName.find("END_SCRIPT") == string::npos);

			//ファイルクローズ
			::fclose(pFile);
		}
		else
		{
			//失敗した場合メッセージボックスを表示
			MessageBox(nullptr, "ヒエラルキーファイルを開くのに失敗しました", "警告", MB_OK | MB_ICONEXCLAMATION);

			return	E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// 階層構造のモデルロード
//=============================================================================
HRESULT CXfile::HierarchyModelLoad(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nXFileNumCnt = 0; nXFileNumCnt < HIERARCHY_XFILE_NUM_MAX; nXFileNumCnt++)
	{
		for (int nCount = 0; nCount < m_nMaxParts[nXFileNumCnt]; nCount++)
		{
			MODEL Hierarchy = { nullptr, nullptr, 0, {} };

			//モデルの読み込み
			D3DXLoadMeshFromX(m_apModelFile[nXFileNumCnt].at(nCount).aFileName.c_str(),
				D3DXMESH_SYSTEMMEM,
				pDevice,
				nullptr,
				&Hierarchy.pBuffMat,
				nullptr,
				&Hierarchy.dwNumMat,
				&Hierarchy.pMesh);

			//マテリアル情報の解析
			D3DXMATERIAL *materials = (D3DXMATERIAL*)Hierarchy.pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)Hierarchy.dwNumMat; nCntMat++)
			{
				LPDIRECT3DTEXTURE9 pTexture = nullptr;

				if (materials[nCntMat].pTextureFilename != nullptr)
				{
					// ファイルネームの取得
					char cData[256] = {};

					sprintf(cData, "data/model/Texture/%s", materials[nCntMat].pTextureFilename);

					// テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice, cData, &pTexture);
				}

				// テクスチャ情報を取得
				Hierarchy.apTexture.push_back(pTexture);
			}

			// モデル情報を取得
			m_apHierarchyModel[nXFileNumCnt].push_back(Hierarchy);
		}
	}

	return S_OK;
}

//=============================================================================
// 階層構造のアンモデルロード
//=============================================================================
void CXfile::HierarchyModelUnLoad(void)
{
	for (int nXFileNumCnt = 0; nXFileNumCnt < HIERARCHY_XFILE_NUM_MAX; nXFileNumCnt++)
	{
		for (size_t nCount = 0; nCount < m_apHierarchyModel[nXFileNumCnt].size(); nCount++)
		{
			//マテリアル情報の破棄
			if (m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat != nullptr)
			{
				m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat->Release();
				m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat = nullptr;
			}

			//メッシュ情報の破棄
			if (m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh != nullptr)
			{
				m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh->Release();
				m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh = nullptr;
			}

			// テクスチャの開放
			for (size_t nCntTexture = 0; nCntTexture < m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.size(); nCntTexture++)
			{
				if (m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.at(nCntTexture) != nullptr)
				{
					m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.at(nCntTexture)->Release();
					m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.at(nCntTexture) = nullptr;
				}
			}

			// テクスチャの配列クリア
			m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.clear();
		}

		// 階層構造の配列クリア
		m_apHierarchyModel[nXFileNumCnt].clear();
	}
}

//=============================================================================
// ファイルの名前を設定
//=============================================================================
void CXfile::SetHierarchyFileName(void)
{
	for (size_t nCount = 0; nCount < m_aHierarchyXfileName.size(); nCount++)
	{
		// 名前を入れる
		m_pFileName[nCount] = m_aHierarchyXfileName.at(nCount);
	}
}

//=============================================================================
// モデルの情報
//=============================================================================
CXfile::MODEL CXfile::GetXfile(XFILE_NUM Tex_Num)
{
	return m_aXfile[Tex_Num];
}

//=============================================================================
// モデルに使用するテクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 *CXfile::GetXfileTexture(XFILE_NUM TexNum)
{
	if (TexNum < XFILE_NUM_MAX)
	{
		if (m_aXfile[TexNum].apTexture.data() != nullptr)
		{
			return m_aXfile[TexNum].apTexture.data();
		}
	}

	return nullptr;
}
