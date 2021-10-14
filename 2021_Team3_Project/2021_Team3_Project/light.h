#ifndef _LIGHT_H_
#define _LIGHT_H_
//=============================================================================
//
// ���C�g���� [light.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CLight
{
public:
	CLight();				// �R���X�g���N�^
	~CLight();				// �f�X�g���N�^

	static CLight *Create(void);	// �C���X�^���X��������
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����

	// Set�֐�
	void SetPos(D3DXVECTOR3 pos) { m_Light.Position = pos; }
	void SetVecDir(D3DXVECTOR3 Dir);

	// Get�֐�
	D3DXVECTOR3 GetPos(void) { return m_Light.Position; }		// ���W
	D3DXVECTOR3 GetLightDir(void) { return m_vecDir; }			// ���C�g�̌���

private:
	D3DLIGHT9 m_Light;		// ���C�g�̕ϐ�
	D3DXVECTOR3 m_vecDir;	// ���C�g�̌���
};
#endif