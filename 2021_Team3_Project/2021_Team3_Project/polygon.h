#ifndef _POLYGON_H_
#define _POLYGON_H_
//=============================================================================
//
// ポリゴン生成クラス処理 [polygon.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// ポリゴンクラス
//=============================================================================
class CPolygon
{
public:
	CPolygon();			// コンストラクタ
	~CPolygon();		// デストラクタ

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
	void SetColor(const D3DXCOLOR color);							// 色の設定

	static CPolygon *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);		// インスタンス生成

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3 m_Size;						// ポリゴンのサイズ
	D3DXVECTOR3 m_pos;						// ライフの位置
};
#endif 