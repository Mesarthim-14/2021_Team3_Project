//=============================================================================
// �{�X���݂��͈� [byte_attack_range.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _BYTE_ATTACK_RANGE_H_
#define _BYTE_ATTACK_RANGE_H_
//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "scene3d.h"
//=============================================================================
// �}�b�v�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CByte_Attack_Range : public CScene3D
{
public:
	CByte_Attack_Range(PRIORITY Priority = PRIORITY_UI);						// �R���X�g���N�^
	~CByte_Attack_Range();														// �f�X�g���N�^
	static CByte_Attack_Range *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);							// ����������
	void Uninit(void);															// �I������
	void Update(void);															// �X�V����
	void Draw(void);															// �`�揈��

private:
	void Collision(void);	// �����蔻��
	int m_nCount;			// �J�E���g
	bool m_bAddColor;		// �F�����Z���邩
};
#endif