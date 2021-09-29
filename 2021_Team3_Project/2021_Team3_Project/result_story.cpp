//=============================================================================CResultStory
//
// ���U���g�X�g�[���[�N���X [result_story.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "game.h"
#include "light.h"
#include "result_story.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define RESULT_STORY_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT*1.5f, 0.0f))
#define RESULT_STORY_SIZE		(D3DXVECTOR3(SCREEN_WIDTH*0.7f, SCREEN_HEIGHT, 0.0f))
#define SCROLL_SPEED			(1.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResultStory::CResultStory(PRIORITY Priority) : CScene2D(Priority)
{
	m_bEnd = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResultStory::~CResultStory()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CResultStory * CResultStory::Create(void)
{
	// �������m��
	CResultStory *pPolygon = new CResultStory(PRIORITY_UI);

	// !nullcheck
	if (pPolygon)
	{
		// ����������
		pPolygon->Init();

		return pPolygon;
	}

	return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResultStory::Init(void)
{
	// ����������
	CScene2D::Init(RESULT_STORY_POS, RESULT_STORY_SIZE);

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CResultStory::Update(void)
{
	GetPos().y -= SCROLL_SPEED;

	// ���_�̍X�V
	SetVertex();

	if (!m_bEnd)
	{
		if (0.0f >= GetPos().y + SCREEN_HEIGHT/2)
		{
			m_bEnd = true;
		}
	}
}

//=============================================================================
// �e�̕`��
//=============================================================================
void CResultStory::Draw(void)
{
	// �����_���[�|�C���^�擾
	CRenderer *pRenderer = CManager::GetRenderer();

	// �X�e���V���e�X�g
	pRenderer->SetStencilTest();

	// �|���S���̕`��
	CScene2D::Draw();

	// �X�e���V�����Z�b�g
	pRenderer->ReSetStateStencil();
}