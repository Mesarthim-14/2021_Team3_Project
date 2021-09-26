//=============================================================================
// �G�̍U����� [enemy_attack_arrow_polygon.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _ENEMY_ATTACK_ARROW_POLYGON_H_
#define _ENEMY_ATTACK_ARROW_POLYGON_H_
//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "billboard.h"
#include "bullet.h"
//=============================================================================
// �}�b�v�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CEnemy_Attack_Arrow_Polygon : public CBillboard
{
public:
	CEnemy_Attack_Arrow_Polygon(PRIORITY Priority = PRIORITY_UI);										// �R���X�g���N�^
	~CEnemy_Attack_Arrow_Polygon();																		// �f�X�g���N�^
	static CEnemy_Attack_Arrow_Polygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CBullet *pBullet);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);													// ����������
	void Uninit(void);																					// �I������
	void Update(void);																					// �X�V����
	void Draw(void);																					// �`�揈��
private:
	void Collision(void);			// �����蔻��
	void Move(void);				// �ړ�
	CBullet *m_pBullet;				// CBullet�̃|�C���^
	int m_nCount;					// �J�E���g
	bool m_bCollision;				// �����蔻��
};
#endif