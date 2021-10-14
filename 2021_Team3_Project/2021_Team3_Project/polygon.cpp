//=============================================================================
//
// �|���S�������N���X���� [polygon.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "polygon.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPolygon::CPolygon()
{
	m_pVtxBuff = nullptr;
	m_pos = ZeroVector3;
	m_Size = ZeroVector3;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPolygon::~CPolygon()
{

}

//=============================================================================
// �C���X�^���X��������
//=============================================================================
CPolygon * CPolygon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �|���S���N���X�̃|�C���^�ϐ�
	CPolygon *pPolygon = nullptr;

	//�������̊m��
	pPolygon = new CPolygon;

	// !nullcheck
	if (pPolygon != nullptr)
	{
		//�����������Ăяo��
		pPolygon->Init(pos, size);

		return pPolygon;

	}

	return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPolygon::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	VERTEX_2D *pVtx = nullptr;												//���_���ւ̃|�C���^

	m_pos = pos;	//�����ʒu�̐ݒ�
	m_Size = size;	//�傫���̐ݒ�

	//���_�o�b�t�@�̍쐬
	pD3DDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX,	//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				//�i�Œ�j
		FVF_VERTEX_2D,					//�t�H�[�}�b�g
		D3DPOOL_MANAGED,				//(�Œ�)
		&m_pVtxBuff,
		nullptr
	);

	//���_�f�[�^�����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-m_Size.x / 2), m_pos.y + (-m_Size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_Size.x / 2), m_pos.y + (-m_Size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-m_Size.x / 2), m_pos.y + (m_Size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_Size.x / 2), m_pos.y + (m_Size.y / 2), 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPolygon::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CPolygon::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPolygon::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̃|�C���^

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, nullptr);

	// �|���S���̕`��
	pD3DDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,
		NUM_POLYGON);	//�|���S����

	//�e�N�X�`���̐ݒ�����ɖ߂�
	pD3DDevice->SetTexture(0, nullptr);
}

//=============================================================================
// �F�̐ݒ�
//=============================================================================
void CPolygon::SetColor(const D3DXCOLOR color)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�f�[�^�����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�J���[�̐ݒ�
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}