#ifndef _CAMERA_H_
#define _CAMERA_H_
//=============================================================================
//
// �J�����N���X�w�b�_�[ [camera.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �J�����N���X
//=============================================================================
class CCamera
{
public:
	CCamera();					// �R���X�g���N�^
	~CCamera();					// �f�X�g���N�^

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void SetCamera(void);		// �J�����̕`��ݒ�

	// Set�֐�
	void SetTarget(bool Target) { m_bTarget = Target; }

	// Get�֐�
	D3DXVECTOR3 GetposV(void)		{ return m_posV; }				// �J�������W
	D3DXVECTOR3 GetposR(void)		{	return m_posR;}				// �J�����p�x
	D3DXMATRIX GetMtxView(void)		{ return m_mtxView; }			// �}�g���N�X�r���[
	D3DXVECTOR3 GetposVDest(void)	{ return m_posVDest; }			// �ړI�̊p�x
	D3DXMATRIX GetMtxProj(void)		{ return m_mtxProjection; }		// �v���W�F�N�g
	bool GetTargetBool(void)		{ return m_bTarget; }			// �^�[�Q�b�g�J�����̃t���O
	float GetVartical(void)			{ return m_fVartical; }			// �c�̉�]
	float GetHorizontal(void)		{return m_fHorizontal;}			// ���̉�]

	static CCamera*Create(void);		// �N���G�C�g

private:
	//=========================================================================
	// �v���C�x�[�g�����o�֐��錾
	//=========================================================================
	void NomalUpdate(D3DXVECTOR3 PlayerPos, D3DXVECTOR3 PlayerRot);

	//=========================================================================
	// �����o�ϐ��錾
	//=========================================================================
	D3DXVECTOR3 m_posV;						// �J�����̍��W
	D3DXVECTOR3 m_posVDest;					// �J�����̍��W�i�ړI�n�j
	D3DXVECTOR3 m_posVRot;					// �J�����̍��W�i�j
	D3DXVECTOR3 m_posR;						// �����_
	D3DXVECTOR3 m_posRDest;					// �����_�i�ړI�n�j
	D3DXVECTOR3 m_posRRot;					// �����_�i�j
	D3DXVECTOR3 m_posU;						// ������x�N�g��
	D3DXMATRIX m_mtxProjection;				// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;					// �r���[�}�g���b�N�X
	D3DXVECTOR3 m_rot;						// ����
	bool m_bTarget;							// �^�[�Q�b�g�g�p�t���O
	float m_fVartical;						// �c��]�p�x
	float m_fHorizontal;					// ����]�p
	float m_fDistance;						// ���_�`�����_�̋���
	float m_fMove;							// �ړ���
};
#endif 