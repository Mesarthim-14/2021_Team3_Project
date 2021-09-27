//=============================================================================
//
// タイトルカメラの処理 [camera_title.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "camera_title.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "joypad.h"
#include "motion.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TITLE_CAMERA_DISTANCE		(3000.0f)				// 距離
#define TITLE_CAMERA_DEFAULT_Fθ	(D3DXToRadian(89.0f))	// カメラ角度縦
#define TITLE_CAMERA_DEFAULT_Hθ	(D3DXToRadian(95.0f))	// カメラ角度横
#define PLAYER_HEIGHT				(600.0f)				// 注視点の高さ
#define CAMERA_MIN_HIGHT			(2.0f)					// カメラの最低高度

//=============================================================================
// インスタンス生成
//=============================================================================
CCameraTitle * CCameraTitle::Create(void)
{
	// メモリ確保
	CCameraTitle *pCamera = new CCameraTitle;

	if (pCamera)
	{
		// 初期化処理
		pCamera->Init();
		return pCamera;
	}

	return nullptr;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CCameraTitle::CCameraTitle()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CCameraTitle::~CCameraTitle()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCameraTitle::Init(void)
{
	D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, PLAYER_HEIGHT, 0.0f);
	D3DXVECTOR3 posV = ZeroVector3;
	float fDistance = TITLE_CAMERA_DISTANCE;
	float fVartical = TITLE_CAMERA_DEFAULT_Fθ;
	float fHorizontal = TITLE_CAMERA_DEFAULT_Hθ;

	SetDistance(fDistance);
	SetVartical(fVartical);
	SetHorizontal(fHorizontal);					// 初期値敵のほう向ける
	GetposR() = posR;
	GetposU() = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// 上方向ベクトル

	posV.x = posR.x + fDistance * sinf(fVartical) * sinf(fHorizontal);	// カメラ位置X
	posV.y = posR.z + fDistance * cosf(fVartical);						// カメラ位置Y
	posV.z = posR.y + fDistance * sinf(fVartical) * cosf(fHorizontal);	// カメラ位置Z

	GetposV() = posV;

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CCameraTitle::Update(void)
{
	// カメラの更新処理
	CCamera::Update();
}

//=============================================================================
// 通常状態の更新処理
//=============================================================================
void CCameraTitle::NomalUpdate(D3DXVECTOR3 PlayerPos, D3DXVECTOR3 PlayerRot)
{
	// カメラ座標
	D3DXVECTOR3 VDest = ZeroVector3;
	D3DXVECTOR3 posRDest = GetposRDest();
	float fDistance = GetDistance();
	float fVartical = GetVartical();
	float fHorizontal = GetHorizontal();

	// カメラの位置設定
	VDest.x = PlayerPos.x + fDistance * sinf(fVartical) * sinf(PlayerRot.y + fHorizontal);	// カメラ位置X設定
	VDest.y = PlayerPos.y + PLAYER_HEIGHT + fDistance * cosf(fVartical);					// カメラ位置Y設定
	VDest.z = PlayerPos.z + fDistance * sinf(fVartical) * cosf(PlayerRot.y + fHorizontal);	// カメラ位置Z設定

	posRDest = D3DXVECTOR3(PlayerPos.x , PlayerPos.y + PLAYER_HEIGHT, PlayerPos.z - 500.0f);	//注視点設定

	//カメラPOSYの下限
	if (VDest.y <= CAMERA_MIN_HIGHT)
	{
		VDest.y = CAMERA_MIN_HIGHT;	//限界値に戻す
	}

	//設定値の反映
	GetposV() += (VDest - GetposV());
	GetposR() += (posRDest - GetposR());
}