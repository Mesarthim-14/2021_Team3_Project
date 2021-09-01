#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
//=====================================================
//
// メッシュフィールドのクラス [meshfield.h]
// Author : Konishi Yuuto
//
//=====================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "mesh_3d.h"

//=============================================================================
// メッシュフィールドクラス
//=============================================================================
class CMeshField : public CMesh3d
{
public:
	CMeshField(PRIORITY = PRIORITY_0);	// コンストラクタ
	~CMeshField();						// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理
	void CreateVerterx(void);								// 頂点の生成
	void SetInfo(D3DXVECTOR3 size, INT_VERTEX_2D PieceNum);	// 情報の設定

	static CMeshField*Create(void);		// メッシュフィールド
private:
};

#endif