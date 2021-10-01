//=============================================================================
// �U������UI�N���X [atack_ui.cpp]
// Author : Konishi Yuuto
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Konishi Yuuto
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "attack_ui.h"
#include "player.h"
#include "modelanime.h"
#include "mode_base.h"

//=============================================================================
// �}�N����`
// Author : Konishi Yuuto
//=============================================================================
#define SIZE		(D3DXVECTOR3(200.0f, 200.0f,0.0f))		// �T�C�Y
#define ADD_POS_Y	(930.0f)								// �ԗւ̏�ɕ\��

//=============================================================================
// �R���X�g���N�^
// Author : Konishi Yuuto
//=============================================================================
CAttackUi::CAttackUi(PRIORITY Priority) : CControlUi(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Konishi Yuuto
//=============================================================================
CAttackUi::~CAttackUi()
{
}

//=============================================================================
// �C���X�^���X����
// Author : Konishi Yuuto
//=============================================================================
CAttackUi * CAttackUi::Create(CModelAnime *pPtr)
{
	// CAttackUi�̃|�C���^
	CAttackUi *pAttackUi = new CAttackUi;

	// !nullcheck
	if (pAttackUi)
	{
		pAttackUi->SetModelPtr(pPtr);

		// ����������
		pAttackUi->Init(pPtr->GetMtxPos(), SIZE);

		// �|�C���^��Ԃ�
		return pAttackUi;
	}

	return nullptr;
}

//=============================================================================
// �����������֐�
// Author : Konishi Yuuto
//=============================================================================
HRESULT CAttackUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CControlUi::Init(pos, size);

	// �e�N�X�`���|�C���^
	CTexture *pTexture = GET_TEXTURE_PTR;
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_R1));

	// �����̐ݒ�
	SetHeight(ADD_POS_Y);

	return S_OK;
}