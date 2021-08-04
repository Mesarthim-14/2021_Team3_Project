#ifndef _MODEL_BOX_H_
#define _MODEL_BOX_H_
//=============================================================================
// �� [character_box.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//============================================================================="
#include "model.h"

//=============================================================================
// ���N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CModel_Box : public CModel
{
public:
	CModel_Box(PRIORITY Priority = PRIORITY_CHARACTER);									// �R���X�g���N�^
	~CModel_Box();																		// �f�X�g���N�^
	static CModel_Box *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel *pModel);		// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);										// ����������
	void Uninit(void);																	// �I������
	void Update(void);																	// �X�V����
	void Draw(void);																	// �`�揈��
private:
	CModel *m_pModel;																// CCharacter�̃|�C���^
};
#endif