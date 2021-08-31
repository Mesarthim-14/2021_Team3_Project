#ifndef _MAIN_H_
#define _MAIN_H_
//=============================================================================
//
// メイン処理 [main.h]
// Author : Konishi Yuuto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <thread>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	//警告対処用（"dinput.h"の直前に定義）
#include <dinput.h>
#include "d3dx9math.h"
#include <vector>
#include <stdlib.h>
#include <crtdbg.h>
#include <algorithm>			// find_if関数等に必要
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

//=============================================================================
// ライブラリのリンク
//=============================================================================
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")	//入力処理に必要
#pragma comment (lib,"ws2_32.lib")

// メモリリーク
#ifdef _DEBUG
#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

//=============================================================================
// マクロ定義
//=============================================================================
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE| D3DFVF_TEX1)	// 座標・法線・カラー
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)				// 頂点フォーマット
#define NUM_VERTEX		(4)															// 頂点数
#define VERTEX_TRIANGLE	(3)															// 三角形の頂点数
#define NUM_POLYGON		(2)															// ポリゴン数

// 初期化用マクロ変数
#define ZeroVector2		(D3DXVECTOR2(0.0f, 0.0f))
#define ZeroVector3		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
#define WhiteColor		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
#define BlackColor		(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))
#define ZERO_INT		(0)			
#define ZERO_FLOAT		(0.0f)

#define DIVIDE_2		(2)
// 名前の省略
using namespace std;

//=============================================================================
//構造体定義
//=============================================================================
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
};

struct VERTEX_2D
{
	D3DXVECTOR3 pos; // 頂点座標
	float rhw;		 //	座標変換用係数（1.0fで固定）
	D3DCOLOR  col;	 // 頂点カラー
	D3DXVECTOR2 tex; // テクスチャ座標
};

// int型の構造体
struct INT_VERTEX_2D
{
	int x;
	int y;
};

#endif