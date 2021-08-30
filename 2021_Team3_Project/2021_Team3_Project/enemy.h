#ifndef _ENEMY_H_
#define _ENEMY_H_
//=============================================================================
//
// �G�l�~�[�N���X�w�b�_�[ [enemy.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"
#include "modelanime.h"

//=============================================================================
// �G�l�~�[�N���X
//=============================================================================
class CEnemy : public CCharacter
{
public:
	struct Vec2
	{
		float x;
		float z;
	};
	//=============================================================================
	//�@���[�V������Ԃ̗񋓌^
	//=============================================================================
	enum ENEMY_MOTION_STATE
	{
		ENEMY_MOTION_NONE = -1,
		ENEMY_MOTION_IDOL,			// �A�C�h�����[�V����
		ENEMY_MOTION_MAX			// ���[�V�����ő吔
	};

	enum ENEMY_ATTACK_DECISION_TYPE
	{
		ATTACK_DECISION_FAN = -1,	// ��
		ATTACK_DECISION_CIRCLE,		// �~
		ATTACK_DECISION_MAX
	};

	CEnemy(PRIORITY Priority = PRIORITY_ENEMY);					// �R���X�g���N�^
	~CEnemy();													// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	void UpdateState(void);										// �v���C���[�̏��
	void FanDecision(void);										// ��̔���
	void CircleDecision(void);									// �~�̔���
	static CEnemy*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// �N���G�C�g

	virtual void Death(void);									// ���񂾂Ƃ��̏���
	virtual void Attack(void);									// �U���̏���
	virtual void Move(void);									// �ړ��̏���

	// �Z�b�^�[
	void SetAttackDecision(ENEMY_ATTACK_DECISION_TYPE Attck_Decision_Type) {m_Attack_Decision_Type = Attck_Decision_Type;}	// �U������ݒ菈��

	// �Q�b�^�[
	ENEMY_ATTACK_DECISION_TYPE GetAttackDecision(void) { return m_Attack_Decision_Type; }	// �U������擾����
	bool Get_bAttackDecision(void) { return m_bAttack_Decision; }							// �U������擾����
private:
	ENEMY_ATTACK_DECISION_TYPE m_Attack_Decision_Type;			// �U������̎��
	bool m_bAttack_Decision;									// �U������p
};
#endif