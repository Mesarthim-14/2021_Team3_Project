//=============================================================================
// �{�X���C�t�Q�[�W [boss_life.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _BOSS_LIFE_H_
#define _BOSS_LIFE_H_
//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "gage_2d.h"
#include "enemy.h"
//=============================================================================
// �Q�[�W�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CBoss_Life :public CGage_2D
{
public:
	CBoss_Life(PRIORITY nPriority = PRIORITY_UI);									// �R���X�g���N�^
	~CBoss_Life();																	// �f�X�g���N�^
	static CBoss_Life *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy *pEnemy);	// ���������֐�
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);						// �����������֐�
	virtual void Uninit(void);														// �I�������֐�
	virtual void Update(void);														// �X�V�����֐�
	virtual void Draw(void);														// �`�揈���֐�
private:
	CEnemy *m_pEnemy;	// CEnemy�̃|�C���^
};
#endif