#ifndef _BOSS_SHARK_H_
#define _BOSS_SHARK_H_
//=============================================================================
//
// �{�X�T�� [boss_shark.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "enemy.h"

//=============================================================================
// �G�l�~�[�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CBoss_Shark : public CEnemy
{
public:
	enum PARTS
	{
		PARTS_BODY = 0,		// ��
		PARTS_HEAD,			// ��
		PARTS_CHIN,			// �{
		PARTS_UNDER_BODY,	// �����g
		PARTS_MAX
	};
	enum MOTION_STATE
	{
		MOTION_STATE_IDLE = 0,
		MOTION_STATE_BYTE,
		MOTION_STATE_SHARK_BULLET
	};
	CBoss_Shark(PRIORITY Priority = PRIORITY_ENEMY);				// �R���X�g���N�^
	~CBoss_Shark();													// �f�X�g���N�^
	static CBoss_Shark *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	bool GetEnd(void) { return m_bEnd; }							// �I���擾
private:
	void Attack(void)override;										// �U������
	void Death(void)override;										// ���S����
	void ByteAttack(void);											// ���݂��U��
	void SharkBulletAttack(void);									// �T���̒e�U��
	void MotionUpdate(void);										// ���[�V��������
	void UpdateRot(void);											// �����X�V
	void Enemy_Create(void);										// �G��������

	MOTION_STATE m_MotionState;	// ���[�V�����̏��
	bool m_bEnd;				// �I��
	bool m_bEnemyCreate;		// �G����
	bool m_bRot;				// ��������
};
#endif