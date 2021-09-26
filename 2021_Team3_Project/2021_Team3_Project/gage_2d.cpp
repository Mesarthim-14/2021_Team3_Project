//=============================================================================
// 2D�Q�[�W [gage_2d.h]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "gage_2d.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define TEX_MIN		(0.0f)								// �e�N�X�`���ŏ�
#define TEX_MAX		(1.0f)								// �e�N�X�`���ő�
#define SUB_GAGE	(1)									// �Q�[�W�̒l�������l
#define COL			(D3DCOLOR_RGBA(255, 255, 255, 255))	// �F
#define GAGE_MIN	(0)									// 0.0f
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CGage_2D::CGage_2D(PRIORITY nPriority) : CSceneBase(nPriority)
{
	m_nGageNum		= ZERO_INT;
	m_fGageNum		= ZERO_FLOAT;
	m_fMaxGageNum	= ZERO_FLOAT;
	m_nAlphaNum		= ZERO_INT;
}
//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CGage_2D::~CGage_2D()
{
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CGage_2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �Q�[�W�̒l�Z�o
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�ϐ��̐錾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		nullptr);

	// ���_���ւ̃|�C���^
	VERTEX_2D*pVtx = nullptr;

	// �ϐ����
	SetPos(pos);
	SetSize(size);

	//���_�o�b�t�@�����b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�ݒ�̐ݒ�
	// �ʒu�ƃT�C�Y
	pVtx[0].pos = D3DXVECTOR3((pos.x - size.x / DIVIDE_2), (pos.y - size.y / DIVIDE_2), size.z);
	pVtx[1].pos = D3DXVECTOR3((pos.x + size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (pos.y - size.y / DIVIDE_2), size.z);
	pVtx[2].pos = D3DXVECTOR3((pos.x - size.x / DIVIDE_2), (pos.y + size.y / DIVIDE_2), size.z);
	pVtx[3].pos = D3DXVECTOR3((pos.x + size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (pos.y + size.y / DIVIDE_2), size.z);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = COL;
	pVtx[1].col = COL;
	pVtx[2].col = COL;
	pVtx[3].col = COL;

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �e���_�̖@���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(TEX_MIN, TEX_MIN);
	pVtx[1].tex = D3DXVECTOR2(TEX_MAX, TEX_MIN);
	pVtx[2].tex = D3DXVECTOR2(TEX_MIN, TEX_MAX);
	pVtx[3].tex = D3DXVECTOR2(TEX_MAX, TEX_MAX);

	// ���_�o�b�t�@�̃A�����b�N
	pVtxBuff->Unlock();

	// �o�b�t�@�̎󂯓n��
	BindVtxBuff(pVtxBuff);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_2D::Uninit(void)
{
	// �I�u�W�F�N�g�j��
	Release();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_2D::Update(void)
{
	// 0.0f�ȉ��̏ꍇ
	if (m_nGageNum <= GAGE_MIN)
	{
		// �I��
		Uninit();

		return;
	}
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_2D::Draw(void)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//�A���t�@�e�X�g��L����
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//�A���t�@�e�X�g��l�̐ݒ�
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�A���t�@�e�X�g�̔�r���@�̐ݒ�(GREATER�͊�l���傫���ꍇ)
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, GetTexture());

	// �|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);

	//�A���t�@�e�X�g�𖳌���
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// �e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, nullptr);
}
//=============================================================================
// �ʒu�ݒ菈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_2D::SetPosition(D3DXVECTOR3 pos)
{
	// �Q�[�W�̒l�Z�o
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

	// ���W�ݒ�
	SetPos(pos);

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// ���_����ݒ�
	VERTEX_2D *pVtx = nullptr;

	// �o�b�t�@�擾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((pos.x - size.x / DIVIDE_2), (pos.y - size.y / DIVIDE_2), size.z);
	pVtx[1].pos = D3DXVECTOR3((pos.x + size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (pos.y - size.y / DIVIDE_2), size.z);
	pVtx[2].pos = D3DXVECTOR3((pos.x - size.x / DIVIDE_2), (pos.y + size.y / DIVIDE_2), size.z);
	pVtx[3].pos = D3DXVECTOR3((pos.x + size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (pos.y + size.y / DIVIDE_2), size.z);

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}
//=============================================================================
// �F�ݒ菈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_2D::SetColor(D3DXCOLOR col)
{
	CSceneBase::SetColor(col);

	// ���_���ւ̃|�C���^
	VERTEX_2D*pVtx = nullptr;

	// �o�b�t�@�̎擾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	//���_�o�b�t�@�����b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j
		pVtx[nCount].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	}

	//���_�o�b�t�@�̃A�����b�N
	pVtxBuff->Unlock();
}
//=============================================================================
// �Q�[�W�̒l�ݒ菈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_2D::SetGageNum(int nGageNum)
{
	// ���
	m_nGageNum = nGageNum;

	// �Q�[�W�̒l�Z�o
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// ���_����ݒ�
	VERTEX_2D *pVtx = nullptr;

	// �o�b�t�@�擾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((pos.x - size.x / DIVIDE_2), (pos.y - size.y / DIVIDE_2), size.z);
	pVtx[1].pos = D3DXVECTOR3((pos.x + size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (pos.y - size.y / DIVIDE_2), size.z);
	pVtx[2].pos = D3DXVECTOR3((pos.x - size.x / DIVIDE_2), (pos.y + size.y / DIVIDE_2), size.z);
	pVtx[3].pos = D3DXVECTOR3((pos.x + size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (pos.y + size.y / DIVIDE_2), size.z);

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}
//=============================================================================
// �Q�[�W�̍ő�l�ݒ菈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_2D::SetMaxGageNum(int nMaxGageNum)
{
	// float�ɕϊ�
	m_fMaxGageNum = (float)nMaxGageNum;
}