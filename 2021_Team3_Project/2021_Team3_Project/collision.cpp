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
	if (pow(pos1.x - pos2.x, 2) +
		pow(pos1.y - pos2.y, 2) +
		pow(pos1.z - pos2.z, 2) <= pow(radius1 + radius2, 2))
	{
		return true;
	}

	return false;
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