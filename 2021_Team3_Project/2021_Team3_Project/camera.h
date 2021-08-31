#ifndef _CAMERA_H_
#define _CAMERA_H_
//=============================================================================
//
// カメラクラスヘッダー [camera.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// カメラクラス
//=============================================================================
class CCamera
{
public:
	CCamera();					// コンストラクタ
	~CCamera();					// デストラクタ

	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void SetCamera(void);		// カメラの描画設定

	// Set関数
	void SetTarget(bool Target);

	// Get関数
	bool GetTargetBool(void);			// ターゲットカメラのフラグ
	float GetVartical(void);			// 縦の回転
	float GetHorizontal(void);			// 横の回転
	D3DXVECTOR3 GetposV(void);			// カメラ座標
	D3DXVECTOR3 GetposR(void);			// カメラ角度
	D3DXMATRIX GetMtxView(void);		// マトリクスビュー
	D3DXVECTOR3 GetposVDest(void);		// 目的の角度
	D3DXMATRIX GetMtxProj(void) { return m_mtxProjection; }

	static CCamera*Create(void);		// クリエイト

private:
	//=========================================================================
	// プライベートメンバ関数宣言
	//=========================================================================
	void NomalUpdate(D3DXVECTOR3 PlayerPos, D3DXVECTOR3 PlayerRot);

	//=========================================================================
	// メンバ変数宣言
	//=========================================================================
	D3DXVECTOR3 m_posV;						// カメラの座標
	D3DXVECTOR3 m_posVDest;					// カメラの座標（目的地）
	D3DXVECTOR3 m_posVRot;					// カメラの座標（）
	D3DXVECTOR3 m_posR;						// 注視点
	D3DXVECTOR3 m_posRDest;					// 注視点（目的地）
	D3DXVECTOR3 m_posRRot;					// 注視点（）
	D3DXVECTOR3 m_posU;						// 上方向ベクトル
	D3DXMATRIX m_mtxProjection;				// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;					// ビューマトリックス
	D3DXVECTOR3 m_rot;						// 向き
	bool m_bTarget;							// ターゲット使用フラグ
	float m_fVartical;						// 縦回転角度
	float m_fHorizontal;					// 横回転角
	float m_fDistance;						// 視点～注視点の距離
	float m_fMove;							// 移動量
};
#endif 