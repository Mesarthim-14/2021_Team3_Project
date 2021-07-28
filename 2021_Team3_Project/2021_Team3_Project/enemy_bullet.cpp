//=============================================================================
// �v���C���[�e [player_bullet.cpp]
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
#define MOVE_VALUE		(40.0f)								// �ړ���
#define MOVE_VALUE_Y	(60.0f)								// �ړ���
#define POS_Y_MAX		(4000.0f)							// Y�ő�l
#define PARENT_NUM		(0)									// �e�̃i���o�[
#define DAMAGE			(100)								// �_���[�W
#define ANGLE_90		(D3DXToRadian(90))					// 90�x
#define ARROW_SIZE	(D3DXVECTOR3(500.0f,300.0f,0.0f))
#define POINT_SIZE	(D3DXVECTOR3(300.0f,0.0f,400.0f))
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Bullet::CEnemy_Bullet(PRIORITY Priority)
{
	m_PlayerPos		= ZeroVector3;
	m_State			= STATE_UP;
	m_pEnemy_Bullet = nullptr;
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
			// ���
			pEnemy_Bullet->m_pEnemy_Bullet = pEnemy_Bullet;

			// ����������
			pEnemy_Bullet->Init(pos, rot);

			// ������
			CModel_Box::Create(pos, rot, pEnemy_Bullet);
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

	// �v���C���[�̃|�C���^�擾
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// �ʒu���W�擾
	m_PlayerPos = pPlayer->GetPos();

	// �U���n�_����
	AttackPoint_Crate();
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

	// �ړ�����
	Move();

	// �����蔻��
	Collision();
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
	float fAngle = atan2f((pos.x - m_PlayerPos.x), (pos.z - m_PlayerPos.z));

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

	// �v���C���[�ʒu���W�擾
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	// �v���C���[�T�C�Y�擾
	D3DXVECTOR3 PlayerSize = pPlayer->GetSize();

	// ����
	if (CCollision::CollisionRectangleAndRectangle(pos, PlayerPos, size, PlayerSize) == true)
	{
		// ��Ԑݒ�
		SetState(STATE_DEAD);
	}
}
//=============================================================================
// �U���n�_����
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Bullet::AttackPoint_Crate(void)
{
	// ��󐶐�
	CEnemy_Attack_Arrow_Polygon::Create(m_PlayerPos, ARROW_SIZE, m_pEnemy_Bullet);

	// �U���n�_����
	CEnemy_Attack_Point_Polygon::Create(m_PlayerPos, POINT_SIZE, m_pEnemy_Bullet);
}