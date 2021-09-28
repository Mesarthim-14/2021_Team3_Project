//=============================================================================
// �ړ��̑���UI�N���X [rotate_ui.cpp]
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
#include "rotate_ui.h"
#include "player.h"
#include "modelanime.h"
#include "mode_base.h"

//=============================================================================
// �}�N����`
// Author : Konishi Yuuto
//=============================================================================
#define SIZE		(D3DXVECTOR3(300.0f, 300.0f,0.0f))		// �T�C�Y
#define ADD_POS_Y	(500.0f)								// �ԗւ̏�ɕ\��

//=============================================================================
// �R���X�g���N�^
// Author : Konishi Yuuto
//=============================================================================
CRotateUi::CRotateUi(PRIORITY Priority) : CControlUi(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Konishi Yuuto
//=============================================================================
CRotateUi::~CRotateUi()
{
}

//=============================================================================
// �C���X�^���X����
// Author : Konishi Yuuto
//=============================================================================
CRotateUi * CRotateUi::Create(CModelAnime *pPtr)
{
	// CRotateUi�̃|�C���^
	CRotateUi *pRotateUi = new CRotateUi;

	// !nullcheck
	if (pRotateUi)
	{
		pRotateUi->SetModelPtr(pPtr);

		// ����������
		pRotateUi->Init(pPtr->GetMtxPos(), SIZE);

		// �|�C���^��Ԃ�
		return pRotateUi;
	}

	return nullptr;
}

//=============================================================================
// �����������֐�
// Author : Konishi Yuuto
//=============================================================================
HRESULT CRotateUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CControlUi::Init(pos, size);

	// �e�N�X�`���|�C���^
	CTexture *pTexture = GET_TEXTURE_PTR;
	BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_MOVE_UI));

	// �A�j���[�V�������ݒ�
	D3DXVECTOR2 TexInfo = pTexture->GetSparateTexInfo(CTexture::SEPARATE_TEX_MOVE_UI);
	bool bLoop = pTexture->GetSparateTexLoop(CTexture::SEPARATE_TEX_MOVE_UI);
	InitAnimation(TexInfo, bLoop);

	// �����̐ݒ�
	SetHeight(ADD_POS_Y);

	return S_OK;
}