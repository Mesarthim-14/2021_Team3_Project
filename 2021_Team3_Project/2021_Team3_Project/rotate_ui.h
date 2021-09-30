#ifndef _ROTATE_UI_H_
#define _ROTATE_UI_H_
//=============================================================================
// �ړ��̑���UI�N���X [rotate_ui.h]
// Author : Konishi Yuuto
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "control_ui.h"

//=============================================================================
// �N���X��`
// Author : Konishi Yuuto
//=============================================================================
class CRotateUi : public CControlUi
{
public:
	CRotateUi(PRIORITY Priority = PRIORITY_UI);			// �R���X�g���N�^
	~CRotateUi();										// �f�X�g���N�^
	static CRotateUi *Create(CModelAnime *pPtr);		// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������

private:
};
#endif