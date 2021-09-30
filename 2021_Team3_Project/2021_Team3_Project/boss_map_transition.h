#ifndef _BOSS_MAP_TRANSITION_H_
#define _BOSS_MAP_TRANSITION_H_
//=============================================================================
// �}�b�v [map.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"

//=============================================================================
// �}�b�v�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CBoss_Map_Transition : public CModel
{
public:
	CBoss_Map_Transition(PRIORITY Priority = PRIORITY_MODEL);								// �R���X�g���N�^
	~CBoss_Map_Transition();															// �f�X�g���N�^
	static CBoss_Map_Transition *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);						// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��
private:
};
#endif