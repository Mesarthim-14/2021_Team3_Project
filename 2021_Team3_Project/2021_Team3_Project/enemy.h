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
	//=============================================================================
	// XZ�̍\����
	//=============================================================================
	struct Vec2
	{
		float x;
		float z;
	};
	//=============================================================================
	//�@�G�̎��
	//=============================================================================
	enum TYPE
	{
		TYPE_NORMAL = 0,
		TYPE_BOSS
	};
	//=============================================================================
	//�@����̎��
	//=============================================================================
	enum ATTACK_DECISION_TYPE
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
	void Hit(int nDamage);										// �q�b�g����
	static CEnemy*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// �N���G�C�g

	virtual void Death(void);									// ���񂾂Ƃ��̏���
	virtual void Attack(void);									// �U���̏���
	virtual void Move(void);									// �ړ��̏���

	// �Z�b�^�[
	void SetAttackDecision(ATTACK_DECISION_TYPE Attck_Decision_Type) {m_Attack_Decision_Type = Attck_Decision_Type;}	// �U������ݒ菈��
	void SetType(TYPE type) { m_Type = type; }
	void SetHit(bool bHit) { m_bHit = bHit; }
	// �Q�b�^�[
	ATTACK_DECISION_TYPE GetAttackDecision(void)	{ return m_Attack_Decision_Type; }		// �U������擾����
	bool Get_bAttackDecision(void)						{ return m_bAttack_Decision; }		// �U������擾����
	int &GetAttackCount(void)							{ return m_AttackCount; }			// �U���̃J�E���g
	bool GetHit(void) { return m_bHit; }													// �q�b�g����擾
private:
	ATTACK_DECISION_TYPE m_Attack_Decision_Type; // �U������̎��
	bool m_bAttack_Decision;					 // �U������p
	int m_AttackCount;							 // �U���J�E���g
	TYPE m_Type;								 // �G�̎��
	bool m_bHit;								 // �q�b�g�����ꍇ
};
#endif