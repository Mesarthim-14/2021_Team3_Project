#ifndef _COLLISION_H_
#define _COLLISION_H_
//=============================================================================
//
// �����蔻�菈�� [collision.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �����蔻��N���X
//=============================================================================
class CCollision
{
public:
	// ����������
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