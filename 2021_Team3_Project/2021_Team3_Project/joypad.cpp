//=============================================================================
//
// ジョイパッドクラスの処理[joypad.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "joypad.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
int CInputJoypad::m_nJoyStickCont = 0;
LPDIRECTINPUTDEVICE8  CInputJoypad::m_apDevice[MAX_JOYSTICK_NUM] = {};

//=====================================================
// コンストラクタ
//=====================================================
CInputJoypad::CInputJoypad()
{
	memset(m_aJoyState, 0, sizeof(m_aJoyState));
	memset(m_aJoyStateTrigger, 0, sizeof(m_aJoyState));
	memset(m_aJoyStateRelease, 0, sizeof(m_aJoyState));
	memset(m_JoyPadState, 0, sizeof(m_JoyPadState));
}

//=====================================================
// デストラクタ
//=====================================================
CInputJoypad::~CInputJoypad()
{
}

//=====================================================
// 初期化処理
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
// 終了処理
//=====================================================
void CInputJoypad::Uninit(void)
{
	// 入力デバイス(キーボード)の開放
	for (int nCnt = 0; nCnt < MAX_JOYSTICK_NUM; nCnt++)
	{
		if (m_apDevice[nCnt] != NULL)
		{
			// キーボードへのアクセス権を開放(入力制御終了)
			m_apDevice[nCnt]->Unacquire();
			m_apDevice[nCnt]->Release();
			m_apDevice[nCnt] = NULL;
		}
	}
	CInput::Uninit();
}

//=====================================================
// 更新処理
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
			//１フレーム前の状態を保存
			m_JoyPadState[nCnt].Old.rgdwPOV[0] = m_JoyPadState[nCnt].Press.rgdwPOV[0];

			m_apDevice[nCnt]->Poll();

			hr = m_apDevice[nCnt]->GetDeviceState(sizeof(DIJOYSTATE), &js);

			//デバイスからデータを取得
			if (SUCCEEDED(hr))
			{
				//十字キーの情報を保存
				m_JoyPadState[nCnt].Press.rgdwPOV[0] = js.rgdwPOV[0];

				for (nCntKey = 0; nCntKey < NUM_JOY_MAX; nCntKey++)
				{
					//キートリガー
					m_aJoyStateTrigger[nCntKey][nCnt] = (m_aJoyState[nCntKey][nCnt] ^ js.rgbButtons[nCntKey]) &  js.rgbButtons[nCntKey];

					//キーリリース
					m_aJoyStateRelease[nCntKey][nCnt] = (m_aJoyState[nCntKey][nCnt] ^ js.rgbButtons[nCntKey]) & ~js.rgbButtons[nCntKey];

					//キープレス情報を保存
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
// プレス情報の取得
//=====================================================
bool CInputJoypad::GetJoystickPress(int nKey, int nId)
{
	return m_aJoyState[nKey][nId] & 0x80 ? true : false;
}

//=====================================================
// トリガー情報の取得
//=====================================================
bool CInputJoypad::GetJoystickTrigger(int nKey, int nId)
{
	return m_aJoyStateTrigger[nKey][nId] & 0x80 ? true : false;
}

//=====================================================
// リリース情報の取得
//=====================================================
bool CInputJoypad::GetJoystickRelease(int nKey, int nId)
{
	return m_aJoyStateRelease[nKey][nId] & 0x80 ? true : false;
}

//=============================================================================
//十字キーが押された瞬間の判定処理
//=============================================================================
bool CInputJoypad::GetPushCross(int nButton, int nId)
{
	//前回が何も押されていないかつ、現在が押されていたら
	if (m_JoyPadState[nId].Old.rgdwPOV[0] == 0xFFFFFFFF && 
		m_JoyPadState[nId].Press.rgdwPOV[0] == nButton)
	{
		return true;
	}

	return false;
}

//=============================================================================
//十字キーが離された瞬間の判定処理
//=============================================================================
bool CInputJoypad::GetPushRelease(int nButton, int nId)
{
	//前回が押されているかつ、現在が押されていない
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
// デバイスの生成
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
// コントローラー情報の設定
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
