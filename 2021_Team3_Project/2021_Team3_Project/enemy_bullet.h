#ifndef _ENEMY_BULLET_H_
#define _ENEMY_BULLET_H_
//=============================================================================
// �v���C���[�̒e [enemy_bullet.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "bullet.h"

//=============================================================================
// �e�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CEnemy_Bullet : public CBullet
{
public:
	enum STATE	// ���
	{
		STATE_UP = 0,
		STATE_DOWN,
	};
	CEnemy_Bullet(PRIORITY Priority = PRIORITY_CHARACTER);		// �R���X�g���N�^
	~CEnemy_Bullet();											// �f�X�g���N�^
	static CEnemy_Bullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
private:
	void Move(void);											// �ړ�����
	void Collision(void);										// �����蔻�菈��

	D3DXVECTOR3 m_PlayerPos;									// �v���C���[�̈ʒu
	STATE m_State;												// ���
};
#endif