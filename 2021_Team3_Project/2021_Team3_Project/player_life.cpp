//=============================================================================
// �v���C���[�̃��C�t [player_lufe.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "game.h"
#include "player.h"
#include "player_life.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define MIN_LIFE	(0)								// ���C�t�̍ŏ�
#define MUT_2		(2.0f)							// �~2		
#define LENGTH		(70.0f)							// ���a
#define ROT			(D3DXToRadian(-3.6f * nCnt))	// ����
#define SIZE		(D3DXVECTOR3(20.0f,20.0f,0.0f))	// �T�C�Y
#define RED			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))// �ԐF
#define BLACK		(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))// ���F
#define ANGLE_90	(D3DXToRadian(90.0f))			// �p�x90
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Life::CPlayer_Life(PRIORITY Priority) : CScene(Priority)
{
	memset(m_apScene2d, 0, sizeof(m_apScene2d));
}
//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Life::~CPlayer_Life()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Life * CPlayer_Life::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPlayer_Life�̃|�C���^
	CPlayer_Life *pPlayer_Life = nullptr;

	// nullcheck
	if (pPlayer_Life == nullptr)
	{
		// �������m��
		pPlayer_Life = new CPlayer_Life(PRIORITY_UI);

		// !nullcheck
		if (pPlayer_Life != nullptr)
		{
			// �ʒu
			pPlayer_Life->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pPlayer_Life;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CPlayer_Life::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �ő吔���J��Ԃ�
	for (int nCnt = MIN_LIFE; nCnt < MAX_LIFE; nCnt++)
	{
		// �ʓx
		float fRadian = (float)nCnt / MAX_LIFE;

		// �ʓx�v�Z
		fRadian = fRadian * D3DX_PI * MUT_2;

		// �ʒu���W
		D3DXVECTOR3 Life_pos = ZeroVector3;

		// ���W�����߂�
		Life_pos.x = pos.x - cosf(fRadian - ANGLE_90) * LENGTH;
		Life_pos.y = pos.y + sinf(fRadian - ANGLE_90) * LENGTH;

		// ����
		m_apScene2d[nCnt] = CScene2D::Create(Life_pos, SIZE);

		// �����̐ݒ�
		m_apScene2d[nCnt]->SetRotation(ROT);

		// �ʒu
		m_apScene2d[nCnt]->SetCol(RED);

	}
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Life::Uninit(void)
{
	// �ő吔�J��Ԃ�
	for (int nCnt = MIN_LIFE; nCnt < MAX_LIFE; nCnt++)
	{
		// !nullcheck
		if (m_apScene2d[nCnt] != nullptr)
		{
			// �I��
			m_apScene2d[nCnt]->Uninit();

			// nullptr��
			m_apScene2d[nCnt] = nullptr;
		}
	}

	// �j��
	Release();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Life::Update(void)
{
	// CPlayer�̃|�C���^
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// �_���[�W��H����Ă�����
		if (pPlayer->GetHitFlag() == true)
		{
			// ���C�t�擾
			int nLife = pPlayer->GetLife();

			// �ő吔���J��Ԃ�
			for (int nCnt = MIN_LIFE; nCnt < MAX_LIFE; nCnt++)
			{
				// nLife�ȉ��̏ꍇ
				if (nCnt <= nLife)
				{
					// �ʒu
					m_apScene2d[nCnt]->SetCol(RED);
				}
				// nLife���傫���ꍇ
				if (nCnt > nLife)
				{
					// �ʒu
					m_apScene2d[nCnt]->SetCol(BLACK);
				}
			}

			// �v���C���[�̃t���O�ύX
			pPlayer->SetHitFlag(false);
		}
	}
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Life::Draw(void)
{
}