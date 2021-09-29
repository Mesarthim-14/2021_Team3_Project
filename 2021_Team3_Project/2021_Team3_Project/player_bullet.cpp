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
#include "model_box.h"
#include "enemy.h"
#include "torpedo.h"
#include "player_bullet.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define MOVE_VALUE	(50.0f)	 // �ړ���
#define PARENT_NUM	(0)		 // �e�̃i���o�[
#define DAMAGE		(25)	 // �_���[�W
#define RAY_RANGE	(100.0f) // ���C�͈̔�
#define RAY_NUM		(1)		 // ���C�̖{��
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Bullet::CPlayer_Bullet(PRIORITY Priority) : CBullet (Priority)
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Bullet::~CPlayer_Bullet()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Bullet * CPlayer_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPlayer_Bullet�̃|�C���^
	CPlayer_Bullet *pPlayer_Bullet = nullptr;

	// nullcheck
	if (pPlayer_Bullet == nullptr)
	{
		// �������m��
		pPlayer_Bullet = new CPlayer_Bullet;

		// !nullcheck
		if (pPlayer_Bullet != nullptr)
		{
			// ����������
			pPlayer_Bullet->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pPlayer_Bullet;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CPlayer_Bullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// XFile���ݒ�
	SetXFileNum(CXfile::XFILE_NUM_BULLET);

	// ����������
	CBullet::Init(pos, ZeroVector3);

	// �ړ�
	D3DXVECTOR3 move = ZeroVector3;

	// �e�̈ړ�
	move.x = -sinf(rot.y) *MOVE_VALUE;
	move.z = -cosf(rot.y) *MOVE_VALUE;

	// �ړ��ʐݒ�
	SetMove(move);

	// ���C�f�[�^
	RAY_DATA Ray_Data = { rot.y , RAY_RANGE , RAY_NUM };

	// ���C�f�[�^�ݒ�
	SetRay_Data(Ray_Data);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Bullet::Uninit(void)
{
	// �I������
	CBullet::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Bullet::Update(void)
{
	// �X�V����
	CBullet::Update();

	// �����蔻��
	Collision();

	// true�̏ꍇ
	if (RayCollision() == true)
	{
		// �I��
		Uninit();
		return;
	}
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Bullet::Draw(void)
{
	// �`�揈��
	CBullet::Draw();
}
//=============================================================================
// �����蔻�菈��
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Bullet::Collision(void)
{
	// CScene�̃|�C���^
	CScene *pScene = nullptr;

	// �D�̈ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// nullcheck
	if (pScene == nullptr)
	{
		// �擪�̃|�C���^�擾
		pScene = GetTop(PRIORITY_ENEMY);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcter�Ƃ̓����蔻��
			while (pScene != nullptr) 	// nullptr�ɂȂ�܂ŉ�
			{
				// �g�b�v���
				CScene *pSceneCur = pScene->GetNext();

				// �ʒu
				D3DXVECTOR3 CharacterPos = ZeroVector3;

				// �ʒu�擾
				CharacterPos.x = ((CEnemy*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._41;
				CharacterPos.y = ((CEnemy*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._42;
				CharacterPos.z = ((CEnemy*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._43;

				// �T�C�Y�擾
				D3DXVECTOR3 CharacterSize = ((CEnemy*)pScene)->GetSize();

				// ����
				if (CCollision::CollisionRectangleAndRectangle(pos, CharacterPos, size, CharacterSize) == true)
				{
					// ���C�t�ݒ�
					((CEnemy*)pScene)->Hit(DAMAGE);

					// �I��
					Uninit();

					return;
				}

				// ���ɑ��
				pScene = pSceneCur;
			}
		}
	}
	// nullcheck
	if (pScene == nullptr)
	{
		// �擪�̃|�C���^�擾
		pScene = GetTop(PRIORITY_TORPEDO);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcter�Ƃ̓����蔻��
			while (pScene != nullptr) 	// nullptr�ɂȂ�܂ŉ�
			{
				// �g�b�v���
				CScene *pSceneCur = pScene->GetNext();

				// �ʒu�擾
				D3DXVECTOR3 TorpedoPos = ((CTorpedo*)pScene)->GetPos();

				// �T�C�Y�擾
				D3DXVECTOR3 TorpedoSize = ((CTorpedo*)pScene)->GetSize();

				// ����
				if (CCollision::CollisionRectangleAndRectangle(pos, TorpedoPos, size, TorpedoSize) == true)
				{
					// �I��
					((CTorpedo*)pScene)->Uninit();

					// �I��
					Uninit();

					return;
				}

				// ���ɑ��
				pScene = pSceneCur;
			}
		}
	}
}