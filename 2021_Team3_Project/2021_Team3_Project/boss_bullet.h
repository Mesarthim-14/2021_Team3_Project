#ifndef _BOSS_BULLET_H_
#define _BOSS_BULLET_H_
//=============================================================================
// �{�X�̒e [boss_bullet.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "enemy_bullet.h"

//=============================================================================
// �e�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CBoss_Bullet : public CEnemy_Bullet
{
public:
	enum TYPE
	{
		TYPE_NORMAL = 0,
		TYPE_RANDOM
	};
	CBoss_Bullet(PRIORITY Priority = PRIORITY_MODEL);							// �R���X�g���N�^
	~CBoss_Bullet();															// �f�X�g���N�^
	static CBoss_Bullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,TYPE type);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);								// ����������
	void Uninit(void);															// �I������
	void Update(void);															// �X�V����
	void Draw(void);															// �`�揈��
	static void CreateBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// �e����
private:
	float m_fAngle;	// �p�x
	TYPE m_Type;	// ���
};
#endif