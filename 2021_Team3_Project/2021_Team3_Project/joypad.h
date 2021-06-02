#ifndef _JOYPAD_H_
#define _JOYPAD_H_

//=======================================================================
//
// �W���C�p�b�h�N���X�w�b�_ [joypad.h]
// Author : Konishi Yuuto
//
//=======================================================================

//=======================================================================
// �C���N���[�h�t�@�C��
//=======================================================================
#include "main.h"
#include "input.h"

//=======================================================================
//�}�N����`
//=======================================================================
#define MAX_JOYSTICK_NUM 4// JOYPAD�ڑ����
#define	NUM_JOY_MAX 32   // �{�^���̍ő吔
#define CROSS_KEY_UP	0				//�\���L�[��
#define CROSS_KEY_TOP_RIGHT 4500		//�\���L�[�E��
#define CROSS_KEY_RIGHT	9000			//�\���L�[�E
#define CROSS_KEY_BOTTOM_RIGHT 13500	//�\���L�[�E��
#define CROSS_KEY_DOWN	18000			//�\���L�[��
#define CROSS_KEY_BOTTOM_LEFT 22500		//�\���L�[����
#define CROSS_KEY_LEFT	27000			//�\���L�[��
#define CROSS_KEY_TOP_LEFT	31500		//�\���L�[����

//=======================================================================
//�W���C�p�b�h�N���X
//=======================================================================
class CInputJoypad : public CInput
{
public:
	//=============================================================================
	//�W���C�p�b�h�{�^���p�̗񋓌^��`
	//=============================================================================
	typedef enum
	{
		JOY_BUTTON_X = 0,		// X�{�^��
		JOY_BUTTON_Y,			// Y�{�^��
		JOY_BUTTON_A,			// A�{�^��
		JOY_BUTTON_B,			// B�{�^��
		JOY_BUTTON_L_TRIGGER,	// L�g���K�[�{�^��
		JOY_BUTTON_R_TRIGGER,	// R�g���K�[�{�^��
		JOY_BUTTON_L2_TRIGGER,	// L�g���K�[�{�^��2
		JOY_BUTTON_R2_TRIGGER,	// R�g���K�[�{�^��2
		JOY_BUTTON_L3,			// L�{�^��
		JOY_BUTTON_R3,			// R�{�^��
		JOY_BUTTON_SELECT,		// SELECT�{�^��
		JOY_BUTTON_START,		// START�{�^��
		JOY_BUTTON_HOME,		// HOME�{�^��
		JOY_BUTTON_MAX,			// �ő�{�^����
	}JOY_BUTTON;

	// �W���C�p�b�h��Ԕ��ʗp�̍\���̒�`
	typedef struct
	{
		DIJOYSTATE	Old;		//�p�b�h�{�^���̑O����
		DIJOYSTATE	Press;		//�p�b�h�{�^���̃v���X���
		DIJOYSTATE	Trigger;	//�p�b�h�{�^���̃g���K�[���
		DIJOYSTATE	Release;	//�p�b�h�{�^���̃����[�X���
	}JoyStickState;

	//�����o�֐�
	CInputJoypad();				// �R���X�g���N�^
	virtual ~CInputJoypad();	// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����

	bool GetJoystickPress(int nKey, int nId);		// �v���X���
	bool GetJoystickTrigger(int nKey, int nId);		// �g���K�[���
	bool GetJoystickRelease(int nKey, int nId);		// �����[�X���
	bool GetPushCross(int nButton, int nId);
	bool GetPushRelease(int nButton, int nId);
	static LPDIRECTINPUTDEVICE8 GetController(int nNumber);

	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);

	// �����o�ϐ�
	BYTE m_aJoyState[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};          // �W���C�p�b�h�̓��͏�񃏁[�N
	BYTE m_aJoyStateTrigger[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};   // �W���C�p�b�h�̃g���K�[���
	BYTE m_aJoyStateRelease[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};   // �W���C�p�b�h�̃����[�X���
	static DIJOYSTATE CInputJoypad::GetStick(const int nID);
	static DIJOYSTATE2 CInputJoypad::GetStick2(const int nID);

private:
	static LPDIRECTINPUTDEVICE8 m_apDevice[MAX_JOYSTICK_NUM];	// �f�o�C�X
	JoyStickState m_JoyPadState[MAX_JOYSTICK_NUM];				// �W���C�p�b�h�̏��
	DIDEVCAPS   m_diDevCaps;
	static int m_nJoyStickCont;
};

#endif