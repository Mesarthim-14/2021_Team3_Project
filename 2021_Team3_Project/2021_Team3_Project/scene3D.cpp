//=============================================================================
//
// �V�[��3D�N���X [scene3D.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene3D::CScene3D(PRIORITY Priority) : CSceneBase(Priority)
{
	m_nCountAnim = 0;
	m_nCountAnimPattern = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nLoop = -1;
	m_fScaleNum = 0.0f;
	m_nAlphaTestNum = 0;
	m_bAlpha = false;
	m_bInverse = false;
	m_fAlphaNum = 0.0f;
	m_move = ZeroVector3;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene3D::~CScene3D()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene3D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �ϐ����
	SetPos(pos);
	SetSize(size);

	// ���_�̐���
	CreateVertex(pos, size);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene3D::Uninit(void)
{
	//�I�u�W�F�N�g�j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene3D::Update(void)
{
	// �ړ��ʉ��Z
	GetPos() += m_move;

	// �A�j���[�V�����̐ݒ肪���ꂽ�Ƃ�
	if (m_nPatternAnim != 0)
	{
		// �A�j���[�V�������X�V����
		UpdateAnimation();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene3D::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v�Z�p�̃}�g���N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	// ���C�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �A���t�@�e�X�g��L�͉�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// ���Z����
	if (m_bBlend == true)
	{
		// ���Z�������s��
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// a�f�X�e�B�l�[�V�����J���[
	}

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GetTexture());

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����擾
	D3DXVECTOR3 rot = GetRot();

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �T�C�Y���
	D3DXVECTOR3 pos = GetPos();

	// �ʒu�𔽉f�A���[���h�}�g���N�X�ݒ�A�|���S���`��
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// ���Z�������s������
	if (m_bBlend == true)
	{
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// a�f�X�e�B�l�[�V�����J���[
	}

	// �A���t�@�e�X�g������
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ���C�g�L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// ���_�̐���
//=============================================================================
void CScene3D::CreateVertex(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;							// ���_�o�b�t�@�ϐ��̐錾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		nullptr);

	VERTEX_3D*pVtx = nullptr;

	//���_�o�b�t�@�����b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-(size.x / 2), (size.y / 2), (size.z / 2));
	pVtx[1].pos = D3DXVECTOR3((size.x / 2), (size.y / 2), (size.z / 2));
	pVtx[2].pos = D3DXVECTOR3(-(size.x / 2), -(size.y / 2), -(size.z / 2));
	pVtx[3].pos = D3DXVECTOR3((size.x / 2), -(size.y / 2),	-(size.z / 2));

	//�e���_�̖@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e���_�̖@���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	pVtxBuff->Unlock();

	// �o�b�t�@�̐ݒ�
	BindVtxBuff(pVtxBuff);
}

//=============================================================================
// �ړ���
//=============================================================================
void CScene3D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// ���W�ݒ�(���W�X�V�p)
//=============================================================================
void CScene3D::SetPosision(D3DXVECTOR3 pos)
{
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
	pVtx[0].pos = D3DXVECTOR3(-(size.x / 2), +(size.y / 2),(size.z / 2));
	pVtx[1].pos = D3DXVECTOR3(+(size.x / 2), +(size.y / 2),(size.z / 2));
	pVtx[2].pos = D3DXVECTOR3(-(size.x / 2), -(size.y / 2),-(size.z / 2));
	pVtx[3].pos = D3DXVECTOR3(+(size.x / 2), -(size.y / 2),-(size.z / 2));

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//=============================================================================
// �F�̐ݒ�
//=============================================================================
void CScene3D::SetColor(D3DXCOLOR col)
{
	// �F��ς���
	CSceneBase::SetColor(col);

	// �o�b�t�@�擾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	VERTEX_3D*pVtx = nullptr;

	//���_�o�b�t�@�����b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@�̃A�����b�N
	pVtxBuff->Unlock();
}

//=============================================
// �A�j���[�V�������擾
//=============================================
void CScene3D::InitAnimation(D3DXVECTOR2 TexInfo, int nLoop)
{
	// �l�̑��
	m_nPatternAnim = (int)TexInfo.x;
	m_nCounterAnim = (int)TexInfo.y;
	m_nLoop = nLoop;

	// �o�b�t�@�擾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	VERTEX_3D *pVtx = nullptr;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W���X�V
	pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//=============================================
// �A�j���[�V�����X�V�֐�
//=============================================
void CScene3D::UpdateAnimation(void)
{
	// �����̃A�j���[�V�����J�E���g��i�߂āA�p�^�[����؂�ւ���
	m_nCountAnim++;

	// ���_���(�e�N�X�`�����W)�̍X�V
	if (m_nCountAnim >= m_nCounterAnim)	// �����̑���
	{
		// �A�j���[�V�����̃J�E���g��0�ɂ���
		m_nCountAnim = 0;

		// �A�j���[�V�����̃p�^�[�����J�E���g������
		m_nCountAnimPattern++;
	}

	// �A�j���[�V�������I�������
	if (m_nCountAnimPattern >= m_nPatternAnim)
	{
		// ���l��߂��Ă���
		m_nCountAnimPattern = 0;

		if (m_nLoop == 0)
		{
			// �I������
			Uninit();
		}
	}
	else
	{
		// �o�b�t�@�擾
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
		VERTEX_3D *pVtx = nullptr;

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W���X�V
		pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

		// ���_�o�b�t�@���A�����b�N����
		pVtxBuff->Unlock();
	}
}

//======================================================
// �g��֐�
//======================================================
void CScene3D::ScaleUp(float fScaleUp)
{
	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	m_fScaleNum += fScaleUp;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();	// �o�b�t�@�擾
	VERTEX_3D *pVtx = nullptr;							//���_���ւ̃|�C���^

	//���_�f�[�^�͈͂����b�N���A���_�o�b�t�@�ւ̃|�C���^������
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-(size.x * m_fScaleNum), +(size.y * m_fScaleNum), (size.z * m_fScaleNum));
	pVtx[1].pos = D3DXVECTOR3(+(size.x * m_fScaleNum), +(size.y * m_fScaleNum), (size.z * m_fScaleNum));
	pVtx[2].pos = D3DXVECTOR3(-(size.x * m_fScaleNum), -(size.y * m_fScaleNum), -(size.z * m_fScaleNum));
	pVtx[3].pos = D3DXVECTOR3(+(size.x * m_fScaleNum), -(size.y * m_fScaleNum), -(size.z * m_fScaleNum));

	//���_�f�[�^���A�����b�N
	pVtxBuff->Unlock();
}

//=============================================================================
// �����x�̌��Z
//=============================================================================
void CScene3D::SubAlpha(float fAlphaNum)
{
	// �F�̏��
	D3DXCOLOR col = GetColor();

	m_fAlphaNum = fAlphaNum;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();	// �o�b�t�@�擾
	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

	//���_�f�[�^�͈͂����b�N���A���_�o�b�t�@�ւ̃|�C���^������
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j
		pVtx[nCount].col = D3DXCOLOR(col.r, col.g, col.b, col.a - m_fAlphaNum);
	}

	//���_�f�[�^���A�����b�N
	pVtxBuff->Unlock();
}

//=============================================================================
// ����
//=============================================================================
void CScene3D::SetAlpha(bool bAlpha)
{
	m_bAlpha = bAlpha;
}

//=============================================================================
// �A���t�@�e�X�g�̒l
//=============================================================================
void CScene3D::SetAlphaNum(int nAlphaNum)
{
	m_nAlphaTestNum = nAlphaNum;
}

//=============================================================================
// ���Z�����̐ݒ�
//=============================================================================
void CScene3D::SetBlend(bool bBlend)
{
	m_bBlend = bBlend;
}

//=============================================================================
// �t�s��̐ݒ�
//=============================================================================
void CScene3D::SetInverse(bool bInverse)
{
	m_bInverse = bInverse;
}