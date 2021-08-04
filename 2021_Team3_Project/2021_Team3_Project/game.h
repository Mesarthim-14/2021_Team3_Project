#ifndef _GAME_H_
#define _GAME_H_
//=======================================================================================
//
// �Q�[���̏��� [game.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "mode_base.h"

//=======================================================================================
// �}�N����`
//=======================================================================================
#define MAX_PLAYER (1)			// �v���C���[�̐�

//=======================================================================================
// �O���錾
//=======================================================================================
class CCamera;
class CLight;
class CMeshField;
class CBg;
class CPlayer;
class CMap;
//=======================================================================================
// �Q�[���N���X
//=======================================================================================
class CGame : public CModeBase
{
public:
	CGame();		// �R���X�g���N�^
	~CGame();		// �f�X�g���N�^

	HRESULT Init(void);				// ����������
	void Uninit(void);				// �I������
	void Update(void);				// �X�V����
	void Draw(void);				// �`�揈��
	void SetGame(void);				// �Q�[���̐ݒ�

	void CreatePlayer(void);		// �v���C���[�̐���	
	void CreateMap(void);			// �}�b�v�̐���	
	void CreateGround(void);		// �n�ʂ̐���
	void CreateEnemy(void);			// �G�����֐�

	CCamera *GetCamera(void);	// �J�����̃|�C���^���
	CLight *GetLight(void);		// ���C�g�̃|�C���^���
	CPlayer *GetPlayer(void);	// �v���C���[�̃|�C���^���
	CMap *GetMap(void) { return m_pMap; }	// �}�b�v�̃|�C���^�擾
private:	
	CCamera *m_pCamera;			// �J�����̃|�C���^	
	CLight *m_pLight;			// ���C�g�̃|�C���^
	CMeshField *m_pMeshField;	// ���b�V���t�B�[���h�̃|�C���^
	CBg *m_pBg;					// �w�i�̃|�C���^
	CPlayer *m_pPlayer;			// �v���C���[�̃|�C���^
	CMap * m_pMap;				// �}�b�v�̃|�C���^
	LPD3DXFONT m_pFont;			// �f�o�b�N�p�t�H���g
	int m_nTimeCounter;			// �Q�[���̃J�E���^�[
	bool m_bGameEnd;			// �Q�[���̃G���h�t���O
};
#endif