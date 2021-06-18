//=============================================================================
// �e [bullet.h]
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
#include "bullet.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define GRAVITY		(0.1f)								// �d��
#define MOVE_VALUE	(40.0f)								// �ړ���
#define ANGLE_180	(D3DXToRadian(180))					// 180�x
#define ANGLE_90	(D3DXToRadian(90))					// 90�x
#define LENGTH		(-800.0f)							// ����
#define BULLET_Y	(500.0f)							// �e��Y��
#define PARENT_NUM	(0)									// �e�̃i���o�[
#define DAMAGE		(100)								// �_���[�W
#define SIZE		(D3DXVECTOR3(100.0f,100.0f,100.0f))	// �T�C�Y
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CBullet::CBullet(PRIORITY Priority)
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CBullet::~CBullet()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CBullet�̃|�C���^
	CBullet *pBullet = nullptr;

	// nullcheck
	if (pBullet == nullptr)
	{
		// �������m��
		pBullet = new CBullet;

		// !nullcheck
		if (pBullet != nullptr)
		{
			// ����������
			pBullet->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pBullet;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_BULLET);

		// ���f���̏���n��
		BindModel(model);
	}

	// ���C�t�ݒ�
	SetLife(500);

	// �T�C�Y
	SetSize(SIZE);

	// ���ˈʒu
	D3DXVECTOR3 bulletpos = ZeroVector3;

	// �ړ�
	D3DXVECTOR3 move = ZeroVector3;

	//���W�����߂�
	bulletpos.x = pos.x + cosf(rot.y - ANGLE_90) * LENGTH;
	bulletpos.z = pos.z + sinf(rot.y + ANGLE_90) * LENGTH;
	bulletpos.y = BULLET_Y;

	// �e�̈ړ�
	move.x = sinf(rot.y + ANGLE_180) *MOVE_VALUE;
	move.z = cosf(rot.y + ANGLE_180) *MOVE_VALUE;

	// �ړ��ʐݒ�
	SetMove(move);

	// ����������
	CModel::Init(bulletpos, ZeroVector3);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Uninit(void)
{
	// �I������
	CModel::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Update(void)
{
	// �X�V����
	CModel::Update();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �ړ�
	move.y -= GRAVITY;

	// �ړ��ʐݒ�
	SetMove(move);

	// �����蔻��
	Collision();

	if (GetLife() <= 0)
	{
		// �I������
		Uninit();

		return;
	}
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}
//=============================================================================
// �����蔻�菈��
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Collision(void)
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
				if (CCollision::CollisionCircularAndCircular(pos, CharacterPos, size.x / DIVIDE_2, CharacterSize.z / DIVIDE_2) == true)  
				{
					// �_���[�W
					int nLife = ((CCharacter*)pScene)->GetLife();

					// ���C�t���Z
					nLife = nLife - DAMAGE;

					// ���C�t�ݒ�
					((CCharacter*)pScene)->SetLife(nLife);

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