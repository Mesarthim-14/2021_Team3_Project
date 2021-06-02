#ifndef _SCENE2D_H_
#define _SCENE2D_H_
//=======================================================================================
// 
// 2D�|���S���`��N���X���� [scene2d.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "scene_base.h"

//=======================================================================================
// �V�[��2D�N���X��`
//=======================================================================================
class CScene2D : public CSceneBase
{
public:
	CScene2D(PRIORITY Priority = PRIORITY_0);							// �R���X�g���N�^
	~CScene2D();														// �f�X�g���N�^

	static CScene2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);					// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��

	void InitAnimation(int nCounterAnim, int nPatternAnim, int nLoop);	// �A�j���[�V������񏉊���
	void InitScroll(int nSpeed, float fDivision);						// �摜�X�N���[���̐ݒ�
	void UpdateAnimation(void);											// �A�j���[�V�����̍X�V
	void UpdateScroll(void);											// �摜�X�N���[���̍X�V
	void ScaleUp(float fScaleUp);										// �g��֐�
	void FlashPolygon(int nFlashFlame);									// �|���S���̓_��

	// Set�֐�
	void SetCol(D3DXCOLOR col);											// �F�̐ݒ�
	void SetRotation(float rotasion);									// ��]�̐ݒ�
	void SetScale(const float &fScale);									// �g��̒l�ݒ�
	void SetSubFlashNum(float fSubNum) { m_fSubNum = fSubNum; }			// �_�ł̒l�ݒ�

	// Get�֐�
	float GetScale(void) { return m_fScaleNum; }						// �g��̒l���

private:
	int m_nCountAnim;			// �A�j���[�V�����e�N�X�`��
	int m_nCountAnimPattern;	// �A�j���[�V�����̃p�^�[��
	int m_nCounterAnim;			// �A�j���[�V�����̃J�E���^�[
	int m_nPatternAnim;			// �A�j���[�V�����̃p�^�[����
	int m_nSpeedTexture;		// �e�N�X�`���̈ړ����x
	int m_nLoop;				// ���[�v���邩�ǂ���
	float m_fDivisionCounter;	// �X�N���[���̃J�E���^�[
	float m_fDivisionBaseNum;	// �X�N���[���̈ړ���
	float m_fRotasion;			// ��]�p�ϐ�
	float m_fScaleNum;			// �g��p�ϐ�
	float m_fSubFlashNum;		// �|���S���̓_���p
	float m_fSubNum;			// �|���S���̓_���p
	int m_nFlashFlame;			// �_���p�̃J�E���^�[
	bool m_bDisappearFlag;		// �_�ŗp�̃t���O
};

#endif // !_SCENE2D_H_