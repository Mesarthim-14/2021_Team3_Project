#ifndef _ENEMY_NORAMLBULLET_H_
#define _ENEMY_NORAMLBULLET_H_
//=============================================================================
// �v���C���[�̒e [enemy_bullet.h]
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
class CEnemy_Normal_Bullet : public CEnemy_Bullet
{
public:
	CEnemy_Normal_Bullet(PRIORITY Priority = PRIORITY_MODEL);				// �R���X�g���N�^
	~CEnemy_Normal_Bullet();												// �f�X�g���N�^
	static CEnemy_Normal_Bullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);							// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��
private:
};
#endif