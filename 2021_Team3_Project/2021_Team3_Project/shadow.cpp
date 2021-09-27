//=============================================================================CShadow
//
// �V���h�E�N���X [shadow.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "game.h"
#include "light.h"
#include "shadow_volume.h"
#include "shadow_polygon.h"

//=============================================================================
// static������
//=============================================================================
CShadowPolygon *CShadow::m_pPolygon = nullptr;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShadow::CShadow()
{
	m_pShadowVolume = nullptr;
	D3DXMatrixIdentity(&m_ModelMtxWorld);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShadow::~CShadow()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CShadow * CShadow::Create(LPD3DXMESH pSrcMesh)
{
	// �������m��
	CShadow *pShadow = new CShadow;

	// !nullcheck
	if (pShadow)
	{
		// ����������
		pShadow->Init(pSrcMesh);
	}

	return pShadow;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CShadow::Init(LPD3DXMESH pSrcMesh)
{
	// nullcheck
	if (!m_pShadowVolume)
	{
		// �e�̐���
		m_pShadowVolume = CShadowVolume::Create(pSrcMesh);
	}

	// nullcheck
	if (!m_pPolygon)
	{
		m_pPolygon = CShadowPolygon::Create();
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CShadow::Uninit(void)
{
	if (m_pShadowVolume)
	{
		// �V���h�E�{�����[���I������
		m_pShadowVolume->Uninit();
		delete m_pShadowVolume;
		m_pShadowVolume = nullptr;
	}
}

//=============================================================================
// �e�̕`�揈��
//=============================================================================
void CShadow::VolumeDraw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

	// �����_���[�|�C���^�擾
	CRenderer *pRenderer = CManager::GetRenderer();

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_ModelMtxWorld);

	// �V���h�E�̕`��
	if (m_pShadowVolume)
	{
		// �X�e���V���ݒ�
		pRenderer->SetStateStencil();

		// �V���h�E�{�����[���̕`��
		m_pShadowVolume->Draw();

		// ��Ԃ����ɖ߂�
		pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
	}
}

//=============================================================================
// �e�̐�������
//=============================================================================
void CShadow::CreateShadow(D3DXVECTOR3 rot, D3DXVECTOR3 ShipRot, D3DXMATRIX ModelMtxWorld)
{
	// �e�̐���
	if (m_pShadowVolume)
	{
		m_pShadowVolume->CreateShadow(rot, ShipRot);
	}

	// ���[���h���W���󂯎��
	m_ModelMtxWorld = ModelMtxWorld;
}

//=============================================================================
// �e�̐�������
//=============================================================================
void CShadow::CreateShadow(D3DXVECTOR3 rot, D3DXMATRIX ModelMtxWorld)
{
	// �e�̐���
	if (m_pShadowVolume)
	{
		m_pShadowVolume->CreateShadow(rot);
	}

	// ���[���h���W���󂯎��
	m_ModelMtxWorld = ModelMtxWorld;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CShadow::PolygonUninit(void)
{
	if (m_pPolygon)
	{
		// �|���S���I������
		m_pPolygon->Uninit();
		m_pPolygon = nullptr;
	}
}