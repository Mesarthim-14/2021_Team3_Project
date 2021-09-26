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
#define FADE_RATE (0.02f)	// ���l�ϓ��W��

//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Fade::CBoss_Fade(PRIORITY Priority = PRIORITY_FADE)
{
	m_FadeMode	= FADE_MODE_NONE;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
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
	m_FadeMode = FADE_MODE_OUT;

	CScene2D::Init(pos, size);
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
	CGame *pGame = CManager::GetGame();

	if (m_FadeMode != FADE_MODE_NONE)
	{
		//�t�F�[�h�C������
		if (m_FadeMode == FADE_MODE_IN)
		{
			//���l�̌��Z
			m_colorFade.a -= FADE_RATE;

			//���l��0.0f��菬�����Ȃ�����t�F�[�h�X�V�I��
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;

				// false��
				pGame->SetbBoss(false);

				// �I��
				Uninit();

				return;
			}
		}

		//�t�F�[�h�A�E�g����
		else if (m_FadeMode == FADE_MODE_OUT)
		{
			//���l�̉��Z
			m_colorFade.a += FADE_RATE;

			//���l��1.0f���傫���Ȃ�����t�F�[�h�C���ֈڍs
			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;

				// �{�X�킩�擾
				bool bBoss = pGame->GetbBoss();

				// true�̏ꍇ
				if (bBoss == true)
				{
					m_FadeMode = FADE_MODE_IN;
				}
			}
		}

		//�����x�̐ݒ�
		SetColor(m_colorFade);
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