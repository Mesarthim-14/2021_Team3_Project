//=============================================================================
// �f�o�b�O�v���V�[�W�� [debug_proc.h]
// Author : SugawaraTsukasa
//=============================================================================
#ifndef _DEBUG_PROC_H_
#define _DEBUG_PROC_H_
//=============================================================================
// �N���X
// Author : SugawaraTsukasa
//=============================================================================
class CDebugProc
{
public:
	CDebugProc();						// �R���X�g���N�^
	~CDebugProc();						// �f�X�g���N�^
	void Init(void);					// �����������֐�
	void Uninit(void);					// �I�������֐�
	static void Print(char *fmt, ...);	// �������ݏ����֐�
	static void Draw(void);				// �`�揈���֐�
private:
	static LPD3DXFONT m_pFont;			// �t�H���g
	static char m_astr[1024];			// ������
};
#endif
