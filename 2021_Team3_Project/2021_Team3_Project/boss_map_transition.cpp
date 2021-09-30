//=============================================================================
// �}�b�v [bullet.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "character.h"
#include "collision.h"
#include "renderer.h"
#include "game.h"
#include "model.h"
#include "boss_map_transition.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Map_Transition::CBoss_Map_Transition(PRIORITY Priority) : CModel(Priority)
{

}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Map_Transition::~CBoss_Map_Transition()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CBoss_Map_Transition * CBoss_Map_Transition::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CBoss_Map_Transition�̃|�C���^
	CBoss_Map_Transition *pMap = nullptr;

	// nullcheck
	if (pMap == nullptr)
	{
		// �������m��
		pMap = new CBoss_Map_Transition;

		// !nullcheck
		if (pMap != nullptr)
		{
			// ����������
			pMap->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pMap;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBoss_Map_Transition::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f��
		CXfile::MODEL model;

		// ���f�����擾
		model = pXfile->GetXfile(CXfile::XFILE_NUM_BOSS_MAP_TRANSITION);

		// ���f���̏���n��
		BindModel(model);
	}

	// ����������
	CModel::Init(pos, rot);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Map_Transition::Uninit(void)
{
	// �I������
	CModel::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Map_Transition::Update(void)
{
	// �X�V����
	CModel::Update();

}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBoss_Map_Transition::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}