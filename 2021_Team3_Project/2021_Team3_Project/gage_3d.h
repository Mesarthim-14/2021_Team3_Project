//=============================================================================
// 3D�Q�[�W [gage_3d.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _GAGE_3D_H_
#define _GAGE_3D_H_
//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "scene_base.h"

//=============================================================================
// �Q�[�W�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CGage_3D :public CSceneBase
{
public:
	CGage_3D(PRIORITY nPriority = PRIORITY_UI);								// �R���X�g���N�^
	~CGage_3D();															// �f�X�g���N�^
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// �����������֐�
	virtual void Uninit(void);												// �I�������֐�
	virtual void Update(void);												// �X�V�����֐�
	virtual void Draw(void);												// �`�揈���֐�

	// Set�֐�
	void SetPosition(const D3DXVECTOR3 pos);								// �ʒu�ݒ菈���֐�
	void SetColor(const D3DXCOLOR col);										// �F�ݒ菈���֐�
	void SetAlpha(bool bAlpha) { m_bAlpha = bAlpha; }						// �A���t�@�e�X�g�̐ݒ�֐�
	void SetAlphaNum(int nAlphaNum) { m_nAlphaNum = nAlphaNum; }			// �A���t�@�e�X�g�̒l�ݒ�֐�
	void SetBlend(bool bBlend) { m_bBlend = bBlend; }						// ���Z�����ݒ�֐�
	void SetGageNum(int nGageNum);											// �Q�[�W�̒l�ݒ菈���֐�
	void SetMaxGageNum(int nMaxGageNum);									// �Q�[�W�̍ő�l�ݒ�
private:
	D3DXMATRIX m_mtxWorld;				// ���[���h���W
	int m_nGageNum;						// �Q�[�W�̒l
	float m_fMaxGageNum;				// �Q�[�W�̍ő�
	float m_fGageNum;					// �Q�[�W�̒l
	int m_nAlphaNum;					// �A���t�@�e�X�g�̒l
	bool m_bAlpha;						// �A���t�@�e�X�g���g�p���邩
	bool m_bBlend;						// ���Z����
};
#endif