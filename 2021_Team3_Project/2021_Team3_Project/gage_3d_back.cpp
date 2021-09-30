//=============================================================================
// ���C�t�Q�[�W�̔w�i [gage_3d_back.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "gage_3d_back.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define POS		(D3DXVECTOR3(pos.x,pos.y + size.y,pos.z))		// �ʒu
#define COL		(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))				// �F
#define SIZE	(D3DXVECTOR3(810.0f,40.0f,0.0f))				// �w�i�T�C�Y
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CGage_3D_Back::CGage_3D_Back(PRIORITY Priority) : CBillboard(Priority)
{
	m_pEnemy = nullptr;
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CGage_3D_Back::~CGage_3D_Back()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CGage_3D_Back * CGage_3D_Back::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy *pEnemy)
{
	// CGage_3D_Back�̃|�C���^
	CGage_3D_Back *pGage_3D_Back = nullptr;

	// nullcheck
	if (pGage_3D_Back == nullptr)
	{
		// �������m��
		pGage_3D_Back = new CGage_3D_Back;

		// !nullcheck
		if (pGage_3D_Back != nullptr)
		{
			// ���
			pGage_3D_Back->m_pEnemy = pEnemy;

			// ����������
			pGage_3D_Back->Init(pos, SIZE);
		}
	}
	// �|�C���^��Ԃ�
	return pGage_3D_Back;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CGage_3D_Back::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CBillboard::Init(pos, size);

	// �����ݒ�
	SetRot(ZeroVector3);

	// �F�ݒ�
	SetColor(COL);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_3D_Back::Uninit(void)
{
	// !nullcheck
	if (m_pEnemy != nullptr)
	{
		// nullptr��
		m_pEnemy = nullptr;
	}

	// �I������
	CBillboard::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_3D_Back::Update(void)
{
	// �X�V����
	CBillboard::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = m_pEnemy->GetPos();

	// �T�C�Y�擾
	D3DXVECTOR3 size = m_pEnemy->GetSize();

	// �ʒu�ݒ�
	SetPos(POS);

	// ���S��Ԃ̏ꍇ
	if (m_pEnemy->GetState() == CEnemy::STATE_DEAD)
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
void CGage_3D_Back::Draw(void)
{
	// �`�揈��
	CBillboard::Draw();
}