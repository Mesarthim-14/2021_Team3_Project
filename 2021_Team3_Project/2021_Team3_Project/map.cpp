//=============================================================================
// �}�b�v [bullet.cpp]
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
#include "renderer.h"
#include "game.h"
#include "model.h"
#include "map.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define SIZE		(D3DXVECTOR3(80.0f,80.0f,80.0f))	// �T�C�Y
#define POS_Y_MIN	(0.0f)								// Y���W�ŏ��l
#define PARENT_NUM	(0)									// �e�̖��O
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CMap::CMap(PRIORITY Priority) : CModel(Priority)
{
	m_Type = TYPE_NORMAL;
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CMap::~CMap()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CMap * CMap::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type)
{
	// CBullet�̃|�C���^
	CMap *pMap = nullptr;

	// nullcheck
	if (pMap == nullptr)
	{
		// �������m��
		pMap = new CMap;

		// !nullcheck
		if (pMap != nullptr)
		{
			// ���
			pMap->m_Type = type;

			// ����������
			pMap->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pMap;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CMap::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f��
		CXfile::MODEL model;

		// TYPE_NORMAL�̏ꍇ
		if (m_Type == TYPE_NORMAL)
		{
			// ���f�����擾
			model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP);
		}
		// TYPE_BOSS�̏ꍇ
		if (m_Type == TYPE_BOSS)
		{
			// ���f�����擾
			model = pXfile->GetXfile(CXfile::XFILE_NUM_BOSS_MAP);
		}
		// ���f���̏���n��
		BindModel(model);
	}

	// ����������
	CModel::Init(pos, ZeroVector3);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CMap::Uninit(void)
{
	// �I������
	CModel::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CMap::Update(void)
{
	// �X�V����
	CModel::Update();


	//RayCollision();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CMap::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}
//=============================================================================
// ���C�̓����蔻�菈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CMap::RayCollision(void)
{
	// CScene�̃|�C���^
	CScene *pScene = nullptr;

	// nullcheck
	if (pScene == nullptr)
	{
		//===============================================================
		// �G�ȊO�̐e�q�֌W�̂���I�u�W�F�N�g
		//===============================================================
		// �擪�̃|�C���^�擾
		pScene = GetTop(PRIORITY_CHARACTER);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcter�Ƃ̓����蔻��
			while (pScene != nullptr) // nullptr�ɂȂ�܂ŉ�
			{
				// ���݂̃|�C���^
				CScene *pSceneCur = pScene->GetNext();

				// �ʒu
				D3DXVECTOR3 Pos = ZeroVector3;

				// ���C�̏��擾
				CCharacter::RAY_DATA RayData = ((CCharacter*)pScene)->GetRay_Data();

				// ���C�̐���0��葽���ꍇ
				if (RayData.nNum > ZERO_INT)
				{
					// �ʒu�擾
					Pos.x = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._41;
					Pos.y = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._42;
					Pos.z = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._43;

					// ���C�̏��
					CCollision::RAY_INFO Ray_Info = CCollision::RayCollision(Pos, this, RayData.fAngle, RayData.fRange, RayData.nNum);

					// true�̏ꍇ
					if (Ray_Info.bHit == true)
					{
						// �q�b�g�}�b�v
						((CCharacter*)pScene)->SetHitMap(true);

						// �ړ���0��
						((CCharacter*)pScene)->SetMove(ZeroVector3);

						// �ʒu
						Pos -= D3DXVECTOR3(sinf(Ray_Info.VecDirection.y), ZERO_FLOAT, cosf(Ray_Info.VecDirection.y));

						// �ʒu�ݒ�
						((CCharacter*)pScene)->SetPos(Pos);
					}
				}
				// ���̃|�C���^�擾
				pScene = pSceneCur;
			}
		}
		//===============================================================
		// �e�q�֌W�̂���G
		//===============================================================
		// �擪�̃|�C���^�擾
		pScene = GetTop(PRIORITY_ENEMY);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcter�Ƃ̓����蔻��
			while (pScene != nullptr) // nullptr�ɂȂ�܂ŉ�
			{
				// ���݂̃|�C���^
				CScene *pSceneCur = pScene->GetNext();

				// �ʒu
				D3DXVECTOR3 Pos = ZeroVector3;

				// ���C�̏��擾
				CCharacter::RAY_DATA RayData = ((CCharacter*)pScene)->GetRay_Data();

				// ���C�̐���0��葽���ꍇ
				if (RayData.nNum > ZERO_INT)
				{
					// �ʒu�擾
					Pos.x = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._41;
					Pos.y = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._42;
					Pos.z = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._43;

					// ���C�̏��
					CCollision::RAY_INFO Ray_Info = CCollision::RayCollision(Pos, this, RayData.fAngle, RayData.fRange, RayData.nNum);

					// true�̏ꍇ
					if (Ray_Info.bHit == true)
					{
						
						// �ړ���0��
						((CCharacter*)pScene)->SetMove(ZeroVector3);

						// �ʒu
						Pos -= D3DXVECTOR3(sinf(Ray_Info.VecDirection.y), ZERO_FLOAT, cosf(Ray_Info.VecDirection.y));

						// �ʒu�ݒ�
						((CCharacter*)pScene)->SetPos(Pos);
					}
				}
				// ���̃|�C���^�擾
				pScene = pSceneCur;
			}
		}

		//===============================================================
		// �e�q�֌W�̂Ȃ��G
		//===============================================================
		// �擪�̃|�C���^�擾
		pScene = GetTop(PRIORITY_TORPEDO);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcter�Ƃ̓����蔻��
			while (pScene != nullptr) // nullptr�ɂȂ�܂ŉ�
			{
				// ���݂̃|�C���^
				CScene *pSceneCur = pScene->GetNext();

				// �ʒu
				D3DXVECTOR3 Pos = ((CModel*)pScene)->GetPos();

				// ���C�̏��擾
				CModel::RAY_DATA RayData = ((CModel*)pScene)->GetRay_Data();

				// ���C�̐���0��葽���ꍇ
				if (RayData.nNum > ZERO_INT)
				{
					// ���C�̏��
					CCollision::RAY_INFO Ray_Info = CCollision::RayCollision(Pos, this, RayData.fAngle, RayData.fRange, RayData.nNum);

					// true�̏ꍇ
					if (Ray_Info.bHit == true)
					{
						// �ړ���0��
						((CModel*)pScene)->SetMove(ZeroVector3);

						// �ʒu
						Pos -= D3DXVECTOR3(sinf(Ray_Info.VecDirection.y), ZERO_FLOAT, cosf(Ray_Info.VecDirection.y));

						// �ʒu�ݒ�
						((CModel*)pScene)->SetPos(Pos);

						// �ʒu�ݒ�
						((CModel*)pScene)->Uninit();

						return;
					}
				}
				// ���̃|�C���^�擾
				pScene = pSceneCur;
			}
		}
	}
}