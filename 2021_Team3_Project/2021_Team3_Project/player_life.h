//=============================================================================
// �v���C���[�̃��C�t [player_lufe.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _PLAYER_LIFE_H_
#define _PLAYER_LIFE_H_
//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "scene2d.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define MAX_LIFE	(100)
//=============================================================================
// �}�b�v�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CPlayer_Life : public CScene
{
public:
	CPlayer_Life(PRIORITY Priority = PRIORITY_UI);					// �R���X�g���N�^
	~CPlayer_Life();												// �f�X�g���N�^
	static CPlayer_Life *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
	CScene2D *m_apScene2d[MAX_LIFE];	// CScene2D�̃|�C���^
};
#endif