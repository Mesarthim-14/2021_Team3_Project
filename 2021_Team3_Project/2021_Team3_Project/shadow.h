#ifndef _SHADOW_H_
#define _SHADOW_H_
//=============================================================================
//
// �V���h�E�N���X�w�b�_�[ [shadow.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "scene.h"

//=========================================================================
// �O���錾
//=========================================================================
class CShadowVolume;
class CShadowPolygon;

//=========================================================================
// �N���X��`
//=========================================================================
class CShadow
{
public:
	CShadow();		// �R���X�g���N�^
	~CShadow();		// �f�X�g���N�^

	static CShadow *Create(LPD3DXMESH pSrcMesh);										// �C���X�^���X����
	HRESULT Init(LPD3DXMESH pSrcMesh);													// ��������������
	void Uninit(void);																	// �I������
	void VolumeDraw(void);																// �e�`�揈��
	void CreateShadow(D3DXVECTOR3 rot, D3DXVECTOR3 ShipRot, D3DXMATRIX ModelMtxWorld);	// �e�̐���
	void CreateShadow(D3DXVECTOR3 rot, D3DXMATRIX ModelMtxWorld);						// �e�̐���
	static void PolygonUninit(void);													// �`�揈��

private:
	CShadowVolume *m_pShadowVolume;		// �V���h�E�{�����[���̃|�C���^
	D3DXMATRIX m_ModelMtxWorld;			// ���f���̃��[���h���W�擾
	static CShadowPolygon *m_pPolygon;	// �|���S���̃|�C���^
};
#endif