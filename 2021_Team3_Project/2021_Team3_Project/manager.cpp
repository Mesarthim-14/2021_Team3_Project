//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "billboard.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "joypad.h"
#include "keyboard.h"
#include "manager.h"
#include "mesh_3d.h"
#include "model.h"
#include "player.h"
#include "renderer.h"
#include "resource_manager.h"
#include "result.h"
#include "scene3D.h"
#include "sound.h"
#include "texture.h"
#include "title.h"
#include "tutorial.h"
#include "xfile.h"
#include "polygon.h"
#include "shadow.h"
#include "debug_proc.h"
#include "water.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CManager::MODE_TYPE CManager::m_mode = CManager::MODE_TYPE_TITLE;
unique_ptr<CRenderer> CManager::m_pRenderer = nullptr;
unique_ptr<CInputKeyboard> CManager::m_pInput = nullptr;
unique_ptr<CFade> CManager::m_pFade = nullptr;
unique_ptr<CInputJoypad> CManager::m_pJoypad = nullptr;
unique_ptr<CScene> CManager::m_pScene = nullptr;
unique_ptr<CResourceManager> CManager::m_pResourceManager = nullptr;
unique_ptr<CModeBase> CManager::m_pModeBase = nullptr;
unique_ptr<CDebugProc> CManager::m_pDebugProc = nullptr;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �������m��
	m_pRenderer.reset(new CRenderer);
	m_pInput.reset(new CInputKeyboard);
	m_pJoypad.reset(new CInputJoypad);
	m_pFade.reset(new CFade);
	m_pResourceManager.reset(CResourceManager::GetInstance());
	m_pDebugProc.reset(new CDebugProc);

	//���������m�ۂł�����
	if (m_pRenderer != nullptr)
	{
		// ����������
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{
			return -1;
		}
	}

	//���������m�ۂł�����
	if (m_pInput != nullptr)
	{
		if (FAILED(m_pInput->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	//���������m�ۂł�����
	if (m_pJoypad != nullptr)
	{
		if (FAILED(m_pJoypad->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	// !nullcheck
	if (m_pFade != nullptr)
	{
		// ����������
		m_pFade->Init();
	}

	// !nullcheck
	if (m_pDebugProc != nullptr)
	{
		// ����������
		m_pDebugProc->Init();
	}

	//�S�e�N�X�`���̓ǂݍ���
	LoadAll();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	// !nullcheck
	if (m_pDebugProc != nullptr)
	{
		// �f�o�b�O�v���V�[�W���̏I�������Ăяo��
		m_pDebugProc->Uninit();
		m_pDebugProc.reset();
		m_pDebugProc = nullptr;
	}
	// !nullchack
	if (m_pFade != nullptr)
	{
		//�t�F�[�h�N���X�̏I�������Ăяo��
		m_pFade->Uninit();
		m_pFade.reset();
		m_pFade = nullptr;
	}

	// !nullcheck
	if (m_pResourceManager != nullptr)
	{
		// ���\�[�X�̃��[�h
		m_pResourceManager.reset();
		m_pResourceManager = nullptr;

	}

	// !nullchack
	if (m_pInput != nullptr)
	{
		//���͏����N���X�̏I�������Ăяo��
		m_pInput->Uninit();

		//�������̍폜
		m_pInput.reset();
		m_pInput = nullptr;
	}

	// !nullchack
	if (m_pJoypad != nullptr)
	{
		//���͏����N���X�̏I�������Ăяo��
		m_pJoypad->Uninit();

		//�������̍폜
		m_pJoypad.reset();
		m_pJoypad = nullptr;
	}

	//�������J��
	if (m_pRenderer != nullptr)
	{	
		// �`��N���X
		m_pRenderer.reset();
		m_pRenderer = nullptr;
	}

	if (m_pModeBase != nullptr)
	{
		// �`��N���X
		m_pModeBase.reset();
		m_pModeBase = nullptr;
	}

	// �V���h�E�|���S���̃����[�X
	CShadow::PolygonRelese();

	// �V�[�����̃����[�X
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	if (m_pInput != nullptr)
	{
		//���͏����N���X�̍X�V�����Ăяo��
		m_pInput->Update();
	}

	if (m_pJoypad != nullptr)
	{
		//���͏����N���X�̍X�V�����Ăяo��
		m_pJoypad->Update();
	}

	if (m_pRenderer != nullptr)
	{
		//�����_���[�N���X�̍X�V�����Ăяo��
		m_pRenderer->Update();
	}

	if (m_pFade != nullptr)
	{
		//�t�F�[�h�N���X�̍X�V�����Ăяo��
		m_pFade->Update();
	}

	// ���[�h�̍X�V����
	if (m_pModeBase != nullptr)
	{
		m_pModeBase->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != nullptr)
	{
		//�����_���[�N���X�̕`�揈���Ăяo��
		m_pRenderer->Draw();
	}

	// ���[�h�̍X�V����
	if (m_pModeBase != nullptr)
	{
		m_pModeBase->Draw();
	}
}

//=============================================================================
// �e�N�X�`���̑S���[�h����
//=============================================================================
void CManager::LoadAll(void)
{
	// !nullcheck
	if (m_pResourceManager != nullptr)
	{
		// ���\�[�X�̃��[�h
		m_pResourceManager->LoadAll();
	}

	// �t�@�C���̓ǂݍ���
	//CMesh3d::ReadFile();

	CWater::LoadShaderFile();
}

//=============================================================================
// �Q�[�����[�h�̐ݒ菈��
//=============================================================================
void CManager::SetMode(MODE_TYPE mode)
{
	// !nullcheck
	if (m_pModeBase != nullptr)
	{
		//�������J��
		m_pModeBase.reset();
		m_pModeBase = nullptr;
	}

	// �T�E���h�̏��
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	//�T�E���h�X�g�b�v
	pSound->StopAll();

	// �V�[�����̃����[�X
	CScene::ReleaseAll();

	// ���[�h��ς���
	m_mode = mode;

	//�ݒ肳�ꂽ���[�h���N���G�C�g
	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TYPE_TITLE:
		// �^�C�g������
		m_pModeBase.reset(new CTitle);
		break;

		// �`���[�g���A��
	case MODE_TYPE_TUTORIAL:
		// �`���[�g���A������
		m_pModeBase.reset(new CTutorial);
		break;

		// �Q�[��
	case MODE_TYPE_GAME:
		// �Q�[������
		m_pModeBase.reset(new CGame);
		break;

		// ���U���g
	case MODE_TYPE_RESULT:
		// ���U���g����
		m_pModeBase.reset(new CResult);
		break;
	default:
		break;
	}

	// !nullcheck
	if (m_pModeBase != nullptr)
	{
		// ����������
		m_pModeBase->Init();
	}
}

//=============================================================================
//�Q�[�����[�h���̎擾
//=============================================================================
CManager::MODE_TYPE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// �Q�[�����[�h���
//=============================================================================
CModeBase * CManager::GetModeBase(void)
{
	// !nullcheck
	if (m_pModeBase != nullptr)
	{
		// �|�C���^��Ԃ�
		return m_pModeBase.get();
	}

	return nullptr;
}

//=============================================================================
// �Q�[�����
//=============================================================================
CGame * CManager::GetGame(void)
{
	//�Q�[�������ǂ���
	if (m_mode == MODE_TYPE_GAME)
	{
		//nullcheck
		if (m_pModeBase)
		{
			//�L���X�g
			CGame *pGame = ((CGame*)m_pModeBase.get());

			// !nullcheck
			if (pGame != nullptr)
			{
				return pGame;
			}
		}
	}

	return nullptr;
}