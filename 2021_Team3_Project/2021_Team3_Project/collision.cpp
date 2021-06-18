//=============================================================================
//
// 当たり判定処理 [collision.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "collision.h"

//=============================================================================
//当たり判定(矩形と矩形)
//=============================================================================
bool CCollision::CollisionRectangleAndRectangle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
{
	if (pos2.x - (size2.x / 2) < pos1.x + (size1.x / 2) &&
		pos2.x + (size2.x / 2) > pos1.x - (size1.x / 2) &&
		pos2.y - (size2.y / 2) < pos1.y + (size1.y / 2) &&
		pos2.y + (size2.y / 2) > pos1.y - (size1.y / 2))
	{
		return true;
	}

	return false;
}

//=============================================================================
//当たり判定(円形と円形)
//=============================================================================
bool CCollision::CollisionCircularAndCircular(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float radius1, float radius2)
{
	bool bCollision = false;

	if (pow(pos1.x - pos2.x, 2) +
		pow(pos1.y - pos2.y, 2) +
		pow(pos1.z - pos2.z, 2) <= pow(radius1 + radius2, 2))
	{
		bCollision = true;
	}

	return bCollision;
}

//=============================================================================
//当たり判定(矩形と円形)
//=============================================================================
bool CCollision::CollisionRectangleAndCircular(D3DXVECTOR3 RectanglePos, D3DXVECTOR3 CircularPos, D3DXVECTOR3 RectangleSize, float CircularRadius, float RectangleRadian)
{
	//矩形の角度を０にした時の円形の座標を求める
	D3DXVECTOR3 NewCircularPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	NewCircularPos.x = (float)(cos(RectangleRadian) * (CircularPos.x - RectanglePos.x) -
		sin(RectangleRadian) * (CircularPos.y - RectanglePos.y) + RectanglePos.x);
	NewCircularPos.y = (float)(sin(RectangleRadian) * (CircularPos.x - RectanglePos.x) +
		cos(RectangleRadian) * (CircularPos.y - RectanglePos.y) + RectanglePos.y);

	if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2) - CircularRadius) ||
		NewCircularPos.x >(RectanglePos.x + (RectangleSize.x / 2) + CircularRadius) ||
		NewCircularPos.y < (RectanglePos.y - (RectangleSize.y / 2) - CircularRadius) ||
		NewCircularPos.y >(RectanglePos.y + (RectangleSize.y / 2) + CircularRadius))
	{ //「矩形の外枠 + 円の半径」の範囲に入っていないとき
		return false;
	}
	if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2)) &&
		NewCircularPos.y < (RectanglePos.y - (RectangleSize.y / 2)) &&
		!(pow((RectanglePos.x - (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.y - (RectangleSize.y / 2)) - NewCircularPos.y, 2)
			< pow(CircularRadius, 2)))
	{ //矩形の左上の判定
		return false;
	}
	if (NewCircularPos.x > (RectanglePos.x + (RectangleSize.x / 2)) &&
		NewCircularPos.y < (RectanglePos.y - (RectangleSize.y / 2)) &&
		!(pow((RectanglePos.x + (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.y - (RectangleSize.y / 2)) - NewCircularPos.y, 2)
			< pow(CircularRadius, 2)))
	{ //矩形の右上の判定
		return false;
	}
	if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2)) &&
		NewCircularPos.y >(RectanglePos.y + (RectangleSize.y / 2)) &&
		!(pow((RectanglePos.x - (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.y + (RectangleSize.y / 2)) - NewCircularPos.y, 2)
			< pow(CircularRadius, 2)))
	{ //矩形の左下の判定
		return false;
	}
	if (NewCircularPos.x > (RectanglePos.x + (RectangleSize.x / 2)) &&
		NewCircularPos.y > (RectanglePos.y + (RectangleSize.y / 2)) &&
		!(pow((RectanglePos.x + (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.y + (RectangleSize.y / 2)) - NewCircularPos.y, 2)
			< pow(CircularRadius, 2)))
	{ //矩形の右下の判定
		return false;
	}

	return true;
}
//=============================================================================
// 当たり判定(矩形と円形)
// Author : SugawaraTsukasa
//=============================================================================
int CCollision::ActiveCollisionRectangleAndRectangle(D3DXVECTOR3 pos1, D3DXVECTOR3 posOld, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
{
	int nSurFace = INIT_INT;

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / DIVIDE_2, size1.y / DIVIDE_2, size1.z / DIVIDE_2) + pos1;
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / DIVIDE_2, -size1.y / DIVIDE_2, -size1.z / DIVIDE_2) + pos1;
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / DIVIDE_2, size2.y / DIVIDE_2, size2.z / DIVIDE_2) + pos2;
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / DIVIDE_2, -size2.y / DIVIDE_2, -size2.z / DIVIDE_2) + pos2;

	if (box1Max.y > box2Min.y &&	// 下
		box1Min.y < box2Max.y &&	// 上
		box1Max.x > box2Min.x &&	// 右から
		box1Min.x < box2Max.x &&	// 左から
		box1Max.z > box2Min.z &&	// 奥から
		box1Min.z < box2Max.z)		// 手前
	{

		// 下
		if (box1Max.y > box2Min.y && posOld.y <= box2Min.y)
		{
			// 下
			nSurFace = SURFACE_DOWN;
		}
		// 上
		if (box1Min.y < box2Max.y && posOld.y >= box2Max.y)
		{
			// 上
			nSurFace = SURFACE_UP;
		}
		// 左
		if (box1Max.x > box2Min.x && posOld.x <= box2Min.x)
		{
			// 左
			nSurFace = SURFACE_LEFT;
		}
		// 右
		if (box1Min.x < box2Max.x && posOld.x >= box2Max.x)
		{
			// 右
			nSurFace = SURFACE_RIGHT;
		}
		// 奥
		if (box1Min.z < box2Max.z && posOld.z >= box2Max.z)
		{
			// 奥
			nSurFace = SURFACE_BACK;
		}
		// 手前
		if (box1Max.z > box2Min.z && posOld.z <= box2Min.z)
		{
			// 手前
			nSurFace = SURFACE_PREVIOUS;
		}
	}
	// 当たった面を返す
	return nSurFace;
}
