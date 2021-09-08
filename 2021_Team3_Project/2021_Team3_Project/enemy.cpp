//=============================================================================
//
// �G�l�~�[�N���X [enemy.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "player.h"
#include "game.h"
#include "fade.h"
#include "resource_manager.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define MIN_LIFE	(0)									// ���C�t�̍ŏ�
#define FAN_LENGTH	(5000.0f)							// ��̒���
#define FAN_DIR		(D3DXVECTOR3(1.0f, 0.0f, 0.0f))		// �ʐ�����
#define ANGLE_90	(D3DXToRadian(90.0f))				// 90�x
#define ANGLE_270	(D3DXToRadian(270.0f))				// 270�x
#define ANGLE_0		(D3DXToRadian(0.0f))				// 0�x
#define ANGLE_360	(D3DXToRadian(360.0f))				// 360�x
#define FAN_COS		(cosf(D3DXToRadian(180.0f / 2.0f)))	// cosf��
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy::CEnemy(PRIORITY Priority) : CCharacter(Priority)
{
	m_Attack_Decision_Type	= ATTACK_DECISION_FAN;
	m_bAttack_Decision		= false;
	m_AttackCount = 0;
}

//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// �I�u�W�F�N�g����
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �������m��
	CEnemy *pEnemy = new CEnemy;

	// ����������
	pEnemy->Init(pos, rot);

	return pEnemy;
}

//=============================================================================
// ����������
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CCharacter::Init(pos, rot);			// ���W�A�p�x

	return S_OK;
}

//=============================================================================
// �I������
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::Uninit(void)
{
	// �I������
	CCharacter::Uninit();
}

//=============================================================================
// �X�V����
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::Update(void)
{
	// �X�V����
	CCharacter::Update();

	// �U�����菈������̏ꍇ
	if (m_Attack_Decision_Type == ATTACK_DECISION_FAN)
	{
		// ��̍U������
		FanDecision();
	}
	// �U�����菈������̏ꍇ
	if (m_Attack_Decision_Type == ATTACK_DECISION_CIRCLE)
	{
		// ��̍U������
		CircleDecision();
	}

	// �̗͂̐ݒ�
	if (GetLife() <= MIN_LIFE)
	{
		// ��Ԑݒ�
		SetState(CCharacter::STATE_DEAD);
	}

	// ��ԏ���
	UpdateState();
}

//=============================================================================
// �`�揈��
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::Draw(void)
{
	// �`�揈��
	CCharacter::Draw();
}

//=============================================================================
// �G�l�~�[�̏��
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::UpdateState(void)
{
	// ��Ԏ擾
	int nState = GetState();

	// ���S���
	if (nState == STATE_DEAD)
	{
		// ���S
		Death();
	}
}
//=============================================================================
// ��`�̔��菈��
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::FanDecision(void)
{
	// �v���C���[�̃|�C���^�擾
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// �ʒu�擾
	D3DXVECTOR3 Pos = GetPos();

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// �v���C���[�̈ʒu���W�擾
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

		// �x�N�g��
		D3DXVECTOR3 Vec = ZeroVector3;

		// �_�Ɛ�̃x�N�g��
		Vec.x = PlayerPos.x - Pos.x;
		Vec.z = PlayerPos.z - Pos.z;

		// �����Z�o
		float fVec_Length = sqrtf((Vec.x * Vec.x) + (Vec.z * Vec.z));

		// �����̔�r
		if (fVec_Length > FAN_LENGTH)
		{
			// �U�������true��
			m_bAttack_Decision = false;
			// �����̏I��
			return;
		}

		// �����擾
		D3DXVECTOR3 Rot = GetRot();

		// ����
		float fRot = ZERO_FLOAT;

		// �O�������Ă邩���������Ă邩
		if (Rot.y > ANGLE_90 && Rot.y < ANGLE_270 || Rot.y < ANGLE_90 && Rot.y > -ANGLE_90)
		{
			// ����
 			fRot = Rot.y - ANGLE_90;
		}
		//�E�������Ă邩���������Ă邩
		if (Rot.y > ANGLE_0 && Rot.y < ANGLE_360 || Rot.y < ANGLE_0 && Rot.y > -ANGLE_0)
		{
			// ����
			fRot = Rot.y + ANGLE_90;
		}

		// ��]
		D3DXVECTOR3 Rotate_ArcDir = ZeroVector3;

		// �x�N�g������]������
		Rotate_ArcDir.x = FAN_DIR.x * cosf(fRot) + FAN_DIR.z * -sinf(fRot);
		Rotate_ArcDir.z = FAN_DIR.x * sinf(fRot) + FAN_DIR.z * cosf(fRot);

		// �P�ʃx�N�g��
		D3DXVECTOR3 Normal_Vec = ZeroVector3;

		// �P�ʃx�N�g���ɂ���
		Normal_Vec.x = Vec.x / fVec_Length;
		Normal_Vec.z = Vec.z / fVec_Length;

		// ���όv�Z
		float fdot = Normal_Vec.x * Rotate_ArcDir.x + Normal_Vec.z * Rotate_ArcDir.z;

		// ��͈̔͂�cos�ɂ���
		float fcos = FAN_COS;

		// �_����͈͓̔��ɂ��邩���r����
		if (fcos > fdot)
		{
			// �U�������true��
			m_bAttack_Decision = false;
		}
		// �_����͈͓̔��ɂ��邩���r����
		if (fcos < fdot)
		{
			// �U�������true��
			m_bAttack_Decision = true;
		}
	}
}
//=============================================================================
// �~�`�̔��菈��
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::CircleDecision(void)
{
	// �v���C���[�̃|�C���^�擾
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// �ʒu�擾
	D3DXVECTOR3 Pos = GetPos();

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// �ʒu�擾
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

		// �~�̔���
		if (CCollision::CollisionCircularAndCircular(Pos, PlayerPos, FAN_LENGTH, ZERO_FLOAT) == true)
		{
			// �U�����肪false�̏ꍇ
			if (m_bAttack_Decision == false)
			{
				// �U�������true��
				m_bAttack_Decision = true;
			}
		}
		else
		{
			// �U�����肪true�̏ꍇ
			if (m_bAttack_Decision == true)
			{
				// �U�������false��
				m_bAttack_Decision = false;
			}
		}
	}
}

//=============================================================================
// ���񂾂Ƃ��̏���
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::Death(void)
{
}

//=============================================================================
// �U���̏���
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::Attack(void)
{
	m_AttackCount++;
}

//=============================================================================
// �ړ��̏���
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy::Move(void)
{
}
