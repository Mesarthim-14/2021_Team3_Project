//=============================================================================
//
// �v���C���[�N���X [player.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"
#include "collision.h"
#include "fade.h"
#include "texture.h"
#include "resource_manager.h"
#include "motion.h"
#include "bullet.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED					(20.0f)							// �v���C���[�̈ړ���
#define STICK_SENSITIVITY				(50.0f)							// �X�e�B�b�N���x
#define PLAYER_ROT_SPEED				(0.1f)							// �L�����N�^�[�̉�]���鑬�x
#define PLAYER_RADIUS					(50.0f)							// ���a�̑傫��
#define BULLET_MOVE						(40.0f)							// �ړ���
#define SHIP_NUM						(0)								// �D�̃i���o�[
#define ANGLE_180						(D3DXToRadian(180))				// 180�x
#define ANGLE_90						(D3DXToRadian(90))				// 90�x
#define LENGTH							(-600.0f)						// ����
#define BULLET_Y						(500.0f)						// �e��Y��
//=============================================================================
// �N���G�C�g
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CPlayer *pPlayer = new CPlayer;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// ����������
		pPlayer->Init(pos, rot);
	}

	return pPlayer;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority)
{
	m_rotDest = ZeroVector3;
	m_bMove = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f���̏���n��
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER);
	}

	CCharacter::Init(pos, rot);												// ���W�@�p�x
	SetSpeed(PLAYER_SPEED);													// ���x�̐ݒ�

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{	
	// �I������
	CCharacter::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// ���W���
	D3DXVECTOR3 pos = GetPos();	// ���݂̍��W�擾
	SetPosOld(pos);				// �Â����W�ۑ�

	// �v���C���[�̏��
	UpdateState();

	// ���[�V�������
	UpdateMotionState();

	// �v���C���[�̐���
	PlayerControl();

	// �p�x�̍X�V����
	UpdateRot();

	// �e�N���X�̍X�V����
	CCharacter::Update();

	// �̗͂�0�ɂȂ�����
	if (GetLife() <= 0)
	{
		// ���񂾂Ƃ�
		Death();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	// �`�揈��
	CCharacter::Draw();
}

//=============================================================================
// �v���C���[�̏��
//=============================================================================
void CPlayer::UpdateState(void)
{

}

//=============================================================================
// ���[�V�������
//=============================================================================
void CPlayer::UpdateMotionState(void)
{
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();
	int nKey = GetMotion()->GetKey();
	int nCountMotion = GetMotion()->GetCountMotion();

	// ���[�V�������
	switch (MotionState)
	{
	case MOTION_IDOL:
		break;
	}
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
void CPlayer::PlayerControl()
{
	// �v���C���[�̈ړ�����
	Move();

	// �U������
	Attack();
}

//=============================================================================
// �p�x�̍X�V����
//=============================================================================
void CPlayer::UpdateRot(void)
{
	// �p�x�̎擾
	D3DXVECTOR3 rot = GetRot();

	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// �L�����N�^�[��]�̑��x
	rot += (m_rotDest - rot) * PLAYER_ROT_SPEED;

	// �p�x�̐ݒ�
	SetRot(rot);
}

//=============================================================================
// ���񂾂Ƃ��̏���
//=============================================================================
void CPlayer::Death(void)
{

}

//=============================================================================
// �ړ��̏���
//=============================================================================
void CPlayer::Move(void)
{
	// ���[�J���ϐ�
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();					// �L�[�{�[�h�X�V
	DIJOYSTATE js = CInputJoypad::GetStick(0);								// �W���C�p�b�h�̎擾
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();		// �T�E���h�̃|�C���^
	float fAngle = GET_CAMERA_PTR->GetHorizontal();							// �J�����̊p�x
	D3DXVECTOR3 pos = GetPos();												// ���W
	D3DXVECTOR3 rot = GetRot();												// �p�x
	float fSpeed = GetSpeed();												// �X�s�[�h
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();	// ���[�V�����̏��

	//���͂����݂���
	if ((js.lX != 0.0f || js.lY != 0.0f))
	{
		float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// �R���g���[���̊p�x
		float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);	// �R���g���[���̊p�x

		// �ړ��ʐݒ�
		pos.x += sinf(fAngle + (fAngle2))* fSpeed;
		pos.z += cosf(fAngle + (fAngle2))* fSpeed;

		// �p�x�̐ݒ�
		m_rotDest.y = fAngle + (fAngle3);
	}
	else
	{

	}

	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_W))
	{
		// �������[�V����
	//	SetMotion(MOTION_WALK);

		// �ړ��ʁE�p�x�̐ݒ�
		pos.x -= sinf(fAngle)*fSpeed;
		pos.z -= cosf(fAngle)*fSpeed;
		m_rotDest.y = fAngle;
		SetRot(D3DXVECTOR3(rot.x, fAngle, rot.z));
	}
	// ���Ɉړ�
	if (pKeyboard->GetPress(DIK_S))
	{
		// �������[�V����
	//	SetMotion(MOTION_WALK);

		// �ړ��ʁE�p�x�̐ݒ�
		pos.x += sinf((fAngle))*fSpeed;
		pos.z += cosf((fAngle))*fSpeed;
		m_rotDest.y = fAngle;
		SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(-180.0f), rot.z));

	}
	// ���Ɉړ�
	if (pKeyboard->GetPress(DIK_A))
	{
		// �������[�V����
	//	SetMotion(MOTION_WALK);

		// �ړ��ʁE�p�x�̐ݒ�
		pos.x += sinf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
		pos.z += cosf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
		m_rotDest.y = fAngle;
		SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(-90.0f), rot.z));

	}
	// �E�Ɉړ�
	if (pKeyboard->GetPress(DIK_D))
	{
		// �������[�V����
	//	SetMotion(MOTION_WALK);

		// �ړ��ʁE�p�x�̐ݒ�
		pos.x += sinf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
		pos.z += cosf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
		m_rotDest.y = fAngle;
		SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(90.0f), rot.z));
	}

	// ���W�ݒ�
	SetPos(pos);

	// �Â����W�擾
	D3DXVECTOR3 OldPos = GetOldPos();

	// �����Ă��Ȃ�������
	if (OldPos == pos)
	{
		// �ʏ탂�[�V����
		SetMotion(MOTION_IDOL);
	}
}

//=============================================================================
// �U������
//=============================================================================
void CPlayer::Attack(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	

	// SPACE�L�[���������ꍇ
	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		// �ړ���
		D3DXVECTOR3 bulletmove = ZeroVector3;

		// �����擾
		D3DXVECTOR3 rot = GetRot();
		
		// ���f���̏��擾
		CModelAnime *pAnime = GetModelAnime(SHIP_NUM);

		// �D�̈ʒu�擾
		D3DXVECTOR3 pos = D3DXVECTOR3(pAnime->GetMtxWorld()._41, pAnime->GetMtxWorld()._42, pAnime->GetMtxWorld()._43);

		// �ʒu
		D3DXVECTOR3 bulletpos = ZeroVector3;

		//���W�����߂�
		bulletpos.x = pos.x - cosf(rot.y + ANGLE_90) * LENGTH;
		bulletpos.z = pos.z + sinf(rot.y + ANGLE_90) * LENGTH;
		bulletpos.y = BULLET_Y;

		// �e�̈ړ�
		bulletmove.x = sinf(rot.y + ANGLE_180) *BULLET_MOVE;
		bulletmove.z = cosf(rot.y + ANGLE_180) *BULLET_MOVE;

		// �e����
		CBullet::Create(bulletpos, ZeroVector3, bulletmove);
	}
}