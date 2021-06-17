//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : konishi Yuuto
//
//=============================================================================
#include "fade.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FADE_RATE (0.02f)	// ���l�ϓ��W��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFade::CFade()
{
	m_pPolygon = nullptr;
	m_FadeMode = FADE_MODE_NONE;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_modeNext = CManager::MODE_TYPE_TITLE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFade::Init(void)
{
	m_FadeMode = FADE_MODE_OUT;

	if (!m_pPolygon)
	{
		//�|���S���N���X�𐶐�
		m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

		if (m_pPolygon)
		{
			//�F��ݒ�
			m_pPolygon->SetColor(m_colorFade);
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFade::Uninit(void)
{
	if (m_pPolygon != nullptr)
	{
		//�|���S���N���X�̏I�������Ăяo��
		m_pPolygon->Uninit();

		//�������̔j��
		delete m_pPolygon;

		//�������̃N���A
		m_pPolygon = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CFade::Update(void)
{
	if (m_pPolygon != nullptr)
	{
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
					m_FadeMode = FADE_MODE_NONE;
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
					m_FadeMode = FADE_MODE_IN;

					CManager::SetMode(m_modeNext);
				}
			}

			//�����x�̐ݒ�
			m_pPolygon->SetColor(m_colorFade);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CFade::Draw(void)
{
	if (m_pPolygon != nullptr)
	{
		if (m_FadeMode != FADE_MODE_NONE)
		{
			// �|���S���N���X�̕`�揈���Ăяo��
			m_pPolygon->Draw();
		}
	}
}

//=============================================================================
// �t�F�[�h�Ăяo��
//=============================================================================
void CFade::SetFade(CManager::MODE_TYPE mode)
{
	m_FadeMode = FADE_MODE_OUT;
	m_modeNext = mode;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//������ʁi���߁j
}

//=============================================================================
// �t�F�[�h���
//=============================================================================
CFade::FADE_MODE CFade::GetFade(void)
{
	return m_FadeMode;
}