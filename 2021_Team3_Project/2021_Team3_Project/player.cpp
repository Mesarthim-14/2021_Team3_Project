//=============================================================================
//
// プレイヤークラス [player.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"
#include "collision.h"
#include "fade.h"
#include "texture.h"
#include "resource_manager.h"
#include "motion.h"
#include "bullet.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED					(20.0f)							// プレイヤーの移動量
#define STICK_SENSITIVITY				(50.0f)							// スティック感度
#define PLAYER_ROT_SPEED				(0.1f)							// キャラクターの回転する速度
#define PLAYER_RADIUS					(50.0f)							// 半径の大きさ
#define BULLET_MOVE						(40.0f)							// 移動量
#define SHIP_NUM						(0)								// 船のナンバー
#define ANGLE_180						(D3DXToRadian(180))				// 180度
#define ANGLE_90						(D3DXToRadian(90))				// 90度
#define LENGTH							(-600.0f)						// 距離
#define BULLET_Y						(500.0f)						// 弾のY軸
//=============================================================================
// クリエイト
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CPlayer *pPlayer = new CPlayer;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// 初期化処理
		pPlayer->Init(pos, rot);
	}

	return pPlayer;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority)
{
	m_rotDest = ZeroVector3;
	m_bMove = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデルの情報を渡す
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER);
	}

	CCharacter::Init(pos, rot);												// 座標　角度
	SetSpeed(PLAYER_SPEED);													// 速度の設定

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{	
	// 終了処理
	CCharacter::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// 座標代入
	D3DXVECTOR3 pos = GetPos();	// 現在の座標取得
	SetPosOld(pos);				// 古い座標保存

	// プレイヤーの状態
	UpdateState();

	// モーション状態
	UpdateMotionState();

	// プレイヤーの制御
	PlayerControl();

	// 角度の更新処理
	UpdateRot();

	// 親クラスの更新処理
	CCharacter::Update();

	// 体力が0になったら
	if (GetLife() <= 0)
	{
		// 死んだとき
		Death();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	// 描画処理
	CCharacter::Draw();
}

//=============================================================================
// プレイヤーの状態
//=============================================================================
void CPlayer::UpdateState(void)
{

}

//=============================================================================
// モーション状態
//=============================================================================
void CPlayer::UpdateMotionState(void)
{
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();
	int nKey = GetMotion()->GetKey();
	int nCountMotion = GetMotion()->GetCountMotion();

	// モーション情報
	switch (MotionState)
	{
	case MOTION_IDOL:
		break;
	}
}

//=============================================================================
// プレイヤーの制御
//=============================================================================
void CPlayer::PlayerControl()
{
	// プレイヤーの移動処理
	Move();

	// 攻撃処理
	Attack();
}

//=============================================================================
// 角度の更新処理
//=============================================================================
void CPlayer::UpdateRot(void)
{
	// 角度の取得
	D3DXVECTOR3 rot = GetRot();

	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// キャラクター回転の速度
	rot += (m_rotDest - rot) * PLAYER_ROT_SPEED;

	// 角度の設定
	SetRot(rot);
}

//=============================================================================
// 死んだときの処理
//=============================================================================
void CPlayer::Death(void)
{

}

//=============================================================================
// 移動の処理
//=============================================================================
void CPlayer::Move(void)
{
	// ローカル変数
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();					// キーボード更新
	DIJOYSTATE js = CInputJoypad::GetStick(0);								// ジョイパッドの取得
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();		// サウンドのポインタ
	float fAngle = GET_CAMERA_PTR->GetHorizontal();							// カメラの角度
	D3DXVECTOR3 pos = GetPos();												// 座標
	D3DXVECTOR3 rot = GetRot();												// 角度
	float fSpeed = GetSpeed();												// スピード
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();	// モーションの状態

	//入力が存在する
	if ((js.lX != 0.0f || js.lY != 0.0f))
	{
		float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// コントローラの角度
		float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);	// コントローラの角度

		// 移動量設定
		pos.x += sinf(fAngle + (fAngle2))* fSpeed;
		pos.z += cosf(fAngle + (fAngle2))* fSpeed;

		// 角度の設定
		m_rotDest.y = fAngle + (fAngle3);
	}
	else
	{

	}

	// 前に移動
	if (pKeyboard->GetPress(DIK_W))
	{
		// 歩きモーション
	//	SetMotion(MOTION_WALK);

		// 移動量・角度の設定
		pos.x -= sinf(fAngle)*fSpeed;
		pos.z -= cosf(fAngle)*fSpeed;
		m_rotDest.y = fAngle;
		SetRot(D3DXVECTOR3(rot.x, fAngle, rot.z));
	}
	// 後ろに移動
	if (pKeyboard->GetPress(DIK_S))
	{
		// 歩きモーション
	//	SetMotion(MOTION_WALK);

		// 移動量・角度の設定
		pos.x += sinf((fAngle))*fSpeed;
		pos.z += cosf((fAngle))*fSpeed;
		m_rotDest.y = fAngle;
		SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(-180.0f), rot.z));

	}
	// 左に移動
	if (pKeyboard->GetPress(DIK_A))
	{
		// 歩きモーション
	//	SetMotion(MOTION_WALK);

		// 移動量・角度の設定
		pos.x += sinf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
		pos.z += cosf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
		m_rotDest.y = fAngle;
		SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(-90.0f), rot.z));

	}
	// 右に移動
	if (pKeyboard->GetPress(DIK_D))
	{
		// 歩きモーション
	//	SetMotion(MOTION_WALK);

		// 移動量・角度の設定
		pos.x += sinf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
		pos.z += cosf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
		m_rotDest.y = fAngle;
		SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(90.0f), rot.z));
	}

	// 座標設定
	SetPos(pos);

	// 古い座標取得
	D3DXVECTOR3 OldPos = GetOldPos();

	// 動いていなかったら
	if (OldPos == pos)
	{
		// 通常モーション
		SetMotion(MOTION_IDOL);
	}
}

//=============================================================================
// 攻撃処理
//=============================================================================
void CPlayer::Attack(void)
{
	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	

	// SPACEキーを押した場合
	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		// 移動量
		D3DXVECTOR3 bulletmove = ZeroVector3;

		// 向き取得
		D3DXVECTOR3 rot = GetRot();
		
		// モデルの情報取得
		CModelAnime *pAnime = GetModelAnime(SHIP_NUM);

		// 船の位置取得
		D3DXVECTOR3 pos = D3DXVECTOR3(pAnime->GetMtxWorld()._41, pAnime->GetMtxWorld()._42, pAnime->GetMtxWorld()._43);

		// 位置
		D3DXVECTOR3 bulletpos = ZeroVector3;

		//座標を求める
		bulletpos.x = pos.x - cosf(rot.y + ANGLE_90) * LENGTH;
		bulletpos.z = pos.z + sinf(rot.y + ANGLE_90) * LENGTH;
		bulletpos.y = BULLET_Y;

		// 弾の移動
		bulletmove.x = sinf(rot.y + ANGLE_180) *BULLET_MOVE;
		bulletmove.z = cosf(rot.y + ANGLE_180) *BULLET_MOVE;

		// 弾生成
		CBullet::Create(bulletpos, ZeroVector3, bulletmove);
	}
}