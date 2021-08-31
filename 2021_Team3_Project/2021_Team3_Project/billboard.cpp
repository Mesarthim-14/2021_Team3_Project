//=====================================================
//
// ビルボードクラス [billboard.cpp]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "billboard.h"
#include "manager.h"
#include "renderer.h"

//=====================================================
// コンストラクタ
//=====================================================
CBillboard::CBillboard(PRIORITY Priority) : CSceneBase(Priority)
{
	m_move = ZeroVector3;
	m_sizeBase = ZeroVector3;
	m_nCountAnim = 0;
	m_nCountAnimPattern = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nLife = 0;
	m_nLoop = -1;
	m_nAlphaNum = 0;
	m_bBlend = false;
}

//=====================================================
// デストラクタ
//=====================================================
CBillboard::~CBillboard()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CBillboard::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;
	VERTEX_3D*pVtx = nullptr;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		nullptr);
	// 情報の代入
	SetPos(pos);
	SetSize(size);
	m_sizeBase = size;
	D3DXCOLOR color = GetColor();

	//頂点バッファをロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定の設定
	pVtx[0].pos = D3DXVECTOR3((-size.x / DIVIDE_2),(size.y / DIVIDE_2),(size.z / DIVIDE_2));
	pVtx[1].pos = D3DXVECTOR3((size.x / DIVIDE_2),	(size.y / DIVIDE_2),(size.z / DIVIDE_2));
	pVtx[2].pos = D3DXVECTOR3((-size.x / DIVIDE_2),(-size.y / DIVIDE_2),(-size.z / DIVIDE_2));
	pVtx[3].pos = D3DXVECTOR3((size.x / DIVIDE_2),	(-size.y / DIVIDE_2),(-size.z / DIVIDE_2));

	//各頂点の法線の設定（※ベクトルの大きさは１にする必要がある）
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定（0～255の数値で設定）
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	// テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	pVtxBuff->Unlock();

	// バッファの受け渡し
	BindVtxBuff(pVtxBuff);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CBillboard::Uninit(void)
{	
	//オブジェクト破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CBillboard::Update(void)
{
	// 移動量加算
	GetPos() += m_move;

	// アニメーションの設定がされたとき
	if (m_nPatternAnim != 0)
	{
		// アニメーションを更新する
		UpdateAnimation();
	}
}

//=====================================================
// 描画処理
//=====================================================
void CBillboard::Draw(void)
{
	// デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//計算用のマトリクス
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	// ライト無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// アルファテストを有力化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// 加算合成
	if (m_bBlend == true)
	{
		// 加算合成を行う
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// aデスティネーションカラー
	}

	// アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, m_nAlphaNum);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// テクスチャの設定
	pDevice->SetTexture(0, GetTexture());

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転の逆行列の生成
	pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
	D3DXMatrixInverse(&m_mtxWorld, nullptr,&mtxRot);
	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// サイズを反映
	D3DXMatrixScaling(&mtxScale,
		size.x / m_sizeBase.x,
		size.y / m_sizeBase.y,
		1.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// サイズ情報
	D3DXVECTOR3 pos = GetPos();

	// 位置を反映、ワールドマトリクス設定、ポリゴン描画
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// 加算合成を行う処理
	if (m_bBlend == true)
	{
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// aデスティネーションカラー
	}

	// アルファテスト無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ライト有効
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================
// アニメーション情報取得
//=============================================
void CBillboard::InitAnimation(D3DXVECTOR2 TexInfo, int nLoop)
{
	// 値の代入
	m_nPatternAnim = (int)TexInfo.x;
	m_nCounterAnim = (int)TexInfo.y;
	m_nLoop = nLoop;

	// 頂点情報を設定
	VERTEX_3D *pVtx;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標を更新
	pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//=============================================
// アニメーション更新関数
//=============================================
void CBillboard::UpdateAnimation(void)
{
	// 爆発のアニメーションカウントを進めて、パターンを切り替える
	m_nCountAnim++;

	// 頂点情報(テクスチャ座標)の更新
	if (m_nCountAnim >= m_nCounterAnim)	// 爆発の速さ
	{
		// アニメーションのカウントを0にする
		m_nCountAnim = 0;

		// アニメーションのパターンをカウントさせる
		m_nCountAnimPattern++;
	}

	// アニメーションが終わったら
	if (m_nCountAnimPattern >= m_nPatternAnim)
	{
		// 数値を戻しておく
		m_nCountAnimPattern = 0;

		// ループしない設定なら
		if (m_nLoop == 0)
		{
			// 終了処理
			Uninit();
		}
	}
	else
	{
		// バッファの取得
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

		// 頂点情報を設定
		VERTEX_3D *pVtx;

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標を更新
		pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

		// 頂点バッファをアンロックする
		pVtxBuff->Unlock();
	}
}

//=============================================================================
// 色の設定
//=============================================================================
void CBillboard::SetColor(D3DXCOLOR col)
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

//=====================================================
// 移動量設定
//=====================================================
void CBillboard::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=====================================================
// ベースサイズ設定
//=====================================================
void CBillboard::SetSizeBase(D3DXVECTOR3 sizeBase)
{
	m_sizeBase = sizeBase;
}

//=====================================================
// 体力の設定
//=====================================================
void CBillboard::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=====================================================
// アルファテストの値
//=====================================================
void CBillboard::SetAlphaNum(int nAlphaNum)
{
	m_nAlphaNum = nAlphaNum;
}

//=====================================================
// 加算合成
//=====================================================
void CBillboard::SetBlend(bool bBlend)
{
	m_bBlend = bBlend;
}

//=====================================================
// 移動量情報
//=====================================================
D3DXVECTOR3 CBillboard::GetMove(void)
{
	return m_move;
}