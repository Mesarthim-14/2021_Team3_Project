#ifndef _MAP_H_
#define _MAP_H_
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
class CMap : public CModel
{
public:
	enum TYPE 
	{
		TYPE_NORMAL = 0,
		TYPE_BOSS
	};
	CMap(PRIORITY Priority = PRIORITY_MAP);								// �R���X�g���N�^
	~CMap();															// �f�X�g���N�^
	static CMap *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);						// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��
	void RayCollision(void);											// ���C�̓����蔻��
private:
	TYPE m_Type;	// ���
};
#endif