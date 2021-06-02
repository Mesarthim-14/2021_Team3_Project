#ifndef _POLYGON_H_
#define _POLYGON_H_
//=============================================================================
//
// �|���S�������N���X���� [polygon.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �|���S���N���X
//=============================================================================
class CPolygon
{
public:
	CPolygon();			// �R���X�g���N�^
	~CPolygon();		// �f�X�g���N�^

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
	void SetColor(const D3DXCOLOR color);							// �F�̐ݒ�

	static CPolygon *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);		// �C���X�^���X����

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_Size;						// �|���S���̃T�C�Y
	D3DXVECTOR3 m_pos;						// ���C�t�̈ʒu
};
#endif 