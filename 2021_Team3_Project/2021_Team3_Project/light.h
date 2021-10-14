#ifndef _LIGHT_H_
#define _LIGHT_H_
//=============================================================================
//
// ライト処理 [light.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// クラス定義
//=============================================================================
class CLight
{
public:
	CLight();				// コンストラクタ
	~CLight();				// デストラクタ

	static CLight *Create(void);	// インスタンス生成処理
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理

	// Set関数
	void SetPos(D3DXVECTOR3 pos) { m_Light.Position = pos; }
	void SetVecDir(D3DXVECTOR3 Dir);

	// Get関数
	D3DXVECTOR3 GetPos(void) { return m_Light.Position; }		// 座標
	D3DXVECTOR3 GetLightDir(void) { return m_vecDir; }			// ライトの向き

private:
	D3DLIGHT9 m_Light;		// ライトの変数
	D3DXVECTOR3 m_vecDir;	// ライトの向き
};
#endif