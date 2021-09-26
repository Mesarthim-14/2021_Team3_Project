//=============================================================================
//
// ���U���g�N���X���� [result.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"
#include "joypad.h"
#include "resource_manager.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define RESULT_BG_POS						(HALF_SCREEN_POS)
#define RESULT_BG_SIZE						(SCREEN_SIZE)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult::CResult()
{
	m_pObject2D.clear();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{
	// �I������
	Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init(void)
{
	
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
	for (auto apObject : m_pObject2D)
	{
		// �I������
		apObject->Uninit();
	}
	m_pObject2D.clear();
}

//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	// �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_TITLE);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{
}

//=============================================================================
// 2D�I�u�W�F�N�g����
//=============================================================================
void CResult::Create2DObject(void)
{
	// �e�N�X�`���̃|�C���擾
	CTexture *pTexture = GET_TEXTURE_PTR;

	// �������m��
	CScene2D *pResultLogo = CScene2D::Create(RESULT_BG_POS, RESULT_BG_SIZE);
	pResultLogo->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_RESULT_BG));

	// �I�u�W�F�N�g�ǉ�
	m_pObject2D.push_back(pResultLogo);
}
