//=============================================================================
//
// ���\�[�X�}�l�[�W���[���� [resource_manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "resource_manager.h"
#include "texture.h"
#include "xfile.h"
#include "sound.h"

//=============================================================================
// static�������錾
//=============================================================================
CResourceManager *CResourceManager::m_pResourceManager = nullptr;	// ���g�̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResourceManager::CResourceManager()
{
	m_pTexture = nullptr;	// �e�N�X�`���̃|�C���^
	m_pXFile = nullptr;		// X�t�@�C���̃|�C���^
	m_pSound = nullptr;		// �T�E���h�̃|�C���^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResourceManager::~CResourceManager()
{
	// �A�����[�h����
	UnLoadAll();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResourceManager::Init(void)
{
	// nullcheck
	if (m_pTexture == nullptr)
	{
		// �e�N�X�`���̃C���X�^���X����
		m_pTexture = CTexture::Create();
	}

	// nullcheck
	if (m_pXFile == nullptr)
	{
		// X�t�@�C���̃C���X�^���X����
		m_pXFile = CXfile::Create();
	}

	// nullcheck
	if (m_pSound == nullptr)
	{
		// �T�E���h�̃C���X�^���X����
		m_pSound = CSound::Create();
	}

	return S_OK;
}

//=============================================================================
// ���[�h����
//=============================================================================
void CResourceManager::LoadAll(void)
{
	// !nullcheck
	if (m_pTexture != nullptr)
	{
		// �e�N�X�`�����[�h
		m_pTexture->LoadAll();
	}

	// !nullcheck
	if (m_pXFile != nullptr)
	{
		// ���f�����[�h
	m_pXFile->ModelLoad();

		// �K�w�\���̃t�@�C���ǂݍ���
	m_pXFile->HierarchyReadFile();

		// �K�w�\���̃��f���ǂݍ���
	m_pXFile->HierarchyModelLoad();

	}
}

//=============================================================================
// �A�����[�h����
//=============================================================================
void CResourceManager::UnLoadAll(void)
{
	// !nullcheck
	if (m_pTexture != nullptr)
	{
		// �e�N�X�`���̃A�����[�h
		m_pTexture->UnLoadAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	// !nullcheck
	if (m_pXFile != nullptr)
	{
		// �e�N�X�`���A�����[�h
		m_pXFile->ModelUnLoad();
		m_pXFile->HierarchyModelUnLoad();
		delete m_pXFile;
		m_pXFile = nullptr;
	}

	// nullcheck
	if (m_pSound != nullptr)
	{
		// �I������
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}
}

//=============================================================================
// �C���X�^���X�擾�֐�
//=============================================================================
CResourceManager * CResourceManager::GetInstance(void)
{
	// nullcheck
	if (m_pResourceManager == nullptr)
	{
		// �������m��
		m_pResourceManager = new CResourceManager;

		// !nullcheck
		if (m_pResourceManager != nullptr)
		{
			// ����������
			m_pResourceManager->Init();
		}
	}

	return m_pResourceManager;
}