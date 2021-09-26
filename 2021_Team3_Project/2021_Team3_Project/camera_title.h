#ifndef _CAMERA_TITLE_H_
#define _CAMERA_TITLE_H_
//=============================================================================
//
// タイトルのカメラクラスヘッダー [camera_title.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "camera.h"

//=============================================================================
// カメラクラス
//=============================================================================
class CCameraTitle : public CCamera
{
public:
	CCameraTitle();					// コンストラクタ
	~CCameraTitle();				// デストラクタ

	HRESULT Init(void);			// 初期化処理
	void Update(void);			// 更新処理
	void NomalUpdate(D3DXVECTOR3 PlayerPos, D3DXVECTOR3 PlayerRot) override;

	static CCameraTitle*Create(void);		// クリエイト

private:

};
#endif 