#ifndef _WATER_H_
#define _WATER_H_
//=============================================================================
//
// ���̃N���X [water.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "meshfield.h"

//=============================================================================
// �O���錾
//=============================================================================
class CWave;

//=============================================================================
// ���N���X
//=============================================================================
class CWater : public CMeshField
{
public:
	CWater(PRIORITY = PRIORITY_0);				// �R���X�g���N�^
	~CWater();									// �f�X�g���N�^
	HRESULT Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��
	void Wave(void);							// �g�̏���
	void SetMatrix(void);						// �}�g���N�X�̐ݒ�
	static CWater*Create(void);					// �C���X�^���X����
	static HRESULT LoadShaderFile(void);		// �V�F�[�_�t�@�C���̓ǂݍ���

private:
	D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���N�X

	// �G�t�F�N�g�쐬
	static LPD3DXEFFECT m_pEffect;							// �G�t�F�N�g�p�|�C���^
	LPDIRECT3DVOLUMETEXTURE9 m_pNoiseVolumeTexture;	// �m�C�Y�e�N�X�`��
	LPDIRECT3DCUBETEXTURE9 m_pEnvironmentTexture;	// �L���[�u�e�N�X�`��
	float m_fFileTime;										// �t�@�C���̌o�ߎ���
	D3DXMATRIXA16 m_MatPlayer;								// �v���C���[�̃}�g���N�X
	CWave *m_pWave;											// �g�̈ړ�
};

#endif