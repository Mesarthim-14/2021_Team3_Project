#ifndef _ENEMY_SCAFFOLDING_H_
#define _ENEMY_SCAFFOLDING_H_
//=============================================================================
//
// �G�̘E [enemy_scaffolding.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "enemy.h"

//=============================================================================
// �E�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CEnemy_Scaffolding : public CEnemy
{
public:
	enum PARTS
	{
		PARTS_SHIP = 0,
		PARTS_BATTERY,		// �C��
		PARTS_MAX
	};
	CEnemy_Scaffolding(PRIORITY Priority = PRIORITY_ENEMY);					// �R���X�g���N�^
	~CEnemy_Scaffolding();													// �f�X�g���N�^
	static CEnemy_Scaffolding *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);							// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��

private:
	void Attack(void) override;		// �U������
};
#endif