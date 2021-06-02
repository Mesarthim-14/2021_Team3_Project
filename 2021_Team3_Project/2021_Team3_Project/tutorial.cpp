//=======================================================================================
//
// �`���[�g���A���N���X [tutorial.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "tutorial.h"
#include "scene2d.h"
#include "manager.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CTutorial::CTutorial()
{
	m_pScene = nullptr;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CTutorial::~CTutorial()
{
	// �I������
	Uninit();
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CTutorial::Init(void)
{
	// nullcheck
	if (m_pScene == nullptr)
	{
		// �C���X�^���X����
		m_pScene = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}
	
	// �T�E���h�̃|�C���^
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
	//pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=======================================================================================
// �I������
//=======================================================================================
void CTutorial::Uninit(void)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		m_pScene = nullptr;
	}
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CTutorial::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	// �R���g���[����start���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}

	//�G���^�[�L�[���������Ƃ�
	if (pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}

}

//=======================================================================================
// �`�揈��
//=======================================================================================
void CTutorial::Draw(void)
{

}
