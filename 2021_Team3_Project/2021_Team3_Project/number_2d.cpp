//=============================================================================
//
// �i���o�[2D�N���X [number.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "number_2d.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SCORE_ANIM_PATTERN	(8)			// �A�j���[�V�����̃p�^�[��
#define NUMBER_NUM			(10)		// �i���o�[�̐�

//=============================================================================
// �C���X�^���X����
//=============================================================================
CNumber2d * CNumber2d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �C���X�^���X����
	CNumber2d *pNumber = new CNumber2d;

	if (pNumber != nullptr)
	{
		// ����������
		pNumber->Init(pos, size);
	}

	return pNumber;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CNumber2d::CNumber2d(PRIORITY Priority) : CSceneBase(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNumber2d::~CNumber2d()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CNumber2d::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �o�b�t�@�̕ϐ�
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,														// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,															// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,														// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pVtxBuff,																// ���_�o�b�t�@�ւ̃|�C���^
		nullptr)))																	// nullptr�ɐݒ�
	{
		return E_FAIL;
	}

	SetPos(pos);			// ���W�ݒ�
	SetSize(size);			// �T�C�Y�ݒ�

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y + size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y + size.y / 2, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �������_�̐F	�����x255
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�����_�̐F	�����x255

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();

	// �o�b�t�@����n��
	BindVtxBuff(pVtxBuff);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CNumber2d::Uninit(void)
{
	// �I���t���O
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CNumber2d::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CNumber2d::Draw(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GetTexture());

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,
		NUM_POLYGON);				// �v���~�e�B�u�̐�

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);
}

//=============================================================================
// �i���o�[�̉��Z
//=============================================================================
void CNumber2d::SetNumber(int nNumber)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((1.0f / NUMBER_NUM) * (float)nNumber, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / NUMBER_NUM) * (float)nNumber + (1.0f / NUMBER_NUM), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / NUMBER_NUM) * (float)nNumber, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / NUMBER_NUM) * (float)nNumber + (1.0f / NUMBER_NUM), 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	GetVtxBuff()->Unlock();
}