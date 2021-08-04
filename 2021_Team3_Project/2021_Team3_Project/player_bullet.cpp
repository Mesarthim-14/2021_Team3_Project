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
#include "player_bullet.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define MOVE_VALUE	(40.0f)								// �ړ���
#define PARENT_NUM	(0)									// �e�̃i���o�[
#define DAMAGE		(100)								// �_���[�W
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Bullet::CPlayer_Bullet(PRIORITY Priority)
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

			// ������
			CModel_Box::Create(pos, rot, pPlayer_Bullet);
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
	// ����������
	CBullet::Init(pos, ZeroVector3);

	// �ړ�
	D3DXVECTOR3 move = ZeroVector3;

	// �e�̈ړ�
	move.x = -sinf(rot.y) *MOVE_VALUE;
	move.z = -cosf(rot.y) *MOVE_VALUE;

	// �ړ��ʐݒ�
	SetMove(move);

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
				CharacterPos.x = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._41;
				CharacterPos.y = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._42;
				CharacterPos.z = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._43;

				// �T�C�Y�擾
				D3DXVECTOR3 CharacterSize = ((CCharacter*)pScene)->GetSize();

				// ����
				if (CCollision::CollisionRectangleAndRectangle(pos, CharacterPos, size, CharacterSize) == true)
				{
					// ��Ԑݒ�
					SetState(CModel::STATE_DEAD);

					// �_���[�W
					int nLife = ((CCharacter*)pScene)->GetLife();

					// ���C�t���Z
					nLife = nLife - DAMAGE;

					// ���C�t�ݒ�
					((CCharacter*)pScene)->SetLife(nLife);
				}

				// ���ɑ��
				pScene = pSceneCur;
			}
		}
	}
}