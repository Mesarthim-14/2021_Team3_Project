//=============================================================================
// �{�X���C�t�Q�[�W�̔w�i [boss_life_back.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _BOSS_LIFE_BACK_H_
#define _BOSS_LIFE_BACK_H_
//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "scene2d.h"
#include "enemy.h"
//=============================================================================
// ���C�t�Q�[�W�w�i�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CBoss_Life_Back : public CScene2D
{
public:
	CBoss_Life_Back(PRIORITY Priority = PRIORITY_3D_UI);									// �R���X�g���N�^
	~CBoss_Life_Back();																	// �f�X�g���N�^
	static CBoss_Life_Back *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy *pEnemy);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);										// ����������
	void Uninit(void);																		// �I������
	void Update(void);																		// �X�V����
	void Draw(void);																		// �`�揈��
private:
	CEnemy *m_pEnemy;					// CEnemy�̃|�C���^
};
#endif