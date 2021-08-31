//=============================================================================
// �f�o�b�O�v���V�[�W�� [debug_proc.cpp]
// Author : SugawaraTsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : SugawaraTsukasa
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "debug_proc.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
// Author : SugawaraTsukasa
//=============================================================================
LPD3DXFONT CDebugProc::m_pFont = nullptr;
char CDebugProc::m_astr[1024] = {};

//=============================================================================
// �R���X�g���N�^
// Author : SugawaraTsukasa
//=============================================================================
CDebugProc::CDebugProc()
{
}

//=============================================================================
// �f�X�g���N�^
// Author : SugawaraTsukasa
//=============================================================================
CDebugProc::~CDebugProc()
{
}

//=============================================================================
//�����������֐�
// Author : SugawaraTsukasa
//=============================================================================
void CDebugProc::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �����_���[�擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
}

//=============================================================================
// �I�������֐�
// Author : SugawaraTsukasa
//=============================================================================
void CDebugProc::Uninit(void)
{
	// m_pFont��NULL�łȂ��ꍇ
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//=============================================================================
// �������ݏ����֐�
// Author : SugawaraTsukasa
//=============================================================================
void CDebugProc::Print(char * fmt, ...)
{
	va_list list;
	// �ϒ������̎擾
	va_start(list, fmt);
	// �ϒ������̃��X�g����������
	vsprintf(m_astr, fmt, list);
	va_end(list);
}

//=============================================================================
// �`�揈���֐�
// Author : SugawaraTsukasa
//=============================================================================
void CDebugProc::Draw(void)
{
	RECT rect = { SCREEN_WIDTH - 500, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, m_astr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
