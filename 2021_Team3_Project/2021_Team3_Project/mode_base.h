#ifndef _MODE_BASE_H_
#define _MODE_BASE_H_
//==============================================================================
//
// ���[�h�̊��N���X  [mode_base.h]
// Author : Konishi Yuuto
//
//==============================================================================

//==============================================================================
// �C���N���[�h
//==============================================================================
#include "main.h"

//=============================================================================
// �O���錾
//=============================================================================
class CLight;
class CCamera;
class CPlayer;

//==============================================================================
// �N���X��`
//==============================================================================
class CModeBase
{
public:
	CModeBase();				// �R���X�g���N�^
	virtual ~CModeBase() {};	// �f�X�g���N�^

	virtual HRESULT Init(void) = 0;		// ������
	virtual void Update(void) = 0;		// �X�V
	virtual void Draw(void) = 0;		// �`��

	// Get�֐�
	virtual CCamera* GetCamera(void) { return m_pCamera; }		// �J�����̃|�C���^
	virtual CLight* GetLight(void) { return m_pLight; }			// ���C�g�̃|�C���^
	virtual CPlayer* GetPlayer(void) { return m_pPlayer; }		// �v���C���[�̃|�C���^

private:
	CCamera *m_pCamera;		// �J�����̃|�C���^
	CLight *m_pLight;		// ���C�g�̃|�C���^
	CPlayer *m_pPlayer;		// �v���C���[�̃|�C���^
};

#endif