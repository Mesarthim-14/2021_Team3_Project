#ifndef _JOYPAD_H_
#define _JOYPAD_H_

//=======================================================================
//
// ジョイパッドクラスヘッダ [joypad.h]
// Author : Konishi Yuuto
//
//=======================================================================

//=======================================================================
// インクルードファイル
//=======================================================================
#include "main.h"
#include "input.h"

//=======================================================================
//マクロ定義
//=======================================================================
#define MAX_JOYSTICK_NUM 4// JOYPAD接続上限
#define	NUM_JOY_MAX 32   // ボタンの最大数
#define CROSS_KEY_UP	0				//十字キー上
#define CROSS_KEY_TOP_RIGHT 4500		//十字キー右上
#define CROSS_KEY_RIGHT	9000			//十字キー右
#define CROSS_KEY_BOTTOM_RIGHT 13500	//十字キー右下
#define CROSS_KEY_DOWN	18000			//十字キー下
#define CROSS_KEY_BOTTOM_LEFT 22500		//十字キー左下
#define CROSS_KEY_LEFT	27000			//十字キー左
#define CROSS_KEY_TOP_LEFT	31500		//十字キー左上

//=======================================================================
//ジョイパッドクラス
//=======================================================================
class CInputJoypad : public CInput
{
public:
	//=============================================================================
	//ジョイパッドボタン用の列挙型定義
	//=============================================================================
	typedef enum
	{
		JOY_BUTTON_X = 0,		// Xボタン
		JOY_BUTTON_Y,			// Yボタン
		JOY_BUTTON_A,			// Aボタン
		JOY_BUTTON_B,			// Bボタン
		JOY_BUTTON_L_TRIGGER,	// Lトリガーボタン
		JOY_BUTTON_R_TRIGGER,	// Rトリガーボタン
		JOY_BUTTON_L2_TRIGGER,	// Lトリガーボタン2
		JOY_BUTTON_R2_TRIGGER,	// Rトリガーボタン2
		JOY_BUTTON_L3,			// Lボタン
		JOY_BUTTON_R3,			// Rボタン
		JOY_BUTTON_SELECT,		// SELECTボタン
		JOY_BUTTON_START,		// STARTボタン
		JOY_BUTTON_HOME,		// HOMEボタン
		JOY_BUTTON_MAX,			// 最大ボタン数
	}JOY_BUTTON;

	// ジョイパッド状態判別用の構造体定義
	typedef struct
	{
		DIJOYSTATE	Old;		//パッドボタンの前回情報
		DIJOYSTATE	Press;		//パッドボタンのプレス情報
		DIJOYSTATE	Trigger;	//パッドボタンのトリガー情報
		DIJOYSTATE	Release;	//パッドボタンのリリース情報
	}JoyStickState;

	//メンバ関数
	CInputJoypad();				// コンストラクタ
	virtual ~CInputJoypad();	// デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理

	bool GetJoystickPress(int nKey, int nId);		// プレス情報
	bool GetJoystickTrigger(int nKey, int nId);		// トリガー情報
	bool GetJoystickRelease(int nKey, int nId);		// リリース情報
	bool GetPushCross(int nButton, int nId);
	bool GetPushRelease(int nButton, int nId);
	static LPDIRECTINPUTDEVICE8 GetController(int nNumber);

	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);

	// メンバ変数
	BYTE m_aJoyState[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};          // ジョイパッドの入力情報ワーク
	BYTE m_aJoyStateTrigger[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};   // ジョイパッドのトリガー情報
	BYTE m_aJoyStateRelease[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};   // ジョイパッドのリリース情報
	static DIJOYSTATE CInputJoypad::GetStick(const int nID);
	static DIJOYSTATE2 CInputJoypad::GetStick2(const int nID);

private:
	static LPDIRECTINPUTDEVICE8 m_apDevice[MAX_JOYSTICK_NUM];	// デバイス
	JoyStickState m_JoyPadState[MAX_JOYSTICK_NUM];				// ジョイパッドの状態
	DIDEVCAPS   m_diDevCaps;
	static int m_nJoyStickCont;
};

#endif