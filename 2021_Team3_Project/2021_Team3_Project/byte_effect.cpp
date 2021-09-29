//=============================================================================
// 噛みつきエフェクト [byte_effect.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "byte_effect.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define MOVE_VALUE	(D3DXVECTOR3(0.0f,30.0f,0.0f))					// 移動量
#define COL			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))				// 色
#define UP_POS		(D3DXVECTOR3(pos.x,pos.y + size.y,pos.z))		// 位置
#define DOWN_POS	(D3DXVECTOR3(pos.x,pos.y - size.y,pos.z))		// 位置
#define UP_ROT		(D3DXVECTOR3(0.0f,0.0f,D3DXToRadian(0.0f)))		// 向き
#define DOWN_ROT	(D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)))	// 向き
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Effect::CByte_Effect(PRIORITY Priority) : CScene3D(Priority)
{
	m_rot		= ZeroVector3;
	m_SavePos	= ZeroVector3;
	m_Type		= TYPE_NONE;
	bEndByte	= false;
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Effect::~CByte_Effect()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Effect * CByte_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot,TYPE type)
{
	// CByte_Effectのポインタ
	CByte_Effect *pByte_Effect = nullptr;

	// nullcheck
	if (pByte_Effect == nullptr)
	{
		// メモリ確保
		pByte_Effect = new CByte_Effect;

		// !nullcheck
		if (pByte_Effect != nullptr)
		{
			// 代入
			pByte_Effect->m_Type = type;

			// 初期化処理
			pByte_Effect->Init(pos, size);

			// 向き設定
			pByte_Effect->SetRot(rot);
		}
	}
	// ポインタを返す
	return pByte_Effect;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CByte_Effect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 位置
	D3DXVECTOR3 Pos = ZeroVector3;

	// UPの場合
	if (m_Type == TYPE_UP)
	{
		// 代入
		Pos = UP_POS;
	}
	// DOWNの場合
	if (m_Type == TYPE_DOWN)
	{
		// 代入
		Pos = DOWN_POS;
	}

	// 初期化処理
	CScene3D::Init(Pos, size);

	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_BYTE));

	// 位置保存
	m_SavePos = pos;

	// 向き
	D3DXVECTOR3 rot = GetRot();

	// UPの場合
	if (m_Type == TYPE_UP)
	{
		// 向き
		rot += UP_ROT;
	}
	// DOWNの場合
	if (m_Type == TYPE_DOWN)
	{
		// 向き
		rot -= DOWN_ROT;

		m_rot = rot;
	}

	// 色設定
	SetColor(COL);

	// 加算合成
	SetBlend(true);

	// 向き設定
	SetRot(rot);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Effect::Uninit(void)
{
	// 終了処理
	CScene3D::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Effect::Update(void)
{
	// 更新処理
	CScene3D::Update();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// UPの場合
	if (m_Type == TYPE_UP)
	{
		// 位置がpos.y以下の場合
		if (pos.y >= m_SavePos.y)
		{
			// 移動
			Move();
		}
		else
		{
			// trueに
			bEndByte = true;
		}
	}
	// DOWNの場合
	if (m_Type == TYPE_DOWN)
	{
		// 向き設定
		SetRot(m_rot);

		// 位置がpos.y以下の場合
		if (pos.y <= m_SavePos.y)
		{
			// 移動
			Move();
		}
		else
		{
			// trueに
			bEndByte = true;
		}
	}
	// trueの場合
	if (bEndByte == true)
	{
		// 終了
		Uninit();
		return;
	}
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Effect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

	// かぶさらないようにする　(Zバッファ)
	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	// 描画処理
	CScene3D::Draw();

	// かぶさらないようにする　(Zバッファ)
	pDevice->SetRenderState(D3DRS_ZENABLE, true);
	
}
//=============================================================================
// エフェクト生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Effect::CrateEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	// 上生成
	Create(pos, size, rot, TYPE_UP);

	// 下生成
	Create(pos, size, rot, TYPE_DOWN);
}
//=============================================================================
// 移動処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Effect::Move(void)
{
	// 移動
	D3DXVECTOR3 move = ZeroVector3;

	// UPの場合
	if (m_Type == TYPE_UP)
	{
		// 移動
		move.y = -MOVE_VALUE.y;
	}
	// DOWNの場合
	if (m_Type == TYPE_DOWN)
	{
		// 移動
		move.y = MOVE_VALUE.y;
	}

	// 移動
	SetMove(move);
}