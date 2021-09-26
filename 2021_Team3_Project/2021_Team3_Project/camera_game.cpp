//=============================================================================
//
// �J�����̏��� [camera.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "camera_game.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "joypad.h"
#include "motion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CAMERA_DEFAULT_F��			(D3DXToRadian(75.0f))			// �J�����̃�Default�l
#define DISTANCE					(2200.0f)						// ���_�`�����_�̋���
#define DISTANCE_FAR_UP				(35.0f)							// �J�����������l
#define FAR_DISTANCE				(3000.0f)						// ���߂̃J����
#define PLAYER_HEIGHT				(600.0f)						// �����_�̍���
#define CAMERA_MIN_F��				(D3DXToRadian(10.0f))			// �J�����̍ŏ��p
#define CAMERA_MAX_F��				(D3DXToRadian(170.0f))			// �J�����̍ő�p
#define CAMERA_MIN_HIGHT			(2.0f)							// �J�����̍Œፂ�x
#define STICK_SENSITIVITY			(100.0f)						// �X�e�B�b�N���x
#define STICK_INPUT_CONVERSION		(D3DXToRadian(2.0f))			// �X�e�B�b�N���͕ω���
#define HEIGHT_DIVIDE				(1.5f)							// ������

//=============================================================================
// �C���X�^���X����
//=============================================================================
CCameraGame * CCameraGame::Create(void)
{
	// �������m��
	CCameraGame *pCamera = new CCameraGame;

	// ����������
	pCamera->Init();

	return pCamera;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCameraGame::CCameraGame()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCameraGame::~CCameraGame()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCameraGame::Init(void)
{
	// ����������
	CCamera::Init();

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CCameraGame::Update(void)
{
	// �J�����̍X�V����
	CCamera::Update();
}

//=============================================================================
// �ʏ��Ԃ̍X�V����
//=============================================================================
void CCameraGame::NomalUpdate(D3DXVECTOR3 PlayerPos, D3DXVECTOR3 PlayerRot)
{
	//�L�[�{�[�h�N���X���̎擾
	CInputKeyboard *pKeyInput = CManager::GetKeyboard();

	// �W���C�p�b�h�̎擾
	DIJOYSTATE js = CInputJoypad::GetStick(0);

	// �p�x�̎擾
	float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// �R���g���[���̊p�x
	float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);	// �R���g���[���̊p�x
	float fAngle = GetHorizontal();							// �J�����̊p�x

	// �J�������W
	D3DXVECTOR3 VDest = ZeroVector3;
	D3DXVECTOR3 posRDest = GetposRDest();
	float fDistance = GetDistance();
	float fVartical = GetVartical();

	// �J�����̈ʒu�ݒ�
	VDest.x = PlayerPos.x + fDistance * sinf(fVartical) * sinf(PlayerRot.y);	// �J�����ʒuX�ݒ�
	VDest.y = PlayerPos.y + PLAYER_HEIGHT + fDistance * cosf(fVartical);		// �J�����ʒuY�ݒ�
	VDest.z = PlayerPos.z + fDistance * sinf(fVartical) * cosf(PlayerRot.y);	// �J�����ʒuZ�ݒ�

	posRDest = D3DXVECTOR3(PlayerPos.x, PlayerPos.y + PLAYER_HEIGHT, PlayerPos.z);	//�����_�ݒ�

	//�J����POSY�̉���
	if (VDest.y <= CAMERA_MIN_HIGHT)
	{
		VDest.y = CAMERA_MIN_HIGHT;	//���E�l�ɖ߂�
	}

	//�ݒ�l�̔��f
	GetposV() += (VDest - GetposV())*0.1f;
	GetposR() += (posRDest - GetposR())*0.9f;
}