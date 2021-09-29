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
// Author : Sugawara Tsukasa
//=============================================================================
#include "enemy.h"

//=============================================================================
// �G�D�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CEnemy_Ship : public CEnemy
{
public:
	enum PARTS
	{
		PARTS_SHIP = 0,
		PARTS_BATTERY,		// �C��
		PARTS_MAX
	};
	CEnemy_Ship(PRIORITY Priority = PRIORITY_ENEMY);				// �R���X�g���N�^
	~CEnemy_Ship();													// �f�X�g���N�^
	static CEnemy_Ship *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

private:
	void Move(void);												// �ړ�����
	void Attack(void) override;										// �U������
};
#endif