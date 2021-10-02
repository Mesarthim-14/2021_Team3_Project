//=============================================================================
//
// テクスチャの管理クラス [texture.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()
{
	memset(m_apTexture, 0, sizeof(m_apTexture));
}

//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{
	for (int nCount = 0; nCount < TEXTURE_TYPE_NUM_MAX; nCount++)
	{
		// 名前データのクリア
		m_aTexFileName[nCount].clear();
	}
}

//=============================================================================
// インスタンス生成
//=============================================================================
CTexture * CTexture::Create(void)
{
	// メモリ確保
	CTexture *pTexture = new CTexture;

	// nullcheck
	if (pTexture)
	{
		// 初期値
		pTexture->SetTextureName();
		return pTexture;
	}
	return pTexture;
}

//=============================================================================
// テクスチャの名前を設定
//=============================================================================
HRESULT CTexture::SetTextureName(void)
{
	// 通常テクスチャ
	m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL] =
	{
		{ "data/Texture/floor.jpg" },					// 床
		{ "data/Texture/target.png" },					// 的
		{ "data/Texture/arrow.png" },					// 矢印
		{ "data/Texture/byte.png" },					// 儼みつき	
		{ "data/Texture/TitleLogo.png" },				// タイトル
		{ "data/Texture/game_explanation_paper.png" },	// ストーリーの背景
		{ "data/Texture/game_explanation1.png" },		// ストーリーの文章
		{ "data/Texture/game_explanation2.png" },		// ストーリーの文章
		{ "data/Texture/game_explanation3.png" },		// ストーリーの文章
		{ "data/Texture/game_explanation4.png" },		// ストーリーの文章
		{ "data/Texture/ResultBg.png" },				// リザルト
		{ "data/Texture/gameclear_story.png" },			// リザルトストーリー
		{ "data/Texture/blackback.png" },				// リザルトストーリー
		{ "data/Texture/Smoke.png" },					// スモーク
		{ "data/Texture/Wave_Effect.png" },				// 波
		{ "data/Texture/R1.png" },						// L1
		{ "data/Texture/Red.png" },						// 赤
	};

	// 分割テクスチャ
	m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE] =
	{
		{ "data/Texture/Move_Ui.png" },					// 移動のUi
		{ "data/Texture/Wood_Animation.png" },			// 木材
		{ "data/Texture/Explosion_Animation.png" },		// 爆発
	};

	// ボリュームテクスチャ
	m_aTexFileName[TEXTURE_TYPE_NUM_VOLUME] =
	{
		{ "data/Texture/NoiseVolume.dds" }
	};

	// キューブテクスチャ
	m_aTexFileName[TEXTURE_TYPE_NUM_CUBE] =
	{
		{ "data/Texture/suimen8.dds" }
	};

	return E_NOTIMPL;
}

//=============================================================================
// 全てのテクスチャロード
//=============================================================================
void CTexture::LoadAll(void)
{
	// 通常テクスチャ
	NormalTexLoad();

	// 分割テクスチャ
	SeparateTexLoad();

	// ボリュームテクスチャ
	VolumeTexLoad();

	// キューブテクスチャ
	CubeTexLoad();
}

//=============================================================================
// 全てのテクスチャアンロード
//=============================================================================
void CTexture::UnLoadAll(void)
{
	// 通常テクスチャ
	NormalTexUnLoad();

	// 分割テクスチャ
	SeparateTexUnLoad();

	// ボリュームテクスチャ
	VolumeTexUnLoad();

	// キューブテクスチャ
	CubeTexUnLoad();
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CTexture::NormalTexLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL].size();

	// テクスチャの読み込み
	for (size_t nCount = 0; nCount < size; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL][nCount].data(), &m_apTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// テクスチャアンロード
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
// 分割テクスチャのロード
//=============================================================================
HRESULT CTexture::SeparateTexLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE].size();

	// 分割テクスチャの読み込み
	for (size_t nCount = 0; nCount < size; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE][nCount].data(), &m_apSeparateTexture[nCount].pSeparateTexture);
	}
	return S_OK;
}

//=============================================================================
// 分割テクスチャのアンロード
//=============================================================================
void CTexture::SeparateTexUnLoad(void)
{
	// テクスチャの解放
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
// テクスチャ情報
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
// 分割テクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// NULLcheck
		if (m_apSeparateTexture[SepaTex_Type].pSeparateTexture != nullptr)
		{
			// テクスチャ情報
			return m_apSeparateTexture[SepaTex_Type].pSeparateTexture;
		}
	}

	return nullptr;
}

//=============================================================================
// 分割テクスチャの情報
//=============================================================================
D3DXVECTOR2 CTexture::GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// テクスチャ情報
		return m_apSeparateTexture[SepaTex_Type].m_TexInfo;
	}

	return D3DXVECTOR2(0.0f, 0.0f);
}

//=============================================================================
// 分割テクスチャのループフラグ
//=============================================================================
bool CTexture::GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// テクスチャ情報
		return m_apSeparateTexture[SepaTex_Type].bLoop;
	}

	return false;
}

//=============================================================================
// ボリュームテクスチャロード
//=============================================================================
HRESULT CTexture::VolumeTexLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

	size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_VOLUME].size();
	// テクスチャの読み込み
	for (size_t nCount = 0; nCount < size; nCount++)
	{
		D3DXCreateVolumeTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_VOLUME][nCount].data(), &m_pVolumeTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// ボリュームテクスチャアンロード
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
// ボリュームテクスチャの情報
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
// キューブテクスチャロード
//=============================================================================
HRESULT CTexture::CubeTexLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

	size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_CUBE].size();
	// テクスチャの読み込み
	for (size_t nCount = 0; nCount < m_aTexFileName[TEXTURE_TYPE_NUM_CUBE].size(); nCount++)
	{
		D3DXCreateCubeTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_CUBE][nCount].data(), &m_pCubeTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// キューブテクスチャアンロード
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
// キューブテクスチャの情報
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