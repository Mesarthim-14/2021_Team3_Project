//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "title.h"
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
#include "title_sky.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define LOGO_POS			(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 150.0f, 0.0f))
#define LOGO_SIZE			(D3DXVECTOR3(950.0f, 220.0f, 0.0f))
#define TITLE_PLAYER_POS	(D3DXVECTOR3(5000.0f, 0.0f, -20000.0f))
#define SHIP_PADDLE_ROTATE	(D3DXToRadian(1.0f))

// LightInfo
#define TITLE_LIGHT_VECDIR	(D3DXVECTOR3(-0.8f, -1.0f, 1.0f))

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	m_pShip = nullptr;
	m_pObject2D.clear();
	m_pCamera = nullptr;
	m_pLight = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
	// �I������
	Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	// 3D�I�u�W�F�N�g����
	Create3DObject();

	// 2D�I�u�W�F�N�g����
	Create2DObject();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	for (auto &object : m_pObject2D)
	{
		// �I������
		object->Uninit();
	}

	// �I�u�W�F�N�g�폜
	m_pObject2D.clear();

	// �J�����I������
	if (m_pCamera)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	// ���C�g�I������
	if (m_pLight)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	// �D�I������
	if (m_pShip)
	{
		m_pShip->Uninit();
		m_pShip = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	// �J�����X�V����
	if (m_pCamera)
	{
		m_pCamera->Update();
	}

	// �D�̃p�h���̉�]
	if (m_pShip)
	{
		m_pShip->PaddleRotateR(-SHIP_PADDLE_ROTATE);
		m_pShip->PaddleRotateL(-SHIP_PADDLE_ROTATE);
	}

	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	// �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_TITLE_STORY);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}

//=============================================================================
// 2D�I�u�W�F�N�g����
//=============================================================================
void CTitle::Create2DObject(void)
{
	// �e�N�X�`���̃|�C���擾
	CTexture *pTexture = GET_TEXTURE_PTR;

	// �������m��
	CScene2D *pTitleLogo = CScene2D::Create(LOGO_POS, LOGO_SIZE);
	pTitleLogo->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TITLE_LOGO));

	// �I�u�W�F�N�g�ǉ�
	m_pObject2D.push_back(pTitleLogo);
}

//=============================================================================
// 3D�I�u�W�F�N�g����
//=============================================================================
void CTitle::Create3DObject(void)
{
	// �^�C�g���J�����̐���
	if (!m_pCamera)
	{
		m_pCamera = CCameraTitle::Create();
	}

	// ���C�g�̐���
	if (!m_pLight)
	{
		m_pLight = CLight::Create();
		m_pLight->SetVecDir(TITLE_LIGHT_VECDIR);
	}

	// �v���C���[�̐���
	if (!m_pShip)
	{
		m_pShip = CPlayer::Create(TITLE_PLAYER_POS, ZeroVector3);
	}

	CWater::Create();		// �C
	CTitleMap::Create();	// �^�C�g���}�b�v
	CTitleSky::Create();	// ��
}