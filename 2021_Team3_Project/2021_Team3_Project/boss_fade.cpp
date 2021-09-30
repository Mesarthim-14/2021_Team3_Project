//=============================================================================
// �{�X�t�F�[�h���� [boss_fade.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "boss_fade.h"

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define FADE_RATE	(0.01f)												// ���l�ϓ��W��
#define POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,0.0f))	// �ʒu
#define SIZE		(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT,0.0f))			// �T�C�Y
#define COL			(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f))						// �F
#define ��MIN		(0.0f)													// ���l�̍ŏ�
#define ��MAX		(1.0f)													// ���l�̍ő�
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Fade::CBoss_Fade(PRIORITY Priority) : CScene2D(Priority)
{
	m_FadeMode	= FADE_MODE_NONE;
}

//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Fade::~CBoss_Fade()
{
}
//=============================================================================
// ����������
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Fade * CBoss_Fade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CBoss_Fade�̃|�C���^
	CBoss_Fade *pBoss_Fade = nullptr;

	// nullcheck
	if (pBoss_Fade == nullptr)
	{
		// �������m��
		pBoss_Fade = new CBoss_Fade;

		// !nullcheck
		if (pBoss_Fade != nullptr)
		{
			// ����������
			pBoss_Fade->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pBoss_Fade;
}

//=============================================================================
// ����������
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBoss_Fade::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �t�F�[�h�A�E�g���
	m_FadeMode = FADE_MODE_IN;

	CScene2D::Init(POS, SIZE);

	// �F�ݒ�
	SetCol(COL);

	return S_OK;
}

//=============================================================================
// �I������
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Fade::Uninit(void)
{
	// �I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Fade::Update(void)
{
	// �X�V����
	CScene2D::Update();

	// �Q�[���擾
	CGame *pGame = (CGame*)CManager::GetModePtr();

	// �F�擾
	D3DXCOLOR col = GetColor();

	if (m_FadeMode != FADE_MODE_NONE)
	{
		//�t�F�[�h�C������
		if (m_FadeMode == FADE_MODE_OUT)
		{
			//���l�̌��Z
			col.a -= FADE_RATE;

			//���l��0.0f��菬�����Ȃ�����t�F�[�h�X�V�I��
			if (col.a <= ��MIN)
			{
				// 0.0f��
				col.a = ��MIN;

				// �{�X��̔���ݒ�
				pGame->SetbBossTransition(false);

				// �{�X��̔���ݒ�
				pGame->SetbBoss(true);

				// �I��
				Uninit();

				return;
			}
		}

		//�t�F�[�h�A�E�g����
		else if (m_FadeMode == FADE_MODE_IN)
		{
			//���l�̉��Z
			col.a += FADE_RATE;

			//���l��1.0f���傫���Ȃ�����t�F�[�h�C���ֈڍs
			if (col.a >= ��MAX)
			{
				// �{�X��̔���ݒ�
				pGame->CreateBossMap();

				// 1.0f��
				col.a = ��MAX;

				// OUT��
				m_FadeMode = FADE_MODE_OUT;
			}
		}
		// �����x�̐ݒ�
		SetCol(col);
	}
}

//=============================================================================
// �`�揈��
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Fade::Draw(void)
{
	// �`�揈��
	CScene2D::Draw();
}