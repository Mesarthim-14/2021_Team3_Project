#ifndef _NUMBER_2D_H_
#define _NUMBER_2D_H_
//=============================================================================
//
// �i���o�[2D�N���X�w�b�_�[ [number_2d.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene_base.h"

//=============================================================================
// �i���o�[2D�N���X
//=============================================================================
class CNumber2d : public CSceneBase
{
public:
	CNumber2d(PRIORITY Priority = PRIORITY_UI);		// �R���X�g���N�^
	~CNumber2d();									// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
	static CNumber2d * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// �N���G�C�g

	void SetNumber(int nNumber);									// �i���o�[�̐ݒ�
private:
};

#endif