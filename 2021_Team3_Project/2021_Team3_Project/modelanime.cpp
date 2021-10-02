//=============================================================================
//
// �K�w�\���p�̃��f���N���X���� [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "modelanime.h"
#include "manager.h"
#include "renderer.h"
#include "resource_manager.h"
#include "shadow.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModelAnime::CModelAnime()
{
	//�e�����o�ϐ��̃N���A
	memset(&m_model, 0, sizeof(m_model));
	m_pos = ZeroVector3;
	m_rot = ZeroVector3;
	m_posAnime = ZeroVector3;
	m_rotAnime = ZeroVector3;
	m_pParent = nullptr;
	ZeroMemory(m_OldMtxWorld, sizeof(m_OldMtxWorld));
	ZeroMemory(m_mtxWorld, sizeof(m_mtxWorld));
	m_pShadow = nullptr;
	m_bRotCalculation = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModelAnime::~CModelAnime()
{
	// �|�C���^�̊J��
	HasPtrDelete();
}

//=============================================================================
// �N���G�C�g����
//=============================================================================
CModelAnime * CModelAnime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXfile::MODEL model)
{
	//�K�w���f���N���X�̃|�C���^�ϐ�
	CModelAnime *pModelAnime = nullptr;

	//�C���X�^���X����
	pModelAnime = new CModelAnime;

	// !nullcheck
	if (pModelAnime != nullptr)
	{
		//�����������Ăяo��
		pModelAnime->Init(pos, rot, model);
	}
	//���s���Ă����ꍇ
	else
	{
		return nullptr;
	}

	return pModelAnime;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CModelAnime::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXfile::MODEL model)
{
	//�ʒu�̐ݒ�
	m_pos = pos;

	//�����̐ݒ�
	m_rot = rot;

	// ���f�����ݒ�
	SetModel(model);

	// nullcheck
	if (!m_pShadow)
	{
		// �e�̐���
		m_pShadow = CShadow::Create(model.pMesh);
	}

	return S_OK;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CModelAnime::Draw(D3DXVECTOR3 rot)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxParent;
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ێ��p
	D3DXMATERIAL*pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	// �Â����[���h���W
	m_OldMtxWorld1[4] = m_OldMtxWorld1[3];
	m_OldMtxWorld1[3] = m_OldMtxWorld1[2];
	m_OldMtxWorld1[2] = m_OldMtxWorld1[1];
	m_OldMtxWorld1[1] = m_OldMtxWorld1[0];
	m_OldMtxWorld1[0] = m_OldMtxWorld;
	m_OldMtxWorld = m_mtxWorld;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y + m_rotAnime.y, m_rot.x + m_rotAnime.x, m_rot.z + m_rotAnime.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�e�����݂���ꍇ
	if (m_pParent != nullptr)
	{
		//�e����ݒ�
		mtxParent = m_pParent->GetMtxWorld();
	}
	//�e�����݂��Ȃ��ꍇ
	else
	{
		//�f�o�C�X����ݒ�
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//�e�̃}�g���N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾����
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_model.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_model.dwNumMat; nCntMat++)
	{
		//�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
		pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (m_model.apTexture[nCntMat] != nullptr)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_model.apTexture[nCntMat]);
		}
		else
		{
			// �e�N�X�`���ݒ�
			pDevice->SetTexture(0, nullptr);
		}

		//���f���p�[�c�̕`��
		m_model.pMesh->DrawSubset(nCntMat);

		// �����x�߂�
		pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
	}

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	// ���[���h�}�g���b�N�X
	if (m_pShadow)
	{
		if (m_bRotCalculation)
		{
			// �e�̐���
			m_pShadow->CreateShadow(m_rot, rot, SetShadowInfo(rot, mtxParent));
		}
		else
		{
			// �e�̐���
			m_pShadow->CreateShadow(m_rot + rot, m_mtxWorld);
		}
	}
}

//=============================================================================
// �e�̕`��
//=============================================================================
void CModelAnime::ShadowDraw(D3DXVECTOR3 rot)
{
	if (m_pShadow)
	{
		// �e�̕`�揈��
		m_pShadow->VolumeDraw();
	}
}

//=============================================================================
// �e�̏��̐ݒ�
//=============================================================================
D3DXMATRIX CModelAnime::SetShadowInfo(D3DXVECTOR3 rot, D3DXMATRIX pParent)
{
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtxWorld;                            // ���[���h�}�g���b�N�X
	D3DXMatrixIdentity(&mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &pParent);

	return mtxWorld;
}

//=============================================================================
// �ێ��|�C���^�̊J������
//=============================================================================
void CModelAnime::HasPtrDelete(void)
{
	if (m_pShadow)
	{
		// �e�̏I������
		m_pShadow->Uninit();
		delete m_pShadow;
		m_pShadow = nullptr;
	}
}

//=============================================================================
//�K�w���f���N���X�̐e���̐ݒ菈��
//=============================================================================
void CModelAnime::SetParent(CModelAnime * pParent)
{
	m_pParent = pParent;
}

//=============================================================================
// �K�w���f���N���X�̌����̐ݒ菈��
//=============================================================================
void CModelAnime::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
//�K�w���f���N���X�̈ʒu�ݒ菈��
//=============================================================================
void CModelAnime::SetPosAnime(const D3DXVECTOR3 posAnime)
{
	m_posAnime = posAnime;
}

//=============================================================================
//���f�������擾
//=============================================================================
void CModelAnime::SetModel(CXfile::MODEL model)
{
	m_model = model;
}

//=============================================================================
//�K�w���f���N���X�̈ʒu�擾����
//=============================================================================
D3DXVECTOR3 CModelAnime::GetPos(void) const
{
	return m_pos;
}

//=============================================================================
//�K�w���f���N���X�̃A�j���[�V�����ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CModelAnime::GetPosAnime(void) const
{
	return m_posAnime;
}

//=============================================================================
//�K�w���f���N���X�̌����̐ݒ菈��
//=============================================================================
void CModelAnime::SetRotAnime(const D3DXVECTOR3 rotAnime)
{
	m_rotAnime = rotAnime;
}

//=============================================================================
//�K�w���f���N���X�̌����̎擾����
//=============================================================================
D3DXVECTOR3 CModelAnime::GetRot(void) const
{
	return m_rot;
}

//=============================================================================
//�K�w���f���N���X�̃A�j���[�V���������̎擾
//=============================================================================
D3DXVECTOR3 CModelAnime::GetRotAnime(void) const
{
	return m_rotAnime;
}

//=============================================================================
// ���[���h�}�g���N�X���W
//=============================================================================
D3DXVECTOR3 CModelAnime::GetMtxPos(void)
{
	return D3DXVECTOR3(
		this->GetMtxWorld()._41, this->GetMtxWorld()._42, this->GetMtxWorld()._43);
}

//=============================================================================
//�K�w���f���N���X�̃}�g���N�X���̎擾����
//=============================================================================
D3DXMATRIX CModelAnime::GetMtxWorld(void)
{
	return m_mtxWorld;
}

//=============================================================================
// �Â����W�̏��
//=============================================================================
D3DXMATRIX CModelAnime::GetOldMtxWorld(void)
{
	return m_OldMtxWorld;
}