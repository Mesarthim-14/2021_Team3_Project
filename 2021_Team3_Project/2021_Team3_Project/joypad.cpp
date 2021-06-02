//=============================================================================
//
// �W���C�p�b�h�N���X�̏���[joypad.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "joypad.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CInputJoypad::m_nJoyStickCont = 0;
LPDIRECTINPUTDEVICE8  CInputJoypad::m_apDevice[MAX_JOYSTICK_NUM] = {};

//=====================================================
// �R���X�g���N�^
//=====================================================
CInputJoypad::CInputJoypad()
{
	memset(m_aJoyState, 0, sizeof(m_aJoyState));
	memset(m_aJoyStateTrigger, 0, sizeof(m_aJoyState));
	memset(m_aJoyStateRelease, 0, sizeof(m_aJoyState));
	memset(m_JoyPadState, 0, sizeof(m_JoyPadState));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CInputJoypad::~CInputJoypad()
{
}

//=====================================================
// ����������
//=====================================================
HRESULT CInputJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT  hr[MAX_JOYSTICK_NUM];
	m_nJoyStickCont = 0;

	for (int nCntJoyStick = 0; nCntJoyStick < MAX_JOYSTICK_NUM; nCntJoyStick++)
	{
		hr[nCntJoyStick] = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
			(void**)&m_pInput, NULL);
	}

	hr[m_nJoyStickCont] = m_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY);

	for (int nCntJoystick = 0; nCntJoystick < m_nJoyStickCont; nCntJoystick++)
	{
		if (m_apDevice[nCntJoystick] != NULL)
		{

			if (FAILED(hr)) {
				MessageBox(hWnd, "Can't create Device.", "Error", MB_OK);
				return FALSE;
			}

			hr[nCntJoystick] = m_apDevice[nCntJoystick]->SetDataFormat(&c_dfDIJoystick);
			if (FAILED(hr[nCntJoystick])) {
				MessageBox(hWnd, "Can't set data format.", "Error", MB_OK);
				return FALSE;
			}

			hr[nCntJoystick] = m_apDevice[nCntJoystick]->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
			if (FAILED(hr[nCntJoystick])) {
				MessageBox(hWnd, "Can't set cooperative level.", "Error", MB_OK);
				return FALSE;
			}

			m_diDevCaps.dwSize = sizeof(DIDEVCAPS);
			hr[nCntJoystick] = m_apDevice[nCntJoystick]->GetCapabilities(&m_diDevCaps);
			if (FAILED(hr[nCntJoystick])) {
				MessageBox(hWnd, "Can't create device capabilities.", "Error", MB_OK);
				return FALSE;
			}

			hr[nCntJoystick] = m_apDevice[nCntJoystick]->EnumObjects(EnumAxesCallback, (VOID*)hWnd, DIDFT_AXIS);
			if (FAILED(hr[nCntJoystick])) {
				MessageBox(hWnd, "Can't set property.", "Error", MB_OK);
				return FALSE;
			}

			hr[nCntJoystick] = m_apDevice[nCntJoystick]->Poll();
			if (FAILED(hr[nCntJoystick])) {
				hr[nCntJoystick] = m_apDevice[nCntJoystick]->Acquire();
				while (hr[nCntJoystick] == DIERR_INPUTLOST) {
					hr[nCntJoystick] = m_apDevice[nCntJoystick]->Acquire();
				}
			}
		}
	}
	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CInputJoypad::Uninit(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	for (int nCnt = 0; nCnt < MAX_JOYSTICK_NUM; nCnt++)
	{
		if (m_apDevice[nCnt] != NULL)
		{
			// �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
			m_apDevice[nCnt]->Unacquire();
			m_apDevice[nCnt]->Release();
			m_apDevice[nCnt] = NULL;
		}
	}
	CInput::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CInputJoypad::Update(void)
{
	int nCntKey;
	DIJOYSTATE js;
	HRESULT hr;

	for (int nCnt = 0; nCnt < m_nJoyStickCont; nCnt++)
	{
		if (m_apDevice[nCnt] != NULL)
		{
			//�P�t���[���O�̏�Ԃ�ۑ�
			m_JoyPadState[nCnt].Old.rgdwPOV[0] = m_JoyPadState[nCnt].Press.rgdwPOV[0];

			m_apDevice[nCnt]->Poll();

			hr = m_apDevice[nCnt]->GetDeviceState(sizeof(DIJOYSTATE), &js);

			//�f�o�C�X����f�[�^���擾
			if (SUCCEEDED(hr))
			{
				//�\���L�[�̏���ۑ�
				m_JoyPadState[nCnt].Press.rgdwPOV[0] = js.rgdwPOV[0];

				for (nCntKey = 0; nCntKey < NUM_JOY_MAX; nCntKey++)
				{
					//�L�[�g���K�[
					m_aJoyStateTrigger[nCntKey][nCnt] = (m_aJoyState[nCntKey][nCnt] ^ js.rgbButtons[nCntKey]) &  js.rgbButtons[nCntKey];

					//�L�[�����[�X
					m_aJoyStateRelease[nCntKey][nCnt] = (m_aJoyState[nCntKey][nCnt] ^ js.rgbButtons[nCntKey]) & ~js.rgbButtons[nCntKey];

					//�L�[�v���X����ۑ�
					m_aJoyState[nCntKey][nCnt] = js.rgbButtons[nCntKey];
				}
			}
			else
			{
				m_apDevice[nCnt]->Acquire();
			}
		}
	}
}

//=====================================================
// �v���X���̎擾
//=====================================================
bool CInputJoypad::GetJoystickPress(int nKey, int nId)
{
	return m_aJoyState[nKey][nId] & 0x80 ? true : false;
}

//=====================================================
// �g���K�[���̎擾
//=====================================================
bool CInputJoypad::GetJoystickTrigger(int nKey, int nId)
{
	return m_aJoyStateTrigger[nKey][nId] & 0x80 ? true : false;
}

//=====================================================
// �����[�X���̎擾
//=====================================================
bool CInputJoypad::GetJoystickRelease(int nKey, int nId)
{
	return m_aJoyStateRelease[nKey][nId] & 0x80 ? true : false;
}

//=============================================================================
//�\���L�[�������ꂽ�u�Ԃ̔��菈��
//=============================================================================
bool CInputJoypad::GetPushCross(int nButton, int nId)
{
	//�O�񂪉���������Ă��Ȃ����A���݂�������Ă�����
	if (m_JoyPadState[nId].Old.rgdwPOV[0] == 0xFFFFFFFF && 
		m_JoyPadState[nId].Press.rgdwPOV[0] == nButton)
	{
		return true;
	}

	return false;
}

//=============================================================================
//�\���L�[�������ꂽ�u�Ԃ̔��菈��
//=============================================================================
bool CInputJoypad::GetPushRelease(int nButton, int nId)
{
	//�O�񂪉�����Ă��邩�A���݂�������Ă��Ȃ�
	if (m_JoyPadState[nId].Old.rgdwPOV[0] == nButton &&
		m_JoyPadState[nId].Press.rgdwPOV[0] == 0xFFFFFFFF)
	{
		return true;
	}
	return false;
}

LPDIRECTINPUTDEVICE8 CInputJoypad::GetController(int nNumber)
{
	return m_apDevice[nNumber];
}

//=====================================================
// �f�o�C�X�̐���
//=====================================================
BOOL CInputJoypad::EnumJoysticksCallback(const DIDEVICEINSTANCE * pdidInstance, VOID * pContext)
{
	HRESULT hr;

	hr = m_pInput->CreateDevice(pdidInstance->guidInstance, &m_apDevice[m_nJoyStickCont], NULL);

	m_nJoyStickCont++;

	if (FAILED(hr))
	{
		return DIENUM_CONTINUE;
	}

	return DIENUM_CONTINUE;
}

//=====================================================
// �R���g���[���[���̐ݒ�
//=====================================================
BOOL CInputJoypad::EnumAxesCallback(const DIDEVICEOBJECTINSTANCE * pdidoi, VOID * pContext)
{
	HRESULT     hr;
	DIPROPRANGE diprg;

	diprg.diph.dwSize = sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow = DIPH_BYID;
	diprg.diph.dwObj = pdidoi->dwType;
	diprg.lMin = 0 - 1000;
	diprg.lMax = 0 + 1000;

	for (int nCnt = 0; nCnt < m_nJoyStickCont; nCnt++)
	{
		hr = m_apDevice[nCnt]->SetProperty(DIPROP_RANGE, &diprg.diph);
	}


	if (FAILED(hr))
	{
		return DIENUM_CONTINUE;
	}

	return DIENUM_CONTINUE;
}

DIJOYSTATE CInputJoypad::GetStick(const int nID)
{
	DIJOYSTATE js = {};

	if (m_apDevice[nID] != NULL)
	{
		m_apDevice[nID]->Poll();
		m_apDevice[nID]->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	return js;

}

DIJOYSTATE2 CInputJoypad::GetStick2(const int nID)
{
	DIJOYSTATE2 js = {};

	if (m_apDevice[nID] != NULL)
	{
		m_apDevice[nID]->Poll();
		m_apDevice[nID]->GetDeviceState(sizeof(DIJOYSTATE2), &js);
	}
	return js;

}
