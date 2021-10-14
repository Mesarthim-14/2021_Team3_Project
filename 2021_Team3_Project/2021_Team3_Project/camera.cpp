//=============================================================================
//
// �J�����̏��� [camera.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "joypad.h"
#include "motion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CAMERA_DEFAULT_F��			(D3DXToRadian(75.0f))			// �J�����̃�Default�l
#define DISTANCE					(2200.0f)						// ���_�`�����_�̋���
#define PLAYER_HEIGHT				(600.0f)						// �����_�̍���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	//�e�����o�ϐ��̃N���A
	m_posV = ZeroVector3;
	m_posVDest = ZeroVector3;
	m_posR = ZeroVector3;
	m_posRDest = ZeroVector3;
	m_posU = ZeroVector3;
	m_rot = ZeroVector3;
	m_fDistance = 0.0f;
	m_fMove = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCamera::Init(void)
{
	m_fMove = 5.0f;
	m_fDistance = DISTANCE;
	m_fVartical = CAMERA_DEFAULT_F��;
	m_fHorizontal = D3DXToRadian(0.0f);											// �����l�G�̂ق�������
	m_posR = D3DXVECTOR3(0.0f, PLAYER_HEIGHT, 0.0f);							// �����_�ݒ�
	m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);										// ������x�N�g��
	m_posV.x = m_posR.x + m_fDistance * sinf(m_fVartical) * sinf(m_fHorizontal);// �J�����ʒuX
	m_posV.y = m_posR.z + m_fDistance * cosf(m_fVartical);						// �J�����ʒuY
	m_posV.z = m_posR.y + m_fDistance * sinf(m_fVartical) * cosf(m_fHorizontal);// �J�����ʒuZ

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	// �v���C���[�̃|�C���^�擾
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// �v���C���[���g���Ă�����
	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 PlayerPos = ZeroVector3;	//�v���C���[�ʒu
		D3DXVECTOR3 PlayerRot = ZeroVector3;	//�v���C���[�p�x

		//�v���C���[1�ʒu�擾
		PlayerPos = pPlayer->GetPos();

		//�v���C���[1�p�x�擾
		PlayerRot = pPlayer->GetRot();

		// �ʏ��Ԃ̃J�����ړ�
		this->NomalUpdate(PlayerPos, PlayerRot);
	}
}

//=============================================================================
//�J�����N���X�̃Z�b�g����
//=============================================================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_posU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		200000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);
}