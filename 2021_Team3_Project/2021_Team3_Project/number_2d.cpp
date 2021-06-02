//=============================================================================
//
// ナンバー2Dクラス [number.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "number_2d.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SCORE_ANIM_PATTERN	(8)			// アニメーションのパターン
#define NUMBER_NUM			(10)		// ナンバーの数

//=============================================================================
// インスタンス生成
//=============================================================================
CNumber2d * CNumber2d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// インスタンス生成
	CNumber2d *pNumber = new CNumber2d;

	if (pNumber != nullptr)
	{
		// 初期化処理
		pNumber->Init(pos, size);
	}

	return pNumber;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CNumber2d::CNumber2d(PRIORITY Priority) : CSceneBase(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CNumber2d::~CNumber2d()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CNumber2d::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// レンダラーの情報を受け取る
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// バッファの変数
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,														// 頂点バッファの使用法　
		FVF_VERTEX_2D,															// 使用する頂点フォーマット
		D3DPOOL_MANAGED,														// リソースのバッファを保持するメモリクラスを指定
		&pVtxBuff,																// 頂点バッファへのポインタ
		nullptr)))																	// nullptrに設定
	{
		return E_FAIL;
	}

	SetPos(pos);			// 座標設定
	SetSize(size);			// サイズ設定

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y + size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y + size.y / 2, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 左上頂点の色	透明度255
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 右上頂点の色	透明度255
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 左下頂点の色	透明度255
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 右下頂点の色	透明度255

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();

	// バッファ情報を渡す
	BindVtxBuff(pVtxBuff);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CNumber2d::Uninit(void)
{
	// 終了フラグ
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CNumber2d::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CNumber2d::Draw(void)
{
	// レンダラーの情報を受け取る
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, GetTexture());

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		// プリミティブの種類
		0,
		NUM_POLYGON);				// プリミティブの数

	// テクスチャの設定
	pDevice->SetTexture(0, nullptr);
}

//=============================================================================
// ナンバーの加算
//=============================================================================
void CNumber2d::SetNumber(int nNumber)
{
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2((1.0f / NUMBER_NUM) * (float)nNumber, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / NUMBER_NUM) * (float)nNumber + (1.0f / NUMBER_NUM), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / NUMBER_NUM) * (float)nNumber, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / NUMBER_NUM) * (float)nNumber + (1.0f / NUMBER_NUM), 1.0f);

	// 頂点バッファをアンロックする
	GetVtxBuff()->Unlock();
}