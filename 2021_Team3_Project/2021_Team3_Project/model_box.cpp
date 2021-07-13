//=============================================================================
// �e [bullet.cpp]
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
#include "modelanime.h"
#include "model_box.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CModel_Box::CModel_Box(PRIORITY Priority)
{
	m_pModel = nullptr;
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CModel_Box::~CModel_Box()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CModel_Box * CModel_Box::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel *pModel)
{
	// CModel_Box�̃|�C���^
	CModel_Box *pBox = nullptr;

	// nullcheck
	if (pBox == nullptr)
	{
		// �������m��
		pBox = new CModel_Box;

		// !nullcheck
		if (pBox != nullptr)
		{
			// �|�C���^���
			pBox->m_pModel = pModel;

			// ����������
			pBox->Init(pos, ZeroVector3);
		}
	}
	// �|�C���^��Ԃ�
	return pBox;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CModel_Box::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_BOX);

		// ���f���̏���n��
		BindModel(model);
	}

	// �T�C�Y�擾
	D3DXVECTOR3 size = m_pModel->GetSize();

	// �g�嗦�̐ݒ�
	SetScale(size);

	// ����������
	CModel::Init(pos, rot);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CModel_Box::Uninit(void)
{
	// �I������
	CModel::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CModel_Box::Update(void)
{
	// �X�V����
	CModel::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = m_pModel->GetPos();

	// ���f���̏�Ԏ擾
	int nState = m_pModel->GetState();

	// �ʒu�ݒ�
	SetPos(pos);

	// ���S��Ԃ̏ꍇ
	if (nState == CModel::STATE_DEAD)
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
void CModel_Box::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}