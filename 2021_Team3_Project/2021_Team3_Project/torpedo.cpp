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
#include "map.h"
#include "model_box.h"

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define SIZE			(D3DXVECTOR3(1000.0f,800.0f,1000.0f))		// �T�C�Y
#define ROT				(D3DXVECTOR3(rot.x,rot.y + m_fAngle,rot.z))	// ����
#define MOVE_VALUE		(10.0f)										// �ړ���
#define DECISION_LENGTH	(5000.0f)									// ��̒���
#define FAN_DIR			(D3DXVECTOR3(1.0f, 0.0f, 0.0f))				// �ʐ�����
#define ANGLE_90		(D3DXToRadian(90.0f))						// 90�x
#define ANGLE_270		(D3DXToRadian(270.0f))						// 270�x
#define ANGLE_0			(D3DXToRadian(0.0f))						// 0�x
#define ANGLE_360		(D3DXToRadian(360.0f))						// 360�x
#define FAN_COS			(cosf(D3DXToRadian(180.0f / 2.0f)))			// cosf��
#define RAY_HIT_RANGE	(250.0f)									// ���C�͈̔�
#define RAY_NUM			(1)											// ���C�̖{��
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CTorpedo::CTorpedo(PRIORITY Priority) : CModel(Priority)
{
	m_bAttackDecision	= false;
	m_bMove				= false;
	m_fAngle			= ZERO_FLOAT;
}
//=============================================================================
// �f�X�g���N�^
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

	// ������
	//CModel_Box::Create(pos, rot, this);

	// ����������
	CModel::Init(pos, ZeroVector3);

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

	// ��̔���
	FanDecision();

	// �U�����肪true�̏ꍇ
	if (m_bAttackDecision == true)
	{
		// �ړ����肪false�̏ꍇ
		if (m_bMove == false)
		{
			// �v���C���[�̃|�C���^�擾
			CPlayer *pPlayer = GET_PLAYER_PTR;

			// �ʒu�擾
			D3DXVECTOR3 pos = GetPos();

			// �����擾
			D3DXVECTOR3 rot = GetRot();

			// !nullcheck
			if (pPlayer != nullptr)
			{
				// �ʒu���W�擾
				D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

				// �p�x
				m_fAngle = atan2f((pos.x - PlayerPos.x), (pos.z - PlayerPos.z));
			}
			
			// ���C�̏��
			CModel::RAY_DATA Ray_Data = { ROT.y, RAY_HIT_RANGE,RAY_NUM };

			// ���C�̏��ݒ�
			SetRay_Data(Ray_Data);

			// ����
			SetRot(ROT);

			// �ړ������true��
			m_bMove = true;
		}
		// �ړ�����
		Move();
	}

	// �����蔻��
	Collision();

	// �Q�[���擾
	CGame *pGame = (CGame*)CManager::GetModePtr();

	// !nullchrck
	if (pGame != nullptr)
	{
		// �{�X��ɑJ�ڂ�����
		bool bBossTransition = pGame->GetbBossTransition();

		// �{�X��ɑJ�ڂ����ꍇ
		if (bBossTransition == true)
		{
			// �I��
			Uninit();

			return;
		}
	}
	// ���C�̓����蔻��
	//RayCollision();
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
		// �I������
		Uninit();

		return;
	}
}
//=============================================================================
// �����蔻�菈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CTorpedo::FanDecision(void)
{
	// �v���C���[�̃|�C���^�擾
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// �ʒu�擾
	D3DXVECTOR3 Pos = GetPos();

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// �v���C���[�̈ʒu���W�擾
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

		// �x�N�g��
		D3DXVECTOR3 Vec = ZeroVector3;

		// �_�Ɛ�̃x�N�g��
		Vec.x = PlayerPos.x - Pos.x;
		Vec.z = PlayerPos.z - Pos.z;

		// �����Z�o
		float fVec_Length = sqrtf((Vec.x * Vec.x) + (Vec.z * Vec.z));

		// �����̔�r
		if (fVec_Length > DECISION_LENGTH)
		{
			// �U�������true��
			m_bAttackDecision = false;
			// �����̏I��
			return;
		}

		// �����擾
		D3DXVECTOR3 Rot = GetRot();

		// ����
		float fRot = ZERO_FLOAT;

		// �O�������Ă邩���������Ă邩
		if (Rot.y > ANGLE_90 && Rot.y < ANGLE_270 || Rot.y < ANGLE_90 && Rot.y > -ANGLE_90)
		{
			// ����
			fRot = Rot.y - ANGLE_90;
		}
		//�E�������Ă邩���������Ă邩
		if (Rot.y > ANGLE_0 && Rot.y < ANGLE_360 || Rot.y < ANGLE_0 && Rot.y > -ANGLE_0)
		{
			// ����
			fRot = Rot.y + ANGLE_90;
		}

		// ����
		D3DXVECTOR3 FanDir = FAN_DIR;

		// ��]
		D3DXVECTOR3 Rotate_ArcDir = ZeroVector3;

		// �x�N�g������]������
		Rotate_ArcDir.x = FanDir.x * cosf(fRot) + FanDir.z * -sinf(fRot);
		Rotate_ArcDir.z = FanDir.x * sinf(fRot) + FanDir.z * cosf(fRot);

		// �P�ʃx�N�g��
		D3DXVECTOR3 Normal_Vec = ZeroVector3;

		// �P�ʃx�N�g���ɂ���
		Normal_Vec.x = Vec.x / fVec_Length;
		Normal_Vec.z = Vec.z / fVec_Length;

		// ���όv�Z
		float fdot = Normal_Vec.x * Rotate_ArcDir.x + Normal_Vec.z * Rotate_ArcDir.z;

		// ��͈̔͂�cos�ɂ���
		float fcos = FAN_COS;

		// �_����͈͓̔��ɂ��邩���r����
		if (fcos < fdot)
		{
			// �U�������true��
			m_bAttackDecision = true;
		}
	}
}
//=============================================================================
// ���C�̓����蔻�菈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CTorpedo::RayCollision(void)
{
	//// �ʒu�擾
	//D3DXVECTOR3 pos = GetPos();

	//// �����擾
	//D3DXVECTOR3 rot = GetRot();

	//// �}�b�v�̃|�C���^�擾
	//CMap *pMap = GET_MAP_PTR;

	//// ���C�̏��
	//CCollision::RAY_INFO Ray_Info;

	//// ���C�̓����蔻��
	//Ray_Info = CCollision::RayCollision(pos, GET_MAP_PTR, rot.y, RAY_HIT_RANGE, RAY_NUM);

	//// true�̏ꍇ
	//if (Ray_Info.bHit == true)
	//{
	//	// �߂�
	//	pos -= (D3DXVECTOR3(sinf(Ray_Info.VecDirection.y), ZERO_FLOAT, cosf(Ray_Info.VecDirection.y)));

	//	// �ʒu�ݒ�
	//	SetPos(pos);

	//	return;
	//}
}