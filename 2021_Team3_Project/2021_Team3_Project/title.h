#ifndef _TITLE_H_
#define _TITLE_H_
//=============================================================================
//
// タイトルクラス [title.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode_base.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;
class CPlayer;
class CCamera;
class CCameraTitle;
class CLight;

//=============================================================================
// クラス定義
//=============================================================================
class CTitle : public CModeBase
{
public:
	CTitle();					// コンストラクタ
	~CTitle();					// デストラクタ

	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理
	void Create2DObject(void);	// 2Dオブジェクトの生成関数
	void Create3DObject(void);	// 3Dに必要な情報を生成

	// Get関数
	CCamera* GetCamera(void) override	{ return (CCamera*)m_pCamera; }		// カメラのポインタ
	CLight* GetLight(void) override		{ return m_pLight; }				// ライトのポインタ
	CPlayer* GetPlayer(void) override	{ return m_pShip; }					// プレイヤーのポインタ
private:
	CPlayer *m_pShip;				// 船
	vector<CScene2D*> m_pObject2D;	// 2Dオブジェクト
	CCameraTitle *m_pCamera;		// カメラのポインタ
	CLight *m_pLight;				// ライトのポインタ
};
#endif