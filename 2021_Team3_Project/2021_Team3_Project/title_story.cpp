//=============================================================================
//
// �^�C�g���X�g�[���[���� [title_story.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "title_story.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"
#include "texture.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"
#include "camera.h"
#include "camera_title.h"
#include "light.h"
#include "player.h"
#include "water.h"
#include "title_map.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BG_POS						(HALF_SCREEN_POS)
#define BG_SIZE						(SCREEN_SIZE)
#define SENTENCE_0_POS				(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 160.0f, 0.0f))
#define SENTENCE_0_SIZE				(D3DXVECTOR3(750.0f, 100.0f, 0.0f))
#define SENTENCE_1_POS				(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 280.0f, 0.0f))
#define SENTENCE_1_SIZE				(D3DXVECTOR3(750.0f, 100.0f, 0.0f))
#define SENTENCE_2_POS				(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 400.0f, 0.0f))
#define SENTENCE_2_SIZE				(D3DXVECTOR3(750.0f, 100.0f, 0.0f))
#define SENTENCE_3_POS				(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 530.0f, 0.0f))
#define SENTENCE_3_SIZE				(D3DXVECTOR3(750.0f, 100.0f, 0.0f))

#define CREATE_SENTENCE_INTER		(120)
#define SENTENCE_FADE_OUT_NUM		(0.05f)

//=============================================================================
// static�錾
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitleStory::CTitleStory()
{
	m_pObject2D.clear();
	m_nSentenceNum = 0;
	m_nTimeCounter = 0;
	m_bEnd = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitleStory::~CTitleStory()
{
	// �I������
	Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitleStory::Init(void)
{
	// �w�i�̐���
	CreateBg();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitleStory::Uninit(void)
{
	for (auto &object : m_pObject2D)
	{
		// �I������
		object->Uninit();
	}

	// �I�u�W�F�N�g�폜
	m_pObject2D.clear();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitleStory::Update(void)
{
	if (!m_bEnd)
	{
		m_nTimeCounter++;

		if (m_nTimeCounter >= CREATE_SENTENCE_INTER)
		{
			// ���͂̐���
			(this->*m_CreateSentence.at(m_nSentenceNum))();

			// ��������֐���i�߂�
			m_nSentenceNum++;
			m_nTimeCounter = 0;
		}

		// ���͂̃X�L�b�v
		SkipSentence();
	}
	else
	{
		// ���[�h�J��
		ModeTransition();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitleStory::Draw(void)
{

}

//=============================================================================
// ���[�h�J��
//=============================================================================
void CTitleStory::ModeTransition(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	// �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}
}

//=============================================================================
// ���̓X�L�b�v
//=============================================================================
void CTitleStory::SkipSentence(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();

	// �{�^���������ꂽ��
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_B, 0)
		|| pKey->GetTrigger(DIK_B))
	{
		while (!m_bEnd)
		{
			// ���͂̐���
			(this->*m_CreateSentence.at(m_nSentenceNum))();

			// ��������֐���i�߂�
			m_nSentenceNum++;
		}
	}
}

//=============================================================================
// �w�i�̐���
//=============================================================================
void CTitleStory::CreateBg(void)
{
	// �e�N�X�`���̃|�C���擾
	CTexture *pTexture = GET_TEXTURE_PTR;

	// �������m��
	CScene2D *pTitleLogo = CScene2D::Create(BG_POS, BG_SIZE);
	pTitleLogo->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_STORY_BG));

	// �I�u�W�F�N�g�ǉ�
	m_pObject2D.push_back(pTitleLogo);
}

//=============================================================================
// ���͂̐���
//=============================================================================
void CTitleStory::CreateSentence0(void)
{
	// �e�N�X�`���̃|�C���擾
	CTexture *pTexture = GET_TEXTURE_PTR;

	// �������m��
	CScene2D *pTitleLogo = CScene2D::Create(SENTENCE_0_POS, SENTENCE_0_SIZE, SENTENCE_FADE_OUT_NUM);
	pTitleLogo->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_STORY_SENTENCE0));

	// �I�u�W�F�N�g�ǉ�
	m_pObject2D.push_back(pTitleLogo);
}

//=============================================================================
// ���͂̐���
//=============================================================================
void CTitleStory::CreateSentence1(void)
{
	// �e�N�X�`���̃|�C���擾
	CTexture *pTexture = GET_TEXTURE_PTR;

	// �������m��
	CScene2D *pTitleLogo = CScene2D::Create(SENTENCE_1_POS, SENTENCE_1_SIZE, SENTENCE_FADE_OUT_NUM);
	pTitleLogo->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_STORY_SENTENCE1));

	// �I�u�W�F�N�g�ǉ�
	m_pObject2D.push_back(pTitleLogo);
}

//=============================================================================
// ���͂̐���
//=============================================================================
void CTitleStory::CreateSentence2(void)
{
	// �e�N�X�`���̃|�C���擾
	CTexture *pTexture = GET_TEXTURE_PTR;

	// �������m��
	CScene2D *pTitleLogo = CScene2D::Create(SENTENCE_2_POS, SENTENCE_2_SIZE, SENTENCE_FADE_OUT_NUM);
	pTitleLogo->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_STORY_SENTENCE2));

	// �I�u�W�F�N�g�ǉ�
	m_pObject2D.push_back(pTitleLogo);
}

//=============================================================================
// ���͂̐���
//=============================================================================
void CTitleStory::CreateSentence3(void)
{
	// �e�N�X�`���̃|�C���擾
	CTexture *pTexture = GET_TEXTURE_PTR;

	// �������m��
	CScene2D *pTitleLogo = CScene2D::Create(SENTENCE_3_POS, SENTENCE_3_SIZE, SENTENCE_FADE_OUT_NUM);
	pTitleLogo->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_STORY_SENTENCE3));

	// �I�u�W�F�N�g�ǉ�
	m_pObject2D.push_back(pTitleLogo);

	m_bEnd = true;
}