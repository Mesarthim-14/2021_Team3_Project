//=============================================================================
//
// メッシュフィールドクラス [meshfield.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "meshfield.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CMeshField::CMeshField(PRIORITY Priority) : CMesh3d(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshField::~CMeshField()
{
}

//=============================================================================
// ポリゴン生成
//=============================================================================
CMeshField * CMeshField::Create(void)
{
	// メモリ確保
	CMeshField *pMeshField = new CMeshField;

	// nullchack
	if (pMeshField != nullptr)
	{
		// 初期化処理
		pMeshField->Init(ZeroVector3, ZeroVector3);
	}

	return pMeshField;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshField::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_FLOOR));

	// 頂点の設定
	CreateVerterx();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshField::Uninit(void)
{
	// 削除フラグ
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshField::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshField::Draw(void)
{
	// 親クラス描画処理
	CMesh3d::Draw();
}

//=============================================================================
// 頂点の生成
//=============================================================================
void CMeshField::CreateVerterx(void)
{
	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	VERTEX_3D *pVtx = nullptr;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;		// バッファ
	LPDIRECT3DINDEXBUFFER9 pIdxBuff = nullptr;		// バッファの番号
	
	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * GetNumVertex(),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL);

	// インデックスバッファ生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * GetNumIndex(),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&pIdxBuff,
		NULL);

	// 1ポリゴンのサイズ
	D3DXVECTOR3 OneSize = GetOneSize();
	D3DXVECTOR3 AllSize = GetSize();
	INT_VERTEX_2D PieceNum = GetPieceNum();

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV < PieceNum.x + 1; nCntV++)
	{
		for (int nCntH = 0; nCntH < PieceNum.y + 1; nCntH++)
		{
			// 頂点の設定
			pVtx[(nCntV * (PieceNum.y + 1)) + nCntH].pos = D3DXVECTOR3(-AllSize.x + (nCntH * OneSize.x), 0.0f, AllSize.z - (nCntV * OneSize.y));

			// 法線ベクトルの設定
			pVtx[(nCntV * (PieceNum.y + 1)) + nCntH].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 色の設定
			pVtx[(nCntV * (PieceNum.y + 1)) + nCntH].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[(nCntV * (PieceNum.y + 1)) + nCntH].tex = D3DXVECTOR2(float(nCntH), float(nCntV));
		}
	}

	// 頂点データをアンロックする
	pVtxBuff->Unlock();

	// 頂点バッファの設定
	BindVtxBuff(pVtxBuff);

	// インデックスバッファの設定
	WORD *pIdx;

	// インデックスバッファをロックし、インデックスデータへのポインタを取得
	pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// インデックス数
	int nNumIndex = GetNumIndex();
	for (int nCount = 0, nCntIndex = 0; nCount < nNumIndex; nCount += 2)
	{
		if (((nCount + 2) % (((PieceNum.x + 1) * 2) + 2)) == 0 && nCount != 0)
		{
			// インデックスの設定
			pIdx[nCount] = nCntIndex - 1;

			// インデックスの設定
			pIdx[nCount + 1] = PieceNum.x + nCntIndex + 1;
		}
		else
		{
			// インデックスの設定
			pIdx[nCount] = PieceNum.x + nCntIndex + 1;

			// インデックスの設定
			pIdx[nCount + 1] = nCntIndex;

			nCntIndex++;
		}
	}

	// 頂点データをアンロックする
	pIdxBuff->Unlock();

	// インデックスバッファを設定
	BindIdxBuff(pIdxBuff);
}

//=============================================================================
// 情報の設定
//=============================================================================
void CMeshField::SetInfo(D3DXVECTOR3 size, INT_VERTEX_2D PieceNum)
{
	// 値の初期化
	SetNumVertex((PieceNum.x + 1) * (PieceNum.y + 1));								// 25
	SetNumIndex((PieceNum.x + 1) * PieceNum.y * 2 + (PieceNum.y - 1) * 2);			// 5*(4*2)+3*2	46
	SetNumPolygon(PieceNum.x * PieceNum.y * 2 + (PieceNum.y - 1) * 4);				// 4*8+3*4	44

	// サイズの設定
	D3DXVECTOR3 AllSize = D3DXVECTOR3(size.x, 0.0f, size.z);
	SetSize(AllSize);
	D3DXVECTOR2 OneSize = D3DXVECTOR2(size.x * 2 / PieceNum.x, size.z * 2 / PieceNum.y);
	SetOneSize(OneSize);

	// ブロックの数
	SetPieceNum(PieceNum);
}