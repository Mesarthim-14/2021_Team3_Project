#ifndef _SCENE3D_H_
#define _SCENE3D_H_
//=============================================================================
//
// 3D�|���S���N���X�w�b�_�[ [scene3D.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "scene_base.h"

//=========================================================================
// 3D�|���S���N���X
//=========================================================================
class CScene3D :public CSceneBase
{
public:
	CScene3D(PRIORITY Priority = PRIORITY_EFFECT);				// �R���X�g���N�^
	virtual ~CScene3D();										// �f�X�g���N�^
	
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	virtual void Uninit(void);									// �I������
	virtual void Update(void);									// �X�V����
	virtual void Draw(void);									// �`�揈��
	void CreateVertex(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// ���_�̐ݒ�

	// Set�֐�
	void SetMove(D3DXVECTOR3 move);								// �ړ���
	void SetPosision(D3DXVECTOR3 pos);							// ���W�̍X�V
	void SetAlpha(bool bAlpha);									// �A���t�@�e�X�g
	void SetAlphaNum(int nAlphaNum);							// �A���t�@�e�X�g�̒l
	void SetBlend(bool bBlend);									// ���Z����
	void SetInverse(bool bInverse);								// �t�s����s����
	void SubAlpha(float fAlphaNum);								// �����x�̌��Z
	void InitAnimation(D3DXVECTOR2 TexInfo, int nLoop);			// �A�j���[�V������񏉊���
	void UpdateAnimation(void);									// �A�j���[�V�����̍X�V
	void ScaleUp(float fScale);									// �g�又��
	void SetColor(D3DXCOLOR color);								// �J���[�̐ݒ�

private:
	D3DXMATRIX	m_mtxWorld;		// ���[���h�}�g���N�X
	D3DXVECTOR3 m_move;			// �ړ���
	int m_nCountAnim;			// �A�j���[�V�����e�N�X�`��
	int m_nCountAnimPattern;	// �A�j���[�V�����̃p�^�[��
	int m_nCounterAnim;			// �A�j���[�V�����̃J�E���^�[
	int m_nPatternAnim;			// �A�j���[�V�����̃p�^�[����
	int m_nLoop;				// ���[�v���邩�ǂ���
	int m_nLife;				// ���C�t
	int m_nAlphaTestNum;		// �����̒l
	float m_fScaleNum;			// �g��l
	float m_fAlphaNum;			// �����x
	bool m_bAlpha;				// �������g���t���O
	bool m_bBlend;				// ���Z����
	bool m_bInverse;			// �t�s��̃t���O
};
#endif