//=============================================================================
// �� [rock.cpp]
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
#include "model_box.h"
#include "game.h"
#include "player.h"
#include "rock.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define GRAVITY		(0.1f)									// �d��
#define SIZE		(D3DXVECTOR3 (1400.0f,1400.0f,1400.0f))	// �T�C�Y
#define POS_Y_MIN	(0.0f)									// Y���W�ŏ��l
#define MIN_MOVE	(D3DXVECTOR3(0.0f,0.0f,0.0f))			// �ړ��ʂ̍ŏ�
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CRock::CRock(PRIORITY Priority) : CModel(Priority)
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CRock::~CRock()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CRock * CRock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CRock�̃|�C���^
	CRock *pRock = nullptr;

	// nullcheck
	if (pRock == nullptr)
	{
		// �������m��
		pRock = new CRock;

		// !nullcheck
		if (pRock != nullptr)
		{
			// ����������
			pRock->Init(pos, rot);

			// ������
			CModel_Box::Create(pos, rot, pRock);
		}
	}
	// �|�C���^��Ԃ�
	return pRock;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CRock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_ROCK);

		// ���f���̏���n��
		BindModel(model);
	}

	// �T�C�Y�ݒ�
	SetSize(SIZE);

	// ����������
	CModel::Init(pos, ZeroVector3);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CRock::Uninit(void)
{
	// �I������
	CModel::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CRock::Update(void)
{
	// �X�V����
	CModel::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CRock::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}