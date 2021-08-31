//=============================================================================
// �e [bullet.cpp]
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
#include "bullet.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define GRAVITY		(0.1f)								// �d��
#define SIZE		(D3DXVECTOR3(80.0f,80.0f,80.0f))	// �T�C�Y
#define POS_Y_MIN	(0.0f)								// Y���W�ŏ��l
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
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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

		// �e�̐ݒ�
		SetShadowInfo(model);
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
	// �X�V����
	CModel::Update();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �ړ�
	move.y -= GRAVITY;

	// �ړ��ʐݒ�
	SetMove(move);

	// y��0�ȉ��̏ꍇ
	if (pos.y <= POS_Y_MIN)
	{
		// ���S��Ԃ�
		SetState(STATE_DEAD);
	}
	// ���S��Ԃ̏ꍇ
	if (GetState() == STATE_DEAD)
	{
		Death();
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
//=============================================================================
// ���S�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Death(void)
{
	// �I������
	Uninit();

	return;
}
