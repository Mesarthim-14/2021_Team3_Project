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

	HRESULT Init(void);						// ����������
	void Uninit(void);						// �I������
	void Update(void);						// �X�V����
	void Draw(void);						// �`�揈��
	void SetGame(void);						// �Q�[���̐ݒ�

	void CreatePlayer(void);				// �v���C���[�̐���	
	void CreateMap(void);					// �}�b�v�̐���	
	void CreateGround(void);				// �n�ʂ̐���
	void CreateEnemy_Obstacle(void);		// �G�����֐�
	void RoadEnemyFile(string pEnemyFile);	// �G�̐����t�@�C���ǂݍ���

	// Get�֐�
	CCamera *GetCamera(void)	{ return m_pCamera; }	// �J�����̃|�C���^���
	CLight *GetLight(void)		{ return m_pLight; }	// ���C�g�̃|�C���^���
	CPlayer *GetPlayer(void)	{ return m_pPlayer; }	// �v���C���[�̃|�C���^���
	CMap *GetMap(void)			{ return m_pMap; }		// �}�b�v�̃|�C���^�擾
private:
	// �֐�
	void DrawPlayerPos(void);				// �v���C���[�̈ʒu��������

	// �|�C���^
	CCamera *m_pCamera;						// �J�����̃|�C���^	
	CLight *m_pLight;						// ���C�g�̃|�C���^
	CMeshField *m_pMeshField;				// ���b�V���t�B�[���h�̃|�C���^
	CBg *m_pBg;								// �w�i�̃|�C���^
	CPlayer *m_pPlayer;						// �v���C���[�̃|�C���^
	CMap * m_pMap;							// �}�b�v�̃|�C���^

	ENEMY_FILE_DATA *m_pEnemyFileData;		// �G�̃t�@�C���f�[�^
	bool m_bGameEnd;						// �Q�[���̃G���h�t���O
	int m_nEnemyNum;						// �G��

	// �f�o�b�N�p
	LPD3DXFONT m_pFont;						// �f�o�b�N�p�t�H���g
};
#endif