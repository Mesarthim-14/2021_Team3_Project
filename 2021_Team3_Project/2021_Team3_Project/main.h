#ifndef _MAIN_H_
#define _MAIN_H_
//=============================================================================
//
// ���C������ [main.h]
// Author : Konishi Yuuto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <thread>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	//�x���Ώ��p�i"dinput.h"�̒��O�ɒ�`�j
#include <dinput.h>
#include "d3dx9math.h"
#include <vector>
#include <stdlib.h>
#include <crtdbg.h>
#include <algorithm>			// find_if�֐����ɕK�v
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

//=============================================================================
// ���C�u�����̃����N
//=============================================================================
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�v
#pragma comment (lib,"ws2_32.lib")

// ���������[�N
#ifdef _DEBUG
#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

//=============================================================================
// �}�N����`
//=============================================================================
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE| D3DFVF_TEX1)	// ���W�E�@���E�J���[
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)				// ���_�t�H�[�}�b�g
#define NUM_VERTEX		(4)															// ���_��
#define VERTEX_TRIANGLE	(3)															// �O�p�`�̒��_��
#define NUM_POLYGON		(2)															// �|���S����

// �������p�}�N���ϐ�
#define ZeroVector2		(D3DXVECTOR2(0.0f, 0.0f))
#define ZeroVector3		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
#define WhiteColor		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
#define BlackColor		(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))
#define ZERO_INT		(0)			
#define ZERO_FLOAT		(0.0f)

#define DIVIDE_2		(2)
// ���O�̏ȗ�
using namespace std;

//=============================================================================
//�\���̒�`
//=============================================================================
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
};

struct VERTEX_2D
{
	D3DXVECTOR3 pos; // ���_���W
	float rhw;		 //	���W�ϊ��p�W���i1.0f�ŌŒ�j
	D3DCOLOR  col;	 // ���_�J���[
	D3DXVECTOR2 tex; // �e�N�X�`�����W
};

// int�^�̍\����
struct INT_VERTEX_2D
{
	int x;
	int y;
};

#endif