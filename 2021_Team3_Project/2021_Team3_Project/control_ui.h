#ifndef _CONTROL_UI_H_
#define _CONTROL_UI_H_
//=============================================================================
// ����UI�N���X [control_ui.h]
// Author : Konishi Yuuto
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "billboard.h"

//=============================================================================
// �O���錾
//=============================================================================
class CModelAnime;

//=============================================================================
// �N���X��`
// Author : Konishi Yuuto
//=============================================================================
class CControlUi : public CBillboard
{
public:
	CControlUi(PRIORITY Priority = PRIORITY_UI);					// �R���X�g���N�^
	~CControlUi();													// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	// Set�֐�
	void SetModelPtr(CModelAnime* pPtr) { m_pModelPtr = pPtr; }		// ���f���̃|�C���^�ݒ�
	void SetHeight(float fHeight)		{ m_fHeight = fHeight; }	// �����̐ݒ�
private:
	CModelAnime* m_pModelPtr;	// ���f���̃|�C���^
	int m_nCounter;				// �^�C���̃J�E���^�[
	float m_fHeight;			// �\�����鍂��
};
#endif