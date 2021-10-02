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

//=======================================================================================
// �O���錾
//=======================================================================================
class CCamera;
class CCameraGame;
class CLight;
class CMeshField;
class CBg;
class CPlayer;
class CMap;
class CBoss_Shark;

//=======================================================================================
// �Q�[���N���X
//=======================================================================================
class CGame : public CModeBase
{
public:
	enum ENEMY_OBSTACLE_TYPE
	{
		ENEMY_OBSTACLE_TYPE_MIN = 0,
		ENEMY_OBSTACLE_TYPE_SHIP,
		ENEMY_OBSTACLE_TYPE_SCAFFOLDING,
		ENEMY_OBSTACLE_TYPE_TORPEDO,
		ENEMY_OBSTACLE_TYPE_ROCK,
		ENEMY_OBSTACLE_TYPE_MAX
	};
	//=============================================================================
	//�@�G�����t�@�C�����̍\����
	//=============================================================================
	struct ENEMY_FILE_DATA
	{
		D3DXVECTOR3 Pos;		// �ʒu�̃I�t�Z�b�g���
		D3DXVECTOR3 Rot;		// �����̃I�t�Z�b�g���
		ENEMY_OBSTACLE_TYPE Type;		// ��ޏ��
	};

	CGame();		// �R���X�g���N�^
	~CGame();		// �f�X�g���N�^

	HRESULT Init(void);								// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��
	void SetGame(void);								// �Q�[���̐ݒ�

	void CreatePlayer(void);						// �v���C���[�̐���	
	void CreateMap(void);							// �}�b�v�̐���	
	void CreateGround(void);						// �n�ʂ̐���
	void CreateEnemy_Obstacle(string pEnemyFile);	// �G�����֐�
	void RoadEnemyFile(string pEnemyFile);			// �G�̐����t�@�C���ǂݍ���
	void DrawPlayerPos(void);						// �v���C���[�̈ʒu��������
	void CreateBossMap(void);						// �{�X�}�b�v����
	void BossTransition(void);						// �{�X��J��
	void ModeTransition(void);						// ���[�h�J��
	void Boss_Enemy_Create(void);					// �{�X��G����
													// Set�֐�
	void SetbBoss(bool bBoss) { m_bBoss = bBoss; }	// �{�X��̔���
	void SetbBossTransition(bool bBossTransition) { m_bBossTransition = bBossTransition; }	// �{�X��J�ڂ̔���

	// Get�֐�
	CCamera *GetCamera(void)		{ return (CCamera*)m_pCamera; }	// �J�����̃|�C���^���
	CLight *GetLight(void)			{ return m_pLight; }			// ���C�g�̃|�C���^���
	CPlayer *GetPlayer(void)		{ return m_pPlayer; }			// �v���C���[�̃|�C���^���
	CMap *GetMap(void)				{ return m_pMap; }				// �}�b�v�̃|�C���^�擾
	bool GetbBoss(void)				{ return m_bBoss; }				// �{�X��bool�擾
	bool GetbBossTransition(void)	{ return m_bBossTransition; }	// �{�X�J�ڔ���擾

private:
	// �|�C���^
	CCameraGame *m_pCamera;					// �J�����̃|�C���^	
	CLight *m_pLight;						// ���C�g�̃|�C���^
	CMeshField *m_pMeshField;				// ���b�V���t�B�[���h�̃|�C���^
	CBg *m_pBg;								// �w�i�̃|�C���^
	CPlayer *m_pPlayer;						// �v���C���[�̃|�C���^
	CMap * m_pMap;							// �}�b�v�̃|�C���^
	CBoss_Shark *m_pBoss_Shark;				// �{�X�̃|�C���^
	ENEMY_FILE_DATA *m_pEnemyFileData;		// �G�̃t�@�C���f�[�^
	int m_nEnemyNum;						// �G��
	bool m_bGameEnd;						// �Q�[���̃G���h�t���O
	bool m_bBossTransition;					// �{�X��ɑJ�ڂ�����
	bool m_bBoss;							// �{�X�킩

	LPD3DXFONT m_pFont;						// �f�o�b�N�p�t�H���g
};
#endif