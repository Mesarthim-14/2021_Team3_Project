#ifndef _CHARACTER_BOX_H_
#define _CHARACTER_BOX_H_
//=============================================================================
// �� [character_box.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "character.h"
#include "model.h"

//=============================================================================
// ���N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CCharacter_Box: public CModel
{
public:
	CCharacter_Box(PRIORITY Priority = PRIORITY_CHARACTER);										// �R���X�g���N�^
	~CCharacter_Box();																			// �f�X�g���N�^
	static CCharacter_Box *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CCharacter *pCharacter);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);												// ����������
	void Uninit(void);																			// �I������
	void Update(void);																			// �X�V����
	void Draw(void);																			// �`�揈��
private:
	CCharacter *m_pCharacter;		// CCharacter�̃|�C���^
};
#endif