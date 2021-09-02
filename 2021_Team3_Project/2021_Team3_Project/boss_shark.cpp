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
#include "boss_shark.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define MAX_LIFE		(100)									// �̗�
#define MOVE_VALUE		(10.0f)									// �ړ���
#define ROT_SPEED		(0.01f)									// ���񑬓x
#define ANGLE_180		(180)									// 180�x
#define ANGLE_360		(360)									// 360�x
#define SIZE			(D3DXVECTOR3 (700.0f,900.0f,700.0f))	// �T�C�Y
#define ATTACK_COUNT	(300)									// �U���Ԋu

//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Shark::CBoss_Shark(PRIORITY Priority) : CEnemy(Priority)
{
	m_nAttackCount = ZERO_INT;
	m_MotionState = MOTION_STATE_IDLE;
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

			// �{�b�N�X����
			CCharacter_Box::Create(pos, rot, pBoss_Shark);
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

	// �U������
	Attack();
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

	// �J�E���g��300�ȏ�̏ꍇ
	if (m_nAttackCount >= ATTACK_COUNT)
	{
		// ���݂��U��
		ByteAttack();

		// 0��
		m_nAttackCount = ZERO_INT;
	}
}
//=============================================================================
// ���݂��U�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Shark::ByteAttack(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// ���݂����[�V����
	m_MotionState = MOTION_STATE_BYTE;

	// ���݂��G�t�F�N�g
	CByte_Effect::CrateEffect(pos, SIZE);
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
		SetMotion(MOTION_STATE_IDLE);
	}
	if (m_MotionState == MOTION_STATE_BYTE)
	{
		// ���[�V�����ݒ�
		SetMotion(MOTION_STATE_BYTE);
	}
}
