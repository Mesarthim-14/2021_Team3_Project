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
#include "player_bullet.h"
#include "effect.h"

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define MOVE_VALUE	(40.0f)								// �ړ���
#define PARENT_NUM	(0)									// �e�̃i���o�[
#define DAMAGE		(100)								// �_���[�W

//�����Ԃ�																			
#define SPLASH_POS			(D3DXVECTOR3(0, 1, 0))									//�ʒu
#define SPLASH_SIZE			(D3DXVECTOR3(80.0f, 80.0f, 80.0f))						//�傫��
#define SPLASH_MOVE			(D3DXVECTOR3(10.0f, 20.0f, 10.0f))						//�ړ���
#define SPLASH_COLOR		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))						//�F
#define SPLASH_LIFE			(200)													//�̗�

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

			// ������
			//CModel_Box::Create(pos, rot, pPlayer_Bullet);
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

	// ������
	//CModel_Box::Create(pos, rot, this);
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
				CharacterPos.x = ((CEnemy*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._41;
				CharacterPos.y = ((CEnemy*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._42;
				CharacterPos.z = ((CEnemy*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._43;

				// �T�C�Y�擾
				D3DXVECTOR3 CharacterSize = ((CEnemy*)pScene)->GetSize();

				//�G�t�F�N�g����
				for (int nCntEffect = 0; nCntEffect < 10; nCntEffect++)
				{
					// �p�[�e�B�N������
					CEffect::Create(CharacterPos,
						SPLASH_SIZE, SPLASH_MOVE, SPLASH_COLOR,
						CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_4), SPLASH_LIFE);
				}

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
}
