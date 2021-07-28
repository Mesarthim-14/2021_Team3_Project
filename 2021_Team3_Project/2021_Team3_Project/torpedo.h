#ifndef _TORPEDO_H_
#define _TORPEDO_H_
//=============================================================================
// ����[torpedo.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"

//=============================================================================
// �e�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CTorpedo : public CModel
{
public:
	CTorpedo(PRIORITY Priority = PRIORITY_CHARACTER);			// �R���X�g���N�^
	~CTorpedo();												// �f�X�g���N�^
	static CTorpedo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
private:
	void Move(void);											// �ړ�
	void Collision(void);										// �����蔻��

	float m_fAngle;		// �p�x
};
#endif