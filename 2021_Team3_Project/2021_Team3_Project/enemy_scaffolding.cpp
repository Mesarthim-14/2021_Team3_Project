//=============================================================================
// �G�̘E [enemy_ship.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "game.h"
#include "player.h"
#include "enemy_bullet.h"
#include "character_box.h"
#include "enemy_normal_bullet.h"
#include "enemy_life.h"
#include "enemy_scaffolding.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define MAX_LIFE		(100)									// �̗�
#define MOVE_VALUE		(10.0f)									// �ړ���
#define ROT_SPEED		(0.01f)									// ���񑬓x
#define ANGLE_180		(180)									// 180�x
#define ANGLE_360		(360)									// 360�x
#define SIZE			(D3DXVECTOR3 (1500.0f,6000.0f,1500.0f))	// �T�C�Y
#define ATTACK_COUNT	(120)									// �U���Ԋu

// �C��̈ʒu
#define BATTERY_POS		(D3DXVECTOR3(pBattery->GetMtxWorld()._41, pBattery->GetMtxWorld()._42, pBattery->GetMtxWorld()._43))
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Scaffolding::CEnemy_Scaffolding(PRIORITY Priority) : CEnemy(Priority)
{
}
//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Scaffolding::~CEnemy_Scaffolding()
{
}
//=============================================================================
// �����֐�
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Scaffolding * CEnemy_Scaffolding::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CEnemy_Ship�|�C���^
	CEnemy_Scaffolding *pEnemy_Scaffolding = nullptr;

	// nullcheck
	if (pEnemy_Scaffolding == nullptr)
	{
		// �������m��
		pEnemy_Scaffolding = new CEnemy_Scaffolding;

		// !nullcheck
		if (pEnemy_Scaffolding != nullptr)
		{
			// ����������
			pEnemy_Scaffolding->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pEnemy_Scaffolding;
}
//=============================================================================
// �������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CEnemy_Scaffolding::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f���̏���n��
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_ENEMY_SCAFFOLDING);
	}

	// �̗͐ݒ�
	SetLife(MAX_LIFE);

	// �T�C�Y�ݒ�
	SetSize(SIZE);

	// �������֐�
	CEnemy::Init(pos, rot);
	return S_OK;
}
//=============================================================================
// �I���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Scaffolding::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}
//=============================================================================
// �X�V�֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Scaffolding::Update(void)
{
	// �X�V����
	CEnemy::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �Â����W�ۑ�
	SetPosOld(pos);

	// �U������
	Attack();

	// ��Ԏ擾
	int nState = GetState();

	// ���S���
	if (nState == STATE_DEAD)
	{
		// �I��
		Uninit();

		return;
	}
}
//=============================================================================
// �`��֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Scaffolding::Draw(void)
{
	// �`��֐�
	CEnemy::Draw();
}
//=============================================================================
// �U�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Scaffolding::Attack(void)
{
	// �C���N�������g
	CEnemy::Attack();

	// �U������擾
	bool bAttack = Get_bAttackDecision();

	// �U�����肪true�̏ꍇ
	if (bAttack == true)
	{
		// �J�E���g��60�ȏ�ɂȂ����ꍇ
		if (GetAttackCount() >= ATTACK_COUNT)
		{
			// �C��̃|�C���^�擾
			CModelAnime *pBattery = GetModelAnime(PARTS_BATTERY);

			// �e����
			CEnemy_Normal_Bullet::Create(BATTERY_POS, ZeroVector3);

			// 0��
			GetAttackCount() = ZERO_INT;
		}
	}
}