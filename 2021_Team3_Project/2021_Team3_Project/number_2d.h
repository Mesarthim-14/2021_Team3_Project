#ifndef _NUMBER_2D_H_
#define _NUMBER_2D_H_
//=============================================================================
//
// ナンバー2Dクラスヘッダー [number_2d.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene_base.h"

//=============================================================================
// ナンバー2Dクラス
//=============================================================================
class CNumber2d : public CSceneBase
{
public:
	CNumber2d(PRIORITY Priority = PRIORITY_UI);		// コンストラクタ
	~CNumber2d();									// デストラクタ

	// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
	static CNumber2d * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// クリエイト

	void SetNumber(int nNumber);									// ナンバーの設定
private:
};

#endif