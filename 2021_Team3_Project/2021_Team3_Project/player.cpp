//=============================================================================
//
// プレイヤークラス [player.cpp]
// Author : Sugawara Tsukasa
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
#include "character_box.h"
#include "player_bullet.h"
#include "map.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED					(10.0f)									// プレイヤーの移動量
#define STICK_SENSITIVITY				(50.0f)									// スティック感度
#define PLAYER_ROT_SPEED				(0.1f)									// キャラクターの回転する速度
#define SHIP_NUM						(0)										// 船のナンバー
#define GEAR_R_NUM						(1)										// 水かきの右ナンバー
#define GEAR_L_NUM						(2)										// 水かきの左ナンバー
#define BATTERY_R_NUM					(3)										// 砲台右のナンバー
#define BATTERY_L_NUM					(4)										// 砲台左のナンバー
#define MIN_MOVE						(D3DXVECTOR3(0.0f,0.0f,0.0f))			// 移動量の最小値
#define SIZE							(D3DXVECTOR3 (800.0f,900.0f,800.0f))	// サイズ
#define PARENT_NUM						(0)										// 親のナンバー
#define GEAR_SPIN_ANGLE					(D3DXToRadian(2.0f))					// 歯車の回転角度
#define SPIN_ANGLE						(D3DXToRadian(1.0f))					// 旋回角度
#define STICK_INPUT_ZONE				(100)									// スティックの入力範囲
#define STICK_INPUT_ZONE_2				(1000)									// スティックの入力範囲
#define STICK_INPUT_ZERO				(0)										// スティックの入力値0
#define MUT_SPEED						(1.5f)									// スピード
#define PAD_1							(0)										// 1番目のパッド
#define PAD_2							(1)										// 2番目のパッド
#define ATTACK_COOLTIME					(90)									// 攻撃のクールタイム
#define RAY_NUM							(4)										// レイの数
#define RAY_RADIUS						(D3DXToRadian(360.0f/4.0f))				// レイを出す方向
#define RAY_RADIUS_UNDER				(D3DXToRadian(-180.0f))					// レイを出す方向
#define RAY_HIT_RANGE					(500.0f)								// 範囲
#define RAY_HIT_RANGE_UNDER				(0.0f)									// 範囲
#define MIN_LIFE						(0)										// ライフの最小
// 船体の位置
#define SHIP_POS						(D3DXVECTOR3(pShip->GetMtxWorld()._41, pShip->GetMtxWorld()._42 + 2.0f, pShip->GetMtxWorld()._43))
// 砲台の位置
#define BATTERY_R_POS					(D3DXVECTOR3(pBattery_R->GetMtxWorld()._41, pBattery_R->GetMtxWorld()._42, pBattery_R->GetMtxWorld()._43))
#define BATTERY_L_POS					(D3DXVECTOR3(pBattery_L->GetMtxWorld()._41, pBattery_L->GetMtxWorld()._42, pBattery_L->GetMtxWorld()._43))

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

		// 箱生成
		CCharacter_Box::Create(pos, rot, pPlayer);
	}

	// ポインタを返す
	return pPlayer;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority)
{
	m_rotDest			= ZeroVector3;
	m_bMove				= false;
	m_nAttackCount_R	= ZERO_INT;
	m_nAttackCount_L	= ZERO_INT;
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

	// 初期化
	CCharacter::Init(pos, rot);

	// サイズ設定
	SetSize(SIZE);

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
	// 親クラスの更新処理
	CCharacter::Update();

	// 座標代入
	D3DXVECTOR3 pos = GetPos();

	// 古い座標保存
	SetPosOld(pos);				

	// プレイヤーの状態
	UpdateState();

	// プレイヤーの制御
	PlayerControl();

	// 角度の更新処理
	UpdateRot();

	// 体力が0になったら
	if (GetLife() <= MIN_LIFE)
	{
		// 死亡状態に設定
		SetState(CCharacter::STATE_DEAD);
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
	// 状態取得
	int nState = GetState();

	// DEADの場合
	if (nState = CCharacter::STATE_DEAD)
	{
		// 死亡処理
		Death();
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

	// 当たり判定
	Collision();

	// マップとの当たり判定
	//RayCollision();
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
	// 終了
	Uninit();

	return;
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
	D3DXVECTOR3 pos = GetPos();												// 座標
	D3DXVECTOR3 rot = GetRot();												// 角度
	float fSpeed = GetSpeed();												// スピード
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();	// モーションの状態

	// 左の歯車の情報取得
	CModelAnime *pGear_L = GetModelAnime(GEAR_L_NUM);
	// 向き取得
	D3DXVECTOR3 Gear_L_rot = pGear_L->GetRot();

	// 右の歯車の情報取得
	CModelAnime *pGear_R = GetModelAnime(GEAR_R_NUM);
	// 向き取得
	D3DXVECTOR3 Gear_R_rot = pGear_R->GetRot();

	////入力が存在する
	//if ((js.lX != 0.0f || js.lY != 0.0f))
	//{
	//	float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// コントローラの角度
	//	float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);	// コントローラの角度

	//	// 移動量設定
	//	move.x = sinf(fAngle + (fAngle2))* fSpeed;
	//	move.z = cosf(fAngle + (fAngle2))* fSpeed;

	//	// 角度の設定
	//	m_rotDest.y = fAngle + (fAngle3);
	//}

	//// 前に移動
	//if (pKeyboard->GetPress(DIK_W))
	//{
	//	// 移動量・角度の設定
	//	move.x = -sinf(fAngle)*fSpeed;
	//	move.z = -cosf(fAngle)*fSpeed;
	//	m_rotDest.y = fAngle;
	//	SetRot(D3DXVECTOR3(rot.x, fAngle, rot.z));
	//}
	//// 後ろに移動
	//if (pKeyboard->GetPress(DIK_S))
	//{
	//	// 移動量・角度の設定
	//	move.x = sinf((fAngle))*fSpeed;
	//	move.z = cosf((fAngle))*fSpeed;
	//	m_rotDest.y = fAngle;
	//	SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(-180.0f), rot.z));
	//}
	//// 左に移動
	//if (pKeyboard->GetPress(DIK_A))
	//{
	//	// 移動量・角度の設定
	//	move.x = sinf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
	//	move.z = cosf((fAngle + D3DXToRadian(90.0f)))*fSpeed;
	//	m_rotDest.y = fAngle;
	//	SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(-90.0f), rot.z));
	//}
	//// 右に移動
	//if (pKeyboard->GetPress(DIK_D))
	//{
	//	// 移動量・角度の設定
	//	move.x = sinf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
	//	move.z = cosf((fAngle + D3DXToRadian(-90.0f)))*fSpeed;
	//	m_rotDest.y = fAngle;
	//	SetRot(D3DXVECTOR3(rot.x, fAngle + D3DXToRadian(90.0f), rot.z));
	//}

//===========================================
// 右歯車
//===========================================
	// 前に移動
	if (pKeyboard->GetPress(DIK_UP) || js.lRz < -STICK_INPUT_ZONE && js.lZ == STICK_INPUT_ZERO ||
		js.lRz < -STICK_INPUT_ZONE && js.lZ < -STICK_INPUT_ZONE && js.lZ > -STICK_INPUT_ZONE_2 ||
		js.lRz < -STICK_INPUT_ZONE && js.lZ > STICK_INPUT_ZONE && js.lZ < STICK_INPUT_ZONE_2)
		
	{
		// 向き加算
		Gear_R_rot.x -= GEAR_SPIN_ANGLE;

		// 向き設定
		pGear_R->SetRot(Gear_R_rot);

		// 移動
		pos.x += -sinf(rot.y)*fSpeed;
		pos.z += -cosf(rot.y)*fSpeed;

		// 目的の向き
		m_rotDest.y = rot.y;
	}
	// 後ろに移動
	if (pKeyboard->GetPress(DIK_DOWN) || js.lRz > STICK_INPUT_ZONE && js.lZ == STICK_INPUT_ZERO ||
		js.lRz > STICK_INPUT_ZONE && js.lZ > STICK_INPUT_ZONE && js.lZ < STICK_INPUT_ZONE_2 ||
		js.lRz > STICK_INPUT_ZONE && js.lZ < -STICK_INPUT_ZONE && js.lZ > -STICK_INPUT_ZONE_2)
	{
		// 向き加算
		Gear_R_rot.x += GEAR_SPIN_ANGLE;

		// 向き設定
		pGear_R->SetRot(Gear_R_rot);

		// 移動
		pos.x += -sinf(rot.y)*-fSpeed;
		pos.z += -cosf(rot.y)*-fSpeed;

		// 目的の向き
		m_rotDest.y = rot.y;
	}

	// 左に移動
	if (pKeyboard->GetPress(DIK_LEFT) || js.lZ < -STICK_INPUT_ZONE && js.lRz == STICK_INPUT_ZERO ||
		js.lZ < -STICK_INPUT_ZONE && js.lRz < -STICK_INPUT_ZONE && js.lRz > -STICK_INPUT_ZONE_2 ||
		js.lZ < -STICK_INPUT_ZONE && js.lRz > STICK_INPUT_ZONE && js.lRz < STICK_INPUT_ZONE_2)
		
	{
		// 向き加算
		Gear_R_rot.x -= GEAR_SPIN_ANGLE;

		// 向き設定
		pGear_R->SetRot(Gear_R_rot);

		// 移動
		pos.x += -sinf(rot.y)*fSpeed;
		pos.z += -cosf(rot.y)*fSpeed;

		// 向き
		rot.y = rot.y - SPIN_ANGLE;

		// 目的の向き
		m_rotDest.y = rot.y;
	}
	// 右に移動
	if (pKeyboard->GetPress(DIK_RIGHT) || js.lZ > STICK_INPUT_ZONE && js.lRz == STICK_INPUT_ZERO ||
		js.lZ > STICK_INPUT_ZONE && js.lRz > STICK_INPUT_ZONE && js.lRz < STICK_INPUT_ZONE_2 ||
		js.lZ > STICK_INPUT_ZONE && js.lRz < -STICK_INPUT_ZONE && js.lRz > -STICK_INPUT_ZONE_2)
		
	{
		// 向き加算
		Gear_R_rot.x += GEAR_SPIN_ANGLE;

		// 向き設定
		pGear_R->SetRot(Gear_R_rot);

		// 移動
		pos.x += -sinf(rot.y)*fSpeed;
		pos.z += -cosf(rot.y)*fSpeed;

		// 向き
		rot.y = rot.y + SPIN_ANGLE;

		// 目的の向き
		m_rotDest.y = rot.y;
	}
//===========================================
// 左歯車
//===========================================
	// 前に移動
	if (pKeyboard->GetPress(DIK_W) || js.lY < -STICK_INPUT_ZONE && js.lX == STICK_INPUT_ZERO ||
		js.lY < -STICK_INPUT_ZONE && js.lX < -STICK_INPUT_ZONE && js.lX > -STICK_INPUT_ZONE_2||
		js.lY < -STICK_INPUT_ZONE && js.lX > STICK_INPUT_ZONE && js.lX < STICK_INPUT_ZONE_2)
	{
		// 向き加算
		Gear_L_rot.x -= GEAR_SPIN_ANGLE;

		// 向き設定
		pGear_L->SetRot(Gear_L_rot);

		// 移動
		pos.x += -sinf(rot.y)*fSpeed;
		pos.z += -cosf(rot.y)*fSpeed;

		// 目的の向き
		m_rotDest.y= rot.y;
	}
	// 後ろに移動
	if (pKeyboard->GetPress(DIK_S) || js.lY > STICK_INPUT_ZONE && js.lX == STICK_INPUT_ZERO ||
		js.lY > STICK_INPUT_ZONE && js.lX > STICK_INPUT_ZONE && js.lX < STICK_INPUT_ZONE_2 ||
		js.lY > STICK_INPUT_ZONE && js.lX < -STICK_INPUT_ZONE && js.lX > -STICK_INPUT_ZONE_2)
	{
		// 向き加算
		Gear_L_rot.x += GEAR_SPIN_ANGLE;

		// 向き設定
		pGear_L->SetRot(Gear_L_rot);

		// 移動
		pos.x += -sinf(rot.y)*-fSpeed;
		pos.z += -cosf(rot.y)*-fSpeed;

		// 目的の向き
		m_rotDest.y = rot.y;
	}

	// 左に移動
	if (pKeyboard->GetPress(DIK_A) || js.lX < -STICK_INPUT_ZONE && js.lY == STICK_INPUT_ZERO ||
		js.lX < -STICK_INPUT_ZONE && js.lY < -STICK_INPUT_ZONE && js.lY > -STICK_INPUT_ZONE_2 ||
		js.lX < -STICK_INPUT_ZONE && js.lY > STICK_INPUT_ZONE && js.lY < STICK_INPUT_ZONE_2)
	{
		// 向き加算
		Gear_L_rot.x += GEAR_SPIN_ANGLE;

		// 向き設定
		pGear_L->SetRot(Gear_L_rot);

		// 移動
		pos.x += -sinf(rot.y)*fSpeed;
		pos.z += -cosf(rot.y)*fSpeed;

		// 向き
		rot.y = rot.y - SPIN_ANGLE;

		// 目的の向き
		m_rotDest.y = rot.y;
	}
	// 右に移動
	if (pKeyboard->GetPress(DIK_D) || js.lX > STICK_INPUT_ZONE && js.lY == STICK_INPUT_ZERO ||
		js.lX > STICK_INPUT_ZONE && js.lY > STICK_INPUT_ZONE && js.lY < STICK_INPUT_ZONE_2 ||
		js.lX > STICK_INPUT_ZONE && js.lY < -STICK_INPUT_ZONE && js.lY > -STICK_INPUT_ZONE_2)
	{
		// 向き加算
		Gear_L_rot.x -= GEAR_SPIN_ANGLE;

		// 向き設定
		pGear_L->SetRot(Gear_L_rot);

		// 移動
		pos.x += -sinf(rot.y)*fSpeed;
		pos.z += -cosf(rot.y)*fSpeed;

		// 向き
		rot.y = rot.y + SPIN_ANGLE;

		// 目的の向き
		m_rotDest.y = rot.y;
	}
	// 向き
	SetRot(rot);

	// 位置設定
	SetPos(pos);
}

//=============================================================================
// 攻撃処理
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Attack(void)
{
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	

	// ジョイパッド取得
	CInputJoypad *pJoypad = CManager::GetJoypad();

	// モデルの情報取得
	CModelAnime *pBattery_R = GetModelAnime(BATTERY_R_NUM);

	// モデルの情報取得
	CModelAnime *pBattery_L = GetModelAnime(BATTERY_L_NUM);

	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	// SPACEキーを押した場合
	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		// 右弾生成
		CPlayer_Bullet::Create(BATTERY_R_POS, rot);
		// 左弾生成
		CPlayer_Bullet::Create(BATTERY_L_POS, rot);
	}

	// カウントが0の場合
	if (m_nAttackCount_R == ZERO_INT)
	{
		// RTトリガーを押した場合
		if (pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, PAD_1)||
			pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, PAD_1))
		{
			// 右弾生成
			CPlayer_Bullet::Create(BATTERY_R_POS, rot);

			// インクリメント
			m_nAttackCount_R++;
		}
	}
	// カウントが0の場合
	if (m_nAttackCount_L == ZERO_INT)
	{
		// LTトリガーを押した場合
		if (pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L2_TRIGGER, PAD_1) ||
			pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L_TRIGGER, PAD_1))
		{
			// 左弾生成
			CPlayer_Bullet::Create(BATTERY_L_POS, rot);

			// インクリメント
			m_nAttackCount_L++;
		}
	}
	// カウントが0より多い場合
	if (m_nAttackCount_R > ZERO_INT)
	{
		// インクリメント
		m_nAttackCount_R++;

		// カウントが60の場合
		if (m_nAttackCount_R >= ATTACK_COOLTIME)
		{
			// 0に
			m_nAttackCount_R = ZERO_INT;
		}
	}
	// カウントが0より多い場合
	if (m_nAttackCount_L > ZERO_INT)
	{
		// インクリメント
		m_nAttackCount_L++;

		// カウントが60の場合
		if (m_nAttackCount_L >= ATTACK_COOLTIME)
		{
			// 0に
			m_nAttackCount_L = ZERO_INT;
		}
	}
}
//=============================================================================
// 当たり判定処理
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Collision(void)
{
	// CSceneのポインタ
	CScene *pScene = nullptr;

	// モデルの情報取得
	CModelAnime *pAnime = GetModelAnime(SHIP_NUM);

	// 位置取得
	D3DXVECTOR3 pos = D3DXVECTOR3(pAnime->GetMtxWorld()._41, pAnime->GetMtxWorld()._42, pAnime->GetMtxWorld()._43);

	// 位置取得
	D3DXVECTOR3 posOld = D3DXVECTOR3(pAnime->GetOldMtxWorld()._41, pAnime->GetOldMtxWorld()._42, pAnime->GetOldMtxWorld()._43);

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// nullcheck
	if (pScene == nullptr)
	{
		// 先頭のポインタ取得
		pScene = GetTop(PRIORITY_ENEMY);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcterとの当たり判定
			while (pScene != nullptr) // nullptrになるまで回す
			{
				// 現在のポインタ
				CScene *pSceneCur = pScene->GetNext();

				// 位置
				D3DXVECTOR3 CharacterPos = ZeroVector3;

				// 位置取得
				CharacterPos.x = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._41;
				CharacterPos.y = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._42;
				CharacterPos.z = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._43;

				// サイズ取得
				D3DXVECTOR3 CharacterSize = ((CCharacter*)pScene)->GetSize();

				//どこの面に当たったか取得
				//下
				if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_DOWN)
				{
					// 移動量取得
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 移動量0
					CharacterMove.y = MIN_MOVE.y;

					// 移動量設定
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// 位置
					pos.y = (-CharacterSize.y / DIVIDE_2 + CharacterPos.y) - (size.y / DIVIDE_2);

					// 位置設定
					SetPos(pos);
				}
				// 上
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_UP)
				{
					// 移動量取得
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 移動量0
					CharacterMove.y = MIN_MOVE.y;

					// 移動量設定
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// 位置
					pos.y = (CharacterSize.y / DIVIDE_2 + CharacterPos.y) + (size.y / DIVIDE_2);

					// 位置設定
					SetPos(pos);
				}
				// 左
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_LEFT)
				{
					// 移動量取得
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 移動量0
					CharacterMove.x = MIN_MOVE.x;

					// 移動量設定
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// 位置
					pos.x = (-CharacterSize.x / DIVIDE_2 + CharacterPos.x) - (size.x / DIVIDE_2);

					// 位置設定
					SetPos(pos);
				}
				// 右
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_RIGHT)
				{
					// 移動量取得
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 移動量0
					CharacterMove.x = MIN_MOVE.x;

					// 移動量設定
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// 位置
					pos.x = (CharacterSize.x / DIVIDE_2 + CharacterPos.x) + (size.x / DIVIDE_2);

					// 位置設定
					SetPos(pos);
				}
				// 手前
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_PREVIOUS)
				{
					// 移動量取得
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 移動量0
					CharacterMove.z = MIN_MOVE.z;

					// 移動量設定
					((CCharacter*)pScene)->SetMove(CharacterMove);
					
					// 位置
					pos.z = (-CharacterSize.z / DIVIDE_2 + CharacterPos.z) - (size.z / DIVIDE_2);

					// 位置設定
					SetPos(pos);
				}
				// 奥
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_BACK)
				{
					// 移動量取得
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 移動量0
					CharacterMove.z = MIN_MOVE.z;

					// 位置
					pos.z = (CharacterSize.z / DIVIDE_2 + CharacterPos.z) + (size.z / DIVIDE_2);

					// 移動量設定
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// 位置設定
					SetPos(pos);
				}
				// 次のポインタ取得
				pScene= pSceneCur;
			} 
		}
	}
}
//=============================================================================
// 外積の当たり判定処理
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::CrossCollision(void)
{
	// CSceneのポインタ
	CScene *pScene = nullptr;

	// モデルの情報取得
	CModelAnime *pAnime = GetModelAnime(SHIP_NUM);

	// 位置取得
	D3DXVECTOR3 pos = D3DXVECTOR3(pAnime->GetMtxWorld()._41, pAnime->GetMtxWorld()._42, pAnime->GetMtxWorld()._43);

	// 位置取得
	D3DXVECTOR3 posOld = D3DXVECTOR3(pAnime->GetOldMtxWorld()._41, pAnime->GetOldMtxWorld()._42, pAnime->GetOldMtxWorld()._43);

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// nullcheck
	if (pScene == nullptr)
	{
		// 先頭のポインタ取得
		pScene = GetTop(PRIORITY_ENEMY);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcterとの当たり判定
			while (pScene != nullptr) // nullptrになるまで回す
			{
				// 現在のポインタ
				CScene *pSceneCur = pScene->GetNext();

				// パーツ数取得
				int nParts = ((CCharacter*)pScene)->GetPartsNum();

				// パーツ数分繰り返す
				for (int nCnt = ZERO_INT; nCnt < nParts; nCnt++)
				{
					// メッシュ取得
					LPD3DXMESH mesh = ((CCharacter*)pScene)->GetModelAnime(nCnt)->GetMesh();

					// フェース数取得
					DWORD FaceNum = mesh->GetNumFaces();
				}
				// 次のポインタ取得
				pScene = pSceneCur;
			}
		}
	}
}
//=============================================================================
// レイ外積の当たり判定処理
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::RayCollision(void)
{
	// レイがヒットしたか
	BOOL bHit = false;
	// レイがヒットしたか
	BOOL bUnderHit = false;

	// 着地
	bool bLanding = false;

	// 距離
	float fDistancePlayer = ZERO_FLOAT;
	// 距離
	float fUnderDistance = ZERO_FLOAT;

	// 位置
	D3DXVECTOR3 vecStart, vecDirection, vecUnderDirection;

	// 角度
	float fRadius = RAY_RADIUS;

	// モデルの情報取得
	CModelAnime *pShip = GetModelAnime(SHIP_NUM);

	// 位置取得
	D3DXVECTOR3 pos = SHIP_POS;

	// マップのポインタ取得
	CMap *pMap = GET_MAP_PTR;

	// 始める座標
	vecStart = pos;

	// レイを出す角度
	vecDirection = D3DXVECTOR3(RAY_RADIUS_UNDER, ZERO_FLOAT, ZERO_FLOAT);

	// レイがヒットしたか
	D3DXIntersect(pMap->GetMesh(), &vecStart, &D3DXVECTOR3(cosf(vecUnderDirection.x), sinf(vecUnderDirection.x), ZERO_FLOAT),
		&bUnderHit, NULL, NULL, NULL, &fUnderDistance, NULL, NULL);

	// trueの場合
	if (bUnderHit == TRUE)
	{
		// 範囲より小さかったら
		if (fUnderDistance < RAY_HIT_RANGE_UNDER)
		{
			// 戻す
			pos -= (D3DXVECTOR3(cosf(vecUnderDirection.x), sinf(vecUnderDirection.x), ZERO_FLOAT));

			// 位置設定
			SetPos(pos);

			// trueに
			bLanding = true;

			return;
		}
	}
	// 4回繰り返す
	for (int nCount = ZERO_INT; nCount < RAY_NUM; nCount++)
	{
		// レイを出す角度
		vecDirection = D3DXVECTOR3(ZERO_FLOAT, fRadius * nCount, ZERO_FLOAT);

		// レイがヒットしたか
		D3DXIntersect(pMap->GetMesh(), &vecStart, &D3DXVECTOR3(sinf(vecDirection.y), ZERO_FLOAT, cosf(vecDirection.y)),
			&bHit, NULL, NULL, NULL, &fDistancePlayer, NULL, NULL);

		// trueの場合
		if (bHit == TRUE)
		{
			// 範囲より小さかったら
			if (fDistancePlayer < RAY_HIT_RANGE)
			{
				// 戻す
				pos -= (D3DXVECTOR3(sinf(vecDirection.y), ZERO_FLOAT, cosf(vecDirection.y)));

				// 位置設定
				SetPos(pos);

				return;
			}
		}
	}

	// 着地状態設定
	SetLanding(bLanding);
}