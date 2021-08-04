//=============================================================================
// �{�X���݂��G�t�F�N�g [byte_effect.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _BYTE_EFFECT_H_
#define _BYTE_EFFECT_H_
//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "billboard.h"
//=============================================================================
// �}�b�v�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CByte_Effect : public CBillboard
{
public:
	CByte_Effect(PRIORITY Priority = PRIORITY_3D_UI);				// �R���X�g���N�^
	~CByte_Effect();												// �f�X�g���N�^
	static CByte_Effect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif