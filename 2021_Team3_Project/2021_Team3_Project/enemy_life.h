//=============================================================================
// �G���C�t�Q�[�W [enemy_life.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _ENEMY_LIFE_H_
#define _ENEMY_LIFE_H_
//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "gage_3d.h"
#include "enemy.h"
#include "gage_3d_back.h"
//=============================================================================
// �G���C�t�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CEnemy_Life :public CGage_3D
{
public:
	CEnemy_Life(PRIORITY nPriority = PRIORITY_UI);										// �R���X�g���N�^
	~CEnemy_Life();																	// �f�X�g���N�^
	static CEnemy_Life *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy *pEnemy);	// ���������֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);								// �����������֐�
	void Uninit(void);																// �I�������֐�
	void Update(void);																// �X�V�����֐�
	void Draw(void);																// �`�揈���֐�

private:
	CEnemy *m_pEnemy;					// CEnemy�̃|�C���^
};
#endif