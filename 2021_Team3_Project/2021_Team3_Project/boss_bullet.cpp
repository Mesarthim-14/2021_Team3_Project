//=============================================================================
// �{�X�̒e [boss_bullet.cpp]
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
#include "enemy_bullet.h"
#include "boss_bullet.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define ADD_ROT			(D3DXVECTOR3(D3DXToRadian(1.5f),0.0f,0.0f))		// �������Z
#define MAX_ANGLE		(D3DXToRadian(270.0f))							// �ő�p�x
#define RAND_POS_MAX	(5000)											// �ő�
#define RAND_POS_MIN	(0)												// �ŏ�
#define RANDOM_POS_MUT	(10)											// 10�{
#define MUT_2			(2)												// 2�{
#define BULLET_NUM		(20)											// �e�̔��ː�
#define ANGLE_180		(D3DXToRadian(90.0f))							// �p�x90
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Bullet::CBoss_Bullet(PRIORITY Priority) : CEnemy_Bullet(Priority)
{
	m_fAngle = ZERO_FLOAT;
	m_Type	 = TYPE_NORMAL;
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Bullet::~CBoss_Bullet()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Bullet * CBoss_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,TYPE type)
{
	// CBoss_Bullet�̃|�C���^
	CBoss_Bullet *pBoss_Bullet = nullptr;

	// nullcheck
	if (pBoss_Bullet == nullptr)
	{
		// �������m��
		pBoss_Bullet = new CBoss_Bullet;

		// !nullcheck
		if (pBoss_Bullet != nullptr)
		{
			// ���
			pBoss_Bullet->m_Type = type;

			// ����������
			pBoss_Bullet->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pBoss_Bullet;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBoss_Bullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����
	D3DXVECTOR3 Rot = rot;

	// XFile���ݒ�
	SetXFileNum(CXfile::XFILE_NUM_TORPEDO);

	// �v���C���[�̃|�C���^�擾
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// �^�[�Q�b�g�ʒu�擾
		D3DXVECTOR3 Targetpos = pPlayer->GetPos();

		// TYPE_RANDOM�̏ꍇ
		if (m_Type == TYPE_RANDOM)
		{
			// �����_���ʒu
			D3DXVECTOR3 randpos = ZeroVector3;

			// �����_��
			randpos.x = float(rand() % RAND_POS_MAX *RANDOM_POS_MUT * MUT_2 - RAND_POS_MAX *RANDOM_POS_MUT / MUT_2);
			randpos.z = float(rand() % RAND_POS_MAX *RANDOM_POS_MUT * MUT_2 - RAND_POS_MAX *RANDOM_POS_MUT / MUT_2);

			// ���Z
			randpos.x = randpos.x / RANDOM_POS_MUT;
			randpos.z = randpos.z / RANDOM_POS_MUT;

			// �ʒu�����_�����Z
			Targetpos += randpos;
		}
		// �^�[�Q�b�g�ʒu�ݒ�
		SetTargetPos(Targetpos);

		// �p�x
		m_fAngle = atan2f((Targetpos.x - pos.x), (Targetpos.z - pos.z));
	}
	// ����
	Rot.y = m_fAngle;

	// 180�x���Z
	Rot.x = ANGLE_180;

	// ����������
	CEnemy_Bullet::Init(pos, Rot);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Bullet::Uninit(void)
{
	// �I������
	CEnemy_Bullet::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Bullet::Update(void)
{
	// �X�V
	CEnemy_Bullet::Update();

	// �����擾
	D3DXVECTOR3 rot = GetRot();

	// �����̊p�x��180���Ⴂ�ꍇ
	if (rot.x < MAX_ANGLE)
	{
		// �������Z
		rot.x += ADD_ROT.x;

		// �����ݒ�
		SetRot(rot);
	}

	// �Ε����ˏ���
	Projectile_motion();

	// �����蔻��
	Collision();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Bullet::Draw(void)
{
	// �`�揈��
	CEnemy_Bullet::Draw();
}
//=============================================================================
// �e���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Bullet::CreateBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �v���C���[�ɔ�Ԓe����
	Create(pos, rot, TYPE_NORMAL);

	// 10�񐶐�
	for (int nCount = ZERO_INT; nCount < BULLET_NUM; nCount++)
	{
		// �����_���e����
		Create(pos, rot, TYPE_RANDOM);
	}
}