//=============================================================================
//
// ���U���g�N���X���� [result.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "result_clear.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"
#include "joypad.h"
#include "resource_manager.h"
#include "texture.h"
#include "result_story.h"
#include "sound.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResultClear::CResultClear()
{
	m_pObject2D = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResultClear::~CResultClear()
{
	// �I������
	Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResultClear::Init(void)
{
	// �I�u�W�F�N�g����
	Create2DObject();

	CSound *pSound = GET_SOUND_PTR;
	pSound->Play(CSound::SOUND_BGM_RESULT_CLEAR);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResultClear::Uninit(void)
{
	if (m_pObject2D)
	{
		m_pObject2D->Uninit();
		m_pObject2D = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CResultClear::Update(void)
{
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	if (m_pObject2D)
	{
		if (m_pObject2D->GetEnd())
		{
			// �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
			if (mode == CFade::FADE_MODE_NONE)
			{
				CFade *pFade = CManager::GetFade();
				pFade->SetFade(CManager::MODE_TYPE_TITLE);
			}
		}
		else
		{
			CInputKeyboard* pKey = CManager::GetKeyboard();

			// �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
			if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
				|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
			{
				CFade *pFade = CManager::GetFade();
				pFade->SetFade(CManager::MODE_TYPE_TITLE);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CResultClear::Draw(void)
{
}

//=============================================================================
// 2D�I�u�W�F�N�g����
//=============================================================================
void CResultClear::Create2DObject(void)
{
	// �e�N�X�`���̃|�C���擾
	CTexture *pTexture = GET_TEXTURE_PTR;

	// �w�i
	CScene2D *pScene2D = CScene2D::Create(HALF_SCREEN_POS, SCREEN_SIZE);
	pScene2D->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_RESULT_STORY_BACK));

	// �������m��
	m_pObject2D = CResultStory::Create();
	m_pObject2D->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_RESULT_STORY));
}