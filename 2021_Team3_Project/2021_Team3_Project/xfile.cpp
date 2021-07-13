//=============================================================================
//
// X�t�@�C���̊Ǘ��N���X [xfile.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "xfile.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CXfile::CXfile()
{
	memset(m_aXfile, 0, sizeof(m_aXfile));
	memset(m_pFileName, 0, sizeof(m_pFileName));
	memset(m_nMaxParts, 0, sizeof(m_nMaxParts));

	for (int nCount = 0; nCount < HIERARCHY_XFILE_NUM_MAX; nCount++)
	{
		// ����������
		m_apHierarchyModel[nCount].clear();
	}

	for (int nCount = 0; nCount < HIERARCHY_XFILE_NUM_MAX; nCount++)
	{
		// ����������
		m_apModelFile[nCount].clear();
	}

	// X�t�@�C���l�[�����擾
	m_aXfileName =
	{
		{ "data/Model/Bullet/bullet.x" },		// �e
		{ "data/Model/box/box.x" },				// ��
		{"data/Model/Map/Map.x"},				// �}�b�v
	};

	m_aHierarchyXfileName =
	{
		{ "data/Text/Player/motion_Player.txt" },		// �v���C���[
		{ "data/Text/Enemy/motion_Enemy_Ship.txt" },	// �G�D
	};
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CXfile::~CXfile()
{
	m_aXfileName.clear();

	m_aHierarchyXfileName.clear();
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CXfile * CXfile::Create(void)
{
	// �������m��
	CXfile *pXfile = new CXfile;

	return pXfile;
}

//=============================================================================
// X�t�@�C�����[�h
//=============================================================================
HRESULT CXfile::ModelLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (size_t nCount = 0; nCount < m_aXfileName.size(); nCount++)
	{
		// X�t�@�C���̓ǂݍ���
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
		//�}�e���A�����̉��
		D3DXMATERIAL *materials = (D3DXMATERIAL*)m_aXfile[nCount].pBuffMat->GetBufferPointer();
		LPDIRECT3DTEXTURE9 pTexture = nullptr;

		for (int nCntMat = 0; nCntMat < (int)m_aXfile[nCount].dwNumMat; nCntMat++)
		{
			// �t�@�C���l�[���̎擾
			char cData[128] = {};

			sprintf(cData, "data/model/Texture/%s", materials[nCntMat].pTextureFilename);

			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, cData, &pTexture);

		}

		// �e�N�X�`�����擾
		m_aXfile[nCount].apTexture.push_back(pTexture);

	}

	return S_OK;
}

//=============================================================================
// X�t�@�C���A�����[�h
//=============================================================================
void CXfile::ModelUnLoad(void)
{
	for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
	{
		//���b�V���̔j��
		if (m_aXfile[nCount].pMesh != nullptr)
		{
			m_aXfile[nCount].pMesh->Release();
			m_aXfile[nCount].pMesh = nullptr;
		}
		//�}�e���A���̔j��
		if (m_aXfile[nCount].pBuffMat != nullptr)
		{
			m_aXfile[nCount].pBuffMat->Release();
			m_aXfile[nCount].pBuffMat = nullptr;
		}

		// �e�N�X�`���̔j��
		for (size_t nCntTexture = 0; nCntTexture < m_aXfile[nCount].apTexture.size(); nCntTexture++)
		{
			if (m_aXfile[nCount].apTexture.at(nCntTexture) != nullptr)
			{
				m_aXfile[nCount].apTexture.at(nCntTexture)->Release();
				m_aXfile[nCount].apTexture.at(nCntTexture) = nullptr;
			}
		}

		// �e�N�X�`���̔z��N���A
		m_aXfile[nCount].apTexture.clear();
	}
}

//=============================================================================
// �K�w�\���̃��f���t�@�C���ǂݍ���
//=============================================================================
HRESULT CXfile::HierarchyReadFile(void)
{
	FILE *pFile = nullptr;		//FILE�|�C���^

	// �t�@�C���̖��O��ݒ�
	SetHierarchyFileName();

	for (int nModelCnt = 0; nModelCnt < HIERARCHY_XFILE_NUM_MAX; nModelCnt++)
	{
		// �t�@�C���I�[�v��
		pFile = fopen(m_pFileName[nModelCnt].c_str(), "r");

		string aHeadData;
		string aModeName;

		int nModelIndex = 0;	// ���f���̃C���f�b�N�X
		int nMotionType = 0;	// ���[�V�����̃^�C�v
		int nKeyNum = 0;		// �L�[�ԍ�
		int nMotionNum = 0;		// ���[�V�����ԍ�

		if (pFile != nullptr)
		{
			do
			{
				// ��������N���A����
				aHeadData.clear();

				//���ǂݍ���Ń��[�h���𒊏o
				getline((ifstream)pFile, aHeadData);

				aModeName = aHeadData;

				if (aHeadData.find("MODEL_FILENAME") != string::npos)
				{
					// ���f���t�@�C���̍\����
					MODELFILE aModelFile = {};

					aModelFile.aFileName = CLibrary::split(aHeadData, ' ', 2);

					if (aModelFile.aFileName.c_str() != NULL)
					{
						// �t�@�C�����m��
						m_apModelFile[nModelCnt].push_back(aModelFile);

						//�C���f�b�N�X���P�i�߂�
						nModelIndex++;
					}
				}

				if (aModeName.compare(string("CHARACTERSET")) == 0)
				{
					//�C���f�b�N�X���ŏ��ɖ߂�
					nModelIndex = 0;

					//END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
					while (aModeName.compare(string("END_CHARACTERSET")) != 0)
					{
						//���ǂݍ���Ń��[�h���𒊏o
						getline((ifstream)pFile, aHeadData);

						// �����̕���
						aModeName = CLibrary::split(aHeadData, ' ', 0);

						if (aModeName.compare(string("PARTSSET")) == 0)
						{
							//END_PARTSSET��ǂݍ��ނ܂ŌJ��Ԃ�
							while (aModeName.compare(string("END_PARTSSET")) != 0)
							{
								//���ǂݍ���Ń��[�h���𒊏o
								getline((ifstream)pFile, aHeadData);
								aModeName = CLibrary::split(aHeadData, ' ', 0);

								if (aModeName.find(string("PARENT")) == 0)
								{
									//�e�q���̐ݒ�
									sscanf(aHeadData.c_str(), "%*s %*s %d", &m_apModelFile[nModelCnt].at(nModelIndex).nParent);

								}
								//if (strcmp(aModeName, "POS") == 0)
								if (aModeName.find(string("POS")) == 0)
								{
									//�ʒu�̐ݒ�
									sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_apModelFile[nModelCnt].at(nModelIndex).offsetPos.x,
										&m_apModelFile[nModelCnt].at(nModelIndex).offsetPos.y, &m_apModelFile[nModelCnt].at(nModelIndex).offsetPos.z);
								}
								//if (strcmp(aModeName, "ROT") == 0)
								if (aModeName.find(string("ROT")) == 0)
								{
									//�����̐ݒ�
									sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_apModelFile[nModelCnt].at(nModelIndex).offsetRot.x,
										&m_apModelFile[nModelCnt].at(nModelIndex).offsetRot.y, &m_apModelFile[nModelCnt].at(nModelIndex).offsetRot.z);
								}
							}

							//�C���f�b�N�X���P�i�߂�
							nModelIndex++;

							// �p�[�c���𐔂���
							m_nMaxParts[nModelCnt]++;

						}
					}
				}

			} while (aModeName.find("END_SCRIPT") == string::npos);

			//�t�@�C���N���[�Y
			::fclose(pFile);
		}
		else
		{
			//���s�����ꍇ���b�Z�[�W�{�b�N�X��\��
			MessageBox(nullptr, "�q�G�����L�[�t�@�C�����J���̂Ɏ��s���܂���", "�x��", MB_OK | MB_ICONEXCLAMATION);

			return	E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// �K�w�\���̃��f�����[�h
//=============================================================================
HRESULT CXfile::HierarchyModelLoad(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nXFileNumCnt = 0; nXFileNumCnt < HIERARCHY_XFILE_NUM_MAX; nXFileNumCnt++)
	{
		for (int nCount = 0; nCount < m_nMaxParts[nXFileNumCnt]; nCount++)
		{
			MODEL Hierarchy = { nullptr, nullptr, 0, {} };

			//���f���̓ǂݍ���
			D3DXLoadMeshFromX(m_apModelFile[nXFileNumCnt].at(nCount).aFileName.c_str(),
				D3DXMESH_SYSTEMMEM,
				pDevice,
				nullptr,
				&Hierarchy.pBuffMat,
				nullptr,
				&Hierarchy.dwNumMat,
				&Hierarchy.pMesh);

			//�}�e���A�����̉��
			D3DXMATERIAL *materials = (D3DXMATERIAL*)Hierarchy.pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)Hierarchy.dwNumMat; nCntMat++)
			{
				LPDIRECT3DTEXTURE9 pTexture = nullptr;

				if (materials[nCntMat].pTextureFilename != nullptr)
				{
					// �t�@�C���l�[���̎擾
					char cData[256] = {};

					sprintf(cData, "data/model/Texture/%s", materials[nCntMat].pTextureFilename);

					// �e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice, cData, &pTexture);
				}

				// �e�N�X�`�������擾
				Hierarchy.apTexture.push_back(pTexture);
			}

			// ���f�������擾
			m_apHierarchyModel[nXFileNumCnt].push_back(Hierarchy);
		}
	}

	return S_OK;
}

//=============================================================================
// �K�w�\���̃A�����f�����[�h
//=============================================================================
void CXfile::HierarchyModelUnLoad(void)
{
	for (int nXFileNumCnt = 0; nXFileNumCnt < HIERARCHY_XFILE_NUM_MAX; nXFileNumCnt++)
	{
		for (size_t nCount = 0; nCount < m_apHierarchyModel[nXFileNumCnt].size(); nCount++)
		{
			//�}�e���A�����̔j��
			if (m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat != nullptr)
			{
				m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat->Release();
				m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat = nullptr;
			}

			//���b�V�����̔j��
			if (m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh != nullptr)
			{
				m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh->Release();
				m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh = nullptr;
			}

			// �e�N�X�`���̊J��
			for (size_t nCntTexture = 0; nCntTexture < m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.size(); nCntTexture++)
			{
				if (m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.at(nCntTexture) != nullptr)
				{
					m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.at(nCntTexture)->Release();
					m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.at(nCntTexture) = nullptr;
				}
			}

			// �e�N�X�`���̔z��N���A
			m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.clear();
		}

		// �K�w�\���̔z��N���A
		m_apHierarchyModel[nXFileNumCnt].clear();
	}
}

//=============================================================================
// �t�@�C���̖��O��ݒ�
//=============================================================================
void CXfile::SetHierarchyFileName(void)
{
	for (size_t nCount = 0; nCount < m_aHierarchyXfileName.size(); nCount++)
	{
		// ���O������
		m_pFileName[nCount] = m_aHierarchyXfileName.at(nCount);
	}
}

//=============================================================================
// ���f���̏��
//=============================================================================
CXfile::MODEL CXfile::GetXfile(XFILE_NUM Tex_Num)
{
	return m_aXfile[Tex_Num];
}

//=============================================================================
// ���f���Ɏg�p����e�N�X�`�����
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
