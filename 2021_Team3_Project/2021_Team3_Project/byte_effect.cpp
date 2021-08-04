//=============================================================================
// ���݂��G�t�F�N�g [byte_effect.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "byte_effect.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COL	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Effect::CByte_Effect(PRIORITY Priority) : CBillboard(Priority)
{

}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Effect::~CByte_Effect()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Effect * CByte_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CGage_3D_Back�̃|�C���^
	CByte_Effect *pGage_3D_Back = nullptr;

	// nullcheck
	if (pGage_3D_Back == nullptr)
	{
		// �������m��
		pGage_3D_Back = new CByte_Effect;

		// !nullcheck
		if (pGage_3D_Back != nullptr)
		{
			// ����������
			pGage_3D_Back->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pGage_3D_Back;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CByte_Effect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CBillboard::Init(pos, size);

	// �����ݒ�
	SetRot(ZeroVector3);

	// �F�ݒ�
	SetColor(COL);

	// ���ߒl�ݒ�
	SetAlpha(true);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Effect::Uninit(void)
{

	// �I������
	CBillboard::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Effect::Update(void)
{
	// �X�V����
	CBillboard::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Effect::Draw(void)
{
	// �`�揈��
	CBillboard::Draw();
}