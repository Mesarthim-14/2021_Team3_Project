//=============================================================================
//
// �L�[�{�[�h�N���X [keyboard.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "keyboard.h"

//=============================================================================
//�L�[�{�[�h�N���X�̃R���X�g���N�^
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	m_pDevice = NULL;	//���̓f�o�C�X

	//�e�����o�ϐ���0�N���A
	memset(m_aKeyState, 0, sizeof(m_aKeyState));
	memset(m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
}

//=============================================================================
//�L�[�{�[�h�N���X�̃f�X�g���N�^
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//=============================================================================
//�L�[�{�[�h�N���X�̏���������
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//���͏����N���X�̏����������Ăяo��
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X�i�L�[�{�[�h�j�̍쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g�ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�i�t�@�I�O���E���h����r�����[�h�j
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l���i���͐���J�n�j
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
//�L�[�{�[�h�N���X�̏I������
//=============================================================================
void CInputKeyboard::Uninit(void)
{ 
	//���͏����N���X�̏I�������Ăяo��
	CInput::Uninit();
}

//=============================================================================
//�L�[�{�[�h�N���X�̍X�V����
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[MAX_KEY_NUM];	//�L�[�{�[�h�̓��͏��

	//�f�o�C�X����f�[�^�擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (int nCntKey = 0; nCntKey < MAX_KEY_NUM; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&~aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	//�L�[�v���X����ۑ�
		}
	}
	else
	{
		//�L�[�{�[�h�ւ̃A�N�Z�X�����擾
		m_pDevice->Acquire();
	}
}

//=============================================================================
//�L�[�{�[�h�̃v���X���̎擾
//=============================================================================
BOOL CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
//�L�[�{�[�h�̃g���K�[���̎擾
//=============================================================================
BOOL CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
//�L�[�{�[�h�̃����[�X���̎擾
//=============================================================================
BOOL CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}