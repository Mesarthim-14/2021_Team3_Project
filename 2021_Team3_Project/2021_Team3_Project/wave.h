#ifndef _WAVE_H_
#define _WAVE_H_
//=============================================================================
//
// �㉺�^���̃N���X	[wave.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "main.h"
#include "xfile.h"

//=========================================================================
// �N���X��`
//=========================================================================
class CWave
{
public:
	CWave();		// �R���X�g���N�^
	~CWave();		// �f�X�g���N�^

	static CWave *Create(float fTimeNum,
		float fPower, float fHeight);		// �e�̐���
	HRESULT Init(float fTimeNum,
		float fPower, float fHeight);		// ����������

	void Update(void);						// �X�V����
	float Wave(void);						// �㉺�����̎���
	float Wave(int nCntV, int nCntH);		// �㉺�����̎���

private:
	float m_fTime;		// ����
	float m_fTimeNum;	// ����
	float m_fPower;		// ��̗�
	float m_fHeight;	// �g�̍���
};
#endif