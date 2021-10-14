#ifndef _MODE_BASE_H_
#define _MODE_BASE_H_
//==============================================================================
//
// モードの基底クラス  [mode_base.h]
// Author : Konishi Yuuto
//
//==============================================================================

//==============================================================================
// インクルード
//==============================================================================
#include "main.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CLight;
class CCamera;
class CPlayer;

//==============================================================================
// クラス定義
//==============================================================================
class CModeBase
{
public:
	CModeBase();				// コンストラクタ
	virtual ~CModeBase() {};	// デストラクタ

	virtual HRESULT Init(void) = 0;		// 初期化
	virtual void Update(void) = 0;		// 更新
	virtual void Draw(void) = 0;		// 描画

	// Get関数
	virtual CCamera* GetCamera(void) { return m_pCamera; }		// カメラのポインタ
	virtual CLight* GetLight(void) { return m_pLight; }			// ライトのポインタ
	virtual CPlayer* GetPlayer(void) { return m_pPlayer; }		// プレイヤーのポインタ

private:
	CCamera *m_pCamera;		// カメラのポインタ
	CLight *m_pLight;		// ライトのポインタ
	CPlayer *m_pPlayer;		// プレイヤーのポインタ
};

#endif