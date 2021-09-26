//=======================================================================================
//
// �V�[��2D�N���X [scene2d.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "keyboard.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CScene2D::CScene2D(PRIORITY Priority) : CSceneBase(Priority)
{
	m_nCountAnim = 0;								// �A�j���[�V�����e�N�X�`��
	m_nCountAnimPattern = 0;						// �A�j���[�V�����̃p�^�[��
	m_nCounterAnim= 0;								// �A�j���[�V�����̃J�E���^�[
	m_nPatternAnim= 0;								// �A�j���[�V�����̃p�^�[����
	m_nSpeedTexture = 0;							// �e�N�X�`���̈ړ����x
	m_nLoop = -1;									// ���[�v���邩�ǂ���
	m_fDivisionCounter = 0.0f;						// �X�N���[���̃J�E���^�[
	m_fDivisionBaseNum = 0.0f;						// �X�N���[���̈ړ���
	m_fRotasion = 0.0f;
	m_fScaleNum = 0.0f;
	m_fSubFlashNum = 0.0f;
	m_fSubNum = 0.0f;
	m_fFadeSpeedNum = 0.0f;
	m_nFlashFlame = 0;
	m_bDisappearFlag = false;
	m_bFadeOut = false;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CScene2D::~CScene2D()
{

}

//=======================================================================================
// Scene�N���X�̐���
//=======================================================================================
CScene2D* CScene2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �I�u�W�F�N�g�𐶐�
	CScene2D* pScene = new CScene2D();

	// !nullcheck
	if (pScene != nullptr)
	{
		// ����������
		pScene->Init(pos, size);
	}

	return pScene;
}

//=======================================================================================
// Scene�N���X�̐��� (Fade�L��)
//=======================================================================================
CScene2D * CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fFadeNum)
{
	// �I�u�W�F�N�g�𐶐�
	CScene2D* pScene = new CScene2D();

	// !nullcheck
	if (pScene != nullptr)
	{
		pScene->m_fFadeSpeedNum = fFadeNum;
		pScene->m_fSubFlashNum = 0.0f;
		pScene->GetColor().a = 0.0f;
		pScene->m_bFadeOut = true;

		// ����������
		pScene->Init(pos, size);
	}

	return pScene;
}

//=======================================================================================
// �|���S���̏�����
//=======================================================================================
HRESULT CScene2D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �������
	SetPos(pos);	// ���W
	SetSize(size);	// �T�C�Y

	// ���_�̐���
	CreateVertex(pos, size);

	return S_OK;
}

//=======================================================================================
// �|���S���̏I������
//=======================================================================================
void CScene2D::Uninit(void)
{
	// �폜�t���O����������
	Release();
}

//=======================================================================================
// �|���S���̍X�V����
//=======================================================================================
void CScene2D::Update(void)
{
	if (m_bFadeOut)
	{
		FadeOut(m_fFadeSpeedNum);
	}
}

//=======================================================================================
// �|���S���̕`�揈��
//=======================================================================================
void CScene2D::Draw(void)
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

//======================================================
//�F�̎擾
//======================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx = nullptr;	//���_���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();		// �o�b�t�@

	// �F�̐ݒ�
	SetColor(col);

	//���_�f�[�^�͈͂����b�N���A���_�o�b�t�@�ւ̃|�C���^������
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�(0~255�̐��l�Őݒ�)
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //r,g,b,a��0~255�͈̔͂Ō��߂邱��
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //r:���b�h g:�O���[���@b:�u���[
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //a�́A�����x��\���Ă���
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	//���_�f�[�^���A�����b�N
	pVtxBuff->Unlock();
}

//=============================================
// ���_�̐����֐�
//=============================================
void CScene2D::CreateVertex(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;		// �o�b�t�@

	// ���_�o�b�t�@�̐���
	pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		nullptr);

	// ���_����ݒ�
	VERTEX_2D *pVtx = nullptr;
	D3DXCOLOR color = GetColor();

	// ���_�f�[�^�����b�N����
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	// ���_�f�[�^���A�����b�N����
	pVtxBuff->Unlock();

	// ���_�o�b�t�@�̐ݒ�
	BindVtxBuff(pVtxBuff);
}

//=============================================
// �A�j���[�V�������擾
//=============================================
void CScene2D::InitAnimation(int nCounterAnim, int nPatternAnim, int nLoop)
{
	m_nCounterAnim = nCounterAnim;
	m_nPatternAnim = nPatternAnim;
	m_nLoop = nLoop;

	// ���_����ݒ�
	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();		// �o�b�t�@�擾

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
void CScene2D::UpdateAnimation(void)
{
	// �����̃A�j���[�V�����J�E���g��i�߂āA�p�^�[����؂�ւ���
	m_nCountAnim++;

	// ���_���(�e�N�X�`�����W)�̍X�V
	if (m_nCountAnim >= m_nCounterAnim)	// �����̑���
	{
		m_nCountAnim = 0;		// �A�j���[�V�����̃J�E���g��0�ɂ���
		m_nCountAnimPattern++;	// �A�j���[�V�����̃p�^�[�����J�E���g������
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
		// ���_����ݒ�
		VERTEX_2D *pVtx = nullptr;
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();		// �o�b�t�@�擾

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

//=============================================
// �e�N�X�`���̃X�N���[�������擾
//=============================================
void CScene2D::InitScroll(int nSpeed, float fDivision)
{
	m_nSpeedTexture = nSpeed;
	m_fDivisionBaseNum = fDivision;
}

//=============================================
// �e�N�X�`���̃X�N���[�������X�V
//=============================================
void CScene2D::UpdateScroll(void)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();		// �o�b�t�@�擾

	// �J�E���^�[��i�߂�
	m_nCounterAnim++;

	// ���_���(�e�N�X�`�����W)�̍X�V
	if (m_nCounterAnim >= m_nSpeedTexture)		// �����̑���
	{
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W���X�V
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - m_fDivisionCounter);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - m_fDivisionCounter);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - m_fDivisionCounter);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - m_fDivisionCounter);

		// ���_�o�b�t�@���A�����b�N����
		pVtxBuff->Unlock();

		// �A�j���[�V�����̃p�^�[�����J�E���g������
		m_fDivisionCounter += m_fDivisionBaseNum;
		m_nCounterAnim = 0;
	}
}

//======================================================
// �g��֐�
//======================================================
void CScene2D::ScaleUp(float fScaleUp)
{
	// ���擾
	D3DXVECTOR3 pos = GetPos();	// ���W
	D3DXVECTOR3 size = GetSize();	// ���W
	m_fScaleNum += fScaleUp;

	VERTEX_2D*pVtx = nullptr;	//���_���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	//���_�f�[�^�͈͂����b�N���A���_�o�b�t�@�ւ̃|�C���^������
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - (size.x / 2 * m_fScaleNum), pos.y - (size.y / 2 * m_fScaleNum), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + (size.x / 2 * m_fScaleNum), pos.y - (size.y / 2 * m_fScaleNum), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - (size.x / 2 * m_fScaleNum), pos.y + (size.y / 2 * m_fScaleNum), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + (size.x / 2 * m_fScaleNum), pos.y + (size.y / 2 * m_fScaleNum), 0.0f);

	//���_�f�[�^���A�����b�N
	pVtxBuff->Unlock();
}

//======================================================
// ���[�e�[�V�����̎擾
//======================================================
void CScene2D::SetRotation(float rotasion)
{
	// ���擾
	D3DXVECTOR3 pos = GetPos();	// ���W
	D3DXVECTOR3 size = GetSize();	// ���W

	// ��]�̒l�����Z
	rotasion += m_fRotasion;

	float r = sqrtf(powf(size.x / 2, 2.0) + powf(size.x / 2, 2.0));	//���a
	float fTheta = atan2(size.x / 2, size.x / 2);					//�V�[�^

	float XAngle = r*cos(fTheta + rotasion);	//X�̊p�x
	float YAngle = r*sin(fTheta + rotasion);	//Y�̊p�x

	VERTEX_2D*pVtx = nullptr;	//���_���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	//���_�f�[�^�͈͂����b�N���A���_�o�b�t�@�ւ̃|�C���^������
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(pos.x + XAngle, pos.y + YAngle, 0.0f);
	XAngle = r*cos(fTheta + D3DXToRadian(90) + rotasion);
	YAngle = r*sin(fTheta + D3DXToRadian(90) + rotasion);
	pVtx[1].pos = D3DXVECTOR3(pos.x + XAngle, pos.y + YAngle, 0.0f);
	XAngle = r*cos(fTheta + D3DXToRadian(-90) + rotasion);
	YAngle = r*sin(fTheta + D3DXToRadian(-90) + rotasion);
	pVtx[2].pos = D3DXVECTOR3(pos.x + XAngle, pos.y + YAngle, 0.0f);
	XAngle = r*cos(fTheta + D3DXToRadian(180) + rotasion);
	YAngle = r*sin(fTheta + D3DXToRadian(180) + rotasion);
	pVtx[3].pos = D3DXVECTOR3(pos.x + XAngle, pos.y + YAngle, 0.0f);

	//���_�f�[�^���A�����b�N
	pVtxBuff->Unlock();

	// ��]��
	m_fRotasion += 0.01f;
}

//=============================================
// �g��̒l�ݒ�
//=============================================
void CScene2D::SetScale(const float &fScale)
{
	m_fScaleNum = fScale;
}

//====================================================================
// �|���S���̓_��
//====================================================================
void CScene2D::FlashPolygon(int nFlashFlame)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �J���[�̌��Z
	m_fSubFlashNum += m_fSubNum;

	// ����ɍs������
	if (m_fSubFlashNum >= 1.0f)
	{
		m_fSubFlashNum = 1.0f;
		m_bDisappearFlag = true;

	}
	else if (m_fSubFlashNum <= 0.0f)
	{
		m_fSubFlashNum = 0;
		m_fSubNum *= -1;
	}

	// ���]���
	if (m_bDisappearFlag == true)
	{
		m_nFlashFlame++;

		if (m_nFlashFlame >= nFlashFlame)
		{
			m_nFlashFlame = 0;
			m_fSubNum *= -1;
			m_bDisappearFlag = false;
		}
	}

	// �J���[���̍X�V
	D3DXCOLOR color = GetColor();

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(color.r, color.g, color.b, color.a - m_fSubFlashNum);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DXCOLOR(color.r, color.g, color.b, color.a - m_fSubFlashNum);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DXCOLOR(color.r, color.g, color.b, color.a - m_fSubFlashNum);	// �������_�̐F	�����x255
	pVtx[3].col = D3DXCOLOR(color.r, color.g, color.b, color.a - m_fSubFlashNum);	// �E�����_�̐F	�����x255

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//====================================================================
// �t�F�[�h�A�E�g
//====================================================================
void CScene2D::FadeOut(float fSpeed)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// �����x�̒l
	m_fSubFlashNum += fSpeed;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���l�𑫂�
	GetColor().a = m_fSubFlashNum;

	// �J���[���̍X�V
	D3DXCOLOR color = GetColor();

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(color.r, color.g, color.b, color.a);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DXCOLOR(color.r, color.g, color.b, color.a);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DXCOLOR(color.r, color.g, color.b, color.a);	// �������_�̐F	�����x255
	pVtx[3].col = D3DXCOLOR(color.r, color.g, color.b, color.a);	// �E�����_�̐F	�����x255

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();

	// �����l�������Ȃ�����
	if (m_fSubFlashNum > 1.0f)
	{
		m_fSubFlashNum = 1.0;
		m_bFadeOut = false;
	}
}