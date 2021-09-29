#ifndef _TITLE_SKY_H_
#define _TITLE_SKY_H_
//=============================================================================
// �^�C�g���}�b�v [title_sky.h]
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
class CTitleSky : public CModel
{
public:
	CTitleSky(PRIORITY Priority = PRIORITY_MODEL);				// �R���X�g���N�^
	~CTitleSky();												// �f�X�g���N�^
	static CTitleSky *Create(void);								// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// ����������
	void Draw(void);											// �`�揈��
private:
};
#endif