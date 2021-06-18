//=============================================================================
//
// �v���C���[�N���X [player.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"
#include "collision.h"
#include "fade.h"
#include "texture.h"
#include "resource_manager.h"
#include "motion.h"
#include "bullet.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED					(20.0f)									// �v���C���[�̈ړ���
#define STICK_SENSITIVITY				(50.0f)									// �X�e�B�b�N���x
#define PLAYER_ROT_SPEED				(0.1f)									// �L�����N�^�[�̉�]���鑬�x
#define SHIP_NUM						(0)										// �D�̃i���o�[
#define MIN_MOVE						(D3DXVECTOR3(0.0f,0.0f,0.0f))			// �ړ��ʂ̍ŏ��l
#define SIZE							(D3DXVECTOR3 (500.0f,500.0f,1500.0f))	// �T�C�Y
#define PARENT_NUM						(0)										// �e�̃i���o�[
//=============================================================================
// �N���G�C�g
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CPlayer *pPlayer = new CPlayer;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// ����������
		pPlayer->Init(pos, rot);
	}

	// �|�C���^��Ԃ�
	return pPlayer;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority)
{
	m_rotDest = ZeroVector3;
	m_bMove = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f���̏���n��
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER);
	}

	CCharacter::Init(pos, rot);												// ���W�@�p�x

	SetSpeed(PLAYER_SPEED);													// ���x�̐ݒ�

	// �T�C�Y�ݒ�
	SetSize(SIZE);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{	
	// �I������
	CCharacter::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// ���W���
	D3DXVECTOR3 pos = GetPos();	// ���݂̍��W�擾
	SetPosOld(pos);				// �Â����W�ۑ�

	// �v���C���[�̏��
	UpdateState();

	// ���[�V�������
	UpdateMotionState();

	// �v���C���[�̐���
	PlayerControl();

	// �p�x�̍X�V����
	UpdateRot();

	// �e�N���X�̍X�V����
	CCharacter::Update();

	// �̗͂�0�ɂȂ�����
	if (GetLife() <= 0)
	{
		// ���񂾂Ƃ�
		Death();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	// �`�揈��
	CCharacter::Draw();
}

//=============================================================================
// �v���C���[�̏��
//=============================================================================
void CPlayer::UpdateState(void)
{

}

//=============================================================================
// ���[�V�������
//=============================================================================
void CPlayer::UpdateMotionState(void)
{
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();
	int nKey = GetMotion()->GetKey();
	int nCountMotion = GetMotion()->GetCountMotion();

	// ���[�V�������
	switch (MotionState)
	{
	case MOTION_IDOL:
		break;
	}
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
void CPlayer::PlayerControl()
{
	// �v���C���[�̈ړ�����
	Move();

	// �U������
	Attack();

	// �����蔻�菈��
	Collision();
}

//=============================================================================
// �p�x�̍X�V����
//=============================================================================
void CPlayer::UpdateRot(void)
{
	// �p�x�̎擾
	D3DXVECTOR3 rot = GetRot();

	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// �L�����N�^�[��]�̑��x
	rot += (m_rotDest - rot) * PLAYER_ROT_SPEED;

	// �p�x�̐ݒ�
	SetRot(rot);
}

//=============================================================================
// ���񂾂Ƃ��̏���
//=============================================================================
void CPlayer::Death(void)
{

}

//=============================================================================
// �ړ��̏���
//=============================================================================
void CPlayer::Move(void)
{
	// ���[�J���ϐ�
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();					// �L�[�{�[�h�X�V
	DIJOYSTATE js = CInputJoypad::GetStick(0);								// �W���C�p�b�h�̎擾
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();		// �T�E���h�̃|�C���^
	float fAngle = GET_CAMERA_PTR->GetHorizontal();							// �J�����̊p�x
	D3DXVECTOR3 pos = GetPos();												// ���W
	D3DXVECTOR3 rot = GetRot();												// �p�x
	D3DXVECTOR3 move = GetMove();											// �ړ�
	float fSpeed = GetSpeed();												// �X�s�[�h
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();	// ���[�V�����̏��

	//���͂����݂���
	if ((js.lX != 0.0f || js.lY != 0.0f))
	{
		float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// �R���g���[���̊p�x
		float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);	// �R���g���[���̊p�x

		// �ړ��ʐݒ�
		move.x = sinf(fAngle + (fAngle2))* fSpeed;
		move.z = cosf(fAngle + (fAngle2))* fSpeed;

		// �p�x�̐ݒ�
		m_rotDest.y = fAngle + (fAngle3);
	}
	else
	{

	}

	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_W))
	{
		// �������[�V����
	//	SetMotion(MOTION_WALK);

		// �ړ��ʁE�p�x�̐ݒ�
		move.x = -sinf(fAngle)*fSpeed;
		move.z = -cosf(fAngle)*fSpeed;
		m_rotDest.y = fAngle;
		SetRot(D3DXVECTOR3(rot.x, fAngle, rot.z));
	}
	// ���Ɉړ�
	if (pKeyboard->GetPress(DIK_S))
	{
		// �������[�V����
	//	SetMotion(MOTION_WALK);

		// �ړ��ʁE�p�x�̐ݒ�
		move.x = sinf((fAngle))*fSpeed;
		move.z = cosf((fAngle))*fSpeed;
		m_rotDest.y = fAngle;
		SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(-180.0f), rot.z));
	}
	// ���Ɉړ�
	if (pKeyboard->GetPress(DIK_A))
	{
		// �������[�V����
	//	SetMotion(MOTION_WALK);

		// �ړ��ʁE�p�x�̐ݒ�
		move.x = sinf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
		move.z = cosf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
		m_rotDest.y = fAngle;
		SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(-90.0f), rot.z));
	}
	// �E�Ɉړ�
	if (pKeyboard->GetPress(DIK_D))
	{
		// �������[�V����
	//	SetMotion(MOTION_WALK);

		// �ړ��ʁE�p�x�̐ݒ�
		move.x = sinf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
		move.z = cosf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
		m_rotDest.y = fAngle;
		SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(90.0f), rot.z));
	}

	// �ړ��ʐݒ�
	SetMove(move);

	// ���͂���Ă��Ȃ��ꍇ
	if (!pKeyboard->GetPress(DIK_W) && !pKeyboard->GetPress(DIK_S) &&
		!pKeyboard->GetPress(DIK_A) && !pKeyboard->GetPress(DIK_D))
	{
		// �ړ��ʐݒ�
		SetMove(MIN_MOVE);
	}

	// �Â����W�擾
	D3DXVECTOR3 OldPos = GetOldPos();

	// �����Ă��Ȃ�������
	if (OldPos == pos)
	{
		// �ʏ탂�[�V����
		SetMotion(MOTION_IDOL);
	}
}

//=============================================================================
// �U������
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Attack(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	

	// SPACE�L�[���������ꍇ
	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		// �ړ���
		D3DXVECTOR3 bulletmove = ZeroVector3;

		// �����擾
		D3DXVECTOR3 rot = GetRot();
		
		// ���f���̏��擾
		CModelAnime *pAnime = GetModelAnime(SHIP_NUM);

		// �D�̈ʒu�擾
		D3DXVECTOR3 pos = D3DXVECTOR3(pAnime->GetMtxWorld()._41, pAnime->GetMtxWorld()._42, pAnime->GetMtxWorld()._43);

		// �e����
		CBullet::Create(pos, rot);
	}
}
//=============================================================================
// �����蔻�菈��
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Collision(void)
{
	// CScene�̃|�C���^
	CScene *pScene = nullptr;

	// ���f���̏��擾
	CModelAnime *pAnime = GetModelAnime(SHIP_NUM);

	// �ʒu�擾
	D3DXVECTOR3 pos = D3DXVECTOR3(pAnime->GetMtxWorld()._41, pAnime->GetMtxWorld()._42, pAnime->GetMtxWorld()._43);

	// �ʒu�擾
	D3DXVECTOR3 posOld = D3DXVECTOR3(pAnime->GetOldMtxWorld()._41, pAnime->GetOldMtxWorld()._42, pAnime->GetOldMtxWorld()._43);

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// nullcheck
	if (pScene == nullptr)
	{
		// �擪�̃|�C���^�擾
		pScene = GetTop(PRIORITY_ENEMY);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcter�Ƃ̓����蔻��
			while (pScene != nullptr) // nullptr�ɂȂ�܂ŉ�
			{
				// ���݂̃|�C���^
				CScene *pSceneCur = pScene->GetNext();

				// �ʒu
				D3DXVECTOR3 CharacterPos = ZeroVector3;

				// �ʒu�擾
				CharacterPos.x = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._41;
				CharacterPos.y = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._42;
				CharacterPos.z = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._43;

				// �T�C�Y�擾
				D3DXVECTOR3 CharacterSize = ((CCharacter*)pScene)->GetSize();

				//�ǂ��̖ʂɓ����������擾
				//��
				if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_DOWN)
				{
					// �ړ���0
					move.y = MIN_MOVE.y;

					// �ړ��ʎ擾
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// �ړ���0
					CharacterMove.y = MIN_MOVE.y;

					// �ړ��ʐݒ�
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// �ʒu
					pos.y = (size.y / DIVIDE_2) - (CharacterPos.y + CharacterSize.y / DIVIDE_2);

					// �ړ��ʐݒ�
					SetMove(move);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ��
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_UP)
				{
					// �ړ���0
					move.y = MIN_MOVE.y;

					// �ړ��ʎ擾
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// �ړ���0
					CharacterMove.y = MIN_MOVE.y;

					// �ړ��ʐݒ�
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// �ʒu
					pos.y = (-size.y / DIVIDE_2) + (CharacterPos.y + CharacterSize.y / DIVIDE_2);

					// �ړ��ʐݒ�
					SetMove(move);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ��
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_LEFT)
				{
					// �ړ���0
					move.x = MIN_MOVE.x;

					// �ړ��ʎ擾
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// �ړ���0
					CharacterMove.x = MIN_MOVE.x;

					// �ړ��ʐݒ�
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// �ʒu
					pos.x = (-size.x / DIVIDE_2) + (CharacterPos.x - CharacterSize.x / DIVIDE_2);

					// �ړ��ʐݒ�
					SetMove(move);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// �E
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_RIGHT)
				{
					// �ړ���0
					move.x = MIN_MOVE.x;

					// �ړ��ʎ擾
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// �ړ���0
					CharacterMove.x = MIN_MOVE.x;

					// �ړ��ʐݒ�
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// �ʒu
					pos.x = (size.x / DIVIDE_2) + (CharacterPos.x + CharacterSize.x / DIVIDE_2);

					// �ړ��ʐݒ�
					SetMove(move);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ��O
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_BACK)
				{
					// �ړ���0
					move.z = MIN_MOVE.z;

					// �ړ��ʎ擾
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// �ړ���0
					CharacterMove.z = MIN_MOVE.z;

					// �ړ��ʐݒ�
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// �ʒu
					pos.z = (size.z / DIVIDE_2) + (CharacterPos.z + CharacterSize.z / DIVIDE_2);

					// �ړ��ʐݒ�
					SetMove(move);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ��
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_PREVIOUS)
				{
					// �ړ���0
					move.z = MIN_MOVE.z;

					// �ړ��ʎ擾
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// �ړ���0
					CharacterMove.z = MIN_MOVE.z;

					// �ʒu
					pos.z = (-size.z / DIVIDE_2) + (CharacterPos.z + CharacterSize.z / DIVIDE_2);

					// �ړ��ʐݒ�
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// �ړ��ʐݒ�
					SetMove(move);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ���̃|�C���^�擾
				pScene= pSceneCur;
			} 
		}
	}
}