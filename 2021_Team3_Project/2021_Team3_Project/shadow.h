#ifndef _SHADOW_H_
#define _SHADOW_H_
//=============================================================================
//
// シャドウクラスヘッダー [shadow.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "scene.h"

//=========================================================================
// 前方宣言
//=========================================================================
class CShadowVolume;
class CShadowPolygon;

//=========================================================================
// クラス定義
//=========================================================================
class CShadow
{
public:
	CShadow();		// コンストラクタ
	~CShadow();		// デストラクタ

	static CShadow *Create(LPD3DXMESH pSrcMesh);										// インスタンス生成
	HRESULT Init(LPD3DXMESH pSrcMesh);													// 初期化生成処理
	void Uninit(void);																	// 終了処理
	void VolumeDraw(void);																// 影描画処理
	void CreateShadow(D3DXVECTOR3 rot, D3DXVECTOR3 ShipRot, D3DXMATRIX ModelMtxWorld);	// 影の生成
	void CreateShadow(D3DXVECTOR3 rot, D3DXMATRIX ModelMtxWorld);						// 影の生成
	static void PolygonUninit(void);													// 描画処理

private:
	CShadowVolume *m_pShadowVolume;		// シャドウボリュームのポインタ
	D3DXMATRIX m_ModelMtxWorld;			// モデルのワールド座標取得
	static CShadowPolygon *m_pPolygon;	// ポリゴンのポインタ
};
#endif