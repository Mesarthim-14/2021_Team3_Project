//=============================================================================
//
// �L�����N�^�[�N���X [character.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"
#include "renderer.h"
#include "manager.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "texture.h"
#include "sound.h"
#include "resource_manager.h"
#include "motion.h"
#include "map.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define GRAVITY_POWAR			(1.0f)						// �d�͂̋���
#define GROUND_RIMIT			(0.0f)						// �n�ʂ̐���
#define PARENT_NUM				(0)							// �e�̃i���o�[
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharacter::CCharacter(PRIORITY Priority) : CScene(Priority)
{
	m_pos = ZeroVector3;
	m_posOld = ZeroVector3;
	m_move = ZeroVector3;
	m_rot = ZeroVector3;
	m_size = ZeroVector3;
	m_nLife = 0;
	m_fSpeed = 0.0f;
	m_bArmor = false;
	m_nStateCounter = 0;
	m_pMotion = nullptr;
	m_nParts = 0;
	m_apModelAnime.clear();
	m_bLanding = false;
	m_State = STATE_NORMAL;
	m_bUseShadow = false;
	m_RayData = { ZERO_FLOAT,ZERO_FLOAT,ZERO_INT };
	m_bGravity = true;
	m_bHitMap = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCharacter::~CCharacter()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCharacter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �����̑��
	m_pos = pos;
	m_rot = rot;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCharacter::Uninit()
{
	for (auto &nCount : m_apModelAnime)
	{
		// !nullcheck
		if (nCount != nullptr)
		{
			//�������̍폜
			delete nCount;

			//�������̃N���A
			nCount = nullptr;
		}
	}

	// �N���A
	m_apModelAnime.clear();

	// !nullcheck
	if (m_pMotion != nullptr)
	{
		//�������̍폜
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CCharacter::Update()
{
	// �d��
	Gravity();

	// false�̏ꍇ
	if (m_bHitMap == false)
	{
		// �ړ��ʉ��Z
		m_pos += m_move;
	}
	// ���G���Ԃ̂Ƃ�
	if (m_bArmor == true)
	{
		// �J�E���^�[��i�߂�
		m_nStateCounter++;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CCharacter::Draw()
{
	// �`�揈��
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���f���̕`��
	for (auto &model : m_apModelAnime)
	{
		if (model != nullptr)
		{
			model->Draw(m_rot);
		}
	}

	if (m_bUseShadow)
	{
		// �e�̕`��
		for (auto &shadow : m_apModelAnime)
		{
			if (shadow != nullptr)
			{
				shadow->ShadowDraw(m_rot);
			}
		}
	}
}

//=============================================================================
// ���f���̐���
//=============================================================================
void CCharacter::ModelCreate(CXfile::HIERARCHY_XFILE_NUM FileNum)
{
	// XFile�̃|�C���^�擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f���p�[�c�̐ݒ�
		m_nParts = pXfile->GetModelParts(FileNum);

		//���f���p�[�c�����J��Ԃ�
		for (int nCntModel = 0; nCntModel < m_nParts; nCntModel++)
		{
			// ���[�J���ϐ��擾
			CModelAnime *pModelAnime = nullptr;
			CXfile::MODELFILE ModelFile = pXfile->GetModelFile(nCntModel, FileNum);
			vector<CXfile::MODEL> model = pXfile->GetHierarchyXfile(FileNum);

			// nullcheck
			if (pModelAnime == nullptr)
			{
				// �C���X�^���X����
				pModelAnime = CModelAnime::Create(ModelFile.offsetPos, ModelFile.offsetRot, model.at(nCntModel));

				// !nullcheck
				if (pModelAnime != nullptr)
				{
					pModelAnime->SetModel(model.at(nCntModel));

					//�e���f���̏ꍇ
					if (nCntModel == 0)
					{
						pModelAnime->SetParent(nullptr);
					}
					//�q���f���̏ꍇ
					else
					{
						//�����̐e����ݒ肷��
						pModelAnime->SetParent(m_apModelAnime.at(ModelFile.nParent));
					}
				}

				// ��������
				m_apModelAnime.push_back(pModelAnime);
			}
		}
		// nullcheck
		if (m_pMotion == nullptr)
		{
			// �C���X�^���X����
			m_pMotion = CMotion::Create(pXfile->GetModelFileName(FileNum));
		}
	}
}

//=============================================================================
// ���f���A�j���[�V����
//=============================================================================
void CCharacter::ModelAnimeUpdate(void)
{
	// ���[�V�����̍X�V����
	if (m_pMotion != nullptr)
	{
		// ���[�V�����̍X�V
		m_pMotion->UpdateMotion(m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// �d�͂̏���
//=============================================================================
void CCharacter::Gravity(void)
{
	// �d�͂�������
	m_move.y -= GRAVITY_POWAR;
	m_pos.y += m_move.y;		// ����

								// �n�ʂ̔���
	if (m_pos.y <= GROUND_RIMIT)
	{
		Landing(GROUND_RIMIT);
	}
}

//=============================================================================
// ���n�̏���
//=============================================================================
void CCharacter::Landing(float fHeight)
{
	m_move.y = 0.0f;
	m_pos.y = fHeight;

	// ���n�̏��
	if (m_bLanding == false)
	{
		m_bLanding = true;
	}
}
//=============================================================================
// ���C�̓����蔻��
// Author : SugawaraTsukasa
//=============================================================================
void CCharacter::RayCollision(void)
{
	// CScene�̃|�C���^
	CScene *pScene = nullptr;

	// nullcheck
	if (pScene == nullptr)
	{
		// �擪�̃|�C���^�擾
		pScene = GetTop(PRIORITY_MAP);

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

				// ���C�̐���0��葽���ꍇ
				if (m_RayData.nNum > ZERO_INT)
				{
					// �ʒu�擾
					Pos.x = GetModelAnime(PARENT_NUM)->GetMtxWorld()._41;
					Pos.y = GetModelAnime(PARENT_NUM)->GetMtxWorld()._42;
					Pos.z = GetModelAnime(PARENT_NUM)->GetMtxWorld()._43;

					// ���C�̏��
					CCollision::RAY_INFO Ray_Info = CCollision::RayCollision(Pos, ((CMap*)pScene), m_RayData.fAngle, m_RayData.fRange, m_RayData.nNum);

					// true�̏ꍇ
					if (Ray_Info.bHit == true)
					{
						// �ړ���0��
						SetMove(ZeroVector3);

						// �ʒu
						Pos -= D3DXVECTOR3(sinf(Ray_Info.VecDirection.y), ZERO_FLOAT, cosf(Ray_Info.VecDirection.y));

						SetPos(Pos);
					}
				}
				// ���̃|�C���^�擾
				pScene = pSceneCur;
			}
		}
	}
}

//=============================================================================
// ���[�V�����̐ݒ�
//=============================================================================
void CCharacter::SetMotion(int nMotionState)
{
	// !nullcheck
	if (m_pMotion != nullptr)
	{
		// ���[�V�����̍X�V
		m_pMotion->SetMotion(nMotionState, m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// �e�̉�]�𔽉f�����邩
//=============================================================================
void CCharacter::SetShadowRotCalculation(void)
{
	// ���f���̕`��
	for (auto &model : m_apModelAnime)
	{
		if (model != nullptr)
		{
			model->SetRotCalculation(true);
		}
	}
}