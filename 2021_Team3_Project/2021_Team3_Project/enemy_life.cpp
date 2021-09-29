//=============================================================================
// �G���C�t�Q�[�W [enemy_life.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "enemy_life.h"
#include "gage_3d_back.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define POS			(D3DXVECTOR3(pos.x,pos.y + size.y,pos.z))		// �ʒu
#define SIZE		(D3DXVECTOR3(800.0f,30.0f,0.0f))				// �T�C�Y
#define COL			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))				// �F
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Life::CEnemy_Life(PRIORITY nPriority) : CGage_3D(nPriority)
{
	m_pEnemy		= nullptr;
}
//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Life::~CEnemy_Life()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Life * CEnemy_Life::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy * pEnemy)
{
	// CEnemy_Life�̃|�C���^
	CEnemy_Life * pEnemy_Life = nullptr;

	// nullcheck
	if (pEnemy_Life == nullptr)
	{
		// �������m��
		pEnemy_Life = new CEnemy_Life;

		// !nullcheck
		if (pEnemy_Life != nullptr)
		{
			// ���
			pEnemy_Life->m_pEnemy = pEnemy;

			// ����������
			pEnemy_Life->Init(pos, SIZE);

			// �w�i����
			CGage_3D_Back::Create(pos, size, pEnemy);
		}
	}
	// �|�C���^��Ԃ�
	return pEnemy_Life;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CEnemy_Life::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ���C�t�擾
	int nLife = m_pEnemy->GetLife();

	// ���C�t�̍ő�l�ݒ�
	SetMaxGageNum(nLife);

	// ����������
	CGage_3D::Init(pos, size);

	// ���C�t�̒l�ݒ�
	SetGageNum(nLife);

	// �F�ݒ�
	SetColor(COL);

	// �A���t�@�u�����h
	SetAlpha(true);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Life::Uninit(void)
{
	// !nullcheck
	if (m_pEnemy != nullptr)
	{
		// nullptr��
		m_pEnemy = nullptr;
	}

	// �I������
	CGage_3D::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Life::Update(void)
{
	// �X�V����
	CGage_3D::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = m_pEnemy->GetPos();

	// �T�C�Y�擾
	D3DXVECTOR3 size = m_pEnemy->GetSize();

	// �ʒu�ݒ�
	SetPosition(POS);

	// �q�b�g����擾
	bool bHit = m_pEnemy->GetHit();
	// true�̏ꍇ
	if (bHit == true)
	{
		// ���C�t�擾
		int nLife = m_pEnemy->GetLife();

		// �Q�[�W�̒l�ݒ�
		SetGageNum(nLife);

		// �q�b�g�ݒ�
		m_pEnemy->SetHit(false);
	}
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
void CEnemy_Life::Draw(void)
{
	// �X�V����
	CGage_3D::Draw();
}