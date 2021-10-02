//=============================================================================
//
// �e�N�X�`���̊Ǘ��N���X [texture.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
	memset(m_apTexture, 0, sizeof(m_apTexture));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{
	for (int nCount = 0; nCount < TEXTURE_TYPE_NUM_MAX; nCount++)
	{
		// ���O�f�[�^�̃N���A
		m_aTexFileName[nCount].clear();
	}
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CTexture * CTexture::Create(void)
{
	// �������m��
	CTexture *pTexture = new CTexture;

	// nullcheck
	if (pTexture)
	{
		// �����l
		pTexture->SetTextureName();
		return pTexture;
	}
	return pTexture;
}

//=============================================================================
// �e�N�X�`���̖��O��ݒ�
//=============================================================================
HRESULT CTexture::SetTextureName(void)
{
	// �ʏ�e�N�X�`��
	m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL] =
	{
		{ "data/Texture/floor.jpg" },					// ��
		{ "data/Texture/target.png" },					// �I
		{ "data/Texture/arrow.png" },					// ���
		{ "data/Texture/byte.png" },					// �V�݂�	
		{ "data/Texture/TitleLogo.png" },				// �^�C�g��
		{ "data/Texture/game_explanation_paper.png" },	// �X�g�[���[�̔w�i
		{ "data/Texture/game_explanation1.png" },		// �X�g�[���[�̕���
		{ "data/Texture/game_explanation2.png" },		// �X�g�[���[�̕���
		{ "data/Texture/game_explanation3.png" },		// �X�g�[���[�̕���
		{ "data/Texture/game_explanation4.png" },		// �X�g�[���[�̕���
		{ "data/Texture/ResultBg.png" },				// ���U���g
		{ "data/Texture/gameclear_story.png" },			// ���U���g�X�g�[���[
		{ "data/Texture/blackback.png" },				// ���U���g�X�g�[���[
		{ "data/Texture/Smoke.png" },					// �X���[�N
		{ "data/Texture/Wave_Effect.png" },				// �g
		{ "data/Texture/R1.png" },						// L1
		{ "data/Texture/Red.png" },						// ��
	};

	// �����e�N�X�`��
	m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE] =
	{
		{ "data/Texture/Move_Ui.png" },					// �ړ���Ui
		{ "data/Texture/Wood_Animation.png" },			// �؍�
		{ "data/Texture/Explosion_Animation.png" },		// ����
	};

	// �{�����[���e�N�X�`��
	m_aTexFileName[TEXTURE_TYPE_NUM_VOLUME] =
	{
		{ "data/Texture/NoiseVolume.dds" }
	};

	// �L���[�u�e�N�X�`��
	m_aTexFileName[TEXTURE_TYPE_NUM_CUBE] =
	{
		{ "data/Texture/suimen8.dds" }
	};

	return E_NOTIMPL;
}

//=============================================================================
// �S�Ẵe�N�X�`�����[�h
//=============================================================================
void CTexture::LoadAll(void)
{
	// �ʏ�e�N�X�`��
	NormalTexLoad();

	// �����e�N�X�`��
	SeparateTexLoad();

	// �{�����[���e�N�X�`��
	VolumeTexLoad();

	// �L���[�u�e�N�X�`��
	CubeTexLoad();
}

//=============================================================================
// �S�Ẵe�N�X�`���A�����[�h
//=============================================================================
void CTexture::UnLoadAll(void)
{
	// �ʏ�e�N�X�`��
	NormalTexUnLoad();

	// �����e�N�X�`��
	SeparateTexUnLoad();

	// �{�����[���e�N�X�`��
	VolumeTexUnLoad();

	// �L���[�u�e�N�X�`��
	CubeTexUnLoad();
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CTexture::NormalTexLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL].size();

	// �e�N�X�`���̓ǂݍ���
	for (size_t nCount = 0; nCount < size; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL][nCount].data(), &m_apTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CTexture::NormalTexUnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_NUM_MAX; nCount++)
	{
		if (m_apTexture[nCount] != nullptr)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = nullptr;
		}
	}
}

//=============================================================================
// �����e�N�X�`���̃��[�h
//=============================================================================
HRESULT CTexture::SeparateTexLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE].size();

	// �����e�N�X�`���̓ǂݍ���
	for (size_t nCount = 0; nCount < size; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE][nCount].data(), &m_apSeparateTexture[nCount].pSeparateTexture);
	}
	return S_OK;
}

//=============================================================================
// �����e�N�X�`���̃A�����[�h
//=============================================================================
void CTexture::SeparateTexUnLoad(void)
{
	// �e�N�X�`���̉��
	for (int nCount = 0; nCount < SEPARATE_TEX_MAX; nCount++)
	{
		if (m_apSeparateTexture[nCount].pSeparateTexture != nullptr)
		{
			m_apSeparateTexture[nCount].pSeparateTexture->Release();
			m_apSeparateTexture[nCount].pSeparateTexture = nullptr;
		}
	}
}

//=============================================================================
// �e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE_TYPE Tex_Num)
{
	if (Tex_Num < TEXTURE_NUM_MAX)
	{
		if (m_apTexture[Tex_Num] != nullptr)
		{
			return m_apTexture[Tex_Num];
		}
	}

	return nullptr;
}

//=============================================================================
// �����e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// NULLcheck
		if (m_apSeparateTexture[SepaTex_Type].pSeparateTexture != nullptr)
		{
			// �e�N�X�`�����
			return m_apSeparateTexture[SepaTex_Type].pSeparateTexture;
		}
	}

	return nullptr;
}

//=============================================================================
// �����e�N�X�`���̏��
//=============================================================================
D3DXVECTOR2 CTexture::GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// �e�N�X�`�����
		return m_apSeparateTexture[SepaTex_Type].m_TexInfo;
	}

	return D3DXVECTOR2(0.0f, 0.0f);
}

//=============================================================================
// �����e�N�X�`���̃��[�v�t���O
//=============================================================================
bool CTexture::GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// �e�N�X�`�����
		return m_apSeparateTexture[SepaTex_Type].bLoop;
	}

	return false;
}

//=============================================================================
// �{�����[���e�N�X�`�����[�h
//=============================================================================
HRESULT CTexture::VolumeTexLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

	size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_VOLUME].size();
	// �e�N�X�`���̓ǂݍ���
	for (size_t nCount = 0; nCount < size; nCount++)
	{
		D3DXCreateVolumeTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_VOLUME][nCount].data(), &m_pVolumeTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// �{�����[���e�N�X�`���A�����[�h
//=============================================================================
void CTexture::VolumeTexUnLoad(void)
{
	for (int nCount = 0; nCount < VOLUME_TEX_MAX; nCount++)
	{
		if (m_pVolumeTexture[nCount] != nullptr)
		{
			m_pVolumeTexture[nCount]->Release();
			m_pVolumeTexture[nCount] = nullptr;
		}
	}
}

//=============================================================================
// �{�����[���e�N�X�`���̏��
//=============================================================================
LPDIRECT3DVOLUMETEXTURE9 CTexture::GetVolumeTexture(VOLUME_TEX_TYPE Tex_Type)
{
	if (Tex_Type < VOLUME_TEX_MAX)
	{
		if (m_pVolumeTexture[Tex_Type] != nullptr)
		{
			return m_pVolumeTexture[Tex_Type];
		}
	}

	return nullptr;
}

//=============================================================================
// �L���[�u�e�N�X�`�����[�h
//=============================================================================
HRESULT CTexture::CubeTexLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

	size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_CUBE].size();
	// �e�N�X�`���̓ǂݍ���
	for (size_t nCount = 0; nCount < m_aTexFileName[TEXTURE_TYPE_NUM_CUBE].size(); nCount++)
	{
		D3DXCreateCubeTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_CUBE][nCount].data(), &m_pCubeTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// �L���[�u�e�N�X�`���A�����[�h
//=============================================================================
void CTexture::CubeTexUnLoad(void)
{
	for (int nCount = 0; nCount < CUBE_TEX_MAX; nCount++)
	{
		if (m_pCubeTexture[nCount] != nullptr)
		{
			m_pCubeTexture[nCount]->Release();
			m_pCubeTexture[nCount] = nullptr;
		}
	}
}

//=============================================================================
// �L���[�u�e�N�X�`���̏��
//=============================================================================
LPDIRECT3DCUBETEXTURE9 CTexture::GetCubeTexture(CUBE_TEX_TYPE Tex_Type)
{
	if (Tex_Type < CUBE_TEX_MAX)
	{
		if (m_pVolumeTexture[Tex_Type] != nullptr)
		{
			return m_pCubeTexture[Tex_Type];
		}
	}

	return nullptr;
}