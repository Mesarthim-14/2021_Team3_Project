#ifndef _MODELANIME_H_
#define _MODELANIME_H_
//=============================================================================
//
// �K�w�\���p�̃��f������ [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "xfile.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_OLD_MTX_WORLD		(5)			// ���[���h�}�g���N�X�̔z��

//=============================================================================
// �O���錾
//=============================================================================
class CShadow;

//=============================================================================
//�K�w���f���N���X
//=============================================================================
class CModelAnime
{
public:
	CModelAnime();		// �R���X�g���N�^
	~CModelAnime();		// �f�X�g���N�^

	static CModelAnime *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXfile::MODEL model);	// �C���X�^���X����

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXfile::MODEL model);	// ����������
	void Draw(D3DXVECTOR3 rot);												// �`�揈��
	void HasPtrDelete(void);												// �ێ��|�C���^�̊J������
	void ShadowDraw(D3DXVECTOR3 rot);										// �e�̕`��

																			// Set�֐�
	void SetParent(CModelAnime *pParent);									// �e�̐ݒ�
	void SetRot(const D3DXVECTOR3 rot);										// �����ݒ�
	void SetPosAnime(const D3DXVECTOR3 posAnime);							// �A�j���[�V�����p�[�c�̍��W
	void SetRotAnime(const D3DXVECTOR3 rotAnime);
	void SetModel(CXfile::MODEL model);										// ���f�����̐ݒ�
	D3DXMATRIX SetShadowInfo(D3DXVECTOR3 rot, D3DXMATRIX pParent);          // �e�̏��̐ݒ�
	void SetRotCalculation(bool bFlag) { m_bRotCalculation = bFlag; }		// �p�x�̌v�Z�t���O�̐ݒ�

																			// Get���
	D3DXVECTOR3 GetPos(void)const;											// ���W���
	D3DXVECTOR3 GetPosAnime(void)const;										// �A�j���[�V�������W���
	D3DXVECTOR3 GetRot(void)const;											// �p�x�̏��
	D3DXVECTOR3 GetRotAnime(void)const;										// �A�j���[�V�����p�x���
	D3DXMATRIX GetMtxWorld(void);											// ���[���h�}�g���N�X���
	D3DXMATRIX GetOldMtxWorld(void);										// �Â����[���h�}�g���N�X�̏��
	LPD3DXMESH GetMesh(void) { return m_model.pMesh; }						// ���f�����擾
private:
	D3DXVECTOR3 m_pos;								// �ʒu
	D3DXVECTOR3 m_rot;								// ����
	D3DXVECTOR3 m_posAnime;							// �A�j���[�V�����p�̈ʒu
	D3DXVECTOR3 m_rotAnime;							// �A�j���[�V�����p�̌���
	D3DXMATRIX m_mtxWorld;							// ���[���h�}�g���b�N�X
	CModelAnime *m_pParent;							// �e���̃|�C���^
	D3DXMATRIX m_OldMtxWorld;						// �Â����[���h���W
	D3DXMATRIX m_OldMtxWorld1[MAX_OLD_MTX_WORLD];	// 5�t���[���܂ł̌Â����W
	CXfile::MODEL m_model;							// ���f�����

													// �e�̐����p
	CShadow *m_pShadow;		// �e�̃|�C���^
	bool m_bRotCalculation;	// �p�x�̌v�Z�t���O
};

#endif 