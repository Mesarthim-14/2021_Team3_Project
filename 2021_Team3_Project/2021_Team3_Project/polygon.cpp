//=============================================================================
//
// ポリゴン生成クラス処理 [polygon.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "polygon.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPolygon::CPolygon()
{
	m_pVtxBuff = nullptr;
	m_pos = ZeroVector3;
	m_Size = ZeroVector3;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPolygon::~CPolygon()
{

}

//=============================================================================
// インスタンス生成処理
//=============================================================================
CPolygon * CPolygon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// ポリゴンクラスのポインタ変数
	CPolygon *pPolygon = nullptr;

	//メモリの確保
	pPolygon = new CPolygon;

	// !nullcheck
	if (pPolygon != nullptr)
	{
		//初期化処理呼び出し
		pPolygon->Init(pos, size);

		return pPolygon;

	}

	return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPolygon::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	//デバイスの取得
	VERTEX_2D *pVtx = nullptr;												//頂点情報へのポインタ

	m_pos = pos;	//初期位置の設定
	m_Size = size;	//大きさの設定

	//頂点バッファの作成
	pD3DDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX,	//バッファサイズ
		D3DUSAGE_WRITEONLY,				//（固定）
		FVF_VERTEX_2D,					//フォーマット
		D3DPOOL_MANAGED,				//(固定)
		&m_pVtxBuff,
		nullptr
	);

	//頂点データをロックし、頂点バッファへのポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-m_Size.x / 2), m_pos.y + (-m_Size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_Size.x / 2), m_pos.y + (-m_Size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-m_Size.x / 2), m_pos.y + (m_Size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_Size.x / 2), m_pos.y + (m_Size.y / 2), 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPolygon::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CPolygon::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CPolygon::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	//デバイスのポインタ

	//頂点バッファをデバイスのデータストリームにバインド
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pD3DDevice->SetTexture(0, nullptr);

	// ポリゴンの描画
	pD3DDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,
		NUM_POLYGON);	//ポリゴン数

	//テクスチャの設定を元に戻す
	pD3DDevice->SetTexture(0, nullptr);
}

//=============================================================================
// 色の設定
//=============================================================================
void CPolygon::SetColor(const D3DXCOLOR color)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点データをロックし、頂点バッファへのポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//カラーの設定
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}