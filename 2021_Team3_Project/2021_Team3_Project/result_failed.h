#ifndef _RESULT_H_
#define _RESULT_H_
//=============================================================================
//
// リザルトクラスヘッダー [result.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode_base.h"

//=============================================================================
//前方宣言
//=============================================================================
class CScene2D;

//=============================================================================
//リザルトクラス
//=============================================================================
class CResultFailed : public CModeBase
{
public:
	CResultFailed();					// コンストラクタ
	~CResultFailed();					// デストラクタ

	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理

	void Create2DObject(void);	// 2Dオブジェクト生成
private:
	vector<CScene2D*> m_pObject2D;	// シーン2Dのポインタ
};
#endif