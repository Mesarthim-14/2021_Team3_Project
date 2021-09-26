#ifndef _SCENE_H_
#define _SCENE_H_
//=============================================================================
//
// �I�u�W�F�N�g���� [scene.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_NUM (4112)

//=============================================================================
// �V�[���N���X
//=============================================================================
class CScene
{
public:
	//=========================================================================
	//�`��̗D�揇�ʂ̗񋓌^
	//=========================================================================
	enum PRIORITY
	{
		PRIORITY_0 = 0,
		PRIORITY_1,
		PRIORITY_OBSTACLE,	// ��Q��
		PRIORITY_MODEL,		// ���f��
		PRIORITY_CHARACTER,	// �L�����N�^�[
		PRIORITY_ENEMY,		// �G
		PRIORITY_TORPEDO,	// ����
		PRIORITY_MAP,		// �}�b�v
		PRIORITY_EFFECT,	// �G�t�F�N�g
		PRIORITY_PARTICLE,	// �G�t�F�N�g
		PRIORITY_3D_UI,		// UI
		PRIORITY_UI,		// UI
		PRIORITY_FADE,		// FADE
		PRIORITY_MAX		// �D�揇�ʂ̍ő吔
	};

	CScene(PRIORITY Priority = PRIORITY_0);						// �R���X�g���N�^
	virtual ~CScene();											// �f�X�g���N�^
	static void ReleaseAll(void);								// �S�ẴI�u�W�F�N�g�������[�X
	static void UpdateAll(void);								// �S�ẴI�u�W�F�N�g���X�V
	static void DrawAll(void);									// �S�ẴI�u�W�F�N�g��`��

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot) = 0;	// ����������
	virtual void Uninit(void) = 0;								// �I������
	virtual void Update(void) = 0;								// �X�V����
	virtual void Draw(void) = 0;								// �`�揈��

	CScene *GetTop(int nCount);									// �V�[���̏��󂯎��
	CScene *GetNext(void);										// ���̏����󂯎��
	static void SetPause(bool Pause);							// �|�[�Y�̏��
	void DeathRelease(void);									// ���S�t���O�̃����[�X

protected:
	void Release(void);					// �I�u�W�F�N�g���J��

private:
	static CScene *m_pTop[PRIORITY_MAX];	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CScene *m_pCur[PRIORITY_MAX];	// ���݂̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pPrev;						// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pNext;						// ���̃I�u�W�F�N�g�ւ̃|�C���^
	PRIORITY m_nPriority;					// �`��̗D�揇��
	bool m_bDeath;							// ���S�t���O
	bool m_bLate;							// �`���x�点�鏈��
	static bool m_bPause;					// �|�[�Y�̏��
};

#endif