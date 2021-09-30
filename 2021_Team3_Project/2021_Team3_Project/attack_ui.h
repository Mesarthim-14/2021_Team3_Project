#ifndef _ATTACK_UI_H_
#define _ATTACK_UI_H_
//=============================================================================
// �U���̑���UI�N���X [attack_ui.h]
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
class CAttackUi : public CControlUi
{
public:
	CAttackUi(PRIORITY Priority = PRIORITY_UI);			// �R���X�g���N�^
	~CAttackUi();										// �f�X�g���N�^
	static CAttackUi *Create(CModelAnime *pPtr);		// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������

private:
};
#endif