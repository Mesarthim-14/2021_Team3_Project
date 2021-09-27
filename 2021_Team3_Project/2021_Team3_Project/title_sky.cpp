//=============================================================================
// �^�C�g���}�b�v [title_map.cpp]
// Author : Konishi Yuuto
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Konishi Yuuto
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "renderer.h"
#include "game.h"
#include "model.h"
#include "title_sky.h"

//=============================================================================
// �}�N����`
// Author : Konishi Yuuto
//=============================================================================
#define POS				(D3DXVECTOR3(5000.0f, 0.0f, -20000.0f))
#define ROT				(D3DXVECTOR3(0.0f, D3DXToRadian(45.0f), 0.0f))
#define SKY_SCALE_NUM	(25.0f)
#define SKY_SCALE		(D3DXVECTOR3(SKY_SCALE_NUM, SKY_SCALE_NUM, SKY_SCALE_NUM))

//=============================================================================
// �R���X�g���N�^
// Author : Konishi Yuuto
//=============================================================================
CTitleSky::CTitleSky(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Konishi Yuuto
//=============================================================================
CTitleSky::~CTitleSky()
{
}

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Konishi Yuuto
//=============================================================================
CTitleSky * CTitleSky::Create(void)
{
	// CBullet�̃|�C���^
	CTitleSky *pSky = new CTitleSky;

	// !nullcheck
	if (pSky != nullptr)
	{
		// ����������
		pSky->Init(POS, ROT);
		pSky->SetScale(SKY_SCALE);

		// �|�C���^��Ԃ�
		return pSky;
	}

	return nullptr;
}

//=============================================================================
// �����������֐�
// Author : Konishi Yuuto
//=============================================================================
HRESULT CTitleSky::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_TITLE_SKY);

		// ���f���̏���n��
		BindModel(model);
	}

	// ����������
	CModel::Init(pos, rot);

	return S_OK;
}

//=============================================================================
// �`�揈��
// Author : Konishi Yuuto
//=============================================================================
void CTitleSky::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	// �`�揈��
	CModel::Draw();

	// ���C�g���ʂ�t����
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}