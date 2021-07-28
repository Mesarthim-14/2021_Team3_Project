#ifndef _ROCK_H_
#define _ROCK_H_
//=============================================================================
// �� [rock.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"

//=============================================================================
// ��N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CRock : public CModel
{
public:
	CRock(PRIORITY Priority = PRIORITY_OBSTACLE);			// �R���X�g���N�^
	~CRock();												// �f�X�g���N�^
	static CRock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
private:
};
#endif