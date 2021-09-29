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
#include "control_ui.h"
#include "player.h"
#include "modelanime.h"
#include "mode_base.h"

//=============================================================================
// �}�N����`
// Author : Konishi Yuuto
//=============================================================================
#define END_TIME	(240)									// �I���̎���

//=============================================================================
// �R���X�g���N�^
// Author : Konishi Yuuto
//=============================================================================
CControlUi::CControlUi(PRIORITY Priority) : CBillboard(Priority)
{
	m_pModelPtr = nullptr;
	m_nCounter = 0;
	m_fHeight = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
// Author : Konishi Yuuto
//=============================================================================
CControlUi::~CControlUi()
{
}

//=============================================================================
// �����������֐�
// Author : Konishi Yuuto
//=============================================================================
HRESULT CControlUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CBillboard::Init(pos, size);

	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Konishi Yuuto
//=============================================================================
void CControlUi::Uninit(void)
{
	// �I������
	CBillboard::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Konishi Yuuto
//=============================================================================
void CControlUi::Update(void)
{
	m_nCounter++;

	// �ԗւ̏�ɐݒ�
	D3DXVECTOR3 pos = m_pModelPtr->GetMtxPos();
	pos.y = pos.y + m_fHeight;
	SetPos(pos);

	// �X�V����
	CBillboard::Update();

	// ��莞�Ԃ�
	if (m_nCounter >= END_TIME)
	{
		// �I������
		Uninit();

		return;
	}
}

//=============================================================================
// �`�揈���֐�
// Author : Konishi Yuuto
//=============================================================================
void CControlUi::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

	// ���Ԃ���Ȃ��悤�ɂ���@(Z�o�b�t�@)
	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	// �`�揈��
	CBillboard::Draw();

	// ���Ԃ���Ȃ��悤�ɂ���@(Z�o�b�t�@)
	pDevice->SetRenderState(D3DRS_ZENABLE, true);
}