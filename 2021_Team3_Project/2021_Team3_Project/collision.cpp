//=============================================================================
//
// �����蔻�菈�� [collision.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "collision.h"

//=============================================================================
//�����蔻��(��`�Ƌ�`)
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
//�����蔻��(�~�`�Ɖ~�`)
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
//�����蔻��(��`�Ɖ~�`)
//=============================================================================
bool CCollision::CollisionRectangleAndCircular(D3DXVECTOR3 RectanglePos, D3DXVECTOR3 CircularPos, D3DXVECTOR3 RectangleSize, float CircularRadius, float RectangleRadian)
{
	//��`�̊p�x���O�ɂ������̉~�`�̍��W�����߂�
	D3DXVECTOR3 NewCircularPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	NewCircularPos.x = (float)(cos(RectangleRadian) * (CircularPos.x - RectanglePos.x) -
		sin(RectangleRadian) * (CircularPos.y - RectanglePos.y) + RectanglePos.x);
	NewCircularPos.y = (float)(sin(RectangleRadian) * (CircularPos.x - RectanglePos.x) +
		cos(RectangleRadian) * (CircularPos.y - RectanglePos.y) + RectanglePos.y);

	if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2) - CircularRadius) ||
		NewCircularPos.x >(RectanglePos.x + (RectangleSize.x / 2) + CircularRadius) ||
		NewCircularPos.y < (RectanglePos.y - (RectangleSize.y / 2) - CircularRadius) ||
		NewCircularPos.y >(RectanglePos.y + (RectangleSize.y / 2) + CircularRadius))
	{ //�u��`�̊O�g + �~�̔��a�v�͈̔͂ɓ����Ă��Ȃ��Ƃ�
		return false;
	}
	if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2)) &&
		NewCircularPos.y < (RectanglePos.y - (RectangleSize.y / 2)) &&
		!(pow((RectanglePos.x - (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.y - (RectangleSize.y / 2)) - NewCircularPos.y, 2)
			< pow(CircularRadius, 2)))
	{ //��`�̍���̔���
		return false;
	}
	if (NewCircularPos.x > (RectanglePos.x + (RectangleSize.x / 2)) &&
		NewCircularPos.y < (RectanglePos.y - (RectangleSize.y / 2)) &&
		!(pow((RectanglePos.x + (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.y - (RectangleSize.y / 2)) - NewCircularPos.y, 2)
			< pow(CircularRadius, 2)))
	{ //��`�̉E��̔���
		return false;
	}
	if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2)) &&
		NewCircularPos.y >(RectanglePos.y + (RectangleSize.y / 2)) &&
		!(pow((RectanglePos.x - (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.y + (RectangleSize.y / 2)) - NewCircularPos.y, 2)
			< pow(CircularRadius, 2)))
	{ //��`�̍����̔���
		return false;
	}
	if (NewCircularPos.x > (RectanglePos.x + (RectangleSize.x / 2)) &&
		NewCircularPos.y > (RectanglePos.y + (RectangleSize.y / 2)) &&
		!(pow((RectanglePos.x + (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.y + (RectangleSize.y / 2)) - NewCircularPos.y, 2)
			< pow(CircularRadius, 2)))
	{ //��`�̉E���̔���
		return false;
	}

	return true;
}
//=============================================================================
// �����蔻��(��`�Ɖ~�`)
// Author : SugawaraTsukasa
//=============================================================================
int CCollision::ActiveCollisionRectangleAndRectangle(D3DXVECTOR3 pos1, D3DXVECTOR3 posOld, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
{
	int nSurFace = INIT_INT;

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / DIVIDE_2, size1.y / DIVIDE_2, size1.z / DIVIDE_2) + pos1;
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / DIVIDE_2, -size1.y / DIVIDE_2, -size1.z / DIVIDE_2) + pos1;
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / DIVIDE_2, size2.y / DIVIDE_2, size2.z / DIVIDE_2) + pos2;
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / DIVIDE_2, -size2.y / DIVIDE_2, -size2.z / DIVIDE_2) + pos2;

	if (box1Max.y > box2Min.y &&	// ��
		box1Min.y < box2Max.y &&	// ��
		box1Max.x > box2Min.x &&	// �E����
		box1Min.x < box2Max.x &&	// ������
		box1Max.z > box2Min.z &&	// ������
		box1Min.z < box2Max.z)		// ��O
	{

		// ��
		if (box1Max.y > box2Min.y && posOld.y <= box2Min.y)
		{
			// ��
			nSurFace = SURFACE_DOWN;
		}
		// ��
		if (box1Min.y < box2Max.y && posOld.y >= box2Max.y)
		{
			// ��
			nSurFace = SURFACE_UP;
		}
		// ��
		if (box1Max.x > box2Min.x && posOld.x <= box2Min.x)
		{
			// ��
			nSurFace = SURFACE_LEFT;
		}
		// �E
		if (box1Min.x < box2Max.x && posOld.x >= box2Max.x)
		{
			// �E
			nSurFace = SURFACE_RIGHT;
		}
		// ��
		if (box1Min.z < box2Max.z && posOld.z >= box2Max.z)
		{
			// ��
			nSurFace = SURFACE_BACK;
		}
		// ��O
		if (box1Max.z > box2Min.z && posOld.z <= box2Min.z)
		{
			// ��O
			nSurFace = SURFACE_PREVIOUS;
		}
	}
	// ���������ʂ�Ԃ�
	return nSurFace;
}
