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
#define GRAVITY							(0.1f)							// �d��
#define MOVE_VALUE						(40.0f)							// �ړ���
#define ANGLE_180						(D3DXToRadian(180))				// 180�x
#define ANGLE_90						(D3DXToRadian(90))				// 90�x
#define LENGTH							(-600.0f)						// ����
#define BULLET_Y						(500.0f)						// �e��Y��
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
	}

	// ���C�t�ݒ�
	SetLife(1000);

	// ���ˈʒu
	D3DXVECTOR3 bulletpos = ZeroVector3;

	// �ړ�
	D3DXVECTOR3 move = ZeroVector3;

	//���W�����߂�
	bulletpos.x = pos.x - cosf(rot.y + ANGLE_90) * LENGTH;
	bulletpos.z = pos.z + sinf(rot.y + ANGLE_90) * LENGTH;
	bulletpos.y = BULLET_Y;

	// �e�̈ړ�
	move.x = sinf(rot.y + ANGLE_180) *MOVE_VALUE;
	move.z = cosf(rot.y + ANGLE_180) *MOVE_VALUE;

	// �ړ��ʐݒ�
	SetMove(move);

	// ����������
	CModel::Init(bulletpos, ZeroVector3);

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