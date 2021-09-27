//=============================================================================
// �{�X���C�t�Q�[�W [boss_life.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "boss_life_back.h"
#include "boss_life.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define POS			(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.05f,0.0f))	// �T�C�Y
#define SIZE		(D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.025f,0.0f))	// �T�C�Y
#define COL			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))								// �F
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Life::CBoss_Life(PRIORITY nPriority) : CGage_2D(nPriority)
{
	m_pEnemy = nullptr;
}
//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Life::~CBoss_Life()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Life * CBoss_Life::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy * pEnemy)
{
	// CBoss_Life�̃|�C���^
	CBoss_Life * pBoss_Life = nullptr;

	// nullcheck
	if (pBoss_Life == nullptr)
	{
		// �������m��
		pBoss_Life = new CBoss_Life;

		// !nullcheck
		if (pBoss_Life != nullptr)
		{
			// ���
			pBoss_Life->m_pEnemy = pEnemy;

			// ����������
			pBoss_Life->Init(POS, SIZE);
		}
	}
	// �|�C���^��Ԃ�
	return pBoss_Life;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBoss_Life::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ���C�t�擾
	int nLife = m_pEnemy->GetLife();

	// ���C�t�̍ő�l�ݒ�
	SetMaxGageNum(nLife);

	// ����������
	CGage_2D::Init(pos, size);

	// ���C�t�̒l�ݒ�
	SetGageNum(nLife);

	// �F�ݒ�
	SetColor(COL);

	// �ʒu�ݒ�
	SetPosition(pos);

	// ���C�t�w�i����
	CBoss_Life_Back::Create(pos, SIZE, m_pEnemy);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Life::Uninit(void)
{
	// !nullcheck
	if (m_pEnemy != nullptr)
	{
		// nullptr��
		m_pEnemy = nullptr;
	}

	// �I������
	CGage_2D::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Life::Update(void)
{
	// �X�V����
	CGage_2D::Update();

	// �q�b�g����擾
	bool bHit = m_pEnemy->GetHit();

	// true�̏ꍇ
	if (bHit == true)
	{
		// ���C�t�擾
		int nLife = m_pEnemy->GetLife();

		// �Q�[�W�̒l�ݒ�
		SetGageNum(nLife);

		// ���C�t�擾
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
void CBoss_Life::Draw(void)
{
	// �X�V����
	CGage_2D::Draw();
}