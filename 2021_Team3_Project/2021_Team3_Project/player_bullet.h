#ifndef _PLAYER_BULLET_H_
#define _PLAYER_BULLET_H_
//=============================================================================
// �v���C���[�̒e [player_bullet.h]
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
class CPlayer_Bullet : public CBullet
{
public:
	CPlayer_Bullet(PRIORITY Priority = PRIORITY_MODEL);		// �R���X�g���N�^
	~CPlayer_Bullet();											// �f�X�g���N�^
	static CPlayer_Bullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

private:
	void Collision(void);										// �����蔻��
};
#endif