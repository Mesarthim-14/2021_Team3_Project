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

//=============================================================================
// �}�N����`
//=============================================================================
#define GRAVITY_POWAR			(0.7f)						// �d�͂̋���
#define GROUND_RIMIT			(0.0f)						// �n�ʂ̐���

//=============================================================================
// static����������
//=============================================================================
 int CCharacter::m_nAllNum = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharacter::CCharacter(PRIORITY Priority) : CScene(Priority)
{
	 m_pos = ZeroVector3;
	 m_posOld = ZeroVector3;
	 m_move = ZeroVector3;
	 m_rot = ZeroVector3;
	 m_nLife = 0;
	 m_fSpeed = 0.0f;
	 m_bArmor = false;
	 m_nStateCounter = 0;
	 m_pMotion = nullptr;
	 m_nParts = 0;
	 m_apModelAnime.clear();
	 m_bLanding = false;
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
	m_pos = pos;	// ���W�̐ݒ�
	m_rot = rot;	// �p�x�̐ݒ�

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCharacter::Uninit()
{
	for (size_t nCntModelNum = 0; nCntModelNum < m_apModelAnime.size(); nCntModelNum++)
	{
		// !nullcheck
		if (m_apModelAnime.at(nCntModelNum) != nullptr)
		{
			//�������̍폜
			delete m_apModelAnime.at(nCntModelNum);

			//�������̃N���A
			m_apModelAnime.at(nCntModelNum) = nullptr;
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
	//�A�j���[�V�����̍X�V����
	ModelAnimeUpdate();

	// �d��
	Gravity();

	// �ړ��ʉ��Z
	m_pos += m_move;

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

	for (int nCntModelNum = 0; nCntModelNum < m_nParts; nCntModelNum++)
	{
		if (m_apModelAnime.at(nCntModelNum) != nullptr)
		{
			//�K�w���f���N���X�̕`�揈��
			m_apModelAnime.at(nCntModelNum)->Draw(m_rot);
		}
	}

	for (int nCntModelNum = 0; nCntModelNum < m_nParts; nCntModelNum++)
	{
		if (m_apModelAnime.at(nCntModelNum) != nullptr)
		{
			// �K�w���f���N���X�̉e�`��
			m_apModelAnime.at(nCntModelNum)->ShadowDraw(m_rot);
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
			std::vector<CXfile::MODEL> model = pXfile->GetHierarchyXfile(FileNum);

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
	// ���n��Ԃ���Ȃ�������
	if (!m_bLanding)
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