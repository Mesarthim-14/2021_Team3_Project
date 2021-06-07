#ifndef _ENEMYSHIP_H_
#define _ENEMYSHIP_H_
//=============================================================================
//
// �G�̑D [enemy_ship.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy.h"

//=============================================================================
// �G�l�~�[�N���X
//=============================================================================
class CEnemy_Ship : public CEnemy
{
public:

	CEnemy_Ship(PRIORITY Priority = PRIORITY_CHARACTER);			// �R���X�g���N�^
	~CEnemy_Ship();													// �f�X�g���N�^
	static CEnemy_Ship *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

private:
	void Move(void);		// �ړ�����
};
#endif