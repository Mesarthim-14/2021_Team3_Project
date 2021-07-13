//=============================================================================
//
// �v���C���[�N���X [player.cpp]
// Author : Sugawara Tsukasa
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
#include "character_box.h"
#include "player_bullet.h"
#include "map.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED					(10.0f)									// �v���C���[�̈ړ���
#define STICK_SENSITIVITY				(50.0f)									// �X�e�B�b�N���x
#define PLAYER_ROT_SPEED				(0.1f)									// �L�����N�^�[�̉�]���鑬�x
#define SHIP_NUM						(0)										// �D�̃i���o�[
#define GEAR_R_NUM						(1)										// �������̉E�i���o�[
#define GEAR_L_NUM						(2)										// �������̍��i���o�[
#define BATTERY_R_NUM					(3)										// �C��E�̃i���o�[
#define BATTERY_L_NUM					(4)										// �C�䍶�̃i���o�[
#define MIN_MOVE						(D3DXVECTOR3(0.0f,0.0f,0.0f))			// �ړ��ʂ̍ŏ��l
#define SIZE							(D3DXVECTOR3 (800.0f,900.0f,800.0f))	// �T�C�Y
#define PARENT_NUM						(0)										// �e�̃i���o�[
#define GEAR_SPIN_ANGLE					(D3DXToRadian(2.0f))					// ���Ԃ̉�]�p�x
#define SPIN_ANGLE						(D3DXToRadian(1.0f))					// ����p�x
#define STICK_INPUT_ZONE				(100)									// �X�e�B�b�N�̓��͔͈�
#define STICK_INPUT_ZONE_2				(1000)									// �X�e�B�b�N�̓��͔͈�
#define STICK_INPUT_ZERO				(0)										// �X�e�B�b�N�̓��͒l0
#define MUT_SPEED						(1.5f)									// �X�s�[�h
#define PAD_1							(0)										// 1�Ԗڂ̃p�b�h
#define PAD_2							(1)										// 2�Ԗڂ̃p�b�h
#define ATTACK_COOLTIME					(90)									// �U���̃N�[���^�C��
#define RAY_NUM							(4)										// ���C�̐�
#define RAY_RADIUS						(D3DXToRadian(360.0f/4.0f))				// ���C���o������
#define RAY_RADIUS_UNDER				(D3DXToRadian(-180.0f))					// ���C���o������
#define RAY_HIT_RANGE					(500.0f)								// �͈�
#define RAY_HIT_RANGE_UNDER				(0.0f)									// �͈�
#define MIN_LIFE						(0)										// ���C�t�̍ŏ�
// �D�̂̈ʒu
#define SHIP_POS						(D3DXVECTOR3(pShip->GetMtxWorld()._41, pShip->GetMtxWorld()._42 + 2.0f, pShip->GetMtxWorld()._43))
// �C��̈ʒu
#define BATTERY_R_POS					(D3DXVECTOR3(pBattery_R->GetMtxWorld()._41, pBattery_R->GetMtxWorld()._42, pBattery_R->GetMtxWorld()._43))
#define BATTERY_L_POS					(D3DXVECTOR3(pBattery_L->GetMtxWorld()._41, pBattery_L->GetMtxWorld()._42, pBattery_L->GetMtxWorld()._43))

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

		// ������
		CCharacter_Box::Create(pos, rot, pPlayer);
	}

	// �|�C���^��Ԃ�
	return pPlayer;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority)
{
	m_rotDest			= ZeroVector3;
	m_bMove				= false;
	m_nAttackCount_R	= ZERO_INT;
	m_nAttackCount_L	= ZERO_INT;
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

	// ������
	CCharacter::Init(pos, rot);

	// �T�C�Y�ݒ�
	SetSize(SIZE);

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
	// �e�N���X�̍X�V����
	CCharacter::Update();

	// ���W���
	D3DXVECTOR3 pos = GetPos();

	// �Â����W�ۑ�
	SetPosOld(pos);				

	// �v���C���[�̏��
	UpdateState();

	// �v���C���[�̐���
	PlayerControl();

	// �p�x�̍X�V����
	UpdateRot();

	// �̗͂�0�ɂȂ�����
	if (GetLife() <= MIN_LIFE)
	{
		// ���S��Ԃɐݒ�
		SetState(CCharacter::STATE_DEAD);
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
	// ��Ԏ擾
	int nState = GetState();

	// DEAD�̏ꍇ
	if (nState = CCharacter::STATE_DEAD)
	{
		// ���S����
		Death();
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

	// �����蔻��
	Collision();

	// �}�b�v�Ƃ̓����蔻��
	//RayCollision();
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
	// �I��
	Uninit();

	return;
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
	D3DXVECTOR3 pos = GetPos();												// ���W
	D3DXVECTOR3 rot = GetRot();												// �p�x
	float fSpeed = GetSpeed();												// �X�s�[�h
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();	// ���[�V�����̏��

	// ���̎��Ԃ̏��擾
	CModelAnime *pGear_L = GetModelAnime(GEAR_L_NUM);
	// �����擾
	D3DXVECTOR3 Gear_L_rot = pGear_L->GetRot();

	// �E�̎��Ԃ̏��擾
	CModelAnime *pGear_R = GetModelAnime(GEAR_R_NUM);
	// �����擾
	D3DXVECTOR3 Gear_R_rot = pGear_R->GetRot();

	////���͂����݂���
	//if ((js.lX != 0.0f || js.lY != 0.0f))
	//{
	//	float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// �R���g���[���̊p�x
	//	float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);	// �R���g���[���̊p�x

	//	// �ړ��ʐݒ�
	//	move.x = sinf(fAngle + (fAngle2))* fSpeed;
	//	move.z = cosf(fAngle + (fAngle2))* fSpeed;

	//	// �p�x�̐ݒ�
	//	m_rotDest.y = fAngle + (fAngle3);
	//}

	//// �O�Ɉړ�
	//if (pKeyboard->GetPress(DIK_W))
	//{
	//	// �ړ��ʁE�p�x�̐ݒ�
	//	move.x = -sinf(fAngle)*fSpeed;
	//	move.z = -cosf(fAngle)*fSpeed;
	//	m_rotDest.y = fAngle;
	//	SetRot(D3DXVECTOR3(rot.x, fAngle, rot.z));
	//}
	//// ���Ɉړ�
	//if (pKeyboard->GetPress(DIK_S))
	//{
	//	// �ړ��ʁE�p�x�̐ݒ�
	//	move.x = sinf((fAngle))*fSpeed;
	//	move.z = cosf((fAngle))*fSpeed;
	//	m_rotDest.y = fAngle;
	//	SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(-180.0f), rot.z));
	//}
	//// ���Ɉړ�
	//if (pKeyboard->GetPress(DIK_A))
	//{
	//	// �ړ��ʁE�p�x�̐ݒ�
	//	move.x = sinf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
	//	move.z = cosf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
	//	m_rotDest.y = fAngle;
	//	SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(-90.0f), rot.z));
	//}
	//// �E�Ɉړ�
	//if (pKeyboard->GetPress(DIK_D))
	//{
	//	// �ړ��ʁE�p�x�̐ݒ�
	//	move.x = sinf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
	//	move.z = cosf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
	//	m_rotDest.y = fAngle;
	//	SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(90.0f), rot.z));
	//}

//===========================================
// �E����
//===========================================
	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_UP) || js.lRz < -STICK_INPUT_ZONE && js.lZ == STICK_INPUT_ZERO ||
		js.lRz < -STICK_INPUT_ZONE && js.lZ < -STICK_INPUT_ZONE && js.lZ > -STICK_INPUT_ZONE_2 ||
		js.lRz < -STICK_INPUT_ZONE && js.lZ > STICK_INPUT_ZONE && js.lZ < STICK_INPUT_ZONE_2)
		
	{
		// �������Z
		Gear_R_rot.x -= GEAR_SPIN_ANGLE;

		// �����ݒ�
		pGear_R->SetRot(Gear_R_rot);

		// �ړ�
		pos.x += -sinf(rot.y)*fSpeed;
		pos.z += -cosf(rot.y)*fSpeed;

		// �ړI�̌���
		m_rotDest.y = rot.y;
	}
	// ���Ɉړ�
	if (pKeyboard->GetPress(DIK_DOWN) || js.lRz > STICK_INPUT_ZONE && js.lZ == STICK_INPUT_ZERO ||
		js.lRz > STICK_INPUT_ZONE && js.lZ > STICK_INPUT_ZONE && js.lZ < STICK_INPUT_ZONE_2 ||
		js.lRz > STICK_INPUT_ZONE && js.lZ < -STICK_INPUT_ZONE && js.lZ > -STICK_INPUT_ZONE_2)
	{
		// �������Z
		Gear_R_rot.x += GEAR_SPIN_ANGLE;

		// �����ݒ�
		pGear_R->SetRot(Gear_R_rot);

		// �ړ�
		pos.x += -sinf(rot.y)*-fSpeed;
		pos.z += -cosf(rot.y)*-fSpeed;

		// �ړI�̌���
		m_rotDest.y = rot.y;
	}

	// ���Ɉړ�
	if (pKeyboard->GetPress(DIK_LEFT) || js.lZ < -STICK_INPUT_ZONE && js.lRz == STICK_INPUT_ZERO ||
		js.lZ < -STICK_INPUT_ZONE && js.lRz < -STICK_INPUT_ZONE && js.lRz > -STICK_INPUT_ZONE_2 ||
		js.lZ < -STICK_INPUT_ZONE && js.lRz > STICK_INPUT_ZONE && js.lRz < STICK_INPUT_ZONE_2)
		
	{
		// �������Z
		Gear_R_rot.x -= GEAR_SPIN_ANGLE;

		// �����ݒ�
		pGear_R->SetRot(Gear_R_rot);

		// �ړ�
		pos.x += -sinf(rot.y)*fSpeed;
		pos.z += -cosf(rot.y)*fSpeed;

		// ����
		rot.y = rot.y - SPIN_ANGLE;

		// �ړI�̌���
		m_rotDest.y = rot.y;
	}
	// �E�Ɉړ�
	if (pKeyboard->GetPress(DIK_RIGHT) || js.lZ > STICK_INPUT_ZONE && js.lRz == STICK_INPUT_ZERO ||
		js.lZ > STICK_INPUT_ZONE && js.lRz > STICK_INPUT_ZONE && js.lRz < STICK_INPUT_ZONE_2 ||
		js.lZ > STICK_INPUT_ZONE && js.lRz < -STICK_INPUT_ZONE && js.lRz > -STICK_INPUT_ZONE_2)
		
	{
		// �������Z
		Gear_R_rot.x += GEAR_SPIN_ANGLE;

		// �����ݒ�
		pGear_R->SetRot(Gear_R_rot);

		// �ړ�
		pos.x += -sinf(rot.y)*fSpeed;
		pos.z += -cosf(rot.y)*fSpeed;

		// ����
		rot.y = rot.y + SPIN_ANGLE;

		// �ړI�̌���
		m_rotDest.y = rot.y;
	}
//===========================================
// ������
//===========================================
	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_W) || js.lY < -STICK_INPUT_ZONE && js.lX == STICK_INPUT_ZERO ||
		js.lY < -STICK_INPUT_ZONE && js.lX < -STICK_INPUT_ZONE && js.lX > -STICK_INPUT_ZONE_2||
		js.lY < -STICK_INPUT_ZONE && js.lX > STICK_INPUT_ZONE && js.lX < STICK_INPUT_ZONE_2)
	{
		// �������Z
		Gear_L_rot.x -= GEAR_SPIN_ANGLE;

		// �����ݒ�
		pGear_L->SetRot(Gear_L_rot);

		// �ړ�
		pos.x += -sinf(rot.y)*fSpeed;
		pos.z += -cosf(rot.y)*fSpeed;

		// �ړI�̌���
		m_rotDest.y= rot.y;
	}
	// ���Ɉړ�
	if (pKeyboard->GetPress(DIK_S) || js.lY > STICK_INPUT_ZONE && js.lX == STICK_INPUT_ZERO ||
		js.lY > STICK_INPUT_ZONE && js.lX > STICK_INPUT_ZONE && js.lX < STICK_INPUT_ZONE_2 ||
		js.lY > STICK_INPUT_ZONE && js.lX < -STICK_INPUT_ZONE && js.lX > -STICK_INPUT_ZONE_2)
	{
		// �������Z
		Gear_L_rot.x += GEAR_SPIN_ANGLE;

		// �����ݒ�
		pGear_L->SetRot(Gear_L_rot);

		// �ړ�
		pos.x += -sinf(rot.y)*-fSpeed;
		pos.z += -cosf(rot.y)*-fSpeed;

		// �ړI�̌���
		m_rotDest.y = rot.y;
	}

	// ���Ɉړ�
	if (pKeyboard->GetPress(DIK_A) || js.lX < -STICK_INPUT_ZONE && js.lY == STICK_INPUT_ZERO ||
		js.lX < -STICK_INPUT_ZONE && js.lY < -STICK_INPUT_ZONE && js.lY > -STICK_INPUT_ZONE_2 ||
		js.lX < -STICK_INPUT_ZONE && js.lY > STICK_INPUT_ZONE && js.lY < STICK_INPUT_ZONE_2)
	{
		// �������Z
		Gear_L_rot.x += GEAR_SPIN_ANGLE;

		// �����ݒ�
		pGear_L->SetRot(Gear_L_rot);

		// �ړ�
		pos.x += -sinf(rot.y)*fSpeed;
		pos.z += -cosf(rot.y)*fSpeed;

		// ����
		rot.y = rot.y - SPIN_ANGLE;

		// �ړI�̌���
		m_rotDest.y = rot.y;
	}
	// �E�Ɉړ�
	if (pKeyboard->GetPress(DIK_D) || js.lX > STICK_INPUT_ZONE && js.lY == STICK_INPUT_ZERO ||
		js.lX > STICK_INPUT_ZONE && js.lY > STICK_INPUT_ZONE && js.lY < STICK_INPUT_ZONE_2 ||
		js.lX > STICK_INPUT_ZONE && js.lY < -STICK_INPUT_ZONE && js.lY > -STICK_INPUT_ZONE_2)
	{
		// �������Z
		Gear_L_rot.x -= GEAR_SPIN_ANGLE;

		// �����ݒ�
		pGear_L->SetRot(Gear_L_rot);

		// �ړ�
		pos.x += -sinf(rot.y)*fSpeed;
		pos.z += -cosf(rot.y)*fSpeed;

		// ����
		rot.y = rot.y + SPIN_ANGLE;

		// �ړI�̌���
		m_rotDest.y = rot.y;
	}
	// ����
	SetRot(rot);

	// �ʒu�ݒ�
	SetPos(pos);
}

//=============================================================================
// �U������
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Attack(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	

	// �W���C�p�b�h�擾
	CInputJoypad *pJoypad = CManager::GetJoypad();

	// ���f���̏��擾
	CModelAnime *pBattery_R = GetModelAnime(BATTERY_R_NUM);

	// ���f���̏��擾
	CModelAnime *pBattery_L = GetModelAnime(BATTERY_L_NUM);

	// �����擾
	D3DXVECTOR3 rot = GetRot();

	// SPACE�L�[���������ꍇ
	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		// �E�e����
		CPlayer_Bullet::Create(BATTERY_R_POS, rot);
		// ���e����
		CPlayer_Bullet::Create(BATTERY_L_POS, rot);
	}

	// �J�E���g��0�̏ꍇ
	if (m_nAttackCount_R == ZERO_INT)
	{
		// RT�g���K�[���������ꍇ
		if (pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, PAD_1)||
			pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, PAD_1))
		{
			// �E�e����
			CPlayer_Bullet::Create(BATTERY_R_POS, rot);

			// �C���N�������g
			m_nAttackCount_R++;
		}
	}
	// �J�E���g��0�̏ꍇ
	if (m_nAttackCount_L == ZERO_INT)
	{
		// LT�g���K�[���������ꍇ
		if (pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L2_TRIGGER, PAD_1) ||
			pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L_TRIGGER, PAD_1))
		{
			// ���e����
			CPlayer_Bullet::Create(BATTERY_L_POS, rot);

			// �C���N�������g
			m_nAttackCount_L++;
		}
	}
	// �J�E���g��0��葽���ꍇ
	if (m_nAttackCount_R > ZERO_INT)
	{
		// �C���N�������g
		m_nAttackCount_R++;

		// �J�E���g��60�̏ꍇ
		if (m_nAttackCount_R >= ATTACK_COOLTIME)
		{
			// 0��
			m_nAttackCount_R = ZERO_INT;
		}
	}
	// �J�E���g��0��葽���ꍇ
	if (m_nAttackCount_L > ZERO_INT)
	{
		// �C���N�������g
		m_nAttackCount_L++;

		// �J�E���g��60�̏ꍇ
		if (m_nAttackCount_L >= ATTACK_COOLTIME)
		{
			// 0��
			m_nAttackCount_L = ZERO_INT;
		}
	}
}
//=============================================================================
// �����蔻�菈��
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Collision(void)
{
	// CScene�̃|�C���^
	CScene *pScene = nullptr;

	// ���f���̏��擾
	CModelAnime *pAnime = GetModelAnime(SHIP_NUM);

	// �ʒu�擾
	D3DXVECTOR3 pos = D3DXVECTOR3(pAnime->GetMtxWorld()._41, pAnime->GetMtxWorld()._42, pAnime->GetMtxWorld()._43);

	// �ʒu�擾
	D3DXVECTOR3 posOld = D3DXVECTOR3(pAnime->GetOldMtxWorld()._41, pAnime->GetOldMtxWorld()._42, pAnime->GetOldMtxWorld()._43);

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// nullcheck
	if (pScene == nullptr)
	{
		// �擪�̃|�C���^�擾
		pScene = GetTop(PRIORITY_ENEMY);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcter�Ƃ̓����蔻��
			while (pScene != nullptr) // nullptr�ɂȂ�܂ŉ�
			{
				// ���݂̃|�C���^
				CScene *pSceneCur = pScene->GetNext();

				// �ʒu
				D3DXVECTOR3 CharacterPos = ZeroVector3;

				// �ʒu�擾
				CharacterPos.x = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._41;
				CharacterPos.y = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._42;
				CharacterPos.z = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._43;

				// �T�C�Y�擾
				D3DXVECTOR3 CharacterSize = ((CCharacter*)pScene)->GetSize();

				//�ǂ��̖ʂɓ����������擾
				//��
				if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_DOWN)
				{
					// �ړ��ʎ擾
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// �ړ���0
					CharacterMove.y = MIN_MOVE.y;

					// �ړ��ʐݒ�
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// �ʒu
					pos.y = (-CharacterSize.y / DIVIDE_2 + CharacterPos.y) - (size.y / DIVIDE_2);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ��
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_UP)
				{
					// �ړ��ʎ擾
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// �ړ���0
					CharacterMove.y = MIN_MOVE.y;

					// �ړ��ʐݒ�
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// �ʒu
					pos.y = (CharacterSize.y / DIVIDE_2 + CharacterPos.y) + (size.y / DIVIDE_2);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ��
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_LEFT)
				{
					// �ړ��ʎ擾
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// �ړ���0
					CharacterMove.x = MIN_MOVE.x;

					// �ړ��ʐݒ�
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// �ʒu
					pos.x = (-CharacterSize.x / DIVIDE_2 + CharacterPos.x) - (size.x / DIVIDE_2);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// �E
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_RIGHT)
				{
					// �ړ��ʎ擾
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// �ړ���0
					CharacterMove.x = MIN_MOVE.x;

					// �ړ��ʐݒ�
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// �ʒu
					pos.x = (CharacterSize.x / DIVIDE_2 + CharacterPos.x) + (size.x / DIVIDE_2);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ��O
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_PREVIOUS)
				{
					// �ړ��ʎ擾
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// �ړ���0
					CharacterMove.z = MIN_MOVE.z;

					// �ړ��ʐݒ�
					((CCharacter*)pScene)->SetMove(CharacterMove);
					
					// �ʒu
					pos.z = (-CharacterSize.z / DIVIDE_2 + CharacterPos.z) - (size.z / DIVIDE_2);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ��
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_BACK)
				{
					// �ړ��ʎ擾
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// �ړ���0
					CharacterMove.z = MIN_MOVE.z;

					// �ʒu
					pos.z = (CharacterSize.z / DIVIDE_2 + CharacterPos.z) + (size.z / DIVIDE_2);

					// �ړ��ʐݒ�
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ���̃|�C���^�擾
				pScene= pSceneCur;
			} 
		}
	}
}
//=============================================================================
// �O�ς̓����蔻�菈��
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::CrossCollision(void)
{
	// CScene�̃|�C���^
	CScene *pScene = nullptr;

	// ���f���̏��擾
	CModelAnime *pAnime = GetModelAnime(SHIP_NUM);

	// �ʒu�擾
	D3DXVECTOR3 pos = D3DXVECTOR3(pAnime->GetMtxWorld()._41, pAnime->GetMtxWorld()._42, pAnime->GetMtxWorld()._43);

	// �ʒu�擾
	D3DXVECTOR3 posOld = D3DXVECTOR3(pAnime->GetOldMtxWorld()._41, pAnime->GetOldMtxWorld()._42, pAnime->GetOldMtxWorld()._43);

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// nullcheck
	if (pScene == nullptr)
	{
		// �擪�̃|�C���^�擾
		pScene = GetTop(PRIORITY_ENEMY);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcter�Ƃ̓����蔻��
			while (pScene != nullptr) // nullptr�ɂȂ�܂ŉ�
			{
				// ���݂̃|�C���^
				CScene *pSceneCur = pScene->GetNext();

				// �p�[�c���擾
				int nParts = ((CCharacter*)pScene)->GetPartsNum();

				// �p�[�c�����J��Ԃ�
				for (int nCnt = ZERO_INT; nCnt < nParts; nCnt++)
				{
					// ���b�V���擾
					LPD3DXMESH mesh = ((CCharacter*)pScene)->GetModelAnime(nCnt)->GetMesh();

					// �t�F�[�X���擾
					DWORD FaceNum = mesh->GetNumFaces();
				}
				// ���̃|�C���^�擾
				pScene = pSceneCur;
			}
		}
	}
}
//=============================================================================
// ���C�O�ς̓����蔻�菈��
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::RayCollision(void)
{
	// ���C���q�b�g������
	BOOL bHit = false;
	// ���C���q�b�g������
	BOOL bUnderHit = false;

	// ���n
	bool bLanding = false;

	// ����
	float fDistancePlayer = ZERO_FLOAT;
	// ����
	float fUnderDistance = ZERO_FLOAT;

	// �ʒu
	D3DXVECTOR3 vecStart, vecDirection, vecUnderDirection;

	// �p�x
	float fRadius = RAY_RADIUS;

	// ���f���̏��擾
	CModelAnime *pShip = GetModelAnime(SHIP_NUM);

	// �ʒu�擾
	D3DXVECTOR3 pos = SHIP_POS;

	// �}�b�v�̃|�C���^�擾
	CMap *pMap = GET_MAP_PTR;

	// �n�߂���W
	vecStart = pos;

	// ���C���o���p�x
	vecDirection = D3DXVECTOR3(RAY_RADIUS_UNDER, ZERO_FLOAT, ZERO_FLOAT);

	// ���C���q�b�g������
	D3DXIntersect(pMap->GetMesh(), &vecStart, &D3DXVECTOR3(cosf(vecUnderDirection.x), sinf(vecUnderDirection.x), ZERO_FLOAT),
		&bUnderHit, NULL, NULL, NULL, &fUnderDistance, NULL, NULL);

	// true�̏ꍇ
	if (bUnderHit == TRUE)
	{
		// �͈͂�菬����������
		if (fUnderDistance < RAY_HIT_RANGE_UNDER)
		{
			// �߂�
			pos -= (D3DXVECTOR3(cosf(vecUnderDirection.x), sinf(vecUnderDirection.x), ZERO_FLOAT));

			// �ʒu�ݒ�
			SetPos(pos);

			// true��
			bLanding = true;

			return;
		}
	}
	// 4��J��Ԃ�
	for (int nCount = ZERO_INT; nCount < RAY_NUM; nCount++)
	{
		// ���C���o���p�x
		vecDirection = D3DXVECTOR3(ZERO_FLOAT, fRadius * nCount, ZERO_FLOAT);

		// ���C���q�b�g������
		D3DXIntersect(pMap->GetMesh(), &vecStart, &D3DXVECTOR3(sinf(vecDirection.y), ZERO_FLOAT, cosf(vecDirection.y)),
			&bHit, NULL, NULL, NULL, &fDistancePlayer, NULL, NULL);

		// true�̏ꍇ
		if (bHit == TRUE)
		{
			// �͈͂�菬����������
			if (fDistancePlayer < RAY_HIT_RANGE)
			{
				// �߂�
				pos -= (D3DXVECTOR3(sinf(vecDirection.y), ZERO_FLOAT, cosf(vecDirection.y)));

				// �ʒu�ݒ�
				SetPos(pos);

				return;
			}
		}
	}

	// ���n��Ԑݒ�
	SetLanding(bLanding);
}