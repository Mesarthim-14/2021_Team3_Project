//=======================================================================================
//
// ゲーム処理 [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "game.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "meshfield.h"
#include "joypad.h"
#include "time.h"
#include "sound.h"
#include "keyboard.h"
#include "enemy.h"
#include "enemy_ship.h"
#include "mesh_3d.h"
#include "resource_manager.h"
#include "enemy_scaffolding.h"
#include "torpedo.h"
#include "rock.h"
#include "map.h"
#include "boss_shark.h"
#include "library.h"
#include "debug_proc.h"
#include "rock.h"
#include "water.h"
#include "camera_game.h"
#include "collision.h"
#include "player_life.h"
#include "fade.h"
#include "boss_fade.h"
#include "rotate_ui.h"
#include "attack_ui.h"
#include "boss_map_transition.h"
//=======================================================================================
// マクロ定義
//=======================================================================================
#define ENEMY_OBSTACLE_CREATE_TEXT	("data/Text/Enemy/Enemy_Obstacle_Create.txt")	// 敵生成テキスト
#define BOSS_ENEMY_CREATE_TEXT		("data/Text/Enemy/boss_enemy.txt")				// 敵生成テキスト
#define ENEMY_POS					(D3DXVECTOR3(0.0f,800.0f,-3000.0f))				// 敵の位置
#define BOSS_POS					(D3DXVECTOR3(500.0f,0.0f,-17000.0f))			// ボスの位置
#define BOSS_ROT					(D3DXVECTOR3(0.0f,D3DXToRadian(0.0f),0.0f))		// ボスの位置
#define ENEMY_POS_2					(D3DXVECTOR3(5000.0f,500.0f,0.0f))				// 敵の位置
#define ENEMY_ROT					(D3DXVECTOR3(0.0f,D3DXToRadian(180.0f),0.0f))	// 敵の向き
#define PLAYER_POS					(D3DXVECTOR3(1500.0f,0.0f,-500.0f))				// プレイヤーの位置
#define BOSS_PLAYER_POS				(D3DXVECTOR3(0.0f,0.0f,0.0f))					// プレイヤーの位置
#define SIZE						(D3DXVECTOR3(2000.0f,1000.0f,0.0f))				// サイズ
#define PLAYER_ROT					(D3DXVECTOR3(0.0f,D3DXToRadian(270.0f),0.0f))	// プレイヤーの向き
#define BOSS_PLAYER_ROT				(D3DXVECTOR3(0.0f,D3DXToRadian(0.0f),0.0f))		// プレイヤーの向き
#define LIFE_POS					(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200.0f,0.0f))
#define BOSS_TRANSITION_POS			(D3DXVECTOR3(78000.0f,0.0f,-52000.0f))				// ボス戦遷移判定位置
#define BOSS_TARNSITION_SIZE		(D3DXVECTOR3(10000.0f,0.0f,5000.0f))				// ボス遷移判定サイズ
#define BOSS_TRT_POS				(D3DXVECTOR3(78000.0f,0.0f,-52000.0f))
#define BOSS_MAP_TRT_MAP_POS		(D3DXVECTOR3(80000.0f,0.0f,-105000.0f))
#define BOSS_MAP_TRT_MAP_ROT		(D3DXVECTOR3(0.0f,D3DXToRadian(175.0f),0.0f))
//=======================================================================================
// コンストラクタ
//=======================================================================================
CGame::CGame()
{
	m_pCamera = nullptr;
	m_pLight = nullptr;
	m_pMeshField = nullptr;
	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pMap = nullptr;
	m_pBoss_Shark = nullptr;
	m_bGameEnd = false;
	m_nEnemyNum = ZERO_INT;
	m_pEnemyFileData = nullptr;
	m_pFont = nullptr;
	m_bBossTransition = false;
	m_bBoss = false;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CGame::~CGame()
{
	// 終了処理
	Uninit();
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CGame::Init(void)
{
	// カメラクラスのクリエイト
	m_pCamera = CCameraGame::Create();

	//ライトクラスの生成
	m_pLight = new CLight;

	// ライトの初期化処理
	if (m_pLight != nullptr)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}
	// プレイヤーの生成
	CreatePlayer();

	// 敵生成
	//CreateEnemy_Obstacle(ENEMY_OBSTACLE_CREATE_TEXT);

	// マップの生成
	CreateMap();

	CSound *pSound = GET_SOUND_PTR;
	pSound->Play(CSound::SOUND_BGM_GAME);

	return S_OK;
}
//=======================================================================================
// 終了処理
//=======================================================================================
void CGame::Uninit(void)
{
	if (m_pCamera != nullptr)
	{
		//カメラクラスの終了処理呼び出す
		m_pCamera->Uninit();

		//メモリの破棄
		delete m_pCamera;

		//メモリのクリア
		m_pCamera = nullptr;
	}

	// ライトの終了処理
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	// プレイヤーの終了処理
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	// 地面の終了処理
	if (m_pMeshField != nullptr)
	{
		m_pMeshField->Uninit();
		m_pMeshField = nullptr;
	}
	// デバッグ情報表示用フォントの破棄
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CGame::Update(void)
{
	// プレイヤーの位置描画
	DrawPlayerPos();

	if (m_pCamera != nullptr)
	{
		//カメラクラスの更新処理
		m_pCamera->Update();
	}
	// ボス戦遷移判定
	if (m_bBoss == false)
	{
		// ボス遷移判定
		BossTransition();
	}

	// モード遷移
	ModeTransition();

	// ゲームの設定
	SetGame();

}

//=======================================================================================
// 描画処理
//=======================================================================================
void CGame::Draw(void)
{

}

//=======================================================================================
// ゲームの設定
//=======================================================================================
void CGame::SetGame(void)
{
}

//=======================================================================================
// プレイヤーの生成
//=======================================================================================
void CGame::CreatePlayer(void)
{
	// プレイヤーの生成
	if (m_pPlayer == nullptr)
	{
		//m_pPlayer = CPlayer::Create(BOSS_TRT_POS, BOSS_PLAYER_ROT);
		m_pPlayer = CPlayer::Create(PLAYER_POS, PLAYER_ROT);
		CPlayer_Life::Create(LIFE_POS, ZeroVector3);			// ライフ生成

																// 操作方法
		CRotateUi::Create(m_pPlayer->GetRightPaddle());
		CRotateUi::Create(m_pPlayer->GetLeftPaddle());
		CAttackUi::Create(m_pPlayer->GetShip());
	}
}

//=======================================================================================
// マップの生成
//=======================================================================================
void CGame::CreateMap(void)
{
	// 地面の生成
	CreateGround();

	// マップ生成
	m_pMap = CMap::Create(ZeroVector3, ZeroVector3, CMap::TYPE_NORMAL);

	CBoss_Map_Transition::Create(BOSS_MAP_TRT_MAP_POS, BOSS_MAP_TRT_MAP_ROT);
}

//=======================================================================================
// 地面の生成
//=======================================================================================
void CGame::CreateGround(void)
{
	// 地面の生成
	CWater::Create();
}
//=======================================================================================
// 敵の生成ファイル読み込み
//=======================================================================================
void CGame::RoadEnemyFile(string pEnemyFile)
{
	// FILEポインタ
	FILE *pFile = nullptr;

	// ファイルオープン
	pFile = fopen(pEnemyFile.c_str(), "r");

	string aHeadData;
	string aModeName;

	// !nullcheck
	if (pFile != nullptr)
	{
		do
		{
			// 文字列をクリアする
			aHeadData.clear();

			//一列読み込んでモード情報を抽出
			getline((ifstream)pFile, aHeadData);

			// 代入
			aModeName = aHeadData;

			// ENEMY_NUMの場合
			if (aHeadData.find("ENEMY_NUM") != string::npos)
			{
				// 文字の分解
				aModeName = CLibrary::split(aHeadData, ' ', 2);

				// 敵数の設定
				sscanf(aHeadData.c_str(), "%*s %*s %d", &m_nEnemyNum);

				// メモリ確保
				m_pEnemyFileData = new ENEMY_FILE_DATA[m_nEnemyNum];
			}
			//  ENEMY_SETの場合
			if (aModeName.compare(string("ENEMY_SET")) == 0)
			{
				// 0に戻す
				m_nEnemyNum = ZERO_INT;

				// END_ENEMY_SETを読み込むまで繰り返す
				while (aModeName.compare(string("END_ENEMY_SET")) != 0)
				{
					// 一列読み込んでモード情報を抽出
					getline((ifstream)pFile, aHeadData);

					// 文字の分解
					aModeName = CLibrary::split(aHeadData, ' ', 0);

					// PARAMETER_SETの場合
					if (aModeName.compare(string("PARAMETER_SET")) == 0)
					{
						// END_PARAMETER_SETを読み込むまで繰り返す
						while (aModeName.compare(string("END_PARAMETER_SET")) != 0)
						{
							// 一列読み込んでモード情報を抽出
							getline((ifstream)pFile, aHeadData);
							aModeName = CLibrary::split(aHeadData, ' ', 1);

							// NUMBERの場合
							if (aModeName.find(string("TYPE")) == 0)
							{
								// 敵種類情報の設定
								sscanf(aHeadData.c_str(), "%*s %*s %d", &m_pEnemyFileData[m_nEnemyNum].Type);

							}
							// POSの場合
							if (aModeName.find(string("POS")) == 0)
							{
								//位置の設定
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_pEnemyFileData[m_nEnemyNum].Pos.x,
									&m_pEnemyFileData[m_nEnemyNum].Pos.y, &m_pEnemyFileData[m_nEnemyNum].Pos.z);
							}
							// ROTの場合
							if (aModeName.find(string("ROT")) == 0)
							{
								//向きの設定
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_pEnemyFileData[m_nEnemyNum].Rot.x,
									&m_pEnemyFileData[m_nEnemyNum].Rot.y, &m_pEnemyFileData[m_nEnemyNum].Rot.z);
							}
						}
						// インデックスを１つ進める
						m_nEnemyNum++;
					}
				}
			}

		} while (aModeName.find("END_SCRIPT") == string::npos);

		//ファイルクローズ
		::fclose(pFile);
	}
	// pFileがnullの場合
	else
	{
		// 失敗した場合メッセージボックスを表示
		MessageBox(nullptr, "ヒエラルキーファイルを開くのに失敗しました", "警告", MB_OK | MB_ICONEXCLAMATION);
	}
}
//=======================================================================================
// 敵生成関数
// Author : Sugawara Tsukasa
//=======================================================================================
void CGame::CreateEnemy_Obstacle(string pEnemyFile)
{
	// 敵のテキストファイル読み込み
	RoadEnemyFile(pEnemyFile);

	// !nullcheck
	if (m_pEnemyFileData != nullptr)
	{
		// 敵数分繰り返す
		for (int nCnt = ZERO_INT; nCnt < m_nEnemyNum; nCnt++)
		{
			// 敵の種類
			switch (m_pEnemyFileData[nCnt].Type)
			{
				// 敵船の場合
			case ENEMY_OBSTACLE_TYPE_SHIP:
				// 敵船生成
				CEnemy_Ship::Create(m_pEnemyFileData[nCnt].Pos, D3DXToRadian(m_pEnemyFileData[nCnt].Rot));
				break;
				// 敵船の場合
			case ENEMY_OBSTACLE_TYPE_SCAFFOLDING:
				// 櫓生成
				CEnemy_Scaffolding::Create(m_pEnemyFileData[nCnt].Pos, D3DXToRadian(m_pEnemyFileData[nCnt].Rot));
				break;
				// 魚雷の場合
			case ENEMY_OBSTACLE_TYPE_TORPEDO:
				// 魚雷生成
				CTorpedo::Create(m_pEnemyFileData[nCnt].Pos, D3DXToRadian(m_pEnemyFileData[nCnt].Rot));
				break;
				// 岩の場合
			case ENEMY_OBSTACLE_TYPE_ROCK:
				// 岩生成
				CRock::Create(m_pEnemyFileData[nCnt].Pos, D3DXToRadian(m_pEnemyFileData[nCnt].Rot));
				break;
				// 例外の場合
			default:
				break;
			}
		}

		// メモリ破棄
		delete[] m_pEnemyFileData;

		// nullptrに
		m_pEnemyFileData = nullptr;

		// 敵数
		m_nEnemyNum = ZERO_INT;
	}
}

//=======================================================================================
// プレイヤーの情報
// Author : SugawaraTsukasa
//=======================================================================================
void CGame::DrawPlayerPos(void)
{
	// プレイヤーの位置取得
	D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();

	// 書き込み
	CDebugProc::Print("POS:X%.1f Y%.1f Z%.1f", PlayerPos.x, PlayerPos.y, PlayerPos.z);
}
//=======================================================================================
// ボスマップ生成
// Author : SugawaraTsukasa
//=======================================================================================
void CGame::CreateBossMap(void)
{
	// !nullcheck
	if (m_pMap != nullptr)
	{
		// 終了処理
		m_pMap->Uninit();

		// nullptrに
		m_pMap = nullptr;
	}
	// nullptrの場合
	if (m_pMap == nullptr)
	{
		// マップ生成
		m_pMap = CMap::Create(ZeroVector3, ZeroVector3, CMap::TYPE_BOSS);

		// ボス生成
		m_pBoss_Shark = CBoss_Shark::Create(BOSS_POS, BOSS_ROT);

		// 位置変更
		m_pPlayer->SetPos(BOSS_PLAYER_POS);

		// 向き変更
		m_pPlayer->SetRot(BOSS_PLAYER_ROT);
	}
}
//=======================================================================================
// ボス遷移処理
// Author : SugawaraTsukasa
//=======================================================================================
void CGame::BossTransition(void)
{
	// !nullcheck
	if (m_pPlayer != nullptr)
	{
		// 位置取得
		D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();

		// 位置取得
		D3DXVECTOR3 PlayerSize = m_pPlayer->GetSize();

		// 位置
		if (CCollision::CollisionRectangleAndRectangle(PlayerPos, BOSS_TRANSITION_POS, PlayerSize, BOSS_TARNSITION_SIZE) == true)
		{
			// ボス遷移状態に
			m_bBossTransition = true;

			// ボス戦状態に
			m_bBoss = true;

			// フェード生成
			CBoss_Fade::Create(ZeroVector3, ZeroVector3);

		}
	}
}

//=======================================================================================
// モード遷移処理
// Author : Konishi Yuuto
//=======================================================================================
void CGame::ModeTransition(void)
{
	if (m_pPlayer->GetEnd())
	{
		CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

		if (mode == CFade::FADE_MODE_NONE)
		{
			CFade *pFade = CManager::GetFade();
			pFade->SetFade(CManager::MODE_TYPE_RESULT_FAILED);
		}
	}
	// !nullcheck
	if (m_pBoss_Shark != nullptr)
	{
		// 終了判定がtrueの場合
		if (m_pBoss_Shark->GetEnd() == true)
		{
			CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

			if (mode == CFade::FADE_MODE_NONE)
			{
				CFade *pFade = CManager::GetFade();
				pFade->SetFade(CManager::MODE_TYPE_RESULT_CLEAR);
			}
		}
	}
}
//=======================================================================================
// ボス戦敵生成
// Author : Konishi Yuuto
//=======================================================================================
void CGame::Boss_Enemy_Create(void)
{
	// 敵生成
	CreateEnemy_Obstacle(BOSS_ENEMY_CREATE_TEXT);
}