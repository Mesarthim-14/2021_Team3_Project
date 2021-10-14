#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
//=====================================================
//
// ���b�V���t�B�[���h�̃N���X [meshfield.h]
// Author : Konishi Yuuto
//
//=====================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "mesh_3d.h"

//=============================================================================
// ���b�V���t�B�[���h�N���X
//=============================================================================
class CMeshField : public CMesh3d
{
public:
	CMeshField(PRIORITY = PRIORITY_0);	// �R���X�g���N�^
	~CMeshField();						// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
	void CreateVerterx(void);								// ���_�̐���
	void SetInfo(D3DXVECTOR3 size, INT_VERTEX_2D PieceNum);	// ���̐ݒ�

	static CMeshField*Create(void);		// ���b�V���t�B�[���h
private:
};

#endif