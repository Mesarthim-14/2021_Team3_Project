//=============================================================================
// �e [bullet.h]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "bullet.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define GRAVITY (0.1f)	//�d��
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CBullet::CBullet(PRIORITY Priority)
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CBullet::~CBullet()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	// CBullet�̃|�C���^
	CBullet *pBullet = nullptr;

	// nullcheck
	if (pBullet == nullptr)
	{
		// �������m��
		pBullet = new CBullet;

		// !nullcheck
		if (pBullet != nullptr)
		{
			// ����������
			pBullet->Init(pos, rot);

			// �ړ��ʑ��
			pBullet->SetMove(move);
		}
	}
	// �|�C���^��Ԃ�
	return pBullet;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_BULLET);

		// ���f���̏���n��
		BindModel(model);

		// �e�N�X�`���󂯓n��
		BindTexture(pXfile->GetXfileTexture(CXfile::XFILE_NUM_BULLET));
	}

	// ���C�t�ݒ�
	SetLife(100);

	// �����ݒ�
	SetRot(ZeroVector3);

	// ����������
	CModel::Init(pos, rot);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Uninit(void)
{
	// �I������
	CModel::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Update(void)
{
	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �ړ�
	move.y -= GRAVITY;

	// �ړ��ʐݒ�
	SetMove(move);

	// �X�V����
	CModel::Update();
	
	if (GetLife() <= 0)
	{
		// �I������
		Uninit();
	}
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}