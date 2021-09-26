#ifndef _CAMERA_GAME_H_
#define _CAMERA_GAME_H_
//=============================================================================
//
// ゲームカメラクラスヘッダー [camera_game.h]
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
class CCameraGame : public CCamera
{
public:
	CCameraGame();					// コンストラクタ
	~CCameraGame();					// デストラクタ

	HRESULT Init(void);					// 初期化処理
	void Update(void);					// 更新処理
	void NomalUpdate(D3DXVECTOR3 PlayerPos, D3DXVECTOR3 PlayerRot) override;
	static CCameraGame*Create(void);	// クリエイト

private:
};
#endif 