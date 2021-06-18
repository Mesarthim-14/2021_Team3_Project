#ifndef _COLLISION_H_
#define _COLLISION_H_
//=============================================================================
//
// 当たり判定処理 [collision.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// 当たり判定クラス
//=============================================================================
class CCollision
{
public:
	// 当たった面
	enum SURFACE
	{
		SURFACE_DOWN = 0,
		SURFACE_UP,
		SURFACE_LEFT,
		SURFACE_RIGHT,
		SURFACE_BACK,
		SURFACE_PREVIOUS
	};
	static bool CollisionRectangleAndRectangle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
	static bool CollisionCircularAndCircular(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float radius1, float radius2);
	static bool CollisionRectangleAndCircular(D3DXVECTOR3 RectanglePos, D3DXVECTOR3 CircularPos, D3DXVECTOR3 RectangleSize, float CircularRadius, float RectangleRadian);
	static int ActiveCollisionRectangleAndRectangle(D3DXVECTOR3 pos1, D3DXVECTOR3 posOld, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
};

#endif