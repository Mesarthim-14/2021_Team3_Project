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
#include "enemy_ship.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define MAX_LIFE	(100)	// �̗�
#define MOVE_VALUE	(10.0f)	// �ړ���
#define ROT_SPEED	(0.01f)	// ���񑬓x
#define ANGLE_180	(180)	// 180�x
#define ANGLE_360	(360)	// 360�x
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Ship::CEnemy_Ship(PRIORITY Priority)
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

	// �������֐�
	CEnemy::Init(pos, rot);

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
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �Â����W�ۑ�
	SetPosOld(pos);	

	// �ړ�����
	Move();

	// �X�V����
	CEnemy::Update();
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
		pGame = CManager::GetGame();

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

					// �ړ�����w
					pos.x += move.x;
					pos.z += move.z;
				}
			}
		}
	}
	// �ʒu�ݒ�
	SetPos(pos);

	// �����ݒ�
	SetRot(rot);
}