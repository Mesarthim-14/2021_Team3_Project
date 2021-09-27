//=============================================================================
//
// �n�ʃt�B�[���h�N���X [ground.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "water.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"
#include "game.h"
#include "manager.h"
#include "light.h"
#include "game.h"
#include "camera.h"
#include "player.h"
#include "wave.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define WATER_WIDTH					(150)			// ������
#define WATER_HEIGHT				(150)			// ������
#define WATER_WIDTH_SIZE			(120000.0f)		// �T�C�Y
#define WATER_HEIGHT_SIZE			(120000.0f)		// �T�C�Y

#define WATER_GRAVITY				(0.01f)			// ���Ɋ|����d��
#define WAVE_TIME_INTER				(1.0f)			// �g�̑��x
#define WAVE_HEIGHT					(30)			// �g�̊Ԋu 30
#define WATER_POWER					(1.2f)			// �U�ꕝ 5.0f

//=========================================================================
// �ÓI�ϐ��̏�����
//=========================================================================
LPD3DXEFFECT CWater::m_pEffect = nullptr;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWater::CWater(PRIORITY Priority) : CMeshField(Priority)
{
	D3DXMatrixIdentity(&m_mtxWorld);
	m_fFileTime = 0.0f;
	m_pWave = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWater::~CWater()
{
}

//=============================================================================
// �|���S������
//=============================================================================
CWater * CWater::Create(void)
{
	// �������m��
	CWater *pWater = new CWater;

	// nullchack
	if (pWater != nullptr)
	{
		// ����������
		pWater->Init();
	}

	return pWater;
}

//=============================================================================
// �V�F�[�_����
//=============================================================================
HRESULT CWater::LoadShaderFile(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;
	ID3DXBuffer *error = 0;

	// �G�t�F�N�g�t�@�C���̓ǂݍ���
	D3DXCreateEffectFromFile(pDevice, "hlsl.fx", NULL, NULL,
		0, NULL, &m_pEffect, &error);

	return S_OK;
}

//=============================================================================
// �V�F�[�_�t�@�C���̃A�����[�h
//=============================================================================
void CWater::UnLoadShaderFile(void)
{
	// �V�F�[�_�G�t�F�N�g
	if (m_pEffect)
	{
		m_pEffect->Release();
		m_pEffect = nullptr;
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CWater::Init(void)
{
	// ���̐ݒ�
	D3DXVECTOR3 size = D3DXVECTOR3(WATER_WIDTH_SIZE, 0.0f, WATER_HEIGHT_SIZE);
	INT_VERTEX_2D PieceNum = { WATER_WIDTH , WATER_HEIGHT };

	// ���b�V�����̐ݒ�
	SetInfo(size, PieceNum);

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	m_pNoiseVolumeTexture = pTexture->GetVolumeTexture(CTexture::VOLUME_TEX_NOISE);
	m_pEnvironmentTexture = pTexture->GetCubeTexture(CTexture::CUBE_TEX_OCEAN);

	// ���_�̐ݒ�
	CreateVerterx();
	
	// nullcheck
	if (!m_pWave)
	{
		// �C���X�^���X����
		m_pWave = CWave::Create(WAVE_TIME_INTER, WATER_POWER, WAVE_HEIGHT);
	}

	// �}�g���N�X�̐ݒ�
	SetMatrix();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CWater::Uninit(void)
{
	// �g�̗h��
	if (m_pWave)
	{
		delete m_pWave;
		m_pWave = nullptr;
	}

	// �I������
	CMeshField::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CWater::Update(void)
{
	if (m_pWave)
	{
		// �g�̏���
		Wave();
		m_pWave->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CWater::Draw(void)
{
	// nullcheck
	if (m_pEffect)
	{
		LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;	//�f�o�C�X���̎擾
		D3DXMATRIXA16 matSuimen;							// ���ʂ̕`��
		D3DXMATRIX mtxRot, mtxTrans, mtxScale;				// �}�g���N�X

		// �����_�[�X�e�[�g�̐ݒ�
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			// ���ʂ��i�����j���J�����O

		//���[���h�}�g���b�N�X�̏�����	
		D3DXMatrixIdentity(&m_mtxWorld);

		m_pEffect->OnResetDevice();

		// ���C�g�̕���
		D3DXVECTOR3 LightDir = CManager::GetModePtr()->GetLight()->GetLightDir();
		m_pEffect->SetValue("lightDir1", (void*)(FLOAT*)&D3DXVECTOR3(0.577f, -0.577f, 0.577f), sizeof(D3DXVECTOR3));

		// �J�����ʒu���Z�b�g
		D3DXVECTOR3 CameraPos = CManager::GetModePtr()->GetCamera()->GetposV();
		D3DXMATRIX matView = CManager::GetModePtr()->GetCamera()->GetMtxView();
		D3DXMATRIX matProj = CManager::GetModePtr()->GetCamera()->GetMtxProj();
		m_pEffect->SetValue("CameraPos", (void*)(FLOAT*)CameraPos, sizeof(D3DXVECTOR3));

		// �v���C���[�̍��W
		D3DXVECTOR3 PlayerPos = CManager::GetModePtr()->GetPlayer()->GetPos();
		m_pEffect->SetValue("PlayerPos", (void*)(FLOAT*)CameraPos, sizeof(D3DXVECTOR3));

		D3DXMatrixIdentity(&matSuimen);

		// ���ʉ�]�𔽉f
		D3DXVECTOR3 rot = GetRot();
		D3DXMatrixRotationYawPitchRoll(
			&mtxRot,
			rot.y,
			rot.x,
			rot.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// ���ʂ̒��S�ƃv���C���[�̒��S
		D3DXVECTOR3 pos = GetPos();
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// �}�g���N�X�̐ݒ�
		D3DXMatrixMultiply(&matSuimen, &matSuimen, &m_mtxWorld);

		// �s���ݒ� 
		D3DXMATRIX matWorldViewProj = matSuimen * matView * matProj;
		D3DXMATRIX matWorldPlayer = m_MatPlayer * matView * matProj;

		// �V�F�[�_�ɒl��n��
		m_pEffect->SetValue("WorldViewProjectionPlayer", (void*)(FLOAT*)matWorldPlayer, sizeof(D3DXMATRIX));
		m_pEffect->SetValue("WorldViewProjection", (void*)(FLOAT*)matWorldViewProj, sizeof(D3DXMATRIX));
		m_pEffect->SetValue("LightDirection", (void*)(FLOAT*)D3DXVECTOR3(-1, 1, -1), sizeof(D3DXVECTOR3));
		m_pEffect->SetValue("DiffuseColor", (void*)(FLOAT*)D3DXVECTOR4(0.7f, 0.7f, 0.7f, 0.7f), sizeof(D3DXVECTOR4));

		// �^�C���𑗂�
		m_pEffect->SetFloat("Time", m_fFileTime);
		m_fFileTime += 0.01f;

		// ���̃e�N�j�b�N�����ɕK�v�ȃp�����[�^�[��ݒ�
		m_pEffect->SetValue("NoiseTex", (void*)&m_pNoiseVolumeTexture, sizeof(LPDIRECT3DBASETEXTURE9));
		m_pEffect->SetValue("skyBoxTex", (void*)&m_pEnvironmentTexture, sizeof(LPDIRECT3DBASETEXTURE9));

		// �e�N�j�b�N��ݒ�
		D3DXHANDLE hTechnique = m_pEffect->GetTechniqueByName("Ocean");
		UINT numPasses;
		m_pEffect->SetTechnique(hTechnique);
		m_pEffect->Begin(&numPasses, 0);

		for (UINT nCount = 0; nCount < numPasses; nCount++)
		{
			m_pEffect->BeginPass(nCount);

			// ���_�̐�
			LPDIRECT3DVERTEXBUFFER9 VtxBuff = GetVtxBuff();
			LPDIRECT3DINDEXBUFFER9 IdxBuff = GetIdxBuff();
			int nNumVertex = GetNumVertex();
			int nNumPolygon = GetNumPolygon();

			// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, VtxBuff,
				0, sizeof(VERTEX_3D));

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetIndices(IdxBuff);

			// ���_���
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,
				0,
				0,
				nNumVertex,
				0,
				nNumPolygon);

			m_pEffect->EndPass();
		}

		m_pEffect->End();
	}
}

//=============================================================================
// �g�̏���
//=============================================================================
void CWater::Wave(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();		// �o�b�t�@
	VERTEX_3D *pVtx = nullptr;

	// ���b�V�����擾
	D3DXVECTOR3 OneSize = GetOneSize();
	D3DXVECTOR3 AllSize = GetSize();
	INT_VERTEX_2D PieceNum = GetPieceNum();

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���̃J�E���g
	for (int nCntV = 0; nCntV < PieceNum.x + 1; nCntV++)
	{
		// �c�̃J�E���g
		for (int nCntH = 0; nCntH < PieceNum.y + 1; nCntH++)
		{
			// ���_�̕ύX
			pVtx[(nCntV * (PieceNum.y + 1)) + nCntH].pos.y += m_pWave->Wave(nCntV, nCntH);
		}
	}

	// ���_�f�[�^���A�����b�N����
	pVtxBuff->Unlock();

	// ���_�o�b�t�@�̐ݒ�
	BindVtxBuff(pVtxBuff);
}

//=============================================================================
// �}�g���N�X�̐ݒ�
//=============================================================================
void CWater::SetMatrix(void)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	// ���ʉ�]�𔽉f
	D3DXVECTOR3 rot = GetRot();
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// ���ʂ̒��S�ƃv���C���[�̒��S
	D3DXVECTOR3 pos = GetPos();
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	// ���ʂ̒��S�ƃv���C���[�̒��S
	D3DXMatrixTranslation(&m_MatPlayer,
		-10000.0f, 0.0f, 5000.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// �}�g���N�X�̐ݒ�
	D3DXMatrixMultiply(&m_MatPlayer, &m_MatPlayer, &m_mtxWorld);
}