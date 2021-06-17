//=============================================================================
//
// �V���h�E�{�����[���N���X [shadow_volume.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "shadow_volume.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "game.h"
#include "light.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TRIANGLE	(3)		// �O�p�`

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShadowVolume::CShadowVolume()
{
	m_LightPos = ZeroVector3;
	m_dwNumVertices = 0;
	m_pSrcMesh = nullptr;
	m_pSrcMesh = nullptr;
	m_MeshVertices = nullptr;
	m_pIndices = nullptr;
	m_dwNumFaces = 0;
	m_pEdges = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShadowVolume::~CShadowVolume()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CShadowVolume * CShadowVolume::Create(LPD3DXMESH pSrcMesh)
{
	// �������m��
	CShadowVolume *pShadowVolume = new CShadowVolume;

	// !nullcheck
	if (pShadowVolume)
	{
		// ����������
		pShadowVolume->Init(pSrcMesh);
	}

	return pShadowVolume;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CShadowVolume::Init(LPD3DXMESH pSrcMesh)
{
	// ���b�V�����
	m_pSrcMesh = pSrcMesh;

	m_dwNumFaces = m_pSrcMesh->GetNumFaces();
	m_LightPos = CManager::GetGame()->GetLight()->GetPos();					// ���C�g�̍��W�ݒ�

	// �G�b�W�̃������m��
	m_pEdges = new WORD[m_dwNumFaces * 6];

	// �e
	CreateShadow(ZeroVector3);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CShadowVolume::Uninit(void)
{
	// nullcheck
	if (m_pEdges)
	{
		delete[] m_pEdges;
		m_pEdges = nullptr;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CShadowVolume::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

	pDevice->SetFVF(D3DFVF_XYZ);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_dwNumVertices / TRIANGLE,
		m_pVertice, sizeof(D3DXVECTOR3));
}

//=============================================================================
// �G�b�W�̏d�Ȃ���J�E���g
//=============================================================================
void CShadowVolume::AddEdge(WORD * pEdges, DWORD & dwNumEdges, WORD v0, WORD v1)
{
	// �G�b�W�̏d�Ȃ�𒲂ׂ�
	for (DWORD i = 0; i < dwNumEdges; i++)
	{
		if ((pEdges[2 * i + 0] == v0 && pEdges[2 * i + 1] == v1) ||
			(pEdges[2 * i + 0] == v1 && pEdges[2 * i + 1] == v0))
		{
			if (dwNumEdges > 1)
			{
				pEdges[2 * i + 0] = pEdges[2 * (dwNumEdges - 1) + 0];
				pEdges[2 * i + 1] = pEdges[2 * (dwNumEdges - 1) + 1];
			}
			dwNumEdges--;
			return;
		}
	}

	pEdges[2 * dwNumEdges + 0] = v0;
	pEdges[2 * dwNumEdges + 1] = v1;
	dwNumEdges++;
}

//=============================================================================
// �e��
//=============================================================================
HRESULT CShadowVolume::CreateShadow(D3DXVECTOR3 rot)
{
	// nullcheck
	if (m_pEdges == nullptr)
	{
		m_pSrcMesh->UnlockVertexBuffer();
		m_pSrcMesh->UnlockIndexBuffer();
		return E_OUTOFMEMORY;
	}

	// �o�b�t�@�̃��b�N
	m_pSrcMesh->LockVertexBuffer(0L, (LPVOID*)&m_MeshVertices);
	m_pSrcMesh->LockIndexBuffer(0L, (LPVOID*)&m_pIndices);

	DWORD dwNumEdges = 0;	// �G�b�W�̃J�E���g
	m_dwNumVertices = 0;	// ���_�̐����Z�b�g

	// �v���C���[�̌����𔽉f
	D3DXVECTOR3 posL = D3DXVECTOR3(
		cosf(rot.y)*m_LightPos.x , m_LightPos.y, sinf(rot.y)*m_LightPos.z );

	// �e�ʂ̐ݒ�
	for (DWORD nCount = 0; nCount < m_dwNumFaces; nCount++)
	{
		WORD wFace0 = m_pIndices[TRIANGLE * nCount + 0];
		WORD wFace1 = m_pIndices[TRIANGLE * nCount + 1];
		WORD wFace2 = m_pIndices[TRIANGLE * nCount + 2];

		// ���_���W��
		D3DXVECTOR3 v0 = m_MeshVertices[wFace0].pos;
		D3DXVECTOR3 v1 = m_MeshVertices[wFace1].pos;
		D3DXVECTOR3 v2 = m_MeshVertices[wFace2].pos;

		// �O�ςŖ@���̌��������߂�
		D3DXVECTOR3 vCross1(v2 - v1);
		D3DXVECTOR3 vCross2(v1 - v0);
		D3DXVECTOR3 vNormal;
		D3DXVec3Cross(&vNormal, &vCross1, &vCross2);

		// �G�b�W���d�Ȃ��Ă�����
		if (D3DXVec3Dot(&vNormal, &posL) >= 0.0f)
		{
			AddEdge(m_pEdges, dwNumEdges, wFace0, wFace1);
			AddEdge(m_pEdges, dwNumEdges, wFace1, wFace2);
			AddEdge(m_pEdges, dwNumEdges, wFace2, wFace0);
		}
	}

	// ���W�̐ݒ�
	for (DWORD nCount = 0; nCount < dwNumEdges; nCount++)
	{
		D3DXVECTOR3 v1 = m_MeshVertices[m_pEdges[2 * nCount + 0]].pos;
		D3DXVECTOR3 v2 = m_MeshVertices[m_pEdges[2 * nCount + 1]].pos;
		D3DXVECTOR3 v3 = v1 - posL * 1;
		D3DXVECTOR3 v4 = v2 - posL * 1;

		// �O�p�`�̒��_��ݒ�
		m_pVertice[m_dwNumVertices++] = v1;
		m_pVertice[m_dwNumVertices++] = v2;
		m_pVertice[m_dwNumVertices++] = v3;

		m_pVertice[m_dwNumVertices++] = v2;
		m_pVertice[m_dwNumVertices++] = v4;
		m_pVertice[m_dwNumVertices++] = v3;
	}

	// �o�b�t�@�̃A�����b�N
	m_pSrcMesh->UnlockVertexBuffer();
	m_pSrcMesh->UnlockIndexBuffer();

	return S_OK;
}