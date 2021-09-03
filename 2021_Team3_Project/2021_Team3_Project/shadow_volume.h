#ifndef _SHADOW_VOLUME_H_
#define _SHADOW_VOLUME_H_
//=============================================================================
//
// �V���h�E�{�����[���N���X�w�b�_�[ [shadow_volume.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "main.h"

//=========================================================================
// �N���X��`
//=========================================================================
class CShadowVolume
{
public:
	// ���b�V�����̍\����
	struct MESHVERTEX
	{
		D3DXVECTOR3 pos, nor;
		FLOAT tu, tv;
	};

	CShadowVolume();		// �R���X�g���N�^
	~CShadowVolume();		// �f�X�g���N�^

	static CShadowVolume *Create(LPD3DXMESH pSrcMesh);					// �C���X�^���X����
	HRESULT Init(LPD3DXMESH pSrcMesh);									// ��������������
	void Uninit(void);													// �I������
	void Draw(void);													// �`�揈��
	void AddEdge(WORD* pEdges, DWORD& dwNumEdges, WORD v0, WORD v1);	// �G�b�W�̐ݒ�
	HRESULT CreateShadow(D3DXVECTOR3 rot, D3DXVECTOR3 ShipRot);			// �e�̐���
	HRESULT CreateShadow(D3DXVECTOR3 ShipRot);							// �e�̐���
	void CreateVolume(vector<D3DXVECTOR3> pos, D3DXVECTOR3 Lpos);		// �V���h�E�{�����[��
private:
	D3DXVECTOR3 m_LightPos;				// ���C�g�̍��W
	DWORD       m_dwNumVertices;		// ���_��
	D3DXVECTOR3 m_pVertice[32000];		// ���_�̔z��
	LPD3DXMESH m_pSrcMesh;				// ���b�V�����
	MESHVERTEX *m_MeshVertices;			// ���b�V���̏��
	WORD *m_pIndices;					// �C���f�b�N�X��
	DWORD m_dwNumFaces;					// ���b�V���̖ʂ̐�
	WORD *m_pEdges;						// �G�b�W�̐�
};
#endif