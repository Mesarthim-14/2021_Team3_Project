//=============================================================================
// �G�̒e [enemy_bullet.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "character.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "model_box.h"
#include "enemy_attack_arrow_polygon.h"
#include "enemy_attack_point_polygon.h"
#include "enemy_bullet.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define MOVE_VALUE			(30.0f)								// �ړ���
#define MOVE_VALUE_Y		(60.0f)								// �ړ���
#define POS_Y_MAX			(4000.0f)							// Y�ő�l
#define PARENT_NUM			(0)									// �e�̃i���o�[
#define DAMAGE				(10)								// �_���[�W
#define GRAVITY				(-1.0f)								// �d��
#define DIVIDE_2F			(2.0f)								// ��2
#define ANGLE				(D3DXToRadian(45.0f))				// �p�x
#define POW_VALUE			(2.0f)								// �ݏ�l
// �U���n�_�̃T�C�Y
#define ARROW_SIZE	(D3DXVECTOR3(500.0f,300.0f,0.0f))
#define POINT_SIZE	(D3DXVECTOR3(300.0f,0.0f,400.0f))
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Bullet::CEnemy_Bullet(PRIORITY Priority)
{
	m_TargetPos = ZeroVector3;
	m_State = STATE_UP;
	m_StartPos = ZeroVector3;
	m_bInitVelocity = true;
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Bullet::~CEnemy_Bullet()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Bullet * CEnemy_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CEnemy_Bullet�̃|�C���^
	CEnemy_Bullet *pEnemy_Bullet = nullptr;

	// nullcheck
	if (pEnemy_Bullet == nullptr)
	{
		// �������m��
		pEnemy_Bullet = new CEnemy_Bullet;

		// !nullcheck
		if (pEnemy_Bullet != nullptr)
		{
			// ����������
			pEnemy_Bullet->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pEnemy_Bullet;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CEnemy_Bullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CBullet::Init(pos, rot);

	// ���
	m_StartPos = pos;

	// ������
	CModel_Box::Create(pos, rot, this);

	// �U���n�_����
	AttackPoint_Crate(this);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Bullet::Uninit(void)
{
	// �I������
	CBullet::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Bullet::Update(void)
{
	// �X�V����
	CBullet::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Bullet::Draw(void)
{
	// �`�揈��
	CBullet::Draw();
}
//=============================================================================
// �ړ�����
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Bullet::Move(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPos();

	// �ړ���
	D3DXVECTOR3 move = ZeroVector3;

	// �p�x
	float fAngle = atan2f((pos.x - m_TargetPos.x), (pos.z - m_TargetPos.z));

	// 0�ȏ�̏ꍇ
	if ((int)fAngle != ZERO_INT)
	{
		// �e�̈ړ�
		move.x = -sinf(fAngle) *MOVE_VALUE;
		move.z = -cosf(fAngle) *MOVE_VALUE;
	}
	// UP�̏ꍇ
	if (m_State == STATE_UP)
	{
		// 1000�ȉ��̏ꍇ
		if (pos.y < POS_Y_MAX)
		{
			// UP��
			m_State = STATE_UP;
		}
	}
	// 1000�ȏ�̏ꍇ
	if (pos.y > POS_Y_MAX)
	{
		// DOWN��
		m_State = STATE_DOWN;
	}
	// UP�̏ꍇ
	if (m_State == STATE_UP)
	{
		// �㏸
		move.y = MOVE_VALUE_Y;
	}
	// DOWN�̏ꍇ
	if (m_State == STATE_DOWN)
	{
		// ����
		move.y = -MOVE_VALUE_Y / DIVIDE_2;
	}

	// �ړ��ʐݒ�
	SetMove(move);
}
//=============================================================================
// �����蔻�菈��
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Bullet::Collision(void)
{
	// �D�̈ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �v���C���[�̃|�C���^�擾
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// nullptr�łȂ��ꍇ
	if (pPlayer != nullptr)
	{
		// �v���C���[�ʒu���W�擾
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

		// �v���C���[�T�C�Y�擾
		D3DXVECTOR3 PlayerSize = pPlayer->GetSize();

		// ����
		if (CCollision::CollisionRectangleAndRectangle(pos, PlayerPos, size, PlayerSize) == true)
		{
			// �q�b�g����
			pPlayer->Hit(DAMAGE);

			// ��Ԑݒ�
			Death();
		}
	}
}
//=============================================================================
// �U���n�_����
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Bullet::AttackPoint_Crate(CBullet * pBullet)
{
	// ��󐶐�
	CEnemy_Attack_Arrow_Polygon::Create(m_TargetPos, ARROW_SIZE, pBullet);

	// �U���n�_����
	CEnemy_Attack_Point_Polygon::Create(m_TargetPos, POINT_SIZE, pBullet);
}
//=============================================================================
// �Ε����ˏ���
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Bullet::Projectile_motion(void)
{
	// ����
	D3DXVECTOR3 Dist = ZeroVector3;

	// �����Z�o
	Dist.x = m_StartPos.x - m_TargetPos.x;
	Dist.y = m_StartPos.y - m_TargetPos.y;
	Dist.z = m_StartPos.z - m_TargetPos.z;

	// ���������̋���
	float fX = sqrtf((Dist.x * Dist.x) + (Dist.z * Dist.z));

	// ��������
	float fY = Dist.y;

	// �Ε����˂̌����������x�ɂ��ĉ���
	float fSpeed = sqrtf(-GRAVITY * powf(fX, POW_VALUE) / (2 * powf(cosf(ANGLE), POW_VALUE) * (fX * tanf(ANGLE) + fY)));

	// �x�N�g��
	D3DXVECTOR3 Vec = ZeroVector3;

	// ���K��
	D3DXVec3Normalize(&Vec, &(D3DXVECTOR3(m_TargetPos.x - m_StartPos.x, fX * tanf(ANGLE), m_TargetPos.z - m_StartPos.z)));

	// ���x
	Vec *= fSpeed;

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// false�̏ꍇ
	if (m_bInitVelocity == false)
	{
		// �d��
		move.y += GRAVITY;
	}
	// true�̏ꍇ
	if (m_bInitVelocity == true)
	{
		// �� =���x * ����
		move = Vec;

		// ���ˎ��d�͂�/2
		move.y += GRAVITY / DIVIDE_2F;

		// false1��
		m_bInitVelocity = false;
	}
	// �ړ���
	SetMove(move);
}