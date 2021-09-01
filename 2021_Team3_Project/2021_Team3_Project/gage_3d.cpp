//=============================================================================
// 3D�Q�[�W [gage_3d.h]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "gage_3d.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define NOR			(D3DXVECTOR3 (0.0f,1.0f,0.0f))		// �@��
#define TEX_MIN		(0.0f)								// �e�N�X�`���ŏ�
#define TEX_MAX		(1.0f)								// �e�N�X�`���ő�
#define SUB_GAGE	(1)									// �Q�[�W�̒l�������l
#define COL			(D3DCOLOR_RGBA(255, 255, 255, 255))	// �F
#define GAGE_MIN	(0)									// 0.0f
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CGage_3D::CGage_3D(PRIORITY nPriority) : CSceneBase(nPriority)
{
	m_nGageNum		= ZERO_INT;
	m_fGageNum		= ZERO_FLOAT;
	m_fMaxGageNum	= ZERO_FLOAT;
	m_nAlphaNum		= ZERO_INT;
	m_bAlpha		= false;
	m_bBlend		= false;
}
//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CGage_3D::~CGage_3D()
{
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CGage_3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �Q�[�W�̒l�Z�o
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	

	// ���_�o�b�t�@�ϐ��̐錾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;							

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		nullptr);

	// �o�[�e�b�N�X
	VERTEX_3D*pVtx = nullptr;

	// �ϐ����
	SetPos(pos);
	SetSize(size);

	//���_�o�b�t�@�����b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�ݒ�̐ݒ�
	// �ʒu�ƃT�C�Y
	pVtx[0].pos = D3DXVECTOR3((-size.x / DIVIDE_2), (size.y / DIVIDE_2), size.z);
	pVtx[1].pos = D3DXVECTOR3((size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (size.y / DIVIDE_2), size.z);
	pVtx[2].pos = D3DXVECTOR3((-size.x / DIVIDE_2), (-size.y / DIVIDE_2), size.z);
	pVtx[3].pos = D3DXVECTOR3((size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (-size.y / DIVIDE_2), size.z);

	// �e���_�̖@���̐ݒ�
	pVtx[0].nor = NOR;
	pVtx[1].nor = NOR;
	pVtx[2].nor = NOR;
	pVtx[3].nor = NOR;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = COL;
	pVtx[1].col = COL;
	pVtx[2].col = COL;
	pVtx[3].col = COL;

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
void CGage_3D::Uninit(void)
{
	// �I�u�W�F�N�g�j��
	Release();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_3D::Update(void)
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
void CGage_3D::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �F�̐ݒ�
	D3DMATERIAL9 material, OldMaterial;
	D3DXCOLOR color = GetColor();
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = color;
	material.Diffuse = color;
	pDevice->GetMaterial(&OldMaterial);
	pDevice->SetMaterial(&material);

	// ���̉e���𖳂���
	DWORD ambient;
	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	pDevice->LightEnable(0, FALSE);

	// �A���t�@�e�X�g��L�͉�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// ���Z����
	if (m_bBlend == true)
	{
		// ���Z�������s��
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// a�f�X�e�B�l�[�V�����J���[
	}

	// �A���t�@�e�X�g���L���Ȃ�
	if (m_bAlpha == true)
	{
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0xC0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	}
	else
	{
		// �A���t�@�e�X�g��l�̐ݒ�
		pDevice->SetRenderState(D3DRS_ALPHAREF, m_nAlphaNum);
	}

	//�v�Z�p�̃}�g���N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�̋t�s��̐���
	pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
	D3DXMatrixInverse(&m_mtxWorld, nullptr,
		&mtxRot);

	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;

	// �T�C�Y���
	D3DXVECTOR3 pos = GetPos();

	// �ʒu�𔽉f�A���[���h�}�g���N�X�ݒ�A�|���S���`��
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// �����擾
	D3DXVECTOR3 rot = GetRot();

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// ���[���h�}�g���N�X�̐ݒ� �������A�����A�ʒu
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GetTexture());

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �e�N�X�`����nullptr
	pDevice->SetTexture(0, nullptr);

	// �A���t�@�e�X�g���L���łȂ�������
	if (m_bAlpha != true)
	{
		// �A���t�@�e�X�g��l�̐ݒ�
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	}

	// ���Z�������s������
	if (m_bBlend == true)
	{
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// a�f�X�e�B�l�[�V�����J���[
	}

	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);	// �A���r�G���g��߂�

	pDevice->SetMaterial(&OldMaterial);					// �}�e���A�������ɖ߂�

	// �A���t�@�e�X�g������
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->LightEnable(0, TRUE);
}
//=============================================================================
// �ʒu�ݒ菈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_3D::SetPosition(D3DXVECTOR3 pos)
{
	// �Q�[�W�̒l�Z�o
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

	// ���W�ݒ�
	SetPos(pos);

	D3DXVECTOR3 size = GetSize();

	// ���_����ݒ�
	VERTEX_3D *pVtx = nullptr;

	// �o�b�t�@�擾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((-size.x / DIVIDE_2), (size.y / DIVIDE_2), size.z);
	pVtx[1].pos = D3DXVECTOR3((size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (size.y / DIVIDE_2), size.z);
	pVtx[2].pos = D3DXVECTOR3((-size.x / DIVIDE_2), (-size.y / DIVIDE_2), size.z);
	pVtx[3].pos = D3DXVECTOR3((size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (-size.y / DIVIDE_2), size.z);

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}
//=============================================================================
// �F�ݒ菈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_3D::SetColor(D3DXCOLOR col)
{
	CSceneBase::SetColor(col);

	VERTEX_3D*pVtx = nullptr;

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
void CGage_3D::SetGageNum(int nGageNum)
{
	// ���
	m_nGageNum = nGageNum;

	// �Q�[�W�̒l�Z�o
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

	D3DXVECTOR3 size = GetSize();

	// ���_����ݒ�
	VERTEX_3D *pVtx = nullptr;

	// �o�b�t�@�擾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((-size.x / DIVIDE_2), (size.y / DIVIDE_2), size.z);
	pVtx[1].pos = D3DXVECTOR3((size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (size.y / DIVIDE_2), size.z);
	pVtx[2].pos = D3DXVECTOR3((-size.x / DIVIDE_2), (-size.y / DIVIDE_2), size.z);
	pVtx[3].pos = D3DXVECTOR3((size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (-size.y / DIVIDE_2), size.z);

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}
//=============================================================================
// �Q�[�W�̍ő�l�ݒ菈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_3D::SetMaxGageNum(int nMaxGageNum)
{
	// float�ɕϊ�
	m_fMaxGageNum = (float)nMaxGageNum;
}