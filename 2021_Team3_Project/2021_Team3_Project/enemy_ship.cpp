//=============================================================================
// �G�̑D [enemy_ship.cpp]
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
#include "collision.h"
#include "map.h"
#include "enemy_ship.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define MAX_LIFE		(100)									// �̗�
#define MOVE_VALUE		(10.0f)									// �ړ���
#define ROT_SPEED		(0.01f)									// ���񑬓x
#define ANGLE_180		(180)									// 180�x
#define ANGLE_360		(360)									// 360�x
#define SIZE			(D3DXVECTOR3 (700.0f,900.0f,700.0f))	// �T�C�Y
#define ATTACK_COUNT	(300)									// �U���Ԋu
#define SHIP_NUM		(0)										// �D�̃i���o�[
#define RAY_NUM			(1)										// ���C�̐�
#define RAY_HIT_RANGE	(600.0f)								// �͈�
#define RAY_ANGLE		(D3DXToRadian(360.0f / 4.0f))			// �p�x
// �D�̂̈ʒu
#define SHIP_POS		(D3DXVECTOR3(pShip->GetMtxWorld()._41, pShip->GetMtxWorld()._42, pShip->GetMtxWorld()._43))
// �C��̈ʒu
#define BATTERY_POS		(D3DXVECTOR3(pBattery->GetMtxWorld()._41, pBattery->GetMtxWorld()._42, pBattery->GetMtxWorld()._43))
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Ship::CEnemy_Ship(PRIORITY Priority) : CEnemy(Priority)
{
}
//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Ship::~CEnemy_Ship()
{
}
//=============================================================================
// �����֐�
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Ship * CEnemy_Ship::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CEnemy_Ship�|�C���^
	CEnemy_Ship *pEnemy_Ship = nullptr;

	// nullcheck
	if (pEnemy_Ship == nullptr)
	{
		// �������m��
		pEnemy_Ship = new CEnemy_Ship;

		// !nullcheck
		if (pEnemy_Ship != nullptr)
		{
			// ����������
			pEnemy_Ship->Init(pos, rot);

			// �{�b�N�X����
			//CCharacter_Box::Create(pos, rot, pEnemy_Ship);
		}
	}
	// �|�C���^��Ԃ�
	return pEnemy_Ship;
}
//=============================================================================
// �������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CEnemy_Ship::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f���̏���n��
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_ENEMY_SHIP);
	}

	// �̗͐ݒ�
	SetLife(MAX_LIFE);

	// �T�C�Y�ݒ�
	SetSize(SIZE);

	// �U������ݒ�
	SetAttackDecision(ATTACK_DECISION_CIRCLE);

	// �������֐�
	CEnemy::Init(pos, rot);

	// ���C�̏��
	CCharacter::RAY_DATA Ray_Data = { RAY_ANGLE, RAY_HIT_RANGE, RAY_NUM };

	// ���C�̏��ݒ�
	SetRay_Data(Ray_Data);
	return S_OK;
}
//=============================================================================
// �I���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Ship::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}
//=============================================================================
// �X�V�֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Ship::Update(void)
{
	// �X�V����
	CEnemy::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// ��Ԏ擾
	int nState = GetState();

	// �Â����W�ۑ�
	SetPosOld(pos);	

	// �U������擾
	bool bAttack = Get_bAttackDecision();

	// �U�����肪true�̏ꍇ
	if (bAttack == true)
	{
		// �U������
		Attack();

		// �ړ�����
		Move();
	}

	// ���S���
	if (nState == STATE_DEAD)
	{
		// �I��
		Uninit();

		return;
	}

	// ���C�̓����蔻��
	RayCollision();
}
//=============================================================================
// �`��֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Ship::Draw(void)
{
	// �`��֐�
	CEnemy::Draw();
}
//=============================================================================
// �ړ������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Ship::Move(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �����擾
	D3DXVECTOR3 rot = GetRot();

	// CGame�̃|�C���^
	CGame *pGame = nullptr;

	// nullcheck
	if (pGame == nullptr)
	{
		// CGame�̏��擾
		pGame = (CGame*)CManager::GetModePtr();

		// !nullcheck
		if (pGame != nullptr)
		{
			// CPlayer�̃|�C���^
			CPlayer *pPlayer = nullptr;

			// nullcheck
			if (pPlayer == nullptr)
			{
				// �v���C���[�̏��擾
				pPlayer = pGame->GetPlayer();

				// !nullcheck
				if (pPlayer != nullptr)
				{
					// �v���C���[�̈ʒu���擾
					D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

					// �p�x�Z�o
					float fAngle = atan2f(PlayerPos.x - pos.x, PlayerPos.z - pos.z);

					// �ړI�̊p�x
					D3DXVECTOR3 rotDest = ZeroVector3;

					// �ړI�̊p�x
					rotDest.y = fAngle;

					// �ړI�̊p�x
					rotDest.y += D3DXToRadian(ANGLE_180);

					while (rotDest.y - rot.y > D3DXToRadian(ANGLE_180))
					{
						rotDest.y -= D3DXToRadian(ANGLE_360);
					}
					while (rotDest.y - rot.y < D3DXToRadian(-ANGLE_180))
					{
						rotDest.y += D3DXToRadian(ANGLE_360);
					}

					// ����
					rot += (rotDest - rot)*ROT_SPEED;

					// �ړ�
					D3DXVECTOR3 move = ZeroVector3;

					// �ړ��ʉ��Z�i���߂��p�x�����ƂɈړ�����j
					move.x = sinf(fAngle)*MOVE_VALUE;
					move.z = cosf(fAngle)*MOVE_VALUE;

					// �ʒu�ݒ�
					SetMove(move);

					// �����ݒ�
					SetRot(rot);
				}
			}
		}
	}
}
//=============================================================================
// �U�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Ship::Attack(void)
{
	// �A�^�b�N����
	CEnemy::Attack();

	// �J�E���g��60�ȏ�ɂȂ����ꍇ
	if (GetAttackCount() >= ATTACK_COUNT)
	{
		// �C��̃|�C���^�擾
		CModelAnime *pBattery = GetModelAnime(PARTS_BATTERY);

		// �e����
		CEnemy_Bullet::Create(BATTERY_POS, ZeroVector3);

		// 0��
		GetAttackCount() = ZERO_INT;
	}
}
//=============================================================================
// ���C�̓����蔻�菈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Ship::RayCollision(void)
{
	//// ���f���̏��擾
	//CModelAnime *pShip = GetModelAnime(SHIP_NUM);

	//// �ʒu�擾
	//D3DXVECTOR3 pos = SHIP_POS;

	//// �����擾
	//D3DXVECTOR3 rot = GetRot();

	//// �}�b�v�̃|�C���^�擾
	//CMap *pMap = GET_MAP_PTR;

	//// !nullcheck
	//if (pShip != nullptr)
	//{
	//	// !nullcheck
	//	if (pMap != nullptr)
	//	{
	//		// ���C�̏��
	//		CCollision::RAY_INFO Ray_Info;

	//		// ���C�̓����蔻��
	//		Ray_Info = CCollision::RayCollision(pos, GET_MAP_PTR, rot.y, RAY_HIT_RANGE, RAY_NUM);

	//		// true�̏ꍇ
	//		if (Ray_Info.bHit == true)
	//		{
	//			// �߂�
	//			pos -= (D3DXVECTOR3(sinf(Ray_Info.VecDirection.y), ZERO_FLOAT, cosf(Ray_Info.VecDirection.y)));

	//			// �ʒu�ݒ�
	//			SetPos(pos);

	//			return;
	//		}
	//	}
	//}
}