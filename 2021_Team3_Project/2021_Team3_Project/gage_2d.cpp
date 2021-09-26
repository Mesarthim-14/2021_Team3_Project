//=============================================================================
// 2Dゲージ [gage_2d.h]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "gage_2d.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define TEX_MIN		(0.0f)								// テクスチャ最小
#define TEX_MAX		(1.0f)								// テクスチャ最大
#define SUB_GAGE	(1)									// ゲージの値を引く値
#define COL			(D3DCOLOR_RGBA(255, 255, 255, 255))	// 色
#define GAGE_MIN	(0)									// 0.0f
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CGage_2D::CGage_2D(PRIORITY nPriority) : CSceneBase(nPriority)
{
	m_nGageNum		= ZERO_INT;
	m_fGageNum		= ZERO_FLOAT;
	m_fMaxGageNum	= ZERO_FLOAT;
	m_nAlphaNum		= ZERO_INT;
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CGage_2D::~CGage_2D()
{
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CGage_2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ゲージの値算出
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファ変数の宣言
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		nullptr);

	// 頂点情報へのポインタ
	VERTEX_2D*pVtx = nullptr;

	// 変数代入
	SetPos(pos);
	SetSize(size);

	//頂点バッファをロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標設定の設定
	// 位置とサイズ
	pVtx[0].pos = D3DXVECTOR3((pos.x - size.x / DIVIDE_2), (pos.y - size.y / DIVIDE_2), size.z);
	pVtx[1].pos = D3DXVECTOR3((pos.x + size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (pos.y - size.y / DIVIDE_2), size.z);
	pVtx[2].pos = D3DXVECTOR3((pos.x - size.x / DIVIDE_2), (pos.y + size.y / DIVIDE_2), size.z);
	pVtx[3].pos = D3DXVECTOR3((pos.x + size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (pos.y + size.y / DIVIDE_2), size.z);

	// 頂点カラーの設定
	pVtx[0].col = COL;
	pVtx[1].col = COL;
	pVtx[2].col = COL;
	pVtx[3].col = COL;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 各頂点の法線の設定
	pVtx[0].tex = D3DXVECTOR2(TEX_MIN, TEX_MIN);
	pVtx[1].tex = D3DXVECTOR2(TEX_MAX, TEX_MIN);
	pVtx[2].tex = D3DXVECTOR2(TEX_MIN, TEX_MAX);
	pVtx[3].tex = D3DXVECTOR2(TEX_MAX, TEX_MAX);

	// 頂点バッファのアンロック
	pVtxBuff->Unlock();

	// バッファの受け渡し
	BindVtxBuff(pVtxBuff);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_2D::Uninit(void)
{
	// オブジェクト破棄
	Release();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_2D::Update(void)
{
	// 0.0f以下の場合
	if (m_nGageNum <= GAGE_MIN)
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
void CGage_2D::Draw(void)
{
	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//アルファテストを有効化
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//アルファテスト基準値の設定
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//アルファテストの比較方法の設定(GREATERは基準値より大きい場合)
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 頂点バッファをデータストリームに設定
	pD3DDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pD3DDevice->SetTexture(0, GetTexture());

	// ポリゴンの描画
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);

	//アルファテストを無効化
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// テクスチャの設定
	pD3DDevice->SetTexture(0, nullptr);
}
//=============================================================================
// 位置設定処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_2D::SetPosition(D3DXVECTOR3 pos)
{
	// ゲージの値算出
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

	// 座標設定
	SetPos(pos);

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 頂点情報を設定
	VERTEX_2D *pVtx = nullptr;

	// バッファ取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定の設定
	pVtx[0].pos = D3DXVECTOR3((pos.x - size.x / DIVIDE_2), (pos.y - size.y / DIVIDE_2), size.z);
	pVtx[1].pos = D3DXVECTOR3((pos.x + size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (pos.y - size.y / DIVIDE_2), size.z);
	pVtx[2].pos = D3DXVECTOR3((pos.x - size.x / DIVIDE_2), (pos.y + size.y / DIVIDE_2), size.z);
	pVtx[3].pos = D3DXVECTOR3((pos.x + size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (pos.y + size.y / DIVIDE_2), size.z);

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}
//=============================================================================
// 色設定処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_2D::SetColor(D3DXCOLOR col)
{
	CSceneBase::SetColor(col);

	// 頂点情報へのポインタ
	VERTEX_2D*pVtx = nullptr;

	// バッファの取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	//頂点バッファをロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//頂点カラーの設定（0～255の数値で設定）
		pVtx[nCount].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	}

	//頂点バッファのアンロック
	pVtxBuff->Unlock();
}
//=============================================================================
// ゲージの値設定処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_2D::SetGageNum(int nGageNum)
{
	// 代入
	m_nGageNum = nGageNum;

	// ゲージの値算出
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 頂点情報を設定
	VERTEX_2D *pVtx = nullptr;

	// バッファ取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定の設定
	pVtx[0].pos = D3DXVECTOR3((pos.x - size.x / DIVIDE_2), (pos.y - size.y / DIVIDE_2), size.z);
	pVtx[1].pos = D3DXVECTOR3((pos.x + size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (pos.y - size.y / DIVIDE_2), size.z);
	pVtx[2].pos = D3DXVECTOR3((pos.x - size.x / DIVIDE_2), (pos.y + size.y / DIVIDE_2), size.z);
	pVtx[3].pos = D3DXVECTOR3((pos.x + size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (pos.y + size.y / DIVIDE_2), size.z);

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}
//=============================================================================
// ゲージの最大値設定処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_2D::SetMaxGageNum(int nMaxGageNum)
{
	// floatに変換
	m_fMaxGageNum = (float)nMaxGageNum;
}