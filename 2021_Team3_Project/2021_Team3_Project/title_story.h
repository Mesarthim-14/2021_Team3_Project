#ifndef _TITLE_STORY_H_
#define _TITLE_STORY_H_
//=============================================================================
//
// �^�C�g���X�g�[���[�N���X [title_story.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode_base.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//=============================================================================
// �N���X��`
//=============================================================================
class CTitleStory : public CModeBase
{
public:
	CTitleStory();						// �R���X�g���N�^
	~CTitleStory();						// �f�X�g���N�^

	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(void);					// �`�揈��
	void ModeTransition(void);			// ���[�h�J��
	void SkipSentence(void);			// ���͂̃X�L�b�v

	void CreateBg(void);			// ���͂̃X�L�b�v
	void CreateSentence0(void);		// ���͂̐���
	void CreateSentence1(void);		// ���͂̐���
	void CreateSentence2(void);		// ���͂̐���
	void CreateSentence3(void);		// ���͂̐���

private:
	vector<CScene2D*> m_pObject2D;						// 2D�I�u�W�F�N�g
	int m_nSentenceNum;									// ���͂̔ԍ�
	int m_nTimeCounter;									// ���Ԃ̃J�E���g
	bool m_bEnd;										// �J�ډ\�t���O

	// ���͂̐����𑣂��֐��|�C���^
	typedef void(CTitleStory::*SENTENCE_FUNC)();
	vector<SENTENCE_FUNC> m_CreateSentence = 
	{ &CTitleStory::CreateSentence0 , &CTitleStory::CreateSentence1,
		&CTitleStory::CreateSentence2, &CTitleStory::CreateSentence3 };

};
#endif