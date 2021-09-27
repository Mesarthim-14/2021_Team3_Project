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
#include "title_map.h"

//=============================================================================
// �}�N����`
// Author : Konishi Yuuto
//=============================================================================
#define POS		(D3DXVECTOR3(-100000.0f, 0.0f, -15000.0f))
#define ROT		(D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f))

//=============================================================================
// �R���X�g���N�^
// Author : Konishi Yuuto
//=============================================================================
CTitleMap::CTitleMap(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Konishi Yuuto
//=============================================================================
CTitleMap::~CTitleMap()
{
}

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Konishi Yuuto
//=============================================================================
CTitleMap * CTitleMap::Create(void)
{
	// CBullet�̃|�C���^
	CTitleMap *pMap = new CTitleMap;

	// !nullcheck
	if (pMap != nullptr)
	{
		// ����������
		pMap->Init(POS, ROT);

		// �|�C���^��Ԃ�
		return pMap;
	}

	return nullptr;
}

//=============================================================================
// �����������֐�
// Author : Konishi Yuuto
//=============================================================================
HRESULT CTitleMap::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_TITLE_MAP);

		// ���f���̏���n��
		BindModel(model);
	}

	// ����������
	CModel::Init(pos, rot);

	return S_OK;
}