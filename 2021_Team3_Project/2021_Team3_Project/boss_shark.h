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
		MOTION_STATE_BYTE
	};
	CBoss_Shark(PRIORITY Priority = PRIORITY_ENEMY);				// �R���X�g���N�^
	~CBoss_Shark();													// �f�X�g���N�^
	static CBoss_Shark *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
	void Attack(void);												// �U������
	void ByteAttack(void);											// ���݂��U��
	void MotionUpdate(void);										// ���[�V��������

	int m_nAttackCount;												// �U���J�E���g
	MOTION_STATE m_MotionState;										// ���[�V�����̏��
};
#endif