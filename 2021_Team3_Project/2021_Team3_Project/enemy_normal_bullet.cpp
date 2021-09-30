//=============================================================================
// �ʏ�G�̒e [enemy_normal_bullet.cpp]
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
#include "enemy_normal_bullet.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Normal_Bullet::CEnemy_Normal_Bullet(PRIORITY Priority) : CEnemy_Bullet(Priority)
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Normal_Bullet::~CEnemy_Normal_Bullet()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Normal_Bullet * CEnemy_Normal_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CEnemy_Normal_Bullet�̃|�C���^
	CEnemy_Normal_Bullet *pEnemy_Noraml_Bullet = nullptr;

	// nullcheck
	if (pEnemy_Noraml_Bullet == nullptr)
	{
		// �������m��
		pEnemy_Noraml_Bullet = new CEnemy_Normal_Bullet;

		// !nullcheck
		if (pEnemy_Noraml_Bullet != nullptr)
		{
			// ����������
			pEnemy_Noraml_Bullet->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pEnemy_Noraml_Bullet;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CEnemy_Normal_Bullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// XFile���ݒ�
	SetXFileNum(CXfile::XFILE_NUM_BULLET);

	// �v���C���[�̃|�C���^�擾
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// �ʒu���W�擾
		SetTargetPos(pPlayer->GetPos());
	}

	// ����������
	CEnemy_Bullet::Init(pos, rot);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Normal_Bullet::Uninit(void)
{
	// �I������
	CEnemy_Bullet::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Normal_Bullet::Update(void)
{
	// �X�V����
	CEnemy_Bullet::Update();

	// �ړ�����
	Projectile_motion();

	// �����蔻��
	Collision();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Normal_Bullet::Draw(void)
{
	// �`�揈��
	CEnemy_Bullet::Draw();
}