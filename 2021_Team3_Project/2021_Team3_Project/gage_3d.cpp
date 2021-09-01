//=============================================================================
// 3Dゲージ [gage_3d.h]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "gage_3d.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define NOR			(D3DXVECTOR3 (0.0f,1.0f,0.0f))		// 法線
#define TEX_MIN		(0.0f)								// テクスチャ最小
#define TEX_MAX		(1.0f)								// テクスチャ最大
#define SUB_GAGE	(1)									// ゲージの値を引く値
#define COL			(D3DCOLOR_RGBA(255, 255, 255, 255))	// 色
#define GAGE_MIN	(0)									// 0.0f
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CGage_3D::CGage_3D(PRIORITY nPriority) : CSceneBase(nPriority)
{
	m_nGageNum		= ZERO_INT;
	m_fGageNum		= ZERO_FLOAT;
	m_fMaxGageNum	= ZERO_FLOAT;
	m_nAlphaNum		= ZERO_INT;
	m_bAlpha		= false;
	m_bBlend		= false;
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CGage_3D::~CGage_3D()
{
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CGage_3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ゲージの値算出
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	

	// 頂点バッファ変数の宣言
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;							

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		nullptr);

	// バーテックス
	VERTEX_3D*pVtx = nullptr;

	// 変数代入
	SetPos(pos);
	SetSize(size);

	//頂点バッファをロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標設定の設定
	// 位置とサイズ
	pVtx[0].pos = D3DXVECTOR3((-size.x / DIVIDE_2), (size.y / DIVIDE_2), size.z);
	pVtx[1].pos = D3DXVECTOR3((size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (size.y / DIVIDE_2), size.z);
	pVtx[2].pos = D3DXVECTOR3((-size.x / DIVIDE_2), (-size.y / DIVIDE_2), size.z);
	pVtx[3].pos = D3DXVECTOR3((size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (-size.y / DIVIDE_2), size.z);

	// 各頂点の法線の設定
	pVtx[0].nor = NOR;
	pVtx[1].nor = NOR;
	pVtx[2].nor = NOR;
	pVtx[3].nor = NOR;

	// 頂点カラーの設定
	pVtx[0].col = COL;
	pVtx[1].col = COL;
	pVtx[2].col = COL;
	pVtx[3].col = COL;

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
void CGage_3D::Uninit(void)
{
	// オブジェクト破棄
	Release();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_3D::Update(void)
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
void CGage_3D::Draw(void)
{
	// デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 色の設定
	D3DMATERIAL9 material, OldMaterial;
	D3DXCOLOR color = GetColor();
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = color;
	material.Diffuse = color;
	pDevice->GetMaterial(&OldMaterial);
	pDevice->SetMaterial(&material);

	// 光の影響を無くす
	DWORD ambient;
	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	pDevice->LightEnable(0, FALSE);

	// アルファテストを有力化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// 加算合成
	if (m_bBlend == true)
	{
		// 加算合成を行う
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// aデスティネーションカラー
	}

	// アルファテストが有効なら
	if (m_bAlpha == true)
	{
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0xC0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	}
	else
	{
		// アルファテスト基準値の設定
		pDevice->SetRenderState(D3DRS_ALPHAREF, m_nAlphaNum);
	}

	//計算用のマトリクス
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転の逆行列の生成
	pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
	D3DXMatrixInverse(&m_mtxWorld, nullptr,
		&mtxRot);

	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;

	// サイズ情報
	D3DXVECTOR3 pos = GetPos();

	// 位置を反映、ワールドマトリクス設定、ポリゴン描画
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// ワールドマトリクスの設定 初期化、向き、位置
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// テクスチャの設定
	pDevice->SetTexture(0, GetTexture());

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// テクスチャをnullptr
	pDevice->SetTexture(0, nullptr);

	// アルファテストが有効でなかったら
	if (m_bAlpha != true)
	{
		// アルファテスト基準値の設定
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	}

	// 加算合成を行う処理
	if (m_bBlend == true)
	{
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// aデスティネーションカラー
	}

	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);	// アンビエントを戻す

	pDevice->SetMaterial(&OldMaterial);					// マテリアルを元に戻す

	// アルファテスト無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->LightEnable(0, TRUE);
}
//=============================================================================
// 位置設定処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_3D::SetPosition(D3DXVECTOR3 pos)
{
	// ゲージの値算出
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

	// 座標設定
	SetPos(pos);

	D3DXVECTOR3 size = GetSize();

	// 頂点情報を設定
	VERTEX_3D *pVtx = nullptr;

	// バッファ取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定の設定
	pVtx[0].pos = D3DXVECTOR3((-size.x / DIVIDE_2), (size.y / DIVIDE_2), size.z);
	pVtx[1].pos = D3DXVECTOR3((size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (size.y / DIVIDE_2), size.z);
	pVtx[2].pos = D3DXVECTOR3((-size.x / DIVIDE_2), (-size.y / DIVIDE_2), size.z);
	pVtx[3].pos = D3DXVECTOR3((size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (-size.y / DIVIDE_2), size.z);

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}
//=============================================================================
// 色設定処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_3D::SetColor(D3DXCOLOR col)
{
	CSceneBase::SetColor(col);

	VERTEX_3D*pVtx = nullptr;

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
void CGage_3D::SetGageNum(int nGageNum)
{
	// 代入
	m_nGageNum = nGageNum;

	// ゲージの値算出
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

	D3DXVECTOR3 size = GetSize();

	// 頂点情報を設定
	VERTEX_3D *pVtx = nullptr;

	// バッファ取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定の設定
	pVtx[0].pos = D3DXVECTOR3((-size.x / DIVIDE_2), (size.y / DIVIDE_2), size.z);
	pVtx[1].pos = D3DXVECTOR3((size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (size.y / DIVIDE_2), size.z);
	pVtx[2].pos = D3DXVECTOR3((-size.x / DIVIDE_2), (-size.y / DIVIDE_2), size.z);
	pVtx[3].pos = D3DXVECTOR3((size.x / DIVIDE_2) - (size.x) * (SUB_GAGE - m_fGageNum), (-size.y / DIVIDE_2), size.z);

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}
//=============================================================================
// ゲージの最大値設定処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGage_3D::SetMaxGageNum(int nMaxGageNum)
{
	// floatに変換
	m_fMaxGageNum = (float)nMaxGageNum;
}