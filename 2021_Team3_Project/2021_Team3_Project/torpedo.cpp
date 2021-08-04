//=============================================================================
// ���� [torpedo.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "character.h"
#include "game.h"
#include "player.h"
#include "collision.h"
#include "torpedo.h"
#include "renderer.h"
#include "model_box.h"

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define SIZE			(D3DXVECTOR3(500.0f,800.0f,1000.0f))			// �T�C�Y
#define ROT				(D3DXVECTOR3(rot.x,rot.y + m_fAngle,rot.z))	// ����
#define MOVE_VALUE		(10.0f)										// �ړ���
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CTorpedo::CTorpedo(PRIORITY Priority)
{
	m_fAngle = ZERO_FLOAT;
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CTorpedo::~CTorpedo()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CTorpedo * CTorpedo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CTorpedo�̃|�C���^
	CTorpedo *pTorpedo = nullptr;

	// nullcheck
	if (pTorpedo == nullptr)
	{
		// �������m��
		pTorpedo = new CTorpedo;

		// !nullcheck
		if (pTorpedo != nullptr)
		{
			// ����������
			pTorpedo->Init(pos, rot);

			// ������
			CModel_Box::Create(pos, rot, pTorpedo);
		}
	}
	// �|�C���^��Ԃ�
	return pTorpedo;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CTorpedo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_TORPEDO);
		 
		// ���f���̏���n��
		BindModel(model);
	}

	// �T�C�Y�ݒ�
	SetSize(SIZE);

	// ����������
	CModel::Init(pos, ZeroVector3);

	// �v���C���[�̃|�C���^�擾
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// nullcheck
	if (pPlayer != nullptr)
	{
		// �ʒu���W�擾
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

		// �p�x
		m_fAngle = atan2f((pos.x - PlayerPos.x), (pos.z - PlayerPos.z));
	}

	// ����
	SetRot(ROT);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CTorpedo::Uninit(void)
{
	// �I������
	CModel::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CTorpedo::Update(void)
{
	// �X�V����
	CModel::Update();

	// �ړ�����
	//Move();

	// �����蔻��
	//Collision();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CTorpedo::Draw(void)
{
	// �`�揈��
	CModel::Draw();

}
//=============================================================================
// �ړ������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CTorpedo::Move(void)
{
	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �e�̈ړ�
	move.x = -sinf(m_fAngle) *MOVE_VALUE;
	move.z = -cosf(m_fAngle) *MOVE_VALUE;

	// �ړ��ݒ�
	SetMove(move);
}
//=============================================================================
// �����蔻�菈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CTorpedo::Collision(void)
{
	// �D�̈ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �v���C���[�̃|�C���^�擾
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// �v���C���[�ʒu���W�擾
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	// �v���C���[�T�C�Y�擾
	D3DXVECTOR3 PlayerSize = pPlayer->GetSize();

	// ����
	if (CCollision::CollisionRectangleAndRectangle(pos, PlayerPos, size, PlayerSize) == true)
	{
		// ��Ԑݒ�
		SetState(STATE_DEAD);

		// �I������
		Uninit();
	}
}