//=============================================================================
//
// �����蔻�菈�� [collision.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include"model.h"
#include "collision.h"

//=============================================================================
//�����蔻��(��`�Ƌ�`)
//=============================================================================
bool CCollision::CollisionRectangleAndRectangle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
{
	bool bCollision = false;

	if (pos2.x - (size2.x / 2) < pos1.x + (size1.x / 2) &&
		pos2.x + (size2.x / 2) > pos1.x - (size1.x / 2) &&
		pos2.y - (size2.y / 2) < pos1.y + (size1.y / 2) &&
		pos2.y + (size2.y / 2) > pos1.y - (size1.y / 2))
	{
		bCollision = true;
	}

	return bCollision;
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
	int nSurFace = ZERO_INT;

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / DIVIDE_2, size1.y / DIVIDE_2, size1.z / DIVIDE_2) + pos1;
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / DIVIDE_2, -size1.y / DIVIDE_2, -size1.z / DIVIDE_2) + pos1;
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / DIVIDE_2, size2.y / DIVIDE_2, size2.z / DIVIDE_2) + pos2;
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / DIVIDE_2, -size2.y / DIVIDE_2, -size2.z / DIVIDE_2) + pos2;

	if (box1Max.y > box2Min.y &&	// ��
		box1Min.y < box2Max.y &&	// ��
		box1Max.x > box2Min.x &&	// ������
		box1Min.x < box2Max.x &&	// �E����
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
		else if (box1Min.y < box2Max.y && posOld.y >= box2Max.y)
		{
			// ��
			nSurFace = SURFACE_UP;
		}
		// ��
		else if (box1Max.x > box2Min.x && posOld.x <= box2Min.x)
		{
			// ��
			nSurFace = SURFACE_LEFT;
		}
		// �E
		else if (box1Min.x < box2Max.x && posOld.x >= box2Max.x)
		{
			// �E
			nSurFace = SURFACE_RIGHT;
		}
		// ��O
		else if (box1Max.z > box2Min.z && posOld.z <= box2Min.z)
		{
			// ��O
			nSurFace = SURFACE_PREVIOUS;
		}
		// ��
		else if (box1Min.z < box2Max.z && posOld.z >= box2Max.z)
		{
			// ��
			nSurFace = SURFACE_BACK;
		}
	}
	// ���������ʂ�Ԃ�
	return nSurFace;
}
//=============================================================================
// ���C�̓����蔻��
// Author : SugawaraTsukasa
//=============================================================================
CCollision::RAY_INFO CCollision::RayCollision(D3DXVECTOR3 Pos, CModel *pModel, float fRadius, float fHitRange, int nNum)
{
	// ���C���q�b�g������
	BOOL bHit = false;

	// ����
	float fDistancePlayer = ZERO_FLOAT;

	// �ʒu
	D3DXVECTOR3 vecDirection;

	// ���C�̏��
	RAY_INFO Ray_Info;

	// ������
	Ray_Info.bHit = false;
	Ray_Info.VecDirection = ZeroVector3;

	// !nullcheck
	if (pModel != nullptr)
	{
		// nNum��J��Ԃ�
		for (int nCount = ZERO_INT; nCount < nNum; nCount++)
		{
			// ���C���o���p�x
			vecDirection = D3DXVECTOR3(ZERO_FLOAT, fRadius * nCount, ZERO_FLOAT);

			// ���C���q�b�g������
			D3DXIntersect(pModel->GetMesh(), &Pos, &D3DXVECTOR3(sinf(vecDirection.y), ZERO_FLOAT, cosf(vecDirection.y)),
				&bHit, NULL, NULL, NULL, &fDistancePlayer, NULL, NULL);

			// true�̏ꍇ
			if (bHit == TRUE)
			{
				// �͈͂�菬����������
				if (fDistancePlayer < fHitRange)
				{
					// true��
					Ray_Info.bHit = true;

					// �x�N�^�[�̕���
					Ray_Info.VecDirection = vecDirection;
				}
			}
		}
	}
	// ����Ԃ�
	return Ray_Info;
}
