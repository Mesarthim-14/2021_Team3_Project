//=============================================================================CShadowPolygon
//
// �V���h�E�|���S���N���X [shadow_polygon.cpp]
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
#include "shadow_polygon.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShadowPolygon::CShadowPolygon(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShadowPolygon::~CShadowPolygon()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CShadowPolygon * CShadowPolygon::Create(void)
{
	// �������m��
	CShadowPolygon *pPolygon = new CShadowPolygon(PRIORITY_SHADOW);

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
HRESULT CShadowPolygon::Init(void)
{
	// ����������
	CScene2D::Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	// �F�̐ݒ�
	SetCol(D3DCOLOR_RGBA(0, 0, 0, 0x7f));

	return S_OK;
}

//=============================================================================
// �e�̕`��
//=============================================================================
void CShadowPolygon::Draw(void)
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