//=============================================================================
// 繝励Ξ繧､繝､繝ｼ繧ｯ繝ｩ繧ｹ [player.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// 繧､繝ｳ繧ｯ繝ｫ繝ｼ繝
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
#include "game.h"
#include "effect.h"

//=============================================================================
// 繝槭け繝ｭ螳夂ｾｩ
// Author : Sugawara Tsukasa
//=============================================================================
#define PLAYER_SPEED			(20.0f)									// プレイヤーの移動量
#define STICK_SENSITIVITY		(50.0f)									// スティック感度
#define PLAYER_ROT_SPEED		(0.1f)									// キャラクターの回転する速度
#define SHIP_NUM				(0)										// 船のナンバー
#define GEAR_R_NUM				(1)										// 水かきの右ナンバー
#define GEAR_L_NUM				(2)										// 水かきの左ナンバー
#define BATTERY_R_NUM			(3)										// 砲台右のナンバー
#define BATTERY_L_NUM			(4)										// 砲台左のナンバー
#define MIN_MOVE				(D3DXVECTOR3(0.0f,0.0f,0.0f))			// 移動量の最小値
#define SIZE					(D3DXVECTOR3 (1200.0f,1000.0f,1200.0f))	// サイズ
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
#define SOUND_INTER_TIME		(10)									// 移動の音の間隔
// 船体の位置
#define SHIP_POS				(D3DXVECTOR3(pShip->GetMtxWorld()._41, pShip->GetMtxWorld()._42, pShip->GetMtxWorld()._43))
// 遐ｲ蜿ｰ縺ｮ菴咲ｽｮ
#define BATTERY_R_POS			(D3DXVECTOR3(pBattery_R->GetMtxWorld()._41, pBattery_R->GetMtxWorld()._42, pBattery_R->GetMtxWorld()._43))
#define BATTERY_L_POS			(D3DXVECTOR3(pBattery_L->GetMtxWorld()._41, pBattery_L->GetMtxWorld()._42, pBattery_L->GetMtxWorld()._43))

//繧ｨ繝輔ぉ繧ｯ繝医�蜷�焚蛟､
//辷�匱
#define EXPLOSION_POS		(D3DXVECTOR3(500.0f, 500.0f, 1.0f))						//菴咲ｽｮ
#define EXPLOSION_SIZE		(D3DXVECTOR3(500, 500, 500))							//螟ｧ縺阪＆
#define EXPLOSION_COLOR		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))						//濶ｲ
#define EXPLOSION_LIFE		(70)													//菴灘鴨

//辣																				
#define SMOKE_POS			(D3DXVECTOR3(0, 1, 0))									//菴咲ｽｮ
#define SMOKE_SIZE			(D3DXVECTOR3(200.0f, 200.0f, 200.0f))					//螟ｧ縺阪＆
#define SMOKE_MOVE			(D3DXVECTOR3(4.0f, 5.0f, 4.0f))							//遘ｻ蜍募鴨
#define SMOKE_COLOR			(D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f))						//濶ｲ
#define SMOKE_LIFE			(500)													//菴灘鴨

//豌ｴ縺励�縺																			
#define SPLASH_POS			(D3DXVECTOR3(0, 1, 0))									//菴咲ｽｮ
#define SPLASH_SIZE			(D3DXVECTOR3(80.0f, 80.0f, 80.0f))						//螟ｧ縺阪＆
#define SPLASH_MOVE			(D3DXVECTOR3(10.0f, 20.0f, 10.0f))						//遘ｻ蜍募鴨
#define SPLASH_COLOR		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))						//濶ｲ
#define SPLASH_LIFE			(200)													//菴灘鴨

//譛ｨ譚																			
#define WOOD_POS			(D3DXVECTOR3(0, 1, 0))									//菴咲ｽｮ
#define WOOD_SIZE			(D3DXVECTOR3(100.0f, 100.0f, 100.0f))					//螟ｧ縺阪＆
#define WOOD_MOVE			(D3DXVECTOR3(10.0f, 10.0f, 10.0f))						//遘ｻ蜍募鴨
#define WOOD_COLOR			(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))						//濶ｲ
#define WOOD_LIFE			(500)													//菴灘鴨

//豕｢																				
#define WAVE_POS			(D3DXVECTOR3(GetPos().x-10.0f, 1, GetPos().z-10.0f))	//菴咲ｽｮ
#define WAVE_SIZE			(D3DXVECTOR3(20, 20, 20))								//螟ｧ縺阪＆
#define WAVE_MOVE			(D3DXVECTOR3(50.0, 8.0, 50.0))							//遘ｻ蜍募鴨
#define WAVE_COLOR			(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))						//濶ｲ
#define WAVE_LIFE			(70)													//菴灘鴨
#define WAVE_MAX_PARTICLE	(10)													//謾ｾ蜃ｺ蝗樊焚

//=============================================================================
// 逕滓�蜃ｦ逅�未謨ｰ
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 蛻晄悄蛹門�逅
	CPlayer *pPlayer = new CPlayer;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// 蛻晄悄蛹門�逅
		pPlayer->Init(pos, rot);
	}

	// 繝昴う繝ｳ繧ｿ繧定ｿ斐☆
	return pPlayer;
}

//=============================================================================
// 繧ｳ繝ｳ繧ｹ繝医Λ繧ｯ繧ｿ
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) : CCharacter(Priority)
{
	m_rotDest = ZeroVector3;
	m_bMove = false;
	m_nAttackCount_R = ZERO_INT;
	m_nAttackCount_L = ZERO_INT;
	m_PadType = PAD_TYPE_1P;
	m_fdisAngle_L = 0;
	m_fdisAngle_R = 0;
	m_nSinkCounter = 0;
	m_bHitFlag = false;
	m_bDeath = false;
	m_bEnd = false;
	m_bKnock_Back = false;
	m_nSoundCounter = 0;
	m_bMoveSound = false;
}

//=============================================================================
// 繝�せ繝医Λ繧ｯ繧ｿ
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 蛻晄悄蛹門�逅
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 繝｢繝�Ν諠�ｱ蜿門ｾ
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// 繝｢繝�Ν縺ｮ諠�ｱ繧呈ｸ｡縺
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER);
	}

	// 蛻晄悄蛹
	CCharacter::Init(pos, rot);

	// 蜷代″莉｣蜈･
	m_rotDest = rot;

	// 繧ｵ繧､繧ｺ險ｭ螳
	SetSize(SIZE);

	// 繝ｩ繧､繝
	SetLife(LIFE);

	// 騾溷ｺｦ險ｭ螳
	SetSpeed(PLAYER_SPEED);

	// 繧ｸ繝ｧ繧､繝代ャ繝峨�蜿門ｾ
	LPDIRECTINPUTDEVICE8 P1_PAD = CInputJoypad::GetController(PAD_P1);
	LPDIRECTINPUTDEVICE8 P2_PAD = CInputJoypad::GetController(PAD_P2);

	// 繝代ャ繝峨′2蛟九▽縺ｪ縺後▲縺ｦ繧句ｴ蜷
	if (P1_PAD != nullptr && P2_PAD != nullptr)
	{
		m_PadType = PAD_TYPE_1P;
	}

	// 蠖ｱ縺ｮ菴ｿ逕ｨ
	SetUseShadow();

	// 蠖ｱ縺ｮ蝗櫁ｻ｢繧貞渚譏縺輔○繧
	SetShadowRotCalculation();

	// 繝ｬ繧､縺ｮ諠�ｱ險ｭ螳
	CCharacter::RAY_DATA Ray_Data = { RAY_RADIUS ,RAY_HIT_RANGE ,RAY_NUM };

	// 繝ｬ繧､縺ｮ諠�ｱ險ｭ螳
	SetRay_Data(Ray_Data);

	// 邂ｱ逕滓�
	//CCharacter_Box::Create(pos, rot, this);

	return S_OK;
}

//=============================================================================
// 邨ゆｺ��逅
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Uninit(void)
{
	// 邨ゆｺ��逅
	CCharacter::Uninit();
}

//=============================================================================
// 譖ｴ譁ｰ蜃ｦ逅
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Update(void)
{
	// 隕ｪ繧ｯ繝ｩ繧ｹ縺ｮ譖ｴ譁ｰ蜃ｦ逅
	CCharacter::Update();

	// 蠎ｧ讓吩ｻ｣蜈･
	D3DXVECTOR3 pos = GetPos();

	// 蜿､縺�ｺｧ讓吩ｿ晏ｭ
	SetPosOld(pos);

	// 繝励Ξ繧､繝､繝ｼ縺ｮ迥ｶ諷
	UpdateState();

	// 菴灘鴨縺0縺ｫ縺ｪ縺｣縺溘ｉ
	if (!m_bDeath)
	{
		// 繝励Ξ繧､繝､繝ｼ縺ｮ蛻ｶ蠕｡
		PlayerControl();
	}
	else
	{
		// 豐医ｓ縺ｧ縺�￥蜃ｦ逅
		SinkEnd();
	}

	// 隗貞ｺｦ縺ｮ譖ｴ譁ｰ蜃ｦ逅
	// 移動のサウンド
	MoveSound();

	// 角度の更新処理
	UpdateRot();
}

//=============================================================================
// 謠冗判蜃ｦ逅
//=============================================================================
void CPlayer::Draw(void)
{
	// 謠冗判蜃ｦ逅
	CCharacter::Draw();
}

//=============================================================================
// Author : Sugawara Tsukasa
// 繝励Ξ繧､繝､繝ｼ縺ｮ迥ｶ諷
//=============================================================================
void CPlayer::UpdateState(void)
{

}

//=============================================================================
// 繝励Ξ繧､繝､繝ｼ縺ｮ蛻ｶ蠕｡
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::PlayerControl()
{
	// 繝｢繝ｼ繝牙叙蠕
	CManager::MODE_TYPE mode = CManager::GetMode();

	// 繧ｲ繝ｼ繝縺ｮ蝣ｴ蜷
	if (mode == CManager::MODE_TYPE_GAME)
	{
		// 繧ｲ繝ｼ繝蜿門ｾ
		CGame *pGame = (CGame*)CManager::GetModePtr();

		// !nullcheck
		if (pGame != nullptr)
		{
			// 繝懊せ驕ｷ遘ｻ蜿門ｾ
			bool bBossTransition = pGame->GetbBossTransition();

			// 繝懊せ驕ｷ遘ｻ迥ｶ諷九〒縺ｪ縺�ｴ蜷
			if (bBossTransition == false)
			{
				// false縺ｮ蝣ｴ蜷
				if (m_bKnock_Back == false)
				{
					// 1P縺ｮ蝣ｴ蜷
					if (m_PadType == PAD_TYPE_1P)
					{
						// 繝励Ξ繧､繝､繝ｼ縺ｮ遘ｻ蜍募�逅
						Move();

						// 謾ｻ謦��逅
						Attack();
					}
					// 1P縺ｮ蝣ｴ蜷
					if (m_PadType == PAD_TYPE_2P)
					{
						// 繝励Ξ繧､繝､繝ｼ縺ｮ遘ｻ蜍募�逅
						Pad2Move();

						// 謾ｻ謦��逅
						Pad2Attack();
					}

					// 繧ｭ繝ｼ繝懊�繝臥ｧｻ蜍
					KeyboardMove();

					// 謾ｻ謦��逅
					Attack();
				}
				// true縺ｮ蝣ｴ蜷
				if (m_bKnock_Back == true)
				{
					// 繝弱ャ繧ｯ繝舌ャ繧ｯ蜃ｦ逅
					Knock_Back();
				}

				// 蠖薙◆繧雁愛螳
				Collision();
			}
		}
	}
}

//=============================================================================
// 隗貞ｺｦ縺ｮ譖ｴ譁ｰ蜃ｦ逅
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::UpdateRot(void)
{
	// 隗貞ｺｦ縺ｮ蜿門ｾ
	D3DXVECTOR3 rot = GetRot();

	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// 繧ｭ繝｣繝ｩ繧ｯ繧ｿ繝ｼ蝗櫁ｻ｢縺ｮ騾溷ｺｦ
	rot += (m_rotDest - rot) * PLAYER_ROT_SPEED;

	// 隗貞ｺｦ縺ｮ險ｭ螳
	SetRot(rot);
}

//=============================================================================
// 謨ｵ縺ｮ蠑ｾ縺ｮ繝偵ャ繝亥�逅
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Hit(int nDamage)
{
	// 繝ｩ繧､繝墓ｸ帷ｮ
	GetLife() -= nDamage;

	// true縺ｫ
	m_bHitFlag = true;

	CSound *pSound = GET_SOUND_PTR;
	pSound->Play(CSound::SOUND_SE_DAMAGE);

	// 0莉･荳九□縺｣縺溘ｉ
	if (!m_bDeath && GetLife() <= 0)
	{
		// 豁ｻ縺ｬ
		Death();
	}
}

//=============================================================================
// 豁ｻ繧薙□縺ｨ縺阪�蜃ｦ逅
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Death(void)
{
	m_bDeath = true;
	SetGravityFlag(false);

	return;
}

//=============================================================================
// 遘ｻ蜍輔�蜃ｦ逅
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Move(void)
{
	DIJOYSTATE js = CInputJoypad::GetStick(PAD_P1);							// 繧ｸ繝ｧ繧､繝代ャ繝峨�蜿門ｾ
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();		// 繧ｵ繧ｦ繝ｳ繝峨�繝昴う繝ｳ繧ｿ
	D3DXVECTOR3 pos = GetPos();												// 蠎ｧ讓
	D3DXVECTOR3 rot = GetRot();												// 隗貞ｺｦ
	float fSpeed = GetSpeed();												// 繧ｹ繝斐�繝
	float fAngle_R = ZERO_FLOAT;											// 蜿ｳ隗貞ｺｦ
	float fAngle_L = ZERO_FLOAT;											// 蟾ｦ隗貞ｺｦ

	//// 蟾ｦ縺ｮ豁ｯ霆翫�諠�ｱ蜿門ｾ
	//CModelAnime *pGear_L = GetModelAnime(GEAR_L_NUM);
	//// 蜷代″蜿門ｾ
	//D3DXVECTOR3 Gear_L_rot = pGear_L->GetRot();

	//// 蜿ｳ縺ｮ豁ｯ霆翫�諠�ｱ蜿門ｾ
	//CModelAnime *pGear_R = GetModelAnime(GEAR_R_NUM);
	//// 蜷代″蜿門ｾ
	//D3DXVECTOR3 Gear_R_rot = pGear_R->GetRot();

	//===========================================
	// 蜿ｳ豁ｯ霆
	//===========================================
	// 蜿ｳ繧ｹ繝�ぅ繝�け縺悟�蜉帙＆繧後※縺�ｋ蝣ｴ蜷
	if (js.lZ != DEAD_ZONE || js.lRz != DEAD_ZONE)
	{	
		// 繧ｳ繝ｳ繝医Ο繝ｼ繝ｩ繝ｼ縺ｮ隗貞ｺｦ
		fAngle_R = atan2f((float)js.lRz, (float)js.lZ);

		//繧ｹ繝�ぅ繝�け縺ｮ譛遏ｭ霍晞屬
		RStickAngle(fAngle_R);

		// 蟾ｦ縺ｫ遘ｻ蜍
		if (fAngle_R < m_fdisAngle_R)
		{
			// 繝代ラ繝ｫ縺ｮ蝗櫁ｻ｢
			PaddleRotateR(-GEAR_SPIN_ANGLE);

			// 遘ｻ蜍
			pos.x += -sinf(rot.y)*fSpeed;
			pos.z += -cosf(rot.y)*fSpeed;

			// 蜷代″
			rot.y = rot.y - SPIN_ANGLE;

			// 逶ｮ逧��蜷代″
			m_rotDest.y = rot.y;

			//豕｢繧ｨ繝輔ぉ繧ｯ繝
			CreateWave();
		}
		// false縺ｮ蝣ｴ蜷
		else if (m_bBack == false)
		{
			// 蜿ｳ縺ｫ遘ｻ蜍
			if (fAngle_R > m_fdisAngle_R)
			{
				// 繝代ラ繝ｫ縺ｮ蝗櫁ｻ｢
				PaddleRotateR(GEAR_SPIN_ANGLE);

				// 遘ｻ蜍
				pos.x += -sinf(rot.y)*fSpeed;
				pos.z += -cosf(rot.y)*fSpeed;

				// 蜷代″
				rot.y = rot.y + SPIN_ANGLE;

				// 逶ｮ逧��蜷代″
				m_rotDest.y = rot.y;

				//豕｢繧ｨ繝輔ぉ繧ｯ繝
				CreateWave();
			}
		}
	}
	//===========================================
	// 蟾ｦ豁ｯ霆
	//===========================================
	// 蟾ｦ繧ｹ繝�ぅ繝�け縺悟�蜉帙＆繧後※縺�ｋ蝣ｴ蜷
	if (js.lX != DEAD_ZONE || js.lY != DEAD_ZONE)
	{
		// 繧ｳ繝ｳ繝医Ο繝ｼ繝ｩ繝ｼ縺ｮ隗貞ｺｦ
		fAngle_L = atan2f((float)js.lY, (float)js.lX);

		//繧ｹ繝�ぅ繝�け縺ｮ譛遏ｭ霍晞屬
		LStickAngle(fAngle_L);

		// 蜿ｳ縺ｫ遘ｻ蜍
		if (fAngle_L < m_fdisAngle_L)
		{
			// 繝代ラ繝ｫ縺ｮ蝗櫁ｻ｢
			PaddleRotateL(-GEAR_SPIN_ANGLE);

			// 遘ｻ蜍
			pos.x += -sinf(rot.y)*fSpeed;
			pos.z += -cosf(rot.y)*fSpeed;

			// 蜷代″
			rot.y = rot.y + SPIN_ANGLE;

			// 逶ｮ逧��蜷代″
			m_rotDest.y = rot.y;

			//豕｢繧ｨ繝輔ぉ繧ｯ繝
			CreateWave();
		}
		// false縺ｮ蝣ｴ蜷
		else if (m_bBack == false)
		{
			// 蟾ｦ縺ｫ遘ｻ蜍
			if (fAngle_L > m_fdisAngle_L)
			{
				// 繝代ラ繝ｫ縺ｮ蝗櫁ｻ｢
				PaddleRotateL(GEAR_SPIN_ANGLE);

				// 遘ｻ蜍
				pos.x += -sinf(rot.y)*fSpeed;
				pos.z += -cosf(rot.y)*fSpeed;

				// 蜷代″
				rot.y = rot.y - SPIN_ANGLE;

				// 逶ｮ逧��蜷代″
				m_rotDest.y = rot.y;

				//豕｢繧ｨ繝輔ぉ繧ｯ繝
				CreateWave();
			}
		}
	}
	// 蜈･蜉帙＆繧後※縺�ｋ蝣ｴ蜷
	if (js.lX != DEAD_ZONE || js.lY != DEAD_ZONE && js.lZ != DEAD_ZONE || js.lRz != DEAD_ZONE)
	{
		// 繧ｳ繝ｳ繝医Ο繝ｼ繝ｩ繝ｼ縺ｮ隗貞ｺｦ
		fAngle_L = atan2f((float)js.lY, (float)js.lX);
		fAngle_R = atan2f((float)js.lRz, (float)js.lZ);

		//繧ｹ繝�ぅ繝�け縺ｮ譛遏ｭ霍晞屬
		LStickAngle(fAngle_L);
		RStickAngle(fAngle_R);

		// 蜿ｳ繧ｹ繝�ぅ繝�け縺ｨ蟾ｦ繧ｹ繝�ぅ繝�け縺御ｸ九↓蛟偵＆繧後※縺�ｋ蝣ｴ蜷
		if (fAngle_L > m_fdisAngle_L && fAngle_R > m_fdisAngle_R)
		{
			// true縺ｫ
			m_bBack = true;
			// true縺ｮ蝣ｴ蜷
			if (m_bBack == true)
			{
				// 繝代ラ繝ｫ縺ｮ蝗櫁ｻ｢
				PaddleRotateR(GEAR_SPIN_ANGLE);
				PaddleRotateL(GEAR_SPIN_ANGLE);

				// 遘ｻ蜍
				pos.x += sinf(rot.y)*fSpeed;
				pos.z += cosf(rot.y)*fSpeed;

				m_bMoveSound = true;
			}
		}

		// 蜿ｳ繧ｹ繝�ぅ繝�け縺ｨ蟾ｦ繧ｹ繝�ぅ繝�け縺御ｸ九↓蛟偵＆繧後※縺�↑縺�ｴ蜷
		else
		{
			// false縺ｫ
			m_bBack = false;
		}
	}
	// 蜿ｳ繧ｹ繝�ぅ繝�け縺ｨ蟾ｦ繧ｹ繝�ぅ繝�け縺御ｸ九↓蛟偵＆繧後※縺�↑縺�ｴ蜷
	if (fAngle_L < m_fdisAngle_L || fAngle_R < m_fdisAngle_R)
	{
		// false縺ｫ
		m_bBack = false;
	}
	

	// 隗貞ｺｦ縺ｮ陬懈ｭ｣
	PaddleRotFix();

	// 蜷代″
	SetRot(rot);

	// 菴咲ｽｮ險ｭ螳
	SetPos(pos);

	//蜑榊屓縺ｮ繧ｹ繝�ぅ繝�け隗貞ｺｦ
	m_fdisAngle_R = fAngle_R;
	m_fdisAngle_L = fAngle_L;

}
//=============================================================================
// 2繝代ャ繝峨�遘ｻ蜍募�逅�未謨ｰ
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Pad2Move(void)
{
	// 繧ｸ繝ｧ繧､繝代ャ繝峨�蜿門ｾ
	DIJOYSTATE P1_js = CInputJoypad::GetStick(PAD_P1);
	DIJOYSTATE P2_js = CInputJoypad::GetStick(PAD_P2);
	float fAngle_R = ZERO_FLOAT;	// 蜿ｳ隗貞ｺｦ
	float fAngle_L = ZERO_FLOAT;	// 蟾ｦ隗貞ｺｦ

	// サウンドのポインタ
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	// 蠎ｧ讓
	D3DXVECTOR3 pos = GetPos();

	// 隗貞ｺｦ
	D3DXVECTOR3 rot = GetRot();

	// 繧ｹ繝斐�繝
	float fSpeed = GetSpeed();


	// 蟾ｦ縺ｮ豁ｯ霆翫�諠�ｱ蜿門ｾ
	CModelAnime *pGear_L = GetModelAnime(GEAR_L_NUM);
	// 蜷代″蜿門ｾ
	D3DXVECTOR3 Gear_L_rot = pGear_L->GetRot();

	// 蜿ｳ縺ｮ豁ｯ霆翫�諠�ｱ蜿門ｾ
	CModelAnime *pGear_R = GetModelAnime(GEAR_R_NUM);
	// 蜷代″蜿門ｾ
	D3DXVECTOR3 Gear_R_rot = pGear_R->GetRot();

	//===========================================
	// 蟾ｦ豁ｯ霆 窶ｻ1Player
	//===========================================
	// 蟾ｦ繧ｹ繝�ぅ繝�け縺悟�蜉帙＆繧後※縺�ｋ蝣ｴ蜷
	if (P1_js.lX != DEAD_ZONE || P1_js.lY != DEAD_ZONE)
	{
		// 繧ｳ繝ｳ繝医Ο繝ｼ繝ｩ繝ｼ縺ｮ隗貞ｺｦ
		fAngle_L = atan2f((float)P1_js.lY, (float)P1_js.lX);
		//繧ｹ繝�ぅ繝�け縺ｮ譛遏ｭ霍晞屬
		LStickAngle(fAngle_L);
		// 蜿ｳ縺ｫ遘ｻ蜍
		if (fAngle_L > m_fdisAngle_L)
		{
			// 蜷代″蜉邂
			Gear_L_rot.x -= GEAR_SPIN_ANGLE;

			// 蜷代″險ｭ螳
			pGear_L->SetRot(Gear_L_rot);

			// 遘ｻ蜍
			pos.x += -sinf(rot.y)*fSpeed;
			pos.z += -cosf(rot.y)*fSpeed;

			// 蜷代″
			rot.y = rot.y + SPIN_ANGLE;

			// 逶ｮ逧��蜷代″
			m_rotDest.y = rot.y;

			//豕｢繧ｨ繝輔ぉ繧ｯ繝
			CreateWave();
		}
		// false縺ｮ蝣ｴ蜷
		if (m_bBack == false)
		{
			// 蟾ｦ縺ｫ遘ｻ蜍
			if (fAngle_L < m_fdisAngle_L)
			{
				// 蜷代″蜉邂
				Gear_L_rot.x += GEAR_SPIN_ANGLE;

				// 蜷代″險ｭ螳
				pGear_L->SetRot(Gear_L_rot);

				// 遘ｻ蜍
				pos.x += -sinf(rot.y)*fSpeed;
				pos.z += -cosf(rot.y)*fSpeed;

				// 蜷代″
				rot.y = rot.y - SPIN_ANGLE;

				// 逶ｮ逧��蜷代″
				m_rotDest.y = rot.y;

				//豕｢繧ｨ繝輔ぉ繧ｯ繝
				CreateWave();
			}
		}
	}
	//===========================================
	// 蜿ｳ豁ｯ霆 窶ｻ2Player
	//===========================================
	// 蟾ｦ繧ｹ繝�ぅ繝�け縺悟�蜉帙＆繧後※縺�ｋ蝣ｴ蜷
	if (P2_js.lX != DEAD_ZONE || P2_js.lY != DEAD_ZONE)
	{
		// 繧ｳ繝ｳ繝医Ο繝ｼ繝ｩ繝ｼ縺ｮ隗貞ｺｦ
		fAngle_R = atan2f((float)P2_js.lY, (float)P2_js.lX);
		//繧ｹ繝�ぅ繝�け縺ｮ譛遏ｭ霍晞屬
		RStickAngle(fAngle_R);
		// 蟾ｦ縺ｫ遘ｻ蜍
		if (fAngle_R > m_fdisAngle_R)
		{
			// 蜷代″蜉邂
			Gear_R_rot.x -= GEAR_SPIN_ANGLE;

			// 蜷代″險ｭ螳
			pGear_R->SetRot(Gear_R_rot);

			// 遘ｻ蜍
			pos.x += -sinf(rot.y)*fSpeed;
			pos.z += -cosf(rot.y)*fSpeed;

			// 蜷代″
			rot.y = rot.y - SPIN_ANGLE;

			// 逶ｮ逧��蜷代″
			m_rotDest.y = rot.y;

			//豕｢繧ｨ繝輔ぉ繧ｯ繝
			CreateWave();
		}
		// false縺ｮ蝣ｴ蜷
		if (m_bBack == false)
		{
			// 蜿ｳ縺ｫ遘ｻ蜍
			if (fAngle_R < m_fdisAngle_R)
			{
				// 蜷代″蜉邂
				Gear_R_rot.x += GEAR_SPIN_ANGLE;

				// 蜷代″險ｭ螳
				pGear_R->SetRot(Gear_R_rot);

				// 遘ｻ蜍
				pos.x += -sinf(rot.y)*fSpeed;
				pos.z += -cosf(rot.y)*fSpeed;

				// 蜷代″
				rot.y = rot.y + SPIN_ANGLE;

				// 逶ｮ逧��蜷代″
				m_rotDest.y = rot.y;

				//豕｢繧ｨ繝輔ぉ繧ｯ繝
				CreateWave();
			}
		}


	}
	// 蜈･蜉帙＆繧後※縺�ｋ蝣ｴ蜷
	if (P1_js.lX != DEAD_ZONE || P1_js.lY != DEAD_ZONE && P2_js.lX != DEAD_ZONE || P2_js.lY != DEAD_ZONE)
	{
		// 蜿ｳ繧ｹ繝�ぅ繝�け縺ｨ蟾ｦ繧ｹ繝�ぅ繝�け縺御ｸ九↓蛟偵＆繧後※縺�ｋ蝣ｴ蜷
		if (fAngle_L < m_fdisAngle_L && fAngle_R < m_fdisAngle_R)
		{
			// 繧ｳ繝ｳ繝医Ο繝ｼ繝ｩ繝ｼ縺ｮ隗貞ｺｦ
			fAngle_L = atan2f((float)P1_js.lY, (float)P1_js.lX);
			fAngle_R = atan2f((float)P2_js.lY, (float)P2_js.lX);

			//繧ｹ繝�ぅ繝�け縺ｮ譛遏ｭ霍晞屬
			LStickAngle(fAngle_L);
			RStickAngle(fAngle_R);
			// true縺ｫ
			m_bBack = true;
			// true縺ｮ蝣ｴ蜷
			if (m_bBack == true)
			{
				// 蜷代″蜉邂
				Gear_L_rot.x += GEAR_SPIN_ANGLE;
				// 蜷代″險ｭ螳
				pGear_L->SetRot(Gear_L_rot);

				// 蜷代″蜉邂
				Gear_R_rot.x += GEAR_SPIN_ANGLE;
				// 蜷代″險ｭ螳
				pGear_R->SetRot(Gear_R_rot);

				// 遘ｻ蜍
				pos.x += sinf(rot.y)*fSpeed;
				pos.z += cosf(rot.y)*fSpeed;
			}
		}
	}
	// 蜿ｳ繧ｹ繝�ぅ繝�け縺ｨ蟾ｦ繧ｹ繝�ぅ繝�け縺御ｸ九↓蛟偵＆繧後※縺�↑縺�ｴ蜷
	if (fAngle_L < m_fdisAngle_L || fAngle_R < m_fdisAngle_R)
	{
		// false縺ｫ
		m_bBack = false;
	}
	
	// 隗貞ｺｦ縺梧怙螟ｧ縺ｫ縺ｪ縺｣縺溷ｴ蜷
	if (Gear_L_rot.x >= ANGLE_MAX || Gear_L_rot.x <= ANGLE_MIN)
	{
		// 0縺ｫ謌ｻ縺
		Gear_L_rot.x = GEAR_DEF_ROT;
		// 蜷代″險ｭ螳
		pGear_L->SetRot(Gear_L_rot);
	}

	// 隗貞ｺｦ縺梧怙螟ｧ縺ｫ縺ｪ縺｣縺溷ｴ蜷
	if (Gear_R_rot.x >= ANGLE_MAX || Gear_R_rot.x <= ANGLE_MIN)
	{
		// 0縺ｫ謌ｻ縺
		Gear_R_rot.x = GEAR_DEF_ROT;
		// 蜷代″險ｭ螳
		pGear_R->SetRot(Gear_R_rot);
	}
	// 蜷代″
	SetRot(rot);

	// 菴咲ｽｮ險ｭ螳
	SetPos(pos);

	//譬ｼ邏
	m_fdisAngle_R = fAngle_R;
	m_fdisAngle_L = fAngle_L;

}

//=============================================================================
// 謾ｻ謦��逅
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Attack(void)
{
	// 繧ｭ繝ｼ繝懊�繝牙叙蠕
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// 繧ｸ繝ｧ繧､繝代ャ繝牙叙蠕
	CInputJoypad *pJoypad = CManager::GetJoypad();

	// 繝｢繝�Ν縺ｮ諠�ｱ蜿門ｾ
	CModelAnime *pBattery_R = GetModelAnime(BATTERY_R_NUM);

	// 繝｢繝�Ν縺ｮ諠�ｱ蜿門ｾ
	CModelAnime *pBattery_L = GetModelAnime(BATTERY_L_NUM);

	// 蜷代″蜿門ｾ
	D3DXVECTOR3 rot = GetRot();

	// SPACE繧ｭ繝ｼ繧呈款縺励◆蝣ｴ蜷
	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		// 蜿ｳ蠑ｾ逕滓�
		CPlayer_Bullet::Create(BATTERY_R_POS, rot);
		// 蟾ｦ蠑ｾ逕滓�
		CPlayer_Bullet::Create(BATTERY_L_POS, rot);
	}

	// 繧ｫ繧ｦ繝ｳ繝医′0縺ｮ蝣ｴ蜷
	if (m_nAttackCount_R == ZERO_INT)
	{
		// RT繝医Μ繧ｬ繝ｼ繧呈款縺励◆蝣ｴ蜷
		if (pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, PAD_1) ||
			pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, PAD_1))
		{
			// 蜿ｳ蠑ｾ逕滓�
			CPlayer_Bullet::Create(BATTERY_R_POS, rot);

			// 繧､繝ｳ繧ｯ繝ｪ繝｡繝ｳ繝
			m_nAttackCount_R++;
		}
	}
	// 繧ｫ繧ｦ繝ｳ繝医′0縺ｮ蝣ｴ蜷
	if (m_nAttackCount_L == ZERO_INT)
	{
		// LT繝医Μ繧ｬ繝ｼ繧呈款縺励◆蝣ｴ蜷
		if (pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L2_TRIGGER, PAD_1) ||
			pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L_TRIGGER, PAD_1))
		{
			// 蟾ｦ蠑ｾ逕滓�
			CPlayer_Bullet::Create(BATTERY_L_POS, rot);

			// 繧､繝ｳ繧ｯ繝ｪ繝｡繝ｳ繝
			m_nAttackCount_L++;
		}
	}
	// 繧ｫ繧ｦ繝ｳ繝医′0繧医ｊ螟壹＞蝣ｴ蜷
	if (m_nAttackCount_R > ZERO_INT)
	{
		// 繧､繝ｳ繧ｯ繝ｪ繝｡繝ｳ繝
		m_nAttackCount_R++;

		// 繧ｫ繧ｦ繝ｳ繝医′60縺ｮ蝣ｴ蜷
		if (m_nAttackCount_R >= ATTACK_COOLTIME)
		{
			// 0縺ｫ
			m_nAttackCount_R = ZERO_INT;
		}
	}
	// 繧ｫ繧ｦ繝ｳ繝医′0繧医ｊ螟壹＞蝣ｴ蜷
	if (m_nAttackCount_L > ZERO_INT)
	{
		// 繧､繝ｳ繧ｯ繝ｪ繝｡繝ｳ繝
		m_nAttackCount_L++;

		// 繧ｫ繧ｦ繝ｳ繝医′60縺ｮ蝣ｴ蜷
		if (m_nAttackCount_L >= ATTACK_COOLTIME)
		{
			// 0縺ｫ
			m_nAttackCount_L = ZERO_INT;
		}
	}
}
//=============================================================================
// 2繧ｳ繝ｳ繝医Ο繝ｼ繝ｩ繝ｼ縺ｮ謾ｻ謦��逅
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Pad2Attack(void)
{
	// 繧ｸ繝ｧ繧､繝代ャ繝牙叙蠕
	CInputJoypad *pJoypad = CManager::GetJoypad();

	// 繝｢繝�Ν縺ｮ諠�ｱ蜿門ｾ
	CModelAnime *pBattery_R = GetModelAnime(BATTERY_R_NUM);

	// 繝｢繝�Ν縺ｮ諠�ｱ蜿門ｾ
	CModelAnime *pBattery_L = GetModelAnime(BATTERY_L_NUM);

	// 蜷代″蜿門ｾ
	D3DXVECTOR3 rot = GetRot();

	// 繧ｫ繧ｦ繝ｳ繝医′0縺ｮ蝣ｴ蜷
	if (m_nAttackCount_L == ZERO_INT)
	{
		// LT繝医Μ繧ｬ繝ｼ繧呈款縺励◆蝣ｴ蜷
		if (pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, PAD_1) ||
			pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, PAD_1))
		{
			// 蟾ｦ蠑ｾ逕滓�
			CPlayer_Bullet::Create(BATTERY_L_POS, rot);

			// 繧､繝ｳ繧ｯ繝ｪ繝｡繝ｳ繝
			m_nAttackCount_L++;
		}
	}
	// 繧ｫ繧ｦ繝ｳ繝医′0繧医ｊ螟壹＞蝣ｴ蜷
	if (m_nAttackCount_L > ZERO_INT)
	{
		// 繧､繝ｳ繧ｯ繝ｪ繝｡繝ｳ繝
		m_nAttackCount_L++;

		// 繧ｫ繧ｦ繝ｳ繝医′60縺ｮ蝣ｴ蜷
		if (m_nAttackCount_L >= ATTACK_COOLTIME)
		{
			// 0縺ｫ
			m_nAttackCount_L = ZERO_INT;
		}
	}
	// 繧ｫ繧ｦ繝ｳ繝医′0縺ｮ蝣ｴ蜷
	if (m_nAttackCount_R == ZERO_INT)
	{
		// RT繝医Μ繧ｬ繝ｼ繧呈款縺励◆蝣ｴ蜷
		if (pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, PAD_2) ||
			pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, PAD_2))
		{
			// 蜿ｳ蠑ｾ逕滓�
			CPlayer_Bullet::Create(BATTERY_R_POS, rot);

			// 繧､繝ｳ繧ｯ繝ｪ繝｡繝ｳ繝
			m_nAttackCount_R++;
		}
	}
	// 繧ｫ繧ｦ繝ｳ繝医′0繧医ｊ螟壹＞蝣ｴ蜷
	if (m_nAttackCount_R > ZERO_INT)
	{
		// 繧､繝ｳ繧ｯ繝ｪ繝｡繝ｳ繝
		m_nAttackCount_R++;

		// 繧ｫ繧ｦ繝ｳ繝医′60縺ｮ蝣ｴ蜷
		if (m_nAttackCount_R >= ATTACK_COOLTIME)
		{
			// 0縺ｫ
			m_nAttackCount_R = ZERO_INT;
		}
	}
}
//=============================================================================
// 繧ｭ繝ｼ繝懊�繝臥ｧｻ蜍募�逅
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::KeyboardMove(void)
{
	// 繧ｭ繝ｼ繝懊�繝画峩譁ｰ
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// 蟾ｦ縺ｮ豁ｯ霆翫�諠�ｱ蜿門ｾ
	CModelAnime *pGear_L = GetModelAnime(GEAR_L_NUM);
	// 蜷代″蜿門ｾ
	D3DXVECTOR3 Gear_L_rot = pGear_L->GetRot();

	// 蜿ｳ縺ｮ豁ｯ霆翫�諠�ｱ蜿門ｾ
	CModelAnime *pGear_R = GetModelAnime(GEAR_R_NUM);
	// 蜷代″蜿門ｾ
	D3DXVECTOR3 Gear_R_rot = pGear_R->GetRot();

	// 蠎ｧ讓
	D3DXVECTOR3 pos = GetPos();

	// 隗貞ｺｦ
	D3DXVECTOR3 rot = GetRot();

	// 繧ｹ繝斐�繝
	float fSpeed = GetSpeed();

	// 蜿ｳ隗貞ｺｦ
	float fAngle_R = ZERO_FLOAT;

	// 蟾ｦ隗貞ｺｦ
	float fAngle_L = ZERO_FLOAT;

	// S縺梧款縺輔ｌ縺ｦ縺�↑蝣ｴ蜷
	if (!pKeyboard->GetPress(DIK_S))
	{
		// 蜿ｳ縺ｫ遘ｻ蜍
		if (pKeyboard->GetPress(DIK_W))
		{
			// 蜷代″蜉邂
			Gear_L_rot.x -= GEAR_SPIN_ANGLE;

			// 蜷代″險ｭ螳
			pGear_L->SetRot(Gear_L_rot);

			// 遘ｻ蜍
			pos.x += -sinf(rot.y)*fSpeed;
			pos.z += -cosf(rot.y)*fSpeed;

			// 蜷代″
			rot.y = rot.y + SPIN_ANGLE;

			// 逶ｮ逧��蜷代″
			m_rotDest.y = rot.y;

			//繧ｨ繝輔ぉ繧ｯ繝
			CreateWave();

			// false縺ｫ
			m_bBack = false;
			m_bMoveSound = true;
		}
	}
	// false縺ｮ蝣ｴ蜷
	if (m_bBack == false)
	{
		// W縺梧款縺輔ｌ縺ｦ縺�↑縺�ｴ蜷
		if (!pKeyboard->GetPress(DIK_W))
		{
			// 蟾ｦ縺ｫ遘ｻ蜍
			if (pKeyboard->GetPress(DIK_S))
			{
				// 蜷代″蜉邂
				Gear_L_rot.x += GEAR_SPIN_ANGLE;

				// 蜷代″險ｭ螳
				pGear_L->SetRot(Gear_L_rot);

				// 遘ｻ蜍
				pos.x += -sinf(rot.y)*fSpeed;
				pos.z += -cosf(rot.y)*fSpeed;

				// 蜷代″
				rot.y = rot.y - SPIN_ANGLE;

				// 逶ｮ逧��蜷代″
				m_rotDest.y = rot.y;

				m_bMoveSound = true;
			}
		}
	}
	// 竊薙′謚ｼ縺輔ｌ縺ｦ縺�↑縺�ｴ蜷
	if (!pKeyboard->GetPress(DIK_DOWN))
	{
		// 蜿ｳ縺ｫ遘ｻ蜍
		if (pKeyboard->GetPress(DIK_UP))
		{
			// 蜷代″蜉邂
			Gear_R_rot.x -= GEAR_SPIN_ANGLE;

			// 蜷代″險ｭ螳
			pGear_R->SetRot(Gear_R_rot);

			// 遘ｻ蜍
			pos.x += -sinf(rot.y)*fSpeed;
			pos.z += -cosf(rot.y)*fSpeed;

			// 蜷代″
			rot.y = rot.y - SPIN_ANGLE;

			// 逶ｮ逧��蜷代″
			m_rotDest.y = rot.y;

			//繧ｨ繝輔ぉ繧ｯ繝
			CreateWave();

			// false縺ｫ
			m_bBack = false;

			m_bMoveSound = true;
		}
	}
	// false縺ｮ蝣ｴ蜷
	if (m_bBack == false)
	{
		// 竊代′謚ｼ縺輔ｌ縺ｦ縺�↑縺�ｴ蜷
		if (!pKeyboard->GetPress(DIK_UP))
		{
			// 蟾ｦ縺ｫ遘ｻ蜍
			if (pKeyboard->GetPress(DIK_DOWN))
			{
				// 蜷代″蜉邂
				Gear_R_rot.x += GEAR_SPIN_ANGLE;

				// 蜷代″險ｭ螳
				pGear_R->SetRot(Gear_R_rot);

				// 遘ｻ蜍
				pos.x += -sinf(rot.y)*fSpeed;
				pos.z += -cosf(rot.y)*fSpeed;

				// 蜷代″
				rot.y = rot.y + SPIN_ANGLE;

				// 逶ｮ逧��蜷代″
				m_rotDest.y = rot.y;

				m_bMoveSound = true;
			}
		}
	}
	// 蠕後ｍ遘ｻ蜍
	if (pKeyboard->GetPress(DIK_DOWN) && pKeyboard->GetPress(DIK_S))
	{
		// true縺ｫ
		m_bBack = true;

		// true縺ｮ蝣ｴ蜷
		if (m_bBack == true)
		{
			// 蜷代″蜉邂
			Gear_L_rot.x += GEAR_SPIN_ANGLE;
			// 蜷代″險ｭ螳
			pGear_L->SetRot(Gear_L_rot);

			// 蜷代″蜉邂
			Gear_R_rot.x += GEAR_SPIN_ANGLE;
			// 蜷代″險ｭ螳
			pGear_R->SetRot(Gear_R_rot);

			// 遘ｻ蜍
			pos.x += sinf(rot.y)*fSpeed;
			pos.z += cosf(rot.y)*fSpeed;

			m_bMoveSound = true;
		}
	}
	// 蠕後ｍ遘ｻ蜍
	if (pKeyboard->GetRelease(DIK_DOWN) || pKeyboard->GetRelease(DIK_S))
	{
		// true縺ｮ蝣ｴ蜷
		if (m_bBack == true)
		{
			// false縺ｫ
			m_bBack = false;

			m_bMoveSound = true;
		}
	}

	if (pKeyboard->GetPress(DIK_P))
	{
		//繝代�繝�ぅ繧ｯ繝ｫ逕滓�
		CreateSmoke();
		CreateWoodEP();
		CreateExplosion();
	}

	// 隗貞ｺｦ縺梧怙螟ｧ縺ｫ縺ｪ縺｣縺溷ｴ蜷
	if (Gear_L_rot.x >= ANGLE_MAX || Gear_L_rot.x <= ANGLE_MIN)
	{
		// 0縺ｫ謌ｻ縺
		Gear_L_rot.x = GEAR_DEF_ROT;
		// 蜷代″險ｭ螳
		pGear_L->SetRot(Gear_L_rot);
	}

	// 隗貞ｺｦ縺梧怙螟ｧ縺ｫ縺ｪ縺｣縺溷ｴ蜷
	if (Gear_R_rot.x >= ANGLE_MAX || Gear_R_rot.x <= ANGLE_MIN)
	{
		// 0縺ｫ謌ｻ縺
		Gear_R_rot.x = GEAR_DEF_ROT;
		// 蜷代″險ｭ螳
		pGear_R->SetRot(Gear_R_rot);
	}
	// 蜷代″
	SetRot(rot);

	// 菴咲ｽｮ險ｭ螳
	SetPos(pos);
}
//=============================================================================
// 蠖薙◆繧雁愛螳壼�逅
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Collision(void)
{
	// CScene縺ｮ繝昴う繝ｳ繧ｿ
	CScene *pScene = nullptr;

	// 繝｢繝�Ν縺ｮ諠�ｱ蜿門ｾ
	CModelAnime *pAnime = GetModelAnime(SHIP_NUM);

	// 菴咲ｽｮ蜿門ｾ
	D3DXVECTOR3 pos = D3DXVECTOR3(pAnime->GetMtxWorld()._41, pAnime->GetMtxWorld()._42, pAnime->GetMtxWorld()._43);

	// 菴咲ｽｮ蜿門ｾ
	D3DXVECTOR3 posOld = D3DXVECTOR3(pAnime->GetOldMtxWorld()._41, pAnime->GetOldMtxWorld()._42, pAnime->GetOldMtxWorld()._43);

	// 繧ｵ繧､繧ｺ蜿門ｾ
	D3DXVECTOR3 size = GetSize();

	// 遘ｻ蜍暮㍼蜿門ｾ
	D3DXVECTOR3 move = GetMove();

	// nullcheck
	if (pScene == nullptr)
	{
		// 蜈磯ｭ縺ｮ繝昴う繝ｳ繧ｿ蜿門ｾ
		pScene = GetTop(PRIORITY_ENEMY);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcter縺ｨ縺ｮ蠖薙◆繧雁愛螳
			while (pScene != nullptr) // nullptr縺ｫ縺ｪ繧九∪縺ｧ蝗槭☆
			{
				// 迴ｾ蝨ｨ縺ｮ繝昴う繝ｳ繧ｿ
				CScene *pSceneCur = pScene->GetNext();

				// 菴咲ｽｮ
				D3DXVECTOR3 CharacterPos = ZeroVector3;

				// 菴咲ｽｮ蜿門ｾ
				CharacterPos.x = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._41;
				CharacterPos.y = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._42;
				CharacterPos.z = ((CCharacter*)pScene)->GetModelAnime(PARENT_NUM)->GetMtxWorld()._43;

				// 繧ｵ繧､繧ｺ蜿門ｾ
				D3DXVECTOR3 CharacterSize = ((CCharacter*)pScene)->GetSize();

				//縺ｩ縺薙�髱｢縺ｫ蠖薙◆縺｣縺溘°蜿門ｾ
				//荳
				if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_DOWN)
				{
					// 遘ｻ蜍暮㍼蜿門ｾ
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 遘ｻ蜍暮㍼0
					CharacterMove.y = MIN_MOVE.y;

					// 遘ｻ蜍暮㍼險ｭ螳
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// 菴咲ｽｮ
					pos.y = (-CharacterSize.y / DIVIDE_2 + CharacterPos.y) - (size.y / DIVIDE_2);

					// 菴咲ｽｮ險ｭ螳
					SetPos(pos);

					CSound *pSound = GET_SOUND_PTR;
					pSound->Play(CSound::SOUND_SE_HIT);
				}
				// 荳
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_UP)
				{
					// 遘ｻ蜍暮㍼蜿門ｾ
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 遘ｻ蜍暮㍼0
					CharacterMove.y = MIN_MOVE.y;

					// 遘ｻ蜍暮㍼險ｭ螳
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// 菴咲ｽｮ
					pos.y = (CharacterSize.y / DIVIDE_2 + CharacterPos.y) + (size.y / DIVIDE_2);

					// 菴咲ｽｮ險ｭ螳
					SetPos(pos);

					CSound *pSound = GET_SOUND_PTR;
					pSound->Play(CSound::SOUND_SE_HIT);
				}
				// 蟾ｦ
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_LEFT)
				{
					// 遘ｻ蜍暮㍼蜿門ｾ
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 遘ｻ蜍暮㍼0
					CharacterMove.x = MIN_MOVE.x;

					// 遘ｻ蜍暮㍼險ｭ螳
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// 菴咲ｽｮ
					pos.x = (-CharacterSize.x / DIVIDE_2 + CharacterPos.x) - (size.x / DIVIDE_2);

					// 菴咲ｽｮ險ｭ螳
					SetPos(pos);

					CSound *pSound = GET_SOUND_PTR;
					pSound->Play(CSound::SOUND_SE_HIT);
				}
				// 蜿ｳ
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_RIGHT)
				{
					// 遘ｻ蜍暮㍼蜿門ｾ
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 遘ｻ蜍暮㍼0
					CharacterMove.x = MIN_MOVE.x;

					// 遘ｻ蜍暮㍼險ｭ螳
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// 菴咲ｽｮ
					pos.x = (CharacterSize.x / DIVIDE_2 + CharacterPos.x) + (size.x / DIVIDE_2);

					// 菴咲ｽｮ險ｭ螳
					SetPos(pos);

					CSound *pSound = GET_SOUND_PTR;
					pSound->Play(CSound::SOUND_SE_HIT);
				}
				// 謇句燕
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_PREVIOUS)
				{
					// 遘ｻ蜍暮㍼蜿門ｾ
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 遘ｻ蜍暮㍼0
					CharacterMove.z = MIN_MOVE.z;

					// 遘ｻ蜍暮㍼險ｭ螳
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// 菴咲ｽｮ
					pos.z = (-CharacterSize.z / DIVIDE_2 + CharacterPos.z) - (size.z / DIVIDE_2);

					// 菴咲ｽｮ險ｭ螳
					SetPos(pos);

					CSound *pSound = GET_SOUND_PTR;
					pSound->Play(CSound::SOUND_SE_HIT);
				}
				// 螂･
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, CharacterPos, size, CharacterSize) == CCollision::SURFACE_BACK)
				{
					// 遘ｻ蜍暮㍼蜿門ｾ
					D3DXVECTOR3 CharacterMove = ((CCharacter*)pScene)->GetMove();

					// 遘ｻ蜍暮㍼0
					CharacterMove.z = MIN_MOVE.z;

					// 菴咲ｽｮ
					pos.z = (CharacterSize.z / DIVIDE_2 + CharacterPos.z) + (size.z / DIVIDE_2);

					// 遘ｻ蜍暮㍼險ｭ螳
					((CCharacter*)pScene)->SetMove(CharacterMove);

					// 菴咲ｽｮ險ｭ螳
					SetPos(pos);

					CSound *pSound = GET_SOUND_PTR;
					pSound->Play(CSound::SOUND_SE_HIT);
				}
				// 谺｡縺ｮ繝昴う繝ｳ繧ｿ蜿門ｾ
				pScene = pSceneCur;
			}
		}

		// 蜈磯ｭ縺ｮ繝昴う繝ｳ繧ｿ蜿門ｾ
		pScene = GetTop(PRIORITY_OBSTACLE);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcter縺ｨ縺ｮ蠖薙◆繧雁愛螳
			while (pScene != nullptr) // nullptr縺ｫ縺ｪ繧九∪縺ｧ蝗槭☆
			{
				// 迴ｾ蝨ｨ縺ｮ繝昴う繝ｳ繧ｿ
				CScene *pSceneCur = pScene->GetNext();

				// 菴咲ｽｮ
				D3DXVECTOR3 ObstaclePos = ((CModel*)pScene)->GetPos();

				// 繧ｵ繧､繧ｺ蜿門ｾ
				D3DXVECTOR3 ObstacleSize = ((CModel*)pScene)->GetSize();

				// 遏ｩ蠖｢縺ｮ蠖薙◆繧雁愛螳
				if (CCollision::CollisionRectangleAndRectangle(ObstaclePos, pos, ObstacleSize, size) == true)
				{
					// 繝吶け繝医Ν
					D3DXVECTOR3 Vec = ZeroVector3;

					// 豕慕ｷ壹�繧ｯ繝医Ν
					D3DXVECTOR3 NormalVec = ZeroVector3;

					// 騾ｲ陦後�繧ｯ繝医Ν
					Vec.x = ObstaclePos.x - pos.x;
					Vec.z = ObstaclePos.z - pos.z;

					// 髟ｷ縺慕ｮ怜�
					float fVec_Length = sqrtf((Vec.x * Vec.x) + (Vec.z * Vec.z));

					// 豕慕ｷ壹�繧ｯ繝医Ν縺ｫ
					NormalVec.x = Vec.x / fVec_Length;
					NormalVec.z = Vec.z / fVec_Length;

					// 蜿榊ｰ��繧ｯ繝医Ν邂怜�
					D3DXVec3Normalize(&m_Reflection_Vec, &(Vec - 2.0f * D3DXVec3Dot(&Vec, &NormalVec) * NormalVec));

					// true縺ｫ
					m_bKnock_Back = true;

					CSound *pSound = GET_SOUND_PTR;
					pSound->Play(CSound::SOUND_SE_HIT);
				}

				// 谺｡縺ｮ繝昴う繝ｳ繧ｿ蜿門ｾ
				pScene = pSceneCur;
			}
		}
	}
}
//=============================================================================
// 螟也ｩ阪�蠖薙◆繧雁愛螳壼�逅
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::CrossCollision(void)
{
	// CScene縺ｮ繝昴う繝ｳ繧ｿ
	CScene *pScene = nullptr;

	// 繝｢繝�Ν縺ｮ諠�ｱ蜿門ｾ
	CModelAnime *pAnime = GetModelAnime(SHIP_NUM);

	// 菴咲ｽｮ蜿門ｾ
	D3DXVECTOR3 pos = D3DXVECTOR3(pAnime->GetMtxWorld()._41, pAnime->GetMtxWorld()._42, pAnime->GetMtxWorld()._43);

	// 菴咲ｽｮ蜿門ｾ
	D3DXVECTOR3 posOld = D3DXVECTOR3(pAnime->GetOldMtxWorld()._41, pAnime->GetOldMtxWorld()._42, pAnime->GetOldMtxWorld()._43);

	// 繧ｵ繧､繧ｺ蜿門ｾ
	D3DXVECTOR3 size = GetSize();

	// 遘ｻ蜍暮㍼蜿門ｾ
	D3DXVECTOR3 move = GetMove();

	// nullcheck
	if (pScene == nullptr)
	{
		// 蜈磯ｭ縺ｮ繝昴う繝ｳ繧ｿ蜿門ｾ
		pScene = GetTop(PRIORITY_ENEMY);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Charcter縺ｨ縺ｮ蠖薙◆繧雁愛螳
			while (pScene != nullptr) // nullptr縺ｫ縺ｪ繧九∪縺ｧ蝗槭☆
			{
				// 迴ｾ蝨ｨ縺ｮ繝昴う繝ｳ繧ｿ
				CScene *pSceneCur = pScene->GetNext();

				// 繝代�繝�焚蜿門ｾ
				int nParts = ((CCharacter*)pScene)->GetPartsNum();

				// 繝代�繝�焚蛻�ｹｰ繧願ｿ斐☆
				for (int nCnt = ZERO_INT; nCnt < nParts; nCnt++)
				{
					// 繝｡繝�す繝･蜿門ｾ
					LPD3DXMESH mesh = ((CCharacter*)pScene)->GetModelAnime(nCnt)->GetMesh();

					// 繝輔ぉ繝ｼ繧ｹ謨ｰ蜿門ｾ
					DWORD FaceNum = mesh->GetNumFaces();
				}
				// 谺｡縺ｮ繝昴う繝ｳ繧ｿ蜿門ｾ
				pScene = pSceneCur;
			}
		}
	}
}

//=======================================================================================
// 豐医�蜃ｦ逅
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
// 移動の音
// Author : Konishi Yuuto
//=======================================================================================
void CPlayer::MoveSound(void)
{
	// 移動したとき
	if (m_bMoveSound)
	{
		// 一定の間隔で
		if (m_nSoundCounter >= SOUND_INTER_TIME)
		{
			// 音を鳴らす
			CSound *pSound = GET_SOUND_PTR;
			pSound->Play(CSound::SOUND_SE_MOVE);

			m_nSoundCounter = 0;
		}

		m_nSoundCounter++;
		m_bMoveSound = false;
	}
}

//=======================================================================================
// 辣咏函謌宣未謨ｰ
// Author : Oguma Akira
//=======================================================================================
void CPlayer::CreateSmoke(void)
{
	// 繝代�繝�ぅ繧ｯ繝ｫ逕滓�
	CEffect::Create(SMOKE_POS, SMOKE_SIZE, SMOKE_MOVE, SMOKE_COLOR,
		CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_1), SMOKE_LIFE);
}

//=======================================================================================
// 譛ｨ譚千�遐ｴ逕滓�髢｢謨ｰ
// Author : Oguma Akira
//=======================================================================================
void CPlayer::CreateWoodEP(void)
{
	// 繝代�繝�ぅ繧ｯ繝ｫ逕滓�
	CEffect::Create(WOOD_POS,
		WOOD_SIZE, WOOD_MOVE, WOOD_COLOR,
		CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_5), WOOD_LIFE);
}

//=======================================================================================
// 豌ｴ縺励�縺咲函謌宣未謨ｰ
// Author : Oguma Akira
//=======================================================================================
void CPlayer::CreateSplash(void)
{
	for (int nCntEffect = 0; nCntEffect < 10; nCntEffect++)
	{
		// 繝代�繝�ぅ繧ｯ繝ｫ逕滓�
		CEffect::Create(SPLASH_POS,
			WOOD_SIZE, SPLASH_MOVE, SPLASH_COLOR,
			CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_4), SPLASH_LIFE);
	}
}

//=======================================================================================
// 辷�匱逕滓�髢｢謨ｰ
// Author : Oguma Akira
//=======================================================================================
void CPlayer::CreateExplosion(void)
{
	// 繝代�繝�ぅ繧ｯ繝ｫ逕滓�
	CEffect::Create(EXPLOSION_POS, EXPLOSION_SIZE, ZeroVector3, EXPLOSION_COLOR,
		CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_2), EXPLOSION_LIFE);

}

//=======================================================================================
// 豕｢逕滓�髢｢謨ｰ
// Author : Oguma Akira
//=======================================================================================
void CPlayer::CreateWave(void)
{
	for (int nCntEffect = 0; nCntEffect < WAVE_MAX_PARTICLE; nCntEffect++)
	{
		// 繝代�繝�ぅ繧ｯ繝ｫ逕滓�
		CEffect::Create(WAVE_POS, WAVE_SIZE, WAVE_MOVE, WAVE_COLOR,
			CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_3), WAVE_LIFE);
	}
}

//=============================================================================
// 繝弱ャ繧ｯ繝舌ャ繧ｯ蜃ｦ逅�未謨ｰ
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Knock_Back(void)
{
	// 繧ｫ繧ｦ繝ｳ繝医う繝ｳ繧ｯ繝ｪ繝｡繝ｳ繝
	m_nRockHitCount++;

	// 遘ｻ蜍暮㍼蜿門ｾ
	D3DXVECTOR3 move = GetMove();

	// 0縺ｮ蝣ｴ蜷
	if (m_nRockHitCount <= KNOCK_BACK_COUNT)
	{
		// 遘ｻ蜍暮㍼
		move.x = m_Reflection_Vec.x *KNOCK_BACK_SPEED;
		move.z = m_Reflection_Vec.z *KNOCK_BACK_SPEED;

		// 遘ｻ蜍暮㍼險ｭ螳
		SetMove(move);
	}
	// 10繧医ｊ螟ｧ縺阪＞蝣ｴ蜷
	if (m_nRockHitCount > KNOCK_BACK_COUNT)
	{
		// 遘ｻ蜍暮㍼險ｭ螳
		SetMove(ZeroVector3);

		// 0縺ｫ謌ｻ縺
		m_nRockHitCount = ZERO_INT;

		// false縺ｫ
		m_bKnock_Back = false;
	}
}

//=============================================================================
// 繝代ラ繝ｫ縺ｮ蜿ｳ蝗櫁ｻ｢
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::PaddleRotateR(float fRotate)
{
	// 蜿ｳ縺ｮ豁ｯ霆翫�諠�ｱ蜿門ｾ
	CModelAnime *pGear_R = GetModelAnime(GEAR_R_NUM);
	// 蜷代″蜿門ｾ
	D3DXVECTOR3 Gear_R_rot = pGear_R->GetRot();

	// 隗貞ｺｦ蜉邂
	Gear_R_rot.x += fRotate;

	// 蜷代″險ｭ螳
	pGear_R->SetRot(Gear_R_rot);
}

//=============================================================================
// 繝代ラ繝ｫ縺ｮ蟾ｦ蝗櫁ｻ｢
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::PaddleRotateL(float fRotate)
{
	// 蟾ｦ縺ｮ豁ｯ霆翫�諠�ｱ蜿門ｾ
	CModelAnime *pGear_L = GetModelAnime(GEAR_L_NUM);
	// 蜷代″蜿門ｾ
	D3DXVECTOR3 Gear_L_rot = pGear_L->GetRot();

	// 隗貞ｺｦ蜉邂
	Gear_L_rot.x += fRotate;

	// 蜷代″險ｭ螳
	pGear_L->SetRot(Gear_L_rot);
}

//=============================================================================
// 繝代ラ繝ｫ縺ｮ隗貞ｺｦ菫ｮ豁｣
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::PaddleRotFix(void)
{
	// 蜿ｳ縺ｮ豁ｯ霆翫�諠�ｱ蜿門ｾ
	CModelAnime *pGear_R = GetModelAnime(GEAR_R_NUM);
	// 蜷代″蜿門ｾ
	D3DXVECTOR3 Gear_R_rot = pGear_R->GetRot();
	// 蟾ｦ縺ｮ豁ｯ霆翫�諠�ｱ蜿門ｾ
	CModelAnime *pGear_L = GetModelAnime(GEAR_L_NUM);
	// 蜷代″蜿門ｾ
	D3DXVECTOR3 Gear_L_rot = pGear_L->GetRot();

	// 隗貞ｺｦ縺梧怙螟ｧ縺ｫ縺ｪ縺｣縺溷ｴ蜷
	if (Gear_L_rot.x >= ANGLE_MAX || Gear_L_rot.x <= ANGLE_MIN)
	{
		// 0縺ｫ謌ｻ縺
		Gear_L_rot.x = GEAR_DEF_ROT;
		// 蜷代″險ｭ螳
		pGear_L->SetRot(Gear_L_rot);
	}

	// 隗貞ｺｦ縺梧怙螟ｧ縺ｫ縺ｪ縺｣縺溷ｴ蜷
	if (Gear_R_rot.x >= ANGLE_MAX || Gear_R_rot.x <= ANGLE_MIN)
	{
		// 0縺ｫ謌ｻ縺
		Gear_R_rot.x = GEAR_DEF_ROT;
		// 蜷代″險ｭ螳
		pGear_R->SetRot(Gear_R_rot);
	}
}

//=============================================================================
// L繧ｹ繝�ぅ繝�け縺ｮ譛遏ｭ隗貞ｺｦ霍晞屬
// Author : Oguma Akira
//=============================================================================
void CPlayer::LStickAngle(float fangle_L)
{
	if (m_fdisAngle_L - fangle_L > D3DXToRadian(180))
	{
		m_fdisAngle_L -= D3DXToRadian(360);
	}
	else if (m_fdisAngle_L - fangle_L < D3DXToRadian(-180))
	{
		m_fdisAngle_L += D3DXToRadian(360);
	}
}

//=============================================================================
// R繧ｹ繝�ぅ繝�け縺ｮ譛遏ｭ隗貞ｺｦ霍晞屬
// Author : Oguma Akira
//=============================================================================
void CPlayer::RStickAngle(float fangle_R)
{
	if (m_fdisAngle_R - fangle_R > D3DXToRadian(180))
	{
		m_fdisAngle_R -= D3DXToRadian(360);
	}
	else if (m_fdisAngle_R - fangle_R < D3DXToRadian(-180))
	{
		m_fdisAngle_R += D3DXToRadian(360);
	}
}

//=============================================================================
// 譛ｬ菴薙�繝昴う繝ｳ繧ｿ
// Author : Konishi Yuuto
//=============================================================================
CModelAnime * CPlayer::GetShip(void)
{
	return GetModelAnime(SHIP_NUM);
}

//=============================================================================
// 蜿ｳ縺ｮ霆願ｼｪ縺ｮ繝昴う繝ｳ繧ｿ
// Author : Konishi Yuuto
//=============================================================================
CModelAnime * CPlayer::GetRightPaddle(void)
{
	return GetModelAnime(GEAR_R_NUM);
}

//=============================================================================
// 蟾ｦ縺ｮ霆願ｼｪ縺ｮ繝昴う繝ｳ繧ｿ
// Author : Konishi Yuuto
//=============================================================================
CModelAnime * CPlayer::GetLeftPaddle(void)
{
	return GetModelAnime(GEAR_L_NUM);
}
