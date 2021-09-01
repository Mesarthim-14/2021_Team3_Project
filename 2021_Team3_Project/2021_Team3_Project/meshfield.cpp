//=============================================================================
//
// ���b�V���t�B�[���h�N���X [meshfield.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "meshfield.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMeshField::CMeshField(PRIORITY Priority) : CMesh3d(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshField::~CMeshField()
{
}

//=============================================================================
// �|���S������
//=============================================================================
CMeshField * CMeshField::Create(void)
{
	// �������m��
	CMeshField *pMeshField = new CMeshField;

	// nullchack
	if (pMeshField != nullptr)
	{
		// ����������
		pMeshField->Init(ZeroVector3, ZeroVector3);
	}

	return pMeshField;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshField::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_FLOOR));

	// ���_�̐ݒ�
	CreateVerterx();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshField::Uninit(void)
{
	// �폜�t���O
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshField::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshField::Draw(void)
{
	// �e�N���X�`�揈��
	CMesh3d::Draw();
}

//=============================================================================
// ���_�̐���
//=============================================================================
void CMeshField::CreateVerterx(void)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	VERTEX_3D *pVtx = nullptr;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;		// �o�b�t�@
	LPDIRECT3DINDEXBUFFER9 pIdxBuff = nullptr;		// �o�b�t�@�̔ԍ�
	
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * GetNumVertex(),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL);

	// �C���f�b�N�X�o�b�t�@����
	pDevice->CreateIndexBuffer(sizeof(WORD) * GetNumIndex(),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&pIdxBuff,
		NULL);

	// 1�|���S���̃T�C�Y
	D3DXVECTOR3 OneSize = GetOneSize();
	D3DXVECTOR3 AllSize = GetSize();
	INT_VERTEX_2D PieceNum = GetPieceNum();

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV < PieceNum.x + 1; nCntV++)
	{
		for (int nCntH = 0; nCntH < PieceNum.y + 1; nCntH++)
		{
			// ���_�̐ݒ�
			pVtx[(nCntV * (PieceNum.y + 1)) + nCntH].pos = D3DXVECTOR3(-AllSize.x + (nCntH * OneSize.x), 0.0f, AllSize.z - (nCntV * OneSize.y));

			// �@���x�N�g���̐ݒ�
			pVtx[(nCntV * (PieceNum.y + 1)) + nCntH].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// �F�̐ݒ�
			pVtx[(nCntV * (PieceNum.y + 1)) + nCntH].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[(nCntV * (PieceNum.y + 1)) + nCntH].tex = D3DXVECTOR2(float(nCntH), float(nCntV));
		}
	}

	// ���_�f�[�^���A�����b�N����
	pVtxBuff->Unlock();

	// ���_�o�b�t�@�̐ݒ�
	BindVtxBuff(pVtxBuff);

	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	WORD *pIdx;

	// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// �C���f�b�N�X��
	int nNumIndex = GetNumIndex();
	for (int nCount = 0, nCntIndex = 0; nCount < nNumIndex; nCount += 2)
	{
		if (((nCount + 2) % (((PieceNum.x + 1) * 2) + 2)) == 0 && nCount != 0)
		{
			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount] = nCntIndex - 1;

			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount + 1] = PieceNum.x + nCntIndex + 1;
		}
		else
		{
			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount] = PieceNum.x + nCntIndex + 1;

			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount + 1] = nCntIndex;

			nCntIndex++;
		}
	}

	// ���_�f�[�^���A�����b�N����
	pIdxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@��ݒ�
	BindIdxBuff(pIdxBuff);
}

//=============================================================================
// ���̐ݒ�
//=============================================================================
void CMeshField::SetInfo(D3DXVECTOR3 size, INT_VERTEX_2D PieceNum)
{
	// �l�̏�����
	SetNumVertex((PieceNum.x + 1) * (PieceNum.y + 1));								// 25
	SetNumIndex((PieceNum.x + 1) * PieceNum.y * 2 + (PieceNum.y - 1) * 2);			// 5*(4*2)+3*2	46
	SetNumPolygon(PieceNum.x * PieceNum.y * 2 + (PieceNum.y - 1) * 4);				// 4*8+3*4	44

	// �T�C�Y�̐ݒ�
	D3DXVECTOR3 AllSize = D3DXVECTOR3(size.x, 0.0f, size.z);
	SetSize(AllSize);
	D3DXVECTOR2 OneSize = D3DXVECTOR2(size.x * 2 / PieceNum.x, size.z * 2 / PieceNum.y);
	SetOneSize(OneSize);

	// �u���b�N�̐�
	SetPieceNum(PieceNum);
}