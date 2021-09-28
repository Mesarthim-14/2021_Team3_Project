#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// �v���C���[�N���X�w�b�_�[ [player.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"
#include "modelanime.h"
#include "effect.h"

//=============================================================================
//�@���[�V������Ԃ̗񋓌^
//=============================================================================
enum PARTS_NUM
{
	PARTS_NUM_NONE = -1,
	PARTS_NUM_WAIST,			// [0]��
	PARTS_NUM_MAX				// ���[�V�����ő吔
};

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer : public CCharacter
{
public:
	//=============================================================================
	//�@��Ԃ̗񋓌^
	//=============================================================================
	enum PLAYER_STATE
	{
		PLAYER_STATE_NONE = 0,		// �����u
		PLAYER_STATE_NORMAL,		// �ʏ���
		PLAYER_STATE_DEAD,			// ���S���
		PLAYER_STATE_MAX			// �ő吔
	};

	//=============================================================================
	//�@���[�V������Ԃ̗񋓌^
	//=============================================================================
	enum MOTION_STATE
	{
		MOTION_NONE = -1,
		MOTION_IDOL,				// �A�C�h�����[�V����
		MOTION_MAX					// ���[�V�����ő吔
	};

	//=============================================================================
	//�@�p�b�h�̎�ނ̗񋓌^
	//=============================================================================
	enum PAD_TYPE
	{
		PAD_TYPE_1P = 0,
		PAD_TYPE_2P,
		PAD_TYPE_MAX
	};

	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);			// �R���X�g���N�^
	~CPlayer();													// �f�X�g���N�^

	static CPlayer*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// �N���G�C�g

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
	void UpdateState(void);										// �v���C���[�̏��
	void PlayerControl(void);									// �v���C���[�̐���
	void UpdateRot(void);										// �p�x�̍X�V����

	void Hit(int nDamage);										// �q�b�g�����֐�
	void Death(void);											// ���S�֐�
	void Move(void);											// �ړ�����
	void Pad2Move(void);										// 2�R���g���[���[�̈ړ�
	void Attack(void);											// �U���̊֐�
	void Pad2Attack(void);										// 2�R���g���[���[�̍U��
	void KeyboardMove(void);									// �L�[�{�[�h�ړ�
	void Collision(void);										// �����蔻��
	void CrossCollision(void);									// �O�ϓ����蔻��
	void SinkEnd(void);											// �D�����ޏ���

	void CreateSmoke(void);										// �������֐�
	void CreateWoodEP(void);									// �؍ސ����֐�
	void CreateSplash(void);									// �����Ԃ������֐�
	void CreateExplosion(void);									// ���������֐�
	void CreateWave(void);										// �g�����֐�

	void Knock_Back(void);										// �m�b�N�o�b�N����
	void PaddleRotateR(float fRotate);							// �p�h���̉�]
	void PaddleRotateL(float fRotate);							// �p�h���̉�]
	void PaddleRotFix(void);									// �p�h���̊p�x��␳

	//�W���C�X�e�B�b�N�̍ŒZ�p�x����
	void LStickAngle(float fangle_L);
	void RStickAngle(float fangle_R);

	void SetHitFlag(bool bHitFlag) { m_bHitFlag = bHitFlag; }
	bool GetHitFlag(void) { return m_bHitFlag; }
	bool GetEnd(void) { return m_bEnd; }

	CModelAnime* GetShip(void);
	CModelAnime* GetRightPaddle(void);
	CModelAnime* GetLeftPaddle(void);


private:
	D3DXVECTOR3 m_rotDest;							// ��](�ڕW�l)
	int m_nAttackCount_R;							// �E�U���J�E���g
	int m_nAttackCount_L;							// ���U���J�E���g
	int m_nRockHitCount;							// ��Ƀq�b�g�����J�E���g
	int m_nSinkCounter;								// ���ނƂ��̃J�E���g
	PAD_TYPE m_PadType;								// �p�b�h�^�C�v
	D3DXVECTOR3 m_Reflection_Vec;					// ���˃x�N�g��
	bool m_bBack;									// ���Ɉړ����Ă��邩
	bool m_bMove;									// �����Ă���t���O
	bool m_bKnock_Back;								// �m�b�N�o�b�N
	float m_fdisAngle_L;							// L�X�e�B�b�N�ߋ��l
	float m_fdisAngle_R;							// R�X�e�B�b�N�ߋ��l
	bool m_bHitFlag;								// �_���[�W���󂯂��t���O
	bool m_bDeath;									// ���S�t���O
	bool m_bEnd;									// �v���C���[�I���̃t���O
};
#endif