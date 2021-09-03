#ifndef _SHADOW_VOLUME_H_
#define _SHADOW_VOLUME_H_
//=============================================================================
//
// シャドウボリュームクラスヘッダー [shadow_volume.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "main.h"

//=========================================================================
// クラス定義
//=========================================================================
class CShadowVolume
{
public:
	// メッシュ情報の構造体
	struct MESHVERTEX
	{
		D3DXVECTOR3 pos, nor;
		FLOAT tu, tv;
	};

	CShadowVolume();		// コンストラクタ
	~CShadowVolume();		// デストラクタ

	static CShadowVolume *Create(LPD3DXMESH pSrcMesh);					// インスタンス生成
	HRESULT Init(LPD3DXMESH pSrcMesh);									// 初期化生成処理
	void Uninit(void);													// 終了処理
	void Draw(void);													// 描画処理
	void AddEdge(WORD* pEdges, DWORD& dwNumEdges, WORD v0, WORD v1);	// エッジの設定
	HRESULT CreateShadow(D3DXVECTOR3 rot, D3DXVECTOR3 ShipRot);			// 影の生成
	HRESULT CreateShadow(D3DXVECTOR3 ShipRot);							// 影の生成
	void CreateVolume(vector<D3DXVECTOR3> pos, D3DXVECTOR3 Lpos);		// シャドウボリューム
private:
	D3DXVECTOR3 m_LightPos;				// ライトの座標
	DWORD       m_dwNumVertices;		// 頂点数
	D3DXVECTOR3 m_pVertice[32000];		// 頂点の配列
	LPD3DXMESH m_pSrcMesh;				// メッシュ情報
	MESHVERTEX *m_MeshVertices;			// メッシュの情報
	WORD *m_pIndices;					// インデックス数
	DWORD m_dwNumFaces;					// メッシュの面の数
	WORD *m_pEdges;						// エッジの数
};
#endif