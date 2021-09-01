//=============================================================================
// ���C�t�Q�[�W�̔w�i [gage_3d_back.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _GAGE_3D_BACK_H_
#define _GAGE_3D_BACK_H_
//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "billboard.h"
#include "enemy.h"
//=============================================================================
// �}�b�v�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CGage_3D_Back : public CBillboard
{
public:
	CGage_3D_Back(PRIORITY Priority = PRIORITY_3D_UI);										// �R���X�g���N�^
	~CGage_3D_Back();																		// �f�X�g���N�^
	static CGage_3D_Back *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy *pEnemy);		// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);										// ����������
	void Uninit(void);																		// �I������
	void Update(void);																		// �X�V����
	void Draw(void);																		// �`�揈��
private:
	CEnemy *m_pEnemy;					// CEnemy�̃|�C���^
};
#endif