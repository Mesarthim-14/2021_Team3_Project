//=============================================================================
// �G�̍U���n�_ [enemy_attack_point_polygon.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _ENEMY_ATTACK_POINT_POLYGON_H_
#define _ENEMY_ATTACK_POINT_POLYGON_H_
//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "scene3D.h"
#include "bullet.h"
//=============================================================================
// �}�b�v�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CEnemy_Attack_Point_Polygon : public CScene3D
{
public:
	CEnemy_Attack_Point_Polygon(PRIORITY Priority = PRIORITY_UI);													// �R���X�g���N�^
	~CEnemy_Attack_Point_Polygon();																					// �f�X�g���N�^
	static CEnemy_Attack_Point_Polygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CBullet *pBullet);				// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);																// ����������
	void Uninit(void);																								// �I������
	void Update(void);																								// �X�V����
	void Draw(void);																								// �`�揈��
private:
	void Collision(void);			// �����蔻��
	void UpdateRot(void);			// �����̏���
	CBullet *m_pBullet;	// CEnemy_Bullet�̃|�C���^
	bool m_bCollision;				// �����蔻��
};
#endif