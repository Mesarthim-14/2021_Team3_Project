//=============================================================================
// �G�̑D [enemy_ship.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "game.h"
#include "player.h"
#include "character_box.h"
#include "byte_effect.h"
#include "motion.h"
#include "boss_bullet.h"
#include "byte_attack_range.h"
#include "boss_shark.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define MAX_LIFE			(500)														// �̗�
#define ROT_SPEED			(0.04f)														// ���񑬓x
#define ANGLE_180			(D3DXToRadian(180))											// 180�x
#define ANGLE_90			(D3DXToRadian(90))											// 90�x
#define ANGLE_360			(D3DXToRadian(360))											// 90�x
#define SIZE				(D3DXVECTOR3(16000.0f,5000.0f,16000.0f))						// �T�C�Y
#define BYTE_SIZE			(D3DXVECTOR3(3000.0f,3000.0f,0.0f))							// ���݂��G�t�F�N�g�T�C�Y
#define BYTE_RANGE_SIZE		(D3DXVECTOR3(10000.0f,0.0f,10000.0f))						// ���݂��͈̓T�C�Y
#define ATTACK_COUNT		(300)														// �U���Ԋu
#define BYTE_COUNT			(500)														// ���݂��U��
#define BYTE_KEY_MAX		(1)															// ���݂��U��Key�̍ő�
#define BYTE_FRAME			(15)														// �G�t�F�N�g����Frame
#define BYTE_FRAME_MAX		(45)														// ���݂��U��Frame�̍ő�
#define BULLET_ROT			(D3DXVECTOR3(D3DXToRadian(90.0f),0.0f,D3DXToRadian(180.0f)))// ����
#define MUT_2				(2)															// 2�{
#define RANGE_LENGTH		(13000.0f)													// �U���͈͈ʒu�Z�o�p
#define RANGE_Y				(100.0f)													// �͈͂�Y���W
#define BYTE_LENGTH			(5000.0f)													// ����
#define BULLET_CNT			(1000)														// �e���˃J�E���g
#define BULLET_KEY_MAX		(3)															// �e���˃L�[�ő�
#define BULLET_KEY			(2)															// �e���˃L�[�ő�
#define BULLET_FRAME		(0)															// �e�t���[��
#define BULLET_FRAME_MAX	(40)														// �e�t���[���ő�
#define BYTE_Y				(2000.0f)													// �ʒu
// �{�̈ʒu
#define CHIN_POS		(D3DXVECTOR3(pChin->GetMtxWorld()._41, pChin->GetMtxWorld()._42, pChin->GetMtxWorld()._43))
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Shark::CBoss_Shark(PRIORITY Priority) : CEnemy(Priority)
{
	m_MotionState	= MOTION_STATE_IDLE;
	m_bEnd			= false;
	m_bEnemyCreate	= false;
	m_bRot			= false;
}
//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Shark::~CBoss_Shark()
{
}
//=============================================================================
// �����֐�
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Shark * CBoss_Shark::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CBoss_Shark�|�C���^
	CBoss_Shark *pBoss_Shark = nullptr;

	// nullcheck
	if (pBoss_Shark == nullptr)
	{
		// �������m��
		pBoss_Shark = new CBoss_Shark;

		// !nullcheck
		if (pBoss_Shark != nullptr)
		{
			// ����������
			pBoss_Shark->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pBoss_Shark;
}
//=============================================================================
// �������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBoss_Shark::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f���̏���n��
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_BOSS_SHARK);
	}

	// �̗͐ݒ�
	SetLife(MAX_LIFE);

	// �T�C�Y�ݒ�
	SetSize(SIZE);

	// �U������ݒ�
	SetAttackDecision(ATTACK_DECISION_CIRCLE);

	// �^�C�v�ݒ�
	SetType(TYPE_BOSS);

	// �e�̎g�p
	SetUseShadow();

	// �e�̉�]�𔽉f������
	SetShadowRotCalculation();

	// �������֐�
	CEnemy::Init(pos, rot);

	return S_OK;
}
//=============================================================================
// �I���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}
//=============================================================================
// �X�V�֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::Update(void)
{
	// �X�V����
	CEnemy::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// ���[�V�����X�V
	ModelAnimeUpdate();

	// ���[�V��������
	MotionUpdate();

	// �Â����W�ۑ�
	SetPosOld(pos);

	// �����X�V
	UpdateRot();

	// �U������
	Attack();

	// false�̏ꍇ
	if (m_bEnemyCreate == false)
	{
		// �G����
		Enemy_Create();
	}
	// ���S����
	Death();
}
//=============================================================================
// �`��֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::Draw(void)
{
	// �`��֐�
	CEnemy::Draw();
}

//=============================================================================
// �U�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::Attack(void)
{
	// �G�l�~�[�̍U��
	CEnemy::Attack();

	// �U���J�E���g�擾
	int nAttackCount = GetAttackCount();

	// ���C�t�擾
	int nLife = GetLife();

	// �J�E���g��300�ȏ�̏ꍇ
	if (nAttackCount == ATTACK_COUNT)
	{
		// �ʒu�擾
		D3DXVECTOR3 pos = GetPos();

		// �����擾
		D3DXVECTOR3 rot = GetRot();

		// �U���͈͈ʒu
		D3DXVECTOR3 RangePos = ZeroVector3;

		// ���W�����߂�
		RangePos.x = pos.x - cosf(rot.y + ANGLE_90) * RANGE_LENGTH;
		RangePos.z = pos.z + sinf(rot.y + ANGLE_90) * RANGE_LENGTH;
		RangePos.y = RANGE_Y;

		// �U���͈͐���
		CByte_Attack_Range::Create(RangePos, BYTE_RANGE_SIZE);

		// false��
		m_bRot = true;
	}
	// �J�E���g��500�ȏ�̏ꍇ
	if (nAttackCount == BYTE_COUNT)
	{
		// ���݂��U��
		ByteAttack();

		// ���C�t���������傫���̏ꍇ
		if (nLife > MAX_LIFE / DIVIDE_2)
		{
			// 0��
			GetAttackCount() = ZERO_INT;
		}
	}
	// ���C�t�������ȉ��̏ꍇ
	if (nLife <= MAX_LIFE / DIVIDE_2)
	{
		// �U���J�E���g
		if (nAttackCount == BULLET_CNT)
		{
			// �e���ˍU��
			m_MotionState = MOTION_STATE_SHARK_BULLET;

			// 0��
			GetAttackCount() = ZERO_INT;
		}
	}
}
//=============================================================================
// ���S�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::Death(void)
{
	// ��Ԏ擾
	int nState = GetState();

	// ���S���
	if (nState == STATE_DEAD)
	{
		// true��
		m_bEnd = true;
	}
}
//=============================================================================
// ���݂��U�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::ByteAttack(void)
{
	// ���݂����[�V����
	m_MotionState = MOTION_STATE_BYTE;

	CSound *pSound = GET_SOUND_PTR;
//	pSound->Play(CSound::SOUND_BGM_RESULT);

}
//=============================================================================
// �T���̒e�U�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::SharkBulletAttack(void)
{
	// �{�̃|�C���^�擾
	CModelAnime *pChin = GetModelAnime(PARTS_CHIN);

	// �e����
	CBoss_Bullet::CreateBullet(CHIN_POS, BULLET_ROT);
}
//=============================================================================
// ���[�V���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::MotionUpdate(void)
{
	// �A�C�h�����[�V����
	if (m_MotionState == MOTION_STATE_IDLE)
	{
		// ���[�V�����ݒ�
		SetMotion(m_MotionState);
	}
	// ���݂����[�V����
	if (m_MotionState == MOTION_STATE_BYTE)
	{
		// ���[�V�����ݒ�
		SetMotion(m_MotionState);

		// �ʒu�擾
		D3DXVECTOR3 pos = GetPos();

		// ���[�V�����擾
		CMotion *pMotion = GetMotion();

		// �L�[�擾
		int nKey = pMotion->GetKey();

		// �t���[���擾
		int nFrame = pMotion->GetCountMotion();
		
		// �L�[�ƃJ�E���g���ő�ɂȂ�����
		if (nKey == BYTE_KEY_MAX && nFrame == BYTE_FRAME)
		{
			// �{�̃|�C���^�擾
			CModelAnime *pChin = GetModelAnime(PARTS_CHIN);

			// �����擾
			D3DXVECTOR3 rot = GetRot();

			// �U���͈͈ʒu
			D3DXVECTOR3 RangePos = ZeroVector3;

			// ���W�����߂�
			RangePos.x = CHIN_POS.x - cosf(rot.y + ANGLE_90) * BYTE_LENGTH;
			RangePos.z = CHIN_POS.z + sinf(rot.y + ANGLE_90) * BYTE_LENGTH;
			RangePos.y = CHIN_POS.y;

			// 180�x���Z
			rot.y += ANGLE_180;

			// ���݂��G�t�F�N�g����
			//CByte_Effect::CrateEffect(RangePos, BYTE_SIZE, rot);
		}
		// �L�[�ƃJ�E���g���ő�ɂȂ�����
		if (nKey == BYTE_KEY_MAX && nFrame >= BYTE_FRAME_MAX - 1)
		{
			// �A�C�h�����[�V������
			m_MotionState = MOTION_STATE_IDLE;

			// false��
			m_bRot = false;
		}
	}
	// �e���ˍU��
	if (m_MotionState == MOTION_STATE_SHARK_BULLET)
	{
		// false��
		m_bRot = true;

		// ���[�V�����ݒ�
		SetMotion(m_MotionState);

		// �ʒu�擾
		D3DXVECTOR3 pos = GetPos();

		// ���[�V�����擾
		CMotion *pMotion = GetMotion();

		// �L�[�擾
		int nKey = pMotion->GetKey();

		// �t���[���擾
		int nFrame = pMotion->GetCountMotion();

		// �L�[�ƃJ�E���g���ő�ɂȂ�����
		if (nKey == BULLET_KEY && nFrame == BULLET_FRAME)
		{
			// �e���ˍU��
			SharkBulletAttack();
		}
		// �L�[�ƃJ�E���g���ő�ɂȂ�����
		if (nKey == BULLET_KEY_MAX && nFrame >= BULLET_FRAME_MAX - 1)
		{
			// �A�C�h�����[�V������
			m_MotionState = MOTION_STATE_IDLE;

			// false��
			m_bRot = false;
		}
	}
}
//=============================================================================
// �����X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::UpdateRot(void)
{
	// �v���C���[�擾
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// false�̏ꍇ
		if (m_bRot == false)
		{
			// �v���C���[�̈ʒu�擾
			D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

			// �ʒu�擾
			D3DXVECTOR3 pos = GetPos();

			// �����擾
			D3DXVECTOR3 rot = GetRot();
			// �p�x
			float fRot = atan2f((PlayerPos.x - pos.x), (PlayerPos.z - pos.z));

			// �ړI�̊p�x
			D3DXVECTOR3 rotDest = ZeroVector3;

			// �ړI�̊p�x
			rotDest.y = fRot;

			// �p�x���
			while (rotDest.y - rot.y > ANGLE_180)
			{
				rotDest.y -= ANGLE_360;
			}
			while (rotDest.y - rot.y < -ANGLE_180)
			{
				rotDest.y += ANGLE_360;
			}

			// ����
			rot += (rotDest - rot)*ROT_SPEED;

			// �����ݒ�
			SetRot(rot);
		}
	}
}
//=============================================================================
// �G���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::Enemy_Create(void)
{
	// ���C�t�擾
	int nLife = GetLife();

	// ���C�t�����ȉ��̏ꍇ
	if (nLife <= MAX_LIFE / DIVIDE_2)
	{
		// �Q�[���̃|�C���^�擾
		CGame *pGame = (CGame*)CManager::GetModePtr();

		// �G����
		pGame->Boss_Enemy_Create();

		// true�̏ꍇ
		m_bEnemyCreate = true;
	}
}
