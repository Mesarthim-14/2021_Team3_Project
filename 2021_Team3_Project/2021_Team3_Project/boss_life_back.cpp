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
#include "boss_life_back.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COL		(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))// �F
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Life_Back::CBoss_Life_Back(PRIORITY Priority) : CScene2D(Priority)
{
	m_pEnemy = nullptr;
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Life_Back::~CBoss_Life_Back()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Life_Back * CBoss_Life_Back::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy *pEnemy)
{
	// CBoss_Life_Back�̃|�C���^
	CBoss_Life_Back *pBoss_Life_Back = nullptr;

	// nullcheck
	if (pBoss_Life_Back == nullptr)
	{
		// �������m��
		pBoss_Life_Back = new CBoss_Life_Back;

		// !nullcheck
		if (pBoss_Life_Back != nullptr)
		{
			// ���
			pBoss_Life_Back->m_pEnemy = pEnemy;

			// ����������
			pBoss_Life_Back->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pBoss_Life_Back;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBoss_Life_Back::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CScene2D::Init(pos, size);

	// �F�ݒ�
	SetCol(COL);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Life_Back::Uninit(void)
{
	// !nullcheck
	if (m_pEnemy != nullptr)
	{
		// nullptr��
		m_pEnemy = nullptr;
	}

	// �I������
	CScene2D::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Life_Back::Update(void)
{
	// �X�V����
	CScene2D::Update();

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
void CBoss_Life_Back::Draw(void)
{
	// �`�揈��
	CScene2D::Draw();
}