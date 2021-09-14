#ifndef _BULLET_H_
#define _BULLET_H_
//=============================================================================
// �e [bullet.h]
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
class CBullet : public CModel
{
public:
	CBullet(PRIORITY Priority = PRIORITY_CHARACTER);			// �R���X�g���N�^
	~CBullet();													// �f�X�g���N�^
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
	void CreateSplash(void);									//�����Ԃ������֐�

private:
	void Death(void);											// ���S�����֐�
};
#endif