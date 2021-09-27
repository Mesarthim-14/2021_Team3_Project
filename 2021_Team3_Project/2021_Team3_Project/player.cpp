//=============================================================================
// �v���C���[�N���X [player.cpp]
// Author : Sugawara Tsukasa
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
#include "player_life.h"
#include "effect.h"

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define PLAYER_SPEED			(50.0f)									// �v���C���[�̈ړ���
#define STICK_SENSITIVITY		(50.0f)									// �X�e�B�b�N���x
#define PLAYER_ROT_SPEED		(0.1f)									// �L�����N�^�[�̉�]���鑬�x
#define SHIP_NUM				(0)										// �D�̃i���o�[
#define GEAR_R_NUM				(1)										// �������̉E�i���o�[
#define GEAR_L_NUM				(2)										// �������̍��i���o�[
#define BATTERY_R_NUM			(3)										// �C��E�̃i���o�[
#define BATTERY_L_NUM			(4)										// �C�䍶�̃i���o�[
#define MIN_MOVE				(D3DXVECTOR3(0.0f,0.0f,0.0f))			// �ړ��ʂ̍ŏ��l
#define SIZE					(D3DXVECTOR3 (800.0f,1000.0f,800.0f))	// �T�C�Y
#define PARENT_NUM				(0)										// �e�̃i���o�[
#define GEAR_SPIN_ANGLE			(D3DXToRadian(2.0f))					// ���Ԃ̉�]�p�x
#define SPIN_ANGLE				(D3DXToRadian(1.0f))					// ����p�x
#define STICK_INPUT_ZONE		(100)									// �X�e�B�b�N�̓��͔͈�
#define STICK_INPUT_ZONE_2		(1000)									// �X�e�B�b�N�̓��͔͈�
#define STICK_INPUT_ZERO		(0)										// �X�e�B�b�N�̓��͒l0
#define MUT_SPEED				(1.5f)									// �X�s�[�h
#define PAD_1					(0)										// 1�Ԗڂ̃p�b�h
#define PAD_2					(1)										// 2�Ԗڂ̃p�b�h
#define ATTACK_COOLTIME			(90)									// �U���̃N�[���^�C��
#define RAY_NUM					(4)										// ���C�̐�
#define RAY_RADIUS				(D3DXToRadian(360.0f/4.0f))				// ���C���o������
#define RAY_HIT_RANGE			(600.0f)								// �͈�
#define MIN_LIFE				(0)										// ���C�t�̍ŏ�
#define LIFE					(100)									// ���C�t
#define ANGLE_MAX				(D3DXToRadian(360.0f))					// �p�x�̍ő�
#define ANGLE_MIN				(D3DXToRadian(-360.0f))					// �p�x�̍ŏ�
#define ANGLE_0					(D3DXToRadian(0.0f))					// �p�x0
#define ANGLE_90				(D3DXToRadian(90.0f))					// �p�x90
#define ANGLE_180				(D3DXToRadian(180.0f))					// �p�x180
#define ANGLE_270				(D3DXToRadian(270.0f))					// �p�x270
#define GEAR_DEF_ROT			(D3DXToRadian(0.0f))					// �f�t�H���g�̊p�x
#define DEAD_ZONE				(0.0f)									// �R���g���[���[�̔������Ȃ��͈�
#define PAD_P1					(0)										// �p�b�h�v���C���[1
#define PAD_P2					(1)										// �p�b�h�v���C���[2
#define KNOCK_BACK_SPEED		(100.0f)								// �m�b�N�o�b�N�̑���
#define KNOCK_BACK_COUNT		(10)									// �m�b�N�o�b�N�J�E���g
#define ARCDIR					(D3DXVECTOR3(1.0f,0.0f,0.0f))			// ����
#define STICK_ANGLERANGE		(1.0f)									//�X�e�B�b�N�̊p�x�͈�
#define SINK_TIME				(120)									// ���ގ���
#define SINK_MOVE				(3.0f)									// ���ޗ�
#define SINK_ROTATE				(3.0f)									// ���ފp�x

// �D�̂̈ʒu
#define SHIP_POS				(D3DXVECTOR3(pShip->GetMtxWorld()._41, pShip->GetMtxWorld()._42, pShip->GetMtxWorld()._43))
// �C��̈ʒu
#define BATTERY_R_POS			(D3DXVECTOR3(pBattery_R->GetMtxWorld()._41, pBattery_R->GetMtxWorld()._42, pBattery_R->GetMtxWorld()._43))
#define BATTERY_L_POS			(D3DXVECTOR3(pBattery_L->GetMtxWorld()._41, pBattery_L->GetMtxWorld()._42, pBattery_L->GetMtxWorld()._43))

//�G�t�F�N�g�̊e���l
//����
#define EXPLOSION_POS		(D3DXVECTOR3(500.0f, 500.0f, 1.0f))						//�ʒu
#define EXPLOSION_SIZE		(D3DXVECTOR3(500, 500, 500))							//�傫��
#define EXPLOSION_COLOR		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))						//�F
#define EXPLOSION_LIFE		(70)													//�̗�

//��																				
#define SMOKE_POS			(D3DXVECTOR3(0, 1, 0))									//�ʒu
#define SMOKE_SIZE			(D3DXVECTOR3(200.0f, 200.0f, 200.0f))					//�傫��
#define SMOKE_MOVE			(D3DXVECTOR3(4.0f, 5.0f, 4.0f))							//�ړ���
#define SMOKE_COLOR			(D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f))						//�F
#define SMOKE_LIFE			(500)													//�̗�

//�����Ԃ�																			
#define SPLASH_POS			(D3DXVECTOR3(0, 1, 0))									//�ʒu
#define SPLASH_SIZE			(D3DXVECTOR3(80.0f, 80.0f, 80.0f))						//�傫��
#define SPLASH_MOVE			(D3DXVECTOR3(10.0f, 20.0f, 10.0f))						//�ړ���
#define SPLASH_COLOR		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))						//�F
#define SPLASH_LIFE			(200)													//�̗�

//�؍�																			
#define WOOD_POS			(D3DXVECTOR3(0, 1, 0))									//�ʒu
#define WOOD_SIZE			(D3DXVECTOR3(100.0f, 100.0f, 100.0f))					//�傫��
#define WOOD_MOVE			(D3DXVECTOR3(10.0f, 10.0f, 10.0f))						//�ړ���
#define WOOD_COLOR			(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))						//�F
#define WOOD_LIFE			(500)													//�̗�

//�g																				
#define WAVE_POS			(D3DXVECTOR3(GetPos().x-10.0f, 1, GetPos().z-10.0f))	//�ʒu
#define WAVE_SIZE			(D3DXVECTOR3(20, 20, 20))								//�傫��
#define WAVE_MOVE			(D3DXVECTOR3(50.0, 8.0, 50.0))							//�ړ���
#define WAVE_COLOR			(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))						//�F
#define WAVE_LIFE			(70)													//�̗�
#define WAVE_MAX_PARTICLE	(10)													//���o��

//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
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
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) : CCharacter(Priority)
{
	m_rotDest = ZeroVector3;
	m_bMove = false;
	m_nAttackCount_R = ZERO_INT;
	m_nAttackCount_L = ZERO_INT;
	m_PadType = PAD_TYPE_1P;
	m_fAngle_L = 0;
	m_fAngle_R = 0;
	m_nSinkCounter = 0;
	m_bHitFlag = false;
	m_bDeath = false;
	m_bEnd = false;
}

//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// ����������
// Author : Sugawara Tsukasa
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

	// �������
	m_rotDest = rot;

	// �T�C�Y�ݒ�
	SetSize(SIZE);

	// ���C�t
	SetLife(LIFE);

	// ���x�ݒ�
	SetSpeed(PLAYER_SPEED);

	// �W���C�p�b�h�̎擾
	LPDIRECTINPUTDEVICE8 P1_PAD = CInputJoypad::GetController(PAD_P1);
	LPDIRECTINPUTDEVICE8 P2_PAD = CInputJoypad::GetController(PAD_P2);

	// �p�b�h��2�Ȃ����Ă�ꍇ
	if (P1_PAD != nullptr && P2_PAD != nullptr)
	{
		m_PadType = PAD_TYPE_1P;
	}

	// �e�̎g�p
	SetUseShadow();

	// �e�̉�]�𔽉f������
	SetShadowRotCalculation();

	// ���C�̏��ݒ�
	CCharacter::RAY_DATA Ray_Data = { RAY_RADIUS ,RAY_HIT_RANGE ,RAY_NUM };

	// ���C�̏��ݒ�
	SetRay_Data(Ray_Data);

	return S_OK;
}

//=============================================================================
// �I������
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Uninit(void)
{
	// �I������
	CCharacter::Uninit();
}

//=============================================================================
// �X�V����
// Author : Sugawara Tsukasa
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

	// �̗͂�0�ɂȂ�����
	if (!m_bDeath)
	{
		// �v���C���[�̐���
		PlayerControl();
	}
	else
	{
		// ����ł�������
		SinkEnd();
	}

	// �p�x�̍X�V����
	UpdateRot();
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
// Author : Sugawara Tsukasa
// �v���C���[�̏��
//=============================================================================
void CPlayer::UpdateState(void)
{

}

//=============================================================================
// �v���C���[�̐���
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::PlayerControl()
{
	CManager::MODE_TYPE mode = CManager::GetMode();

	if (mode == CManager::MODE_TYPE_GAME)
	{
		// 1P�̏ꍇ
		if (m_PadType == PAD_TYPE_1P)
		{
			// �v���C���[�̈ړ�����
			Move();

			// �U������
			Attack();
		}
		// 1P�̏ꍇ
		if (m_PadType == PAD_TYPE_2P)
		{
			// �v���C���[�̈ړ�����
			Pad2Move();

			// �U������
			Pad2Attack();
		}

		// �L�[�{�[�h�ړ�
		KeyboardMove();

		// �U������
		Attack();

		// �����蔻��
		Collision();
	}
}

//=============================================================================
// �p�x�̍X�V����
// Author : Sugawara Tsukasa
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
// �G�̒e�̃q�b�g����
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Hit(int nDamage)
{
	GetLife() = -nDamage;

	// 0�ȉ���������
	if (!m_bDeath && GetLife() <= 0)
	{
		// ����
		Death();
	}
}

//=============================================================================
// ���񂾂Ƃ��̏���
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Death(void)
{
	m_bDeath = true;
	SetGravityFlag(false);

	return;
}

//=============================================================================
// �ړ��̏���
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Move(void)
{
	DIJOYSTATE js = CInputJoypad::GetStick(PAD_P1);							// �W���C�p�b�h�̎擾
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();		// �T�E���h�̃|�C���^
	D3DXVECTOR3 pos = GetPos();												// ���W
	D3DXVECTOR3 rot = GetRot();												// �p�x
	float fSpeed = GetSpeed();												// �X�s�[�h
	float fAngle_R = ZERO_FLOAT;											// �E�p�x
	float fAngle_L = ZERO_FLOAT;											// ���p�x
	float disfAngle_R = GetAngle_R();										//�O�̃R���g���[���[�̊p�x���擾
	float disfAngle_L = GetAngle_L();										//�O�̃R���g���[���[�̊p�x���擾

																			//// ���̎��Ԃ̏��擾
																			//CModelAnime *pGear_L = GetModelAnime(GEAR_L_NUM);
																			//// �����擾
																			//D3DXVECTOR3 Gear_L_rot = pGear_L->GetRot();

																			//// �E�̎��Ԃ̏��擾
																			//CModelAnime *pGear_R = GetModelAnime(GEAR_R_NUM);
																			//// �����擾
																			//D3DXVECTOR3 Gear_R_rot = pGear_R->GetRot();

																			//===========================================
																			// �E����
																			//===========================================
																			// �E�X�e�B�b�N�����͂���Ă���ꍇ
	if (js.lZ != DEAD_ZONE || js.lRz != DEAD_ZONE)
	{
		// �R���g���[���[�̊p�x
		fAngle_R = atan2f((float)js.lRz, (float)js.lZ);

		// ���Ɉړ�
		if (fAngle_R < disfAngle_R && fAngle_R + STICK_ANGLERANGE > disfAngle_R)
		{
			// �p�h���̉�]
			PaddleRotateR(-GEAR_SPIN_ANGLE);

			// �ړ�
			pos.x += -sinf(rot.y)*fSpeed;
			pos.z += -cosf(rot.y)*fSpeed;

			// ����
			rot.y = rot.y - SPIN_ANGLE;

			// �ړI�̌���
			m_rotDest.y = rot.y;
		}
		// false�̏ꍇ
		else if (m_bBack == false)
		{
			// �E�Ɉړ�
			if (fAngle_R > disfAngle_R && fAngle_R - STICK_ANGLERANGE < disfAngle_R)
			{
				// �p�h���̉�]
				PaddleRotateR(GEAR_SPIN_ANGLE);

				// �ړ�
				pos.x += -sinf(rot.y)*fSpeed;
				pos.z += -cosf(rot.y)*fSpeed;

				// ����
				rot.y = rot.y + SPIN_ANGLE;

				// �ړI�̌���
				m_rotDest.y = rot.y;
			}
		}
		//�g�G�t�F�N�g
		CreateWave();
		SetAngle_R(fAngle_R);
	}
	//===========================================
	// ������
	//===========================================
	// ���X�e�B�b�N�����͂���Ă���ꍇ
	if (js.lX != DEAD_ZONE || js.lY != DEAD_ZONE)
	{
		// �R���g���[���[�̊p�x
		fAngle_L = atan2f((float)js.lY, (float)js.lX);

		// �E�Ɉړ�
		if (fAngle_L < disfAngle_L && fAngle_L + STICK_ANGLERANGE > disfAngle_L)
		{
			// �p�h���̉�]
			PaddleRotateL(-GEAR_SPIN_ANGLE);

			// �ړ�
			pos.x += -sinf(rot.y)*fSpeed;
			pos.z += -cosf(rot.y)*fSpeed;

			// ����
			rot.y = rot.y + SPIN_ANGLE;

			// �ړI�̌���
			m_rotDest.y = rot.y;
		}
		// false�̏ꍇ
		else if (m_bBack == false)
		{
			// ���Ɉړ�
			if (fAngle_L > disfAngle_L && fAngle_L - STICK_ANGLERANGE < disfAngle_L)
			{
				// �p�h���̉�]
				PaddleRotateL(GEAR_SPIN_ANGLE);

				// �ړ�
				pos.x += -sinf(rot.y)*fSpeed;
				pos.z += -cosf(rot.y)*fSpeed;

				// ����
				rot.y = rot.y - SPIN_ANGLE;

				// �ړI�̌���
				m_rotDest.y = rot.y;
			}
		}
		//�g�G�t�F�N�g
		CreateWave();
		SetAngle_L(fAngle_L);
	}
	// ���͂���Ă���ꍇ
	if (js.lX != DEAD_ZONE || js.lY != DEAD_ZONE && js.lZ != DEAD_ZONE || js.lRz != DEAD_ZONE)
	{
		// �E�X�e�B�b�N�ƍ��X�e�B�b�N�����ɓ|����Ă���ꍇ
		if (fAngle_L > disfAngle_L && fAngle_R > disfAngle_R)
		{
			// true��
			m_bBack = true;
			// true�̏ꍇ
			if (m_bBack == true)
			{
				// �p�h���̉�]
				PaddleRotateR(GEAR_SPIN_ANGLE);
				PaddleRotateL(GEAR_SPIN_ANGLE);

				// �ړ�
				pos.x += sinf(rot.y)*fSpeed;
				pos.z += cosf(rot.y)*fSpeed;

			}
		}
		// �E�X�e�B�b�N�ƍ��X�e�B�b�N�����ɓ|����Ă��Ȃ��ꍇ
		else
		{
			// false��
			m_bBack = false;
		}
	}

	// �p�x�̕␳
	PaddleRotFix();

	// ����
	SetRot(rot);

	// �ʒu�ݒ�
	SetPos(pos);
}
//=============================================================================
// 2�p�b�h�̈ړ������֐�
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Pad2Move(void)
{
	// �W���C�p�b�h�̎擾
	DIJOYSTATE P1_js = CInputJoypad::GetStick(PAD_P1);
	DIJOYSTATE P2_js = CInputJoypad::GetStick(PAD_P2);
	float disfAngle_R = GetAngle_R();										//�O�̃R���g���[���[�̊p�x���擾
	float disfAngle_L = GetAngle_L();										//�O�̃R���g���[���[�̊p�x���擾

																			// �T�E���h�̃|�C���^
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	// ���W
	D3DXVECTOR3 pos = GetPos();

	// �p�x
	D3DXVECTOR3 rot = GetRot();

	// �X�s�[�h
	float fSpeed = GetSpeed();

	// �E�p�x
	float fAngle_R = ZERO_FLOAT;

	// ���p�x
	float fAngle_L = ZERO_FLOAT;

	// ���̎��Ԃ̏��擾
	CModelAnime *pGear_L = GetModelAnime(GEAR_L_NUM);
	// �����擾
	D3DXVECTOR3 Gear_L_rot = pGear_L->GetRot();

	// �E�̎��Ԃ̏��擾
	CModelAnime *pGear_R = GetModelAnime(GEAR_R_NUM);
	// �����擾
	D3DXVECTOR3 Gear_R_rot = pGear_R->GetRot();

	//===========================================
	// ������ ��1Player
	//===========================================
	// ���X�e�B�b�N�����͂���Ă���ꍇ
	if (P1_js.lX != DEAD_ZONE || P1_js.lY != DEAD_ZONE)
	{
		// �R���g���[���[�̊p�x
		fAngle_L = atan2f((float)P1_js.lY, (float)P1_js.lX);

		// �E�Ɉړ�
		if (fAngle_L < disfAngle_L)
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
		// false�̏ꍇ
		if (m_bBack == false)
		{
			// ���Ɉړ�
			if (fAngle_L > disfAngle_L)
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
		}
		//�g�G�t�F�N�g
		CreateWave();
		SetAngle_L(fAngle_L);
	}
	//===========================================
	// �E���� ��2Player
	//===========================================
	// ���X�e�B�b�N�����͂���Ă���ꍇ
	if (P2_js.lX != DEAD_ZONE || P2_js.lY != DEAD_ZONE)
	{
		// �R���g���[���[�̊p�x
		fAngle_R = atan2f((float)P2_js.lY, (float)P2_js.lX);

		// ���Ɉړ�
		if (fAngle_R < disfAngle_R)
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
		// false�̏ꍇ
		if (m_bBack == false)
		{
			// �E�Ɉړ�
			if (fAngle_R > disfAngle_R)
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
		}
		//�g�G�t�F�N�g
		CreateWave();
		//�i�[
		SetAngle_R(fAngle_R);
	}
	// ���͂���Ă���ꍇ
	if (P1_js.lX != DEAD_ZONE || P1_js.lY != DEAD_ZONE && P2_js.lX != DEAD_ZONE || P2_js.lY != DEAD_ZONE)
	{
		// �E�X�e�B�b�N�ƍ��X�e�B�b�N�����ɓ|����Ă���ꍇ
		if (fAngle_L > disfAngle_L && fAngle_R > disfAngle_R)
		{
			// true��
			m_bBack = true;
			// true�̏ꍇ
			if (m_bBack == true)
			{
				// �������Z
				Gear_L_rot.x += GEAR_SPIN_ANGLE;
				// �����ݒ�
				pGear_L->SetRot(Gear_L_rot);

				// �������Z
				Gear_R_rot.x += GEAR_SPIN_ANGLE;
				// �����ݒ�
				pGear_R->SetRot(Gear_R_rot);

				// �ړ�
				pos.x += sinf(rot.y)*fSpeed;
				pos.z += cosf(rot.y)*fSpeed;
			}
		}
		// ���͂���Ă��Ȃ��ꍇ
		else
		{
			// false��
			m_bBack = false;
		}
	}

	// �p�x���ő�ɂȂ����ꍇ
	if (Gear_L_rot.x >= ANGLE_MAX || Gear_L_rot.x <= ANGLE_MIN)
	{
		// 0�ɖ߂�
		Gear_L_rot.x = GEAR_DEF_ROT;
		// �����ݒ�
		pGear_L->SetRot(Gear_L_rot);
	}

	// �p�x���ő�ɂȂ����ꍇ
	if (Gear_R_rot.x >= ANGLE_MAX || Gear_R_rot.x <= ANGLE_MIN)
	{
		// 0�ɖ߂�
		Gear_R_rot.x = GEAR_DEF_ROT;
		// �����ݒ�
		pGear_R->SetRot(Gear_R_rot);
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
		if (pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, PAD_1) ||
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
// 2�R���g���[���[�̍U������
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Pad2Attack(void)
{
	// �W���C�p�b�h�擾
	CInputJoypad *pJoypad = CManager::GetJoypad();

	// ���f���̏��擾
	CModelAnime *pBattery_R = GetModelAnime(BATTERY_R_NUM);

	// ���f���̏��擾
	CModelAnime *pBattery_L = GetModelAnime(BATTERY_L_NUM);

	// �����擾
	D3DXVECTOR3 rot = GetRot();

	// �J�E���g��0�̏ꍇ
	if (m_nAttackCount_L == ZERO_INT)
	{
		// LT�g���K�[���������ꍇ
		if (pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, PAD_1) ||
			pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, PAD_1))
		{
			// ���e����
			CPlayer_Bullet::Create(BATTERY_L_POS, rot);

			// �C���N�������g
			m_nAttackCount_L++;
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
	// �J�E���g��0�̏ꍇ
	if (m_nAttackCount_R == ZERO_INT)
	{
		// RT�g���K�[���������ꍇ
		if (pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, PAD_2) ||
			pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, PAD_2))
		{
			// �E�e����
			CPlayer_Bullet::Create(BATTERY_R_POS, rot);

			// �C���N�������g
			m_nAttackCount_R++;
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
}
//=============================================================================
// �L�[�{�[�h�ړ�����
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::KeyboardMove(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// ���̎��Ԃ̏��擾
	CModelAnime *pGear_L = GetModelAnime(GEAR_L_NUM);
	// �����擾
	D3DXVECTOR3 Gear_L_rot = pGear_L->GetRot();

	// �E�̎��Ԃ̏��擾
	CModelAnime *pGear_R = GetModelAnime(GEAR_R_NUM);
	// �����擾
	D3DXVECTOR3 Gear_R_rot = pGear_R->GetRot();

	// ���W
	D3DXVECTOR3 pos = GetPos();

	// �p�x
	D3DXVECTOR3 rot = GetRot();

	// �X�s�[�h
	float fSpeed = GetSpeed();

	// �E�p�x
	float fAngle_R = ZERO_FLOAT;

	// ���p�x
	float fAngle_L = ZERO_FLOAT;

	// �E�Ɉړ�
	if (pKeyboard->GetPress(DIK_W))
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

		//�G�t�F�N�g
		CreateWave();

		// false��
		m_bBack = false;
	}
	// false�̏ꍇ
	if (m_bBack == false)
	{
		// ���Ɉړ�
		if (pKeyboard->GetPress(DIK_S))
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
	}
	// �E�Ɉړ�
	if (pKeyboard->GetPress(DIK_UP))
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

		//�G�t�F�N�g
		CreateWave();

		// false��
		m_bBack = false;
	}
	// false�̏ꍇ
	if (m_bBack == false)
	{
		// ���Ɉړ�
		if (pKeyboard->GetPress(DIK_DOWN))
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
	}
	// ���ړ�
	if (pKeyboard->GetPress(DIK_DOWN) && pKeyboard->GetPress(DIK_S))
	{
		// true��
		m_bBack = true;

		// true�̏ꍇ
		if (m_bBack == true)
		{
			// �������Z
			Gear_L_rot.x += GEAR_SPIN_ANGLE;
			// �����ݒ�
			pGear_L->SetRot(Gear_L_rot);

			// �������Z
			Gear_R_rot.x += GEAR_SPIN_ANGLE;
			// �����ݒ�
			pGear_R->SetRot(Gear_R_rot);

			// �ړ�
			pos.x += sinf(rot.y)*fSpeed;
			pos.z += cosf(rot.y)*fSpeed;
		}
	}

	if (pKeyboard->GetPress(DIK_P))
	{
		//�p�[�e�B�N������
		CreateSmoke();
		CreateWoodEP();
		CreateExplosion();
	}

	// �p�x���ő�ɂȂ����ꍇ
	if (Gear_L_rot.x >= ANGLE_MAX || Gear_L_rot.x <= ANGLE_MIN)
	{
		// 0�ɖ߂�
		Gear_L_rot.x = GEAR_DEF_ROT;
		// �����ݒ�
		pGear_L->SetRot(Gear_L_rot);
	}

	// �p�x���ő�ɂȂ����ꍇ
	if (Gear_R_rot.x >= ANGLE_MAX || Gear_R_rot.x <= ANGLE_MIN)
	{
		// 0�ɖ߂�
		Gear_R_rot.x = GEAR_DEF_ROT;
		// �����ݒ�
		pGear_R->SetRot(Gear_R_rot);
	}
	// ����
	SetRot(rot);

	// �ʒu�ݒ�
	SetPos(pos);
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
				pScene = pSceneCur;
			}
		}

		// �擪�̃|�C���^�擾
		pScene = GetTop(PRIORITY_OBSTACLE);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcter�Ƃ̓����蔻��
			while (pScene != nullptr) // nullptr�ɂȂ�܂ŉ�
			{
				// ���݂̃|�C���^
				CScene *pSceneCur = pScene->GetNext();

				// �ʒu
				D3DXVECTOR3 ObstaclePos = ((CModel*)pScene)->GetPos();

				// �T�C�Y�擾
				D3DXVECTOR3 ObstacleSize = ((CModel*)pScene)->GetSize();

				// ��`�̓����蔻��
				if (CCollision::CollisionRectangleAndRectangle(ObstaclePos, pos, ObstacleSize, size) == true)
				{
					// �x�N�g��
					D3DXVECTOR3 Vec = ZeroVector3;

					// �@���x�N�g��
					D3DXVECTOR3 NormalVec = ZeroVector3;

					// �i�s�x�N�g��
					Vec.x = ObstaclePos.x - pos.x;
					Vec.z = ObstaclePos.z - pos.z;

					// �����Z�o
					float fVec_Length = sqrtf((Vec.x * Vec.x) + (Vec.z * Vec.z));

					// �@���x�N�g����
					NormalVec.x = Vec.x / fVec_Length;
					NormalVec.z = Vec.z / fVec_Length;

					// ���˃x�N�g���Z�o
					D3DXVec3Normalize(&m_Reflection_Vec, &(Vec - 2.0f * D3DXVec3Dot(&Vec, &NormalVec) * NormalVec));

					// true��
					m_bKnock_Back = true;
				}

				// ���̃|�C���^�擾
				pScene = pSceneCur;
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

//=======================================================================================
// ���ޏ���
// Author : Konishi Yuuto
//=======================================================================================
void CPlayer::SinkEnd(void)
{
	if (!m_bEnd)
	{
		m_nSinkCounter++;

		GetPos().y -= SINK_MOVE;

		if (m_nSinkCounter >= SINK_TIME)
		{
			m_bEnd = true;
			m_nSinkCounter = 0;
		}
	}
	GetRot().x += D3DXToRadian(SINK_ROTATE);
}

//=======================================================================================
// �������֐�
// Author : Oguma Akira
//=======================================================================================
void CPlayer::CreateSmoke(void)
{
	// �p�[�e�B�N������
	CEffect::Create(SMOKE_POS, SMOKE_SIZE, SMOKE_MOVE, SMOKE_COLOR,
		CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_1), SMOKE_LIFE);
}

//=======================================================================================
// �؍ޔ��j�����֐�
// Author : Oguma Akira
//=======================================================================================
void CPlayer::CreateWoodEP(void)
{
	// �p�[�e�B�N������
	CEffect::Create(WOOD_POS,
		WOOD_SIZE, WOOD_MOVE, WOOD_COLOR,
		CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_5), WOOD_LIFE);
}

//=======================================================================================
// �����Ԃ������֐�
// Author : Oguma Akira
//=======================================================================================
void CPlayer::CreateSplash(void)
{
	for (int nCntEffect = 0; nCntEffect < 10; nCntEffect++)
	{
		// �p�[�e�B�N������
		CEffect::Create(SPLASH_POS,
			WOOD_SIZE, SPLASH_MOVE, SPLASH_COLOR,
			CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_4), SPLASH_LIFE);
	}
}

//=======================================================================================
// ���������֐�
// Author : Oguma Akira
//=======================================================================================
void CPlayer::CreateExplosion(void)
{
	// �p�[�e�B�N������
	CEffect::Create(EXPLOSION_POS, EXPLOSION_SIZE, ZeroVector3, EXPLOSION_COLOR,
		CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_2), EXPLOSION_LIFE);

}

//=======================================================================================
// �g�����֐�
// Author : Oguma Akira
//=======================================================================================
void CPlayer::CreateWave(void)
{
	for (int nCntEffect = 0; nCntEffect < WAVE_MAX_PARTICLE; nCntEffect++)
	{
		// �p�[�e�B�N������
		CEffect::Create(WAVE_POS, WAVE_SIZE, WAVE_MOVE, WAVE_COLOR,
			CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_3), WAVE_LIFE);
	}
}

//=============================================================================
// �m�b�N�o�b�N�����֐�
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Knock_Back(void)
{
	// �J�E���g�C���N�������g
	m_nRockHitCount++;

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// 0�̏ꍇ
	if (m_nRockHitCount <= KNOCK_BACK_COUNT)
	{
		// �ړ���
		move.x = m_Reflection_Vec.x *KNOCK_BACK_SPEED;
		move.z = m_Reflection_Vec.z *KNOCK_BACK_SPEED;

		// �ړ��ʐݒ�
		SetMove(move);
	}
	// 10���傫���ꍇ
	if (m_nRockHitCount > KNOCK_BACK_COUNT)
	{
		// �ړ��ʐݒ�
		SetMove(ZeroVector3);

		// 0�ɖ߂�
		m_nRockHitCount = ZERO_INT;

		// false��
		m_bKnock_Back = false;
	}
}

//=============================================================================
// �p�h���̉E��]
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::PaddleRotateR(float fRotate)
{
	// �E�̎��Ԃ̏��擾
	CModelAnime *pGear_R = GetModelAnime(GEAR_R_NUM);
	// �����擾
	D3DXVECTOR3 Gear_R_rot = pGear_R->GetRot();

	// �p�x���Z
	Gear_R_rot.x += fRotate;

	// �����ݒ�
	pGear_R->SetRot(Gear_R_rot);
}

//=============================================================================
// �p�h���̍���]
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::PaddleRotateL(float fRotate)
{
	// ���̎��Ԃ̏��擾
	CModelAnime *pGear_L = GetModelAnime(GEAR_L_NUM);
	// �����擾
	D3DXVECTOR3 Gear_L_rot = pGear_L->GetRot();

	// �p�x���Z
	Gear_L_rot.x += fRotate;

	// �����ݒ�
	pGear_L->SetRot(Gear_L_rot);
}

//=============================================================================
// �p�h���̊p�x�C��
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::PaddleRotFix(void)
{
	// �E�̎��Ԃ̏��擾
	CModelAnime *pGear_R = GetModelAnime(GEAR_R_NUM);
	// �����擾
	D3DXVECTOR3 Gear_R_rot = pGear_R->GetRot();
	// ���̎��Ԃ̏��擾
	CModelAnime *pGear_L = GetModelAnime(GEAR_L_NUM);
	// �����擾
	D3DXVECTOR3 Gear_L_rot = pGear_L->GetRot();

	// �p�x���ő�ɂȂ����ꍇ
	if (Gear_L_rot.x >= ANGLE_MAX || Gear_L_rot.x <= ANGLE_MIN)
	{
		// 0�ɖ߂�
		Gear_L_rot.x = GEAR_DEF_ROT;
		// �����ݒ�
		pGear_L->SetRot(Gear_L_rot);
	}

	// �p�x���ő�ɂȂ����ꍇ
	if (Gear_R_rot.x >= ANGLE_MAX || Gear_R_rot.x <= ANGLE_MIN)
	{
		// 0�ɖ߂�
		Gear_R_rot.x = GEAR_DEF_ROT;
		// �����ݒ�
		pGear_R->SetRot(Gear_R_rot);
	}
}

//=============================================================================
// L�X�e�B�b�N�p�x�l�i�[�֐�
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::SetAngle_L(float fangle_L)
{
	m_fAngle_L = fangle_L;
}

//=============================================================================
// R�X�e�B�b�N�p�x�l�i�[�֐�
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::SetAngle_R(float fangle_R)
{
	m_fAngle_R = fangle_R;
}