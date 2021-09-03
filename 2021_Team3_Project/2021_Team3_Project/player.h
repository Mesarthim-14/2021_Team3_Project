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

	void Death(void);											// ���S�֐�
	void Move(void);											// �ړ�����
	void Pad2Move(void);										// 2�R���g���[���[�̈ړ�
	void Attack(void);											// �U���̊֐�
	void Pad2Attack(void);										// 2�R���g���[���[�̍U��
	void KeyboardMove(void);									// �L�[�{�[�h�ړ�
	void Collision(void);										// �����蔻��
	void CrossCollision(void);									// �O�ϓ����蔻��
	void RayCollision(void);									// ���C�̓����蔻��
private:
	D3DXVECTOR3 m_rotDest;							// ��](�ڕW�l)
	bool m_bMove;									// �����Ă���t���O
	int m_nAttackCount_R;							// �E�U���J�E���g
	int m_nAttackCount_L;							// ���U���J�E���g
	PAD_TYPE m_PadType;								// �p�b�h�^�C�v
	bool m_bBack;									// ���Ɉړ����Ă��邩
};
#endif