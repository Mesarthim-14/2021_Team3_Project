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
#include "byte_effect.h"
#include "library.h"
#include "debug_proc.h"
#include "rock.h"
#include "water.h"

//=======================================================================================
// マクロ定義
//=======================================================================================
#define ENEMY_OBSTACLE_CREATE_TEXT	("data/Text/Enemy/Enemy_Obstacle_Create.txt")	// 敵生成テキスト
#define ENEMY_POS					(D3DXVECTOR3(0.0f,800.0f,-3000.0f))				// 敵の位置
#define ENEMY_POS_2					(D3DXVECTOR3(5000.0f,500.0f,0.0f))				// 敵の位置
#define ENEMY_ROT					(D3DXVECTOR3(0.0f,D3DXToRadian(180.0f),0.0f))	// 敵の向き
#define PLAYER_POS					(D3DXVECTOR3(0.0f,0.0f,-500.0f))				// プレイヤーの位置
#define SIZE						(D3DXVECTOR3(2000.0f,1000.0f,0.0f))				// サイズ
#define PALYER_ROT					(D3DXVECTOR3(0.0f,D3DXToRadian(270.0f),0.0f))	// プレイヤーの向き

//=======================================================================================
// コンストラクタ
//=======================================================================================
CGame::CGame()
{
	m_pCamera			= nullptr;
	m_pLight			= nullptr;
	m_pMeshField		= nullptr;
	m_pBg				= nullptr;
	m_pPlayer			= nullptr;
	m_pMap				= nullptr;
	m_bGameEnd			= false;
	m_nEnemyNum			= ZERO_INT;
	m_pEnemyFileData	= nullptr;
	m_pFont				= nullptr;
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
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// カメラクラスのクリエイト
	m_pCamera = CCamera::Create();

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
	CreateEnemy_Obstacle();

	// マップの生成
	CreateMap();

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
	DrawPlayerPos();

	if (m_pCamera != nullptr)
	{
		//カメラクラスの更新処理
		m_pCamera->Update();
	}

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
		m_pPlayer = CPlayer::Create(PLAYER_POS, PALYER_ROT);
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
	m_pMap = CMap::Create(ZeroVector3, ZeroVector3);
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
}
//=======================================================================================
// 敵生成関数
// Author : Sugawara Tsukasa
//=======================================================================================
void CGame::CreateEnemy_Obstacle(void)
{
	// 敵のテキストファイル読み込み
	RoadEnemyFile(ENEMY_OBSTACLE_CREATE_TEXT);

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