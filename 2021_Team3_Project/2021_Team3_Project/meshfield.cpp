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
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	VERTEX_3D *pVtx = nullptr;

	// ���[�J���ϐ�
	int nCount = 0;			// for���p
	int nCntIndex = 0;		// ���_�̐����ԍ�
	int nCntH = 0;			// �c�̒��_�J�E���^
	int nCntV = 0;			// ���̒��_�J�E���^

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_FLOOR));

	// �l�̏�����
	SetNumVertex((FIELD_WIDTH + 1) * (FIELD_HEIGHT + 1));								// 25
	SetNumIndex((FIELD_WIDTH + 1) * FIELD_HEIGHT * 2 + (FIELD_HEIGHT - 1) * 2);			// 5*(4*2)+3*2	46
	SetNumPolygon(FIELD_WIDTH * FIELD_HEIGHT * 2 + (FIELD_HEIGHT - 1) * 4);				// 4*8+3*4	44
	D3DXVECTOR2 OneSize = D3DXVECTOR2(FIELD_WIDTH_SIZE * 2 / FIELD_WIDTH, FIELD_HEIGHT_SIZE * 2 / FIELD_HEIGHT);
	SetOneSize(OneSize);

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

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntV = 0; nCntV < FIELD_HEIGHT + 1; nCntV++)
	{
		for (nCntH = 0; nCntH < FIELD_WIDTH + 1; nCntH++)
		{
			// ���_�̐ݒ�
			pVtx[(nCntV * (FIELD_HEIGHT + 1)) + nCntH].pos = D3DXVECTOR3(-FIELD_WIDTH_SIZE + (nCntH * OneSize.x), 0.0f, FIELD_HEIGHT_SIZE - (nCntV * OneSize.y));

			// �@���x�N�g���̐ݒ�
			pVtx[(nCntV * (FIELD_HEIGHT + 1)) + nCntH].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// �F�̐ݒ�
			pVtx[(nCntV * (FIELD_HEIGHT + 1)) + nCntH].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[(nCntV * (FIELD_HEIGHT + 1)) + nCntH].tex = D3DXVECTOR2(float(nCntH), float(nCntV));
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
	for (nCount = 0, nCntIndex = 0; nCount < nNumIndex; nCount += 2)
	{
		if (((nCount + 2) % (((FIELD_WIDTH + 1) * 2) + 2)) == 0 && nCount != 0)
		{
			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount] = nCntIndex - 1;

			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount + 1] = FIELD_WIDTH + nCntIndex + 1;
		}
		else
		{
			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount] = FIELD_WIDTH + nCntIndex + 1;

			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount + 1] = nCntIndex;

			nCntIndex++;
		}
	}

	// ���_�f�[�^���A�����b�N����
	pIdxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@��ݒ�
	BindIdxBuff(pIdxBuff);

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