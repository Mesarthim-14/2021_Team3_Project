#ifndef _MAP_H_
#define _MAP_H_
//=============================================================================
// �^�C�g���}�b�v [titlr_map.h]
// Author : Konishi Yuuto
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Konishi Yuuto
//=============================================================================
#include "model.h"

//=============================================================================
// �}�b�v�N���X
// Author : Konishi Yuuto
//=============================================================================
class CTitleMap : public CModel
{
public:
	CTitleMap(PRIORITY Priority = PRIORITY_MAP);				// �R���X�g���N�^
	~CTitleMap();												// �f�X�g���N�^
	static CTitleMap *Create(void);								// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// ����������

private:
};
#endif