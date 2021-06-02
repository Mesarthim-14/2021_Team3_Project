//=============================================================================
//
// キーボードクラス [keyboard.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "keyboard.h"

//=============================================================================
//キーボードクラスのコンストラクタ
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	m_pDevice = NULL;	//入力デバイス

	//各メンバ変数を0クリア
	memset(m_aKeyState, 0, sizeof(m_aKeyState));
	memset(m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
}

//=============================================================================
//キーボードクラスのデストラクタ
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//=============================================================================
//キーボードクラスの初期化処理
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//入力処理クラスの初期化処理呼び出し
	CInput::Init(hInstance, hWnd);

	//入力デバイス（キーボード）の作成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマット設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定（ファオグラウンド＆非排他モード）
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得（入力制御開始）
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
//キーボードクラスの終了処理
//=============================================================================
void CInputKeyboard::Uninit(void)
{ 
	//入力処理クラスの終了処理呼び出し
	CInput::Uninit();
}

//=============================================================================
//キーボードクラスの更新処理
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[MAX_KEY_NUM];	//キーボードの入力情報

	//デバイスからデータ取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (int nCntKey = 0; nCntKey < MAX_KEY_NUM; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&~aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	//キープレス情報を保存
		}
	}
	else
	{
		//キーボードへのアクセス権を取得
		m_pDevice->Acquire();
	}
}

//=============================================================================
//キーボードのプレス情報の取得
//=============================================================================
BOOL CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
//キーボードのトリガー情報の取得
//=============================================================================
BOOL CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
//キーボードのリリース情報の取得
//=============================================================================
BOOL CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}