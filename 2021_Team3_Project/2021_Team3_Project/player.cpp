//=============================================================================
// プレイヤークラス [player.cpp]
// Author : Sugawara Tsukasa
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
#include "player_life.h"
#include "effect.h"

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define PLAYER_SPEED			(50.0f)									// プレイヤーの移動量
#define STICK_SENSITIVITY		(50.0f)									// スティック感度
#define PLAYER_ROT_SPEED		(0.1f)									// キャラクターの回転する速度
#define SHIP_NUM				(0)										// 船のナンバー
#define GEAR_R_NUM				(1)										// 水かきの右ナンバー
#define GEAR_L_NUM				(2)										// 水かきの左ナンバー
#define BATTERY_R_NUM			(3)										// 砲台右のナンバー
#define BATTERY_L_NUM			(4)										// 砲台左のナンバー
#define MIN_MOVE				(D3DXVECTOR3(0.0f,0.0f,0.0f))			// 移動量の最小値
#define SIZE					(D3DXVECTOR3 (800.0f,1000.0f,800.0f))	// サイズ
#define PARENT_NUM				(0)										// 親のナンバー
#define GEAR_SPIN_ANGLE			(D3DXToRadian(2.0f))					// 歯車の回転角度
#define SPIN_ANGLE				(D3DXToRadian(1.0f))					// 旋回角度
#define STICK_INPUT_ZONE		(100)									// スティックの入力範囲
#define STICK_INPUT_ZONE_2		(1000)									// スティックの入力範囲
#define STICK_INPUT_ZERO		(0)										// スティックの入力値0
#define MUT_SPEED				(1.5f)									// スピード
#define PAD_1					(0)										// 1番目のパッド
#define PAD_2					(1)										// 2番目のパッド
#define ATTACK_COOLTIME			(90)									// 攻撃のクールタイム
#define RAY_NUM					(4)										// レイの数
#define RAY_RADIUS				(D3DXToRadian(360.0f/4.0f))				// レイを出す方向
#define RAY_HIT_RANGE			(600.0f)								// 範囲
#define MIN_LIFE				(0)										// ライフの最小
#define LIFE					(100)									// ライフ
#define ANGLE_MAX				(D3DXToRadian(360.0f))					// 角度の最大
#define ANGLE_MIN				(D3DXToRadian(-360.0f))					// 角度の最小
#define ANGLE_0					(D3DXToRadian(0.0f))					// 角度0
#define ANGLE_90				(D3DXToRadian(90.0f))					// 角度90
#define ANGLE_180				(D3DXToRadian(180.0f))					// 角度180
#define ANGLE_270				(D3DXToRadian(270.0f))					// 角度270
#define GEAR_DEF_ROT			(D3DXToRadian(0.0f))					// デフォルトの角度
#define DEAD_ZONE				(0.0f)									// コントローラーの反応しない範囲
#define PAD_P1					(0)										// パッドプレイヤー1
#define PAD_P2					(1)										// パッドプレイヤー2
#define KNOCK_BACK_SPEED		(100.0f)								// ノックバックの速さ
#define KNOCK_BACK_COUNT		(10)									// ノックバックカウント
#define ARCDIR					(D3DXVECTOR3(1.0f,0.0f,0.0f))			// 方向
#define STICK_ANGLERANGE		(1.0f)									//スティックの角度範囲
#define SINK_TIME				(120)									// 沈む時間
#define SINK_MOVE				(3.0f)									// 沈む量
#define SINK_ROTATE				(3.0f)									// 沈む角度

// 船体の位置
#define SHIP_POS				(D3DXVECTOR3(pShip->GetMtxWorld()._41, pShip->GetMtxWorld()._42, pShip->GetMtxWorld()._43))
// 砲台の位置
#define BATTERY_R_POS			(D3DXVECTOR3(pBattery_R->GetMtxWorld()._41, pBattery_R->GetMtxWorld()._42, pBattery_R->GetMtxWorld()._43))
#define BATTERY_L_POS			(D3DXVECTOR3(pBattery_L->GetMtxWorld()._41, pBattery_L->GetMtxWorld()._42, pBattery_L->GetMtxWorld()._43))

//エフェクトの各数値
//爆発
#define EXPLOSION_POS		(D3DXVECTOR3(500.0f, 500.0f, 1.0f))						//位置
#define EXPLOSION_SIZE		(D3DXVECTOR3(500, 500, 500))							//大きさ
#define EXPLOSION_COLOR		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))						//色
#define EXPLOSION_LIFE		(70)													//体力

//煙																				
#define SMOKE_POS			(D3DXVECTOR3(0, 1, 0))									//位置
#define SMOKE_SIZE			(D3DXVECTOR3(200.0f, 200.0f, 200.0f))					//大きさ
#define SMOKE_MOVE			(D3DXVECTOR3(4.0f, 5.0f, 4.0f))							//移動力
#define SMOKE_COLOR			(D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f))						//色
#define SMOKE_LIFE			(500)													//体力

//水しぶき																			
#define SPLASH_POS			(D3DXVECTOR3(0, 1, 0))									//位置
#define SPLASH_SIZE			(D3DXVECTOR3(80.0f, 80.0f, 80.0f))						//大きさ
#define SPLASH_MOVE			(D3DXVECTOR3(10.0f, 20.0f, 10.0f))						//移動力
#define SPLASH_COLOR		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))						//色
#define SPLASH_LIFE			(200)													//体力

//木材																			
#define WOOD_POS			(D3DXVECTOR3(0, 1, 0))									//位置
#define WOOD_SIZE			(D3DXVECTOR3(100.0f, 100.0f, 100.0f))					//大きさ
#define WOOD_MOVE			(D3DXVECTOR3(10.0f, 10.0f, 10.0f))						//移動力
#define WOOD_COLOR			(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))						//色
#define WOOD_LIFE			(500)													//体力

//波																				
#define WAVE_POS			(D3DXVECTOR3(GetPos().x-10.0f, 1, GetPos().z-10.0f))	//位置
#define WAVE_SIZE			(D3DXVECTOR3(20, 20, 20))								//大きさ
#define WAVE_MOVE			(D3DXVECTOR3(50.0, 8.0, 50.0))							//移動力
#define WAVE_COLOR			(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))						//色
#define WAVE_LIFE			(70)													//体力
#define WAVE_MAX_PARTICLE	(10)													//放出回数

//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
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
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) : CCharacter(Priority)
{
	m_rotDest = ZeroVector3;
	m_bMove = false;
	m_nAttackCount_R = ZERO_INT;
	m_nAttackCount_L = ZERO_INT;
	m_PadType = PAD_TYPE_1P;
	m_fAngle_L = 0;
	m_fAngle_R = 0;
	m_nSinkCounter = 0;
	m_bHitFlag = false;
	m_bDeath = false;
	m_bEnd = false;
}

//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 初期化処理
// Author : Sugawara Tsukasa
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

	// 向き代入
	m_rotDest = rot;

	// サイズ設定
	SetSize(SIZE);

	// ライフ
	SetLife(LIFE);

	// 速度設定
	SetSpeed(PLAYER_SPEED);

	// ジョイパッドの取得
	LPDIRECTINPUTDEVICE8 P1_PAD = CInputJoypad::GetController(PAD_P1);
	LPDIRECTINPUTDEVICE8 P2_PAD = CInputJoypad::GetController(PAD_P2);

	// パッドが2個つながってる場合
	if (P1_PAD != nullptr && P2_PAD != nullptr)
	{
		m_PadType = PAD_TYPE_1P;
	}

	// 影の使用
	SetUseShadow();

	// 影の回転を反映させる
	SetShadowRotCalculation();

	// レイの情報設定
	CCharacter::RAY_DATA Ray_Data = { RAY_RADIUS ,RAY_HIT_RANGE ,RAY_NUM };

	// レイの情報設定
	SetRay_Data(Ray_Data);

	return S_OK;
}

//=============================================================================
// 終了処理
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Uninit(void)
{
	// 終了処理
	CCharacter::Uninit();
}

//=============================================================================
// 更新処理
// Author : Sugawara Tsukasa
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

	// 体力が0になったら
	if (!m_bDeath)
	{
		// プレイヤーの制御
		PlayerControl();
	}
	else
	{
		// 沈んでいく処理
		SinkEnd();
	}

	// 角度の更新処理
	UpdateRot();
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
// Author : Sugawara Tsukasa
// プレイヤーの状態
//=============================================================================
void CPlayer::UpdateState(void)
{

}

//=============================================================================
// プレイヤーの制御
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::PlayerControl()
{
	CManager::MODE_TYPE mode = CManager::GetMode();

	if (mode == CManager::MODE_TYPE_GAME)
	{
		// 1Pの場合
		if (m_PadType == PAD_TYPE_1P)
		{
			// プレイヤーの移動処理
			Move();

			// 攻撃処理
			Attack();
		}
		// 1Pの場合
		if (m_PadType == PAD_TYPE_2P)
		{
			// プレイヤーの移動処理
			Pad2Move();

			// 攻撃処理
			Pad2Attack();
		}

		// キーボード移動
		KeyboardMove();

		// 攻撃処理
		Attack();

		// 当たり判定
		Collision();
	}
}

//=============================================================================
// 角度の更新処理
// Author : Sugawara Tsukasa
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
// 敵の弾のヒット処理
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Hit(int nDamage)
{
	GetLife() = -nDamage;

	// 0以下だったら
	if (!m_bDeath && GetLife() <= 0)
	{
		// 死ぬ
		Death();
	}
}

//=============================================================================
// 死んだときの処理
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Death(void)
{
	m_bDeath = true;
	SetGravityFlag(false);

	return;
}

//=============================================================================
// 移動の処理
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Move(void)
{
	DIJOYSTATE js = CInputJoypad::GetStick(PAD_P1);							// ジョイパッドの取得
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();		// サウンドのポインタ
	D3DXVECTOR3 pos = GetPos();												// 座標
	D3DXVECTOR3 rot = GetRot();												// 角度
	float fSpeed = GetSpeed();												// スピード
	float fAngle_R = ZERO_FLOAT;											// 右角度
	float fAngle_L = ZERO_FLOAT;											// 左角度
	float disfAngle_R = GetAngle_R();										//前のコントローラーの角度を取得
	float disfAngle_L = GetAngle_L();										//前のコントローラーの角度を取得

																			//// 左の歯車の情報取得
																			//CModelAnime *pGear_L = GetModelAnime(GEAR_L_NUM);
																			//// 向き取得
																			//D3DXVECTOR3 Gear_L_rot = pGear_L->GetRot();

																			//// 右の歯車の情報取得
																			//CModelAnime *pGear_R = GetModelAnime(GEAR_R_NUM);
																			//// 向き取得
																			//D3DXVECTOR3 Gear_R_rot = pGear_R->GetRot();

																			//===========================================
																			// 右歯車
																			//===========================================
																			// 右スティックが入力されている場合
	if (js.lZ != DEAD_ZONE || js.lRz != DEAD_ZONE)
	{
		// コントローラーの角度
		fAngle_R = atan2f((float)js.lRz, (float)js.lZ);

		// 左に移動
		if (fAngle_R < disfAngle_R && fAngle_R + STICK_ANGLERANGE > disfAngle_R)
		{
			// パドルの回転
			PaddleRotateR(-GEAR_SPIN_ANGLE);

			// 移動
			pos.x += -sinf(rot.y)*fSpeed;
			pos.z += -cosf(rot.y)*fSpeed;

			// 向き
			rot.y = rot.y - SPIN_ANGLE;

			// 目的の向き
			m_rotDest.y = rot.y;
		}
		// falseの場合
		else if (m_bBack == false)
		{
			// 右に移動
			if (fAngle_R > disfAngle_R && fAngle_R - STICK_ANGLERANGE < disfAngle_R)
			{
				// パドルの回転
				PaddleRotateR(GEAR_SPIN_ANGLE);

				// 移動
				pos.x += -sinf(rot.y)*fSpeed;
				pos.z += -cosf(rot.y)*fSpeed;

				// 向き
				rot.y = rot.y + SPIN_ANGLE;

				// 目的の向き
				m_rotDest.y = rot.y;
			}
		}
		//波エフェクト
		CreateWave();
		SetAngle_R(fAngle_R);
	}
	//===========================================
	// 左歯車
	//===========================================
	// 左スティックが入力されている場合
	if (js.lX != DEAD_ZONE || js.lY != DEAD_ZONE)
	{
		// コントローラーの角度
		fAngle_L = atan2f((float)js.lY, (float)js.lX);

		// 右に移動
		if (fAngle_L < disfAngle_L && fAngle_L + STICK_ANGLERANGE > disfAngle_L)
		{
			// パドルの回転
			PaddleRotateL(-GEAR_SPIN_ANGLE);

			// 移動
			pos.x += -sinf(rot.y)*fSpeed;
			pos.z += -cosf(rot.y)*fSpeed;

			// 向き
			rot.y = rot.y + SPIN_ANGLE;

			// 目的の向き
			m_rotDest.y = rot.y;
		}
		// falseの場合
		else if (m_bBack == false)
		{
			// 左に移動
			if (fAngle_L > disfAngle_L && fAngle_L - STICK_ANGLERANGE < disfAngle_L)
			{
				// パドルの回転
				PaddleRotateL(GEAR_SPIN_ANGLE);

				// 移動
				pos.x += -sinf(rot.y)*fSpeed;
				pos.z += -cosf(rot.y)*fSpeed;

				// 向き
				rot.y = rot.y - SPIN_ANGLE;

				// 目的の向き
				m_rotDest.y = rot.y;
			}
		}
		//波エフェクト
		CreateWave();
		SetAngle_L(fAngle_L);
	}
	// 入力されている場合
	if (js.lX != DEAD_ZONE || js.lY != DEAD_ZONE && js.lZ != DEAD_ZONE || js.lRz != DEAD_ZONE)
	{
		// 右スティックと左スティックが下に倒されている場合
		if (fAngle_L > disfAngle_L && fAngle_R > disfAngle_R)
		{
			// trueに
			m_bBack = true;
			// trueの場合
			if (m_bBack == true)
			{
				// パドルの回転
				PaddleRotateR(GEAR_SPIN_ANGLE);
				PaddleRotateL(GEAR_SPIN_ANGLE);

				// 移動
				pos.x += sinf(rot.y)*fSpeed;
				pos.z += cosf(rot.y)*fSpeed;

			}
		}
		// 右スティックと左スティックが下に倒されていない場合
		else
		{
			// falseに
			m_bBack = false;
		}
	}

	// 角度の補正
	PaddleRotFix();

	// 向き
	SetRot(rot);

	// 位置設定
	SetPos(pos);
}
//=============================================================================
// 2パッドの移動処理関数
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Pad2Move(void)
{
	// ジョイパッドの取得
	DIJOYSTATE P1_js = CInputJoypad::GetStick(PAD_P1);
	DIJOYSTATE P2_js = CInputJoypad::GetStick(PAD_P2);
	float disfAngle_R = GetAngle_R();										//前のコントローラーの角度を取得
	float disfAngle_L = GetAngle_L();										//前のコントローラーの角度を取得

																			// サウンドのポインタ
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	// 座標
	D3DXVECTOR3 pos = GetPos();

	// 角度
	D3DXVECTOR3 rot = GetRot();

	// スピード
	float fSpeed = GetSpeed();

	// 右角度
	float fAngle_R = ZERO_FLOAT;

	// 左角度
	float fAngle_L = ZERO_FLOAT;

	// 左の歯車の情報取得
	CModelAnime *pGear_L = GetModelAnime(GEAR_L_NUM);
	// 向き取得
	D3DXVECTOR3 Gear_L_rot = pGear_L->GetRot();

	// 右の歯車の情報取得
	CModelAnime *pGear_R = GetModelAnime(GEAR_R_NUM);
	// 向き取得
	D3DXVECTOR3 Gear_R_rot = pGear_R->GetRot();

	//===========================================
	// 左歯車 ※1Player
	//===========================================
	// 左スティックが入力されている場合
	if (P1_js.lX != DEAD_ZONE || P1_js.lY != DEAD_ZONE)
	{
		// コントローラーの角度
		fAngle_L = atan2f((float)P1_js.lY, (float)P1_js.lX);

		// 右に移動
		if (fAngle_L < disfAngle_L)
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
		// falseの場合
		if (m_bBack == false)
		{
			// 左に移動
			if (fAngle_L > disfAngle_L)
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
		}
		//波エフェクト
		CreateWave();
		SetAngle_L(fAngle_L);
	}
	//===========================================
	// 右歯車 ※2Player
	//===========================================
	// 左スティックが入力されている場合
	if (P2_js.lX != DEAD_ZONE || P2_js.lY != DEAD_ZONE)
	{
		// コントローラーの角度
		fAngle_R = atan2f((float)P2_js.lY, (float)P2_js.lX);

		// 左に移動
		if (fAngle_R < disfAngle_R)
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
		// falseの場合
		if (m_bBack == false)
		{
			// 右に移動
			if (fAngle_R > disfAngle_R)
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
		}
		//波エフェクト
		CreateWave();
		//格納
		SetAngle_R(fAngle_R);
	}
	// 入力されている場合
	if (P1_js.lX != DEAD_ZONE || P1_js.lY != DEAD_ZONE && P2_js.lX != DEAD_ZONE || P2_js.lY != DEAD_ZONE)
	{
		// 右スティックと左スティックが下に倒されている場合
		if (fAngle_L > disfAngle_L && fAngle_R > disfAngle_R)
		{
			// trueに
			m_bBack = true;
			// trueの場合
			if (m_bBack == true)
			{
				// 向き加算
				Gear_L_rot.x += GEAR_SPIN_ANGLE;
				// 向き設定
				pGear_L->SetRot(Gear_L_rot);

				// 向き加算
				Gear_R_rot.x += GEAR_SPIN_ANGLE;
				// 向き設定
				pGear_R->SetRot(Gear_R_rot);

				// 移動
				pos.x += sinf(rot.y)*fSpeed;
				pos.z += cosf(rot.y)*fSpeed;
			}
		}
		// 入力されていない場合
		else
		{
			// falseに
			m_bBack = false;
		}
	}

	// 角度が最大になった場合
	if (Gear_L_rot.x >= ANGLE_MAX || Gear_L_rot.x <= ANGLE_MIN)
	{
		// 0に戻す
		Gear_L_rot.x = GEAR_DEF_ROT;
		// 向き設定
		pGear_L->SetRot(Gear_L_rot);
	}

	// 角度が最大になった場合
	if (Gear_R_rot.x >= ANGLE_MAX || Gear_R_rot.x <= ANGLE_MIN)
	{
		// 0に戻す
		Gear_R_rot.x = GEAR_DEF_ROT;
		// 向き設定
		pGear_R->SetRot(Gear_R_rot);
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
		if (pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, PAD_1) ||
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
// 2コントローラーの攻撃処理
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Pad2Attack(void)
{
	// ジョイパッド取得
	CInputJoypad *pJoypad = CManager::GetJoypad();

	// モデルの情報取得
	CModelAnime *pBattery_R = GetModelAnime(BATTERY_R_NUM);

	// モデルの情報取得
	CModelAnime *pBattery_L = GetModelAnime(BATTERY_L_NUM);

	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	// カウントが0の場合
	if (m_nAttackCount_L == ZERO_INT)
	{
		// LTトリガーを押した場合
		if (pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, PAD_1) ||
			pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, PAD_1))
		{
			// 左弾生成
			CPlayer_Bullet::Create(BATTERY_L_POS, rot);

			// インクリメント
			m_nAttackCount_L++;
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
	// カウントが0の場合
	if (m_nAttackCount_R == ZERO_INT)
	{
		// RTトリガーを押した場合
		if (pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, PAD_2) ||
			pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, PAD_2))
		{
			// 右弾生成
			CPlayer_Bullet::Create(BATTERY_R_POS, rot);

			// インクリメント
			m_nAttackCount_R++;
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
}
//=============================================================================
// キーボード移動処理
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::KeyboardMove(void)
{
	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// 左の歯車の情報取得
	CModelAnime *pGear_L = GetModelAnime(GEAR_L_NUM);
	// 向き取得
	D3DXVECTOR3 Gear_L_rot = pGear_L->GetRot();

	// 右の歯車の情報取得
	CModelAnime *pGear_R = GetModelAnime(GEAR_R_NUM);
	// 向き取得
	D3DXVECTOR3 Gear_R_rot = pGear_R->GetRot();

	// 座標
	D3DXVECTOR3 pos = GetPos();

	// 角度
	D3DXVECTOR3 rot = GetRot();

	// スピード
	float fSpeed = GetSpeed();

	// 右角度
	float fAngle_R = ZERO_FLOAT;

	// 左角度
	float fAngle_L = ZERO_FLOAT;

	// 右に移動
	if (pKeyboard->GetPress(DIK_W))
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

		//エフェクト
		CreateWave();

		// falseに
		m_bBack = false;
	}
	// falseの場合
	if (m_bBack == false)
	{
		// 左に移動
		if (pKeyboard->GetPress(DIK_S))
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
	}
	// 右に移動
	if (pKeyboard->GetPress(DIK_UP))
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

		//エフェクト
		CreateWave();

		// falseに
		m_bBack = false;
	}
	// falseの場合
	if (m_bBack == false)
	{
		// 左に移動
		if (pKeyboard->GetPress(DIK_DOWN))
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
	}
	// 後ろ移動
	if (pKeyboard->GetPress(DIK_DOWN) && pKeyboard->GetPress(DIK_S))
	{
		// trueに
		m_bBack = true;

		// trueの場合
		if (m_bBack == true)
		{
			// 向き加算
			Gear_L_rot.x += GEAR_SPIN_ANGLE;
			// 向き設定
			pGear_L->SetRot(Gear_L_rot);

			// 向き加算
			Gear_R_rot.x += GEAR_SPIN_ANGLE;
			// 向き設定
			pGear_R->SetRot(Gear_R_rot);

			// 移動
			pos.x += sinf(rot.y)*fSpeed;
			pos.z += cosf(rot.y)*fSpeed;
		}
	}

	if (pKeyboard->GetPress(DIK_P))
	{
		//パーティクル生成
		CreateSmoke();
		CreateWoodEP();
		CreateExplosion();
	}

	// 角度が最大になった場合
	if (Gear_L_rot.x >= ANGLE_MAX || Gear_L_rot.x <= ANGLE_MIN)
	{
		// 0に戻す
		Gear_L_rot.x = GEAR_DEF_ROT;
		// 向き設定
		pGear_L->SetRot(Gear_L_rot);
	}

	// 角度が最大になった場合
	if (Gear_R_rot.x >= ANGLE_MAX || Gear_R_rot.x <= ANGLE_MIN)
	{
		// 0に戻す
		Gear_R_rot.x = GEAR_DEF_ROT;
		// 向き設定
		pGear_R->SetRot(Gear_R_rot);
	}
	// 向き
	SetRot(rot);

	// 位置設定
	SetPos(pos);
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
				pScene = pSceneCur;
			}
		}

		// 先頭のポインタ取得
		pScene = GetTop(PRIORITY_OBSTACLE);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcterとの当たり判定
			while (pScene != nullptr) // nullptrになるまで回す
			{
				// 現在のポインタ
				CScene *pSceneCur = pScene->GetNext();

				// 位置
				D3DXVECTOR3 ObstaclePos = ((CModel*)pScene)->GetPos();

				// サイズ取得
				D3DXVECTOR3 ObstacleSize = ((CModel*)pScene)->GetSize();

				// 矩形の当たり判定
				if (CCollision::CollisionRectangleAndRectangle(ObstaclePos, pos, ObstacleSize, size) == true)
				{
					// ベクトル
					D3DXVECTOR3 Vec = ZeroVector3;

					// 法線ベクトル
					D3DXVECTOR3 NormalVec = ZeroVector3;

					// 進行ベクトル
					Vec.x = ObstaclePos.x - pos.x;
					Vec.z = ObstaclePos.z - pos.z;

					// 長さ算出
					float fVec_Length = sqrtf((Vec.x * Vec.x) + (Vec.z * Vec.z));

					// 法線ベクトルに
					NormalVec.x = Vec.x / fVec_Length;
					NormalVec.z = Vec.z / fVec_Length;

					// 反射ベクトル算出
					D3DXVec3Normalize(&m_Reflection_Vec, &(Vec - 2.0f * D3DXVec3Dot(&Vec, &NormalVec) * NormalVec));

					// trueに
					m_bKnock_Back = true;
				}

				// 次のポインタ取得
				pScene = pSceneCur;
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

//=======================================================================================
// 沈む処理
// Author : Konishi Yuuto
//=======================================================================================
void CPlayer::SinkEnd(void)
{
	if (!m_bEnd)
	{
		m_nSinkCounter++;

		GetPos().y -= SINK_MOVE;

		if (m_nSinkCounter >= SINK_TIME)
		{
			m_bEnd = true;
			m_nSinkCounter = 0;
		}
	}
	GetRot().x += D3DXToRadian(SINK_ROTATE);
}

//=======================================================================================
// 煙生成関数
// Author : Oguma Akira
//=======================================================================================
void CPlayer::CreateSmoke(void)
{
	// パーティクル生成
	CEffect::Create(SMOKE_POS, SMOKE_SIZE, SMOKE_MOVE, SMOKE_COLOR,
		CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_1), SMOKE_LIFE);
}

//=======================================================================================
// 木材爆破生成関数
// Author : Oguma Akira
//=======================================================================================
void CPlayer::CreateWoodEP(void)
{
	// パーティクル生成
	CEffect::Create(WOOD_POS,
		WOOD_SIZE, WOOD_MOVE, WOOD_COLOR,
		CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_5), WOOD_LIFE);
}

//=======================================================================================
// 水しぶき生成関数
// Author : Oguma Akira
//=======================================================================================
void CPlayer::CreateSplash(void)
{
	for (int nCntEffect = 0; nCntEffect < 10; nCntEffect++)
	{
		// パーティクル生成
		CEffect::Create(SPLASH_POS,
			WOOD_SIZE, SPLASH_MOVE, SPLASH_COLOR,
			CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_4), SPLASH_LIFE);
	}
}

//=======================================================================================
// 爆発生成関数
// Author : Oguma Akira
//=======================================================================================
void CPlayer::CreateExplosion(void)
{
	// パーティクル生成
	CEffect::Create(EXPLOSION_POS, EXPLOSION_SIZE, ZeroVector3, EXPLOSION_COLOR,
		CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_2), EXPLOSION_LIFE);

}

//=======================================================================================
// 波生成関数
// Author : Oguma Akira
//=======================================================================================
void CPlayer::CreateWave(void)
{
	for (int nCntEffect = 0; nCntEffect < WAVE_MAX_PARTICLE; nCntEffect++)
	{
		// パーティクル生成
		CEffect::Create(WAVE_POS, WAVE_SIZE, WAVE_MOVE, WAVE_COLOR,
			CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_3), WAVE_LIFE);
	}
}

//=============================================================================
// ノックバック処理関数
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Knock_Back(void)
{
	// カウントインクリメント
	m_nRockHitCount++;

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 0の場合
	if (m_nRockHitCount <= KNOCK_BACK_COUNT)
	{
		// 移動量
		move.x = m_Reflection_Vec.x *KNOCK_BACK_SPEED;
		move.z = m_Reflection_Vec.z *KNOCK_BACK_SPEED;

		// 移動量設定
		SetMove(move);
	}
	// 10より大きい場合
	if (m_nRockHitCount > KNOCK_BACK_COUNT)
	{
		// 移動量設定
		SetMove(ZeroVector3);

		// 0に戻す
		m_nRockHitCount = ZERO_INT;

		// falseに
		m_bKnock_Back = false;
	}
}

//=============================================================================
// パドルの右回転
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::PaddleRotateR(float fRotate)
{
	// 右の歯車の情報取得
	CModelAnime *pGear_R = GetModelAnime(GEAR_R_NUM);
	// 向き取得
	D3DXVECTOR3 Gear_R_rot = pGear_R->GetRot();

	// 角度加算
	Gear_R_rot.x += fRotate;

	// 向き設定
	pGear_R->SetRot(Gear_R_rot);
}

//=============================================================================
// パドルの左回転
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::PaddleRotateL(float fRotate)
{
	// 左の歯車の情報取得
	CModelAnime *pGear_L = GetModelAnime(GEAR_L_NUM);
	// 向き取得
	D3DXVECTOR3 Gear_L_rot = pGear_L->GetRot();

	// 角度加算
	Gear_L_rot.x += fRotate;

	// 向き設定
	pGear_L->SetRot(Gear_L_rot);
}

//=============================================================================
// パドルの角度修正
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::PaddleRotFix(void)
{
	// 右の歯車の情報取得
	CModelAnime *pGear_R = GetModelAnime(GEAR_R_NUM);
	// 向き取得
	D3DXVECTOR3 Gear_R_rot = pGear_R->GetRot();
	// 左の歯車の情報取得
	CModelAnime *pGear_L = GetModelAnime(GEAR_L_NUM);
	// 向き取得
	D3DXVECTOR3 Gear_L_rot = pGear_L->GetRot();

	// 角度が最大になった場合
	if (Gear_L_rot.x >= ANGLE_MAX || Gear_L_rot.x <= ANGLE_MIN)
	{
		// 0に戻す
		Gear_L_rot.x = GEAR_DEF_ROT;
		// 向き設定
		pGear_L->SetRot(Gear_L_rot);
	}

	// 角度が最大になった場合
	if (Gear_R_rot.x >= ANGLE_MAX || Gear_R_rot.x <= ANGLE_MIN)
	{
		// 0に戻す
		Gear_R_rot.x = GEAR_DEF_ROT;
		// 向き設定
		pGear_R->SetRot(Gear_R_rot);
	}
}

//=============================================================================
// Lスティック角度値格納関数
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::SetAngle_L(float fangle_L)
{
	m_fAngle_L = fangle_L;
}

//=============================================================================
// Rスティック角度値格納関数
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::SetAngle_R(float fangle_R)
{
	m_fAngle_R = fangle_R;
}