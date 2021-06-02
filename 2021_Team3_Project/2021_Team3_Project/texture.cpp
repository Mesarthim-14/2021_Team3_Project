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

	// 通常テクスチャの名前の設定
	m_aTexFileName =
	{
		{ "data/Texture/floor.jpg" },
	};

	// 分割テクスチャの名前の設定
	m_aSparateTexFileName =
	{
	//	{"data/Texture/sharp_effect.png"},				// 鋭いエフェクト
	};
}

//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{
	// 通常テクスチャクリア
	m_aTexFileName.clear();

	// 分割テクスチャクリア
	m_aSparateTexFileName.clear();
}

//=============================================================================
// インスタンス生成
//=============================================================================
CTexture * CTexture::Create(void)
{
	// メモリ確保
	CTexture *pTexture = new CTexture;

	return pTexture;
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CTexture::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	for (size_t nCount = 0; nCount < m_aTexFileName.size(); nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aTexFileName[nCount].data(), &m_apTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CTexture::UnLoad(void)
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

	// 分割テクスチャの読み込み
	for (size_t nCount = 0; nCount < m_aSparateTexFileName.size(); nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aSparateTexFileName[nCount].data(), &m_apSeparateTexture[nCount].pSeparateTexture);
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