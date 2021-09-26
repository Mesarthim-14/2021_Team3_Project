//=======================================================================================
//
// �Q�[������ [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
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

//=======================================================================================
// �}�N����`
//=======================================================================================
#define ENEMY_OBSTACLE_CREATE_TEXT	("data/Text/Enemy/Enemy_Obstacle_Create.txt")	// �G�����e�L�X�g
#define ENEMY_POS					(D3DXVECTOR3(0.0f,800.0f,-3000.0f))				// �G�̈ʒu
#define ENEMY_POS_2					(D3DXVECTOR3(5000.0f,500.0f,0.0f))				// �G�̈ʒu
#define ENEMY_ROT					(D3DXVECTOR3(0.0f,D3DXToRadian(180.0f),0.0f))	// �G�̌���
#define PLAYER_POS					(D3DXVECTOR3(0.0f,0.0f,-500.0f))				// �v���C���[�̈ʒu
#define SIZE						(D3DXVECTOR3(2000.0f,1000.0f,0.0f))				// �T�C�Y
#define PALYER_ROT					(D3DXVECTOR3(0.0f,D3DXToRadian(270.0f),0.0f))	// �v���C���[�̌���
#define LIFE_POS					(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200.0f,0.0f))

#define BOSS_TRANSITION_POS			(D3DXVECTOR3(0.0f,0.0f,0.0f))					// �{�X��J�ڔ���ʒu
#define BOSS_TARNSITION_SIZE		(D3DXVECTOR3(0.0f,0.0f,0.0f))					// �{�X�J�ڔ���T�C�Y
//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CGame::CGame()
{
	m_pCamera = nullptr;
	m_pLight = nullptr;
	m_pMeshField = nullptr;
	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pMap = nullptr;
	m_bGameEnd = false;
	m_nEnemyNum = ZERO_INT;
	m_pEnemyFileData = nullptr;
	m_pFont = nullptr;
	m_bBossTransition = false;
	m_bBoss = true;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CGame::~CGame()
{
	// �I������
	Uninit();
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CGame::Init(void)
{
	// �J�����N���X�̃N���G�C�g
	m_pCamera = CCameraGame::Create();

	//���C�g�N���X�̐���
	m_pLight = new CLight;

	// ���C�g�̏���������
	if (m_pLight != nullptr)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}
	// �v���C���[�̐���
	CreatePlayer();

	// �G����
	CreateEnemy_Obstacle(ENEMY_OBSTACLE_CREATE_TEXT);

	// �}�b�v�̐���
	CreateMap();

	return S_OK;
}

//=======================================================================================
// �I������
//=======================================================================================
void CGame::Uninit(void)
{
	if (m_pCamera != nullptr)
	{
		//�J�����N���X�̏I�������Ăяo��
		m_pCamera->Uninit();

		//�������̔j��
		delete m_pCamera;

		//�������̃N���A
		m_pCamera = nullptr;
	}

	// ���C�g�̏I������
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	// �v���C���[�̏I������
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	// �n�ʂ̏I������
	if (m_pMeshField != nullptr)
	{
		m_pMeshField->Uninit();
		m_pMeshField = nullptr;
	}
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CGame::Update(void)
{
	//DrawPlayerPos();

	if (m_pCamera != nullptr)
	{
		//�J�����N���X�̍X�V����
		m_pCamera->Update();
	}
	// �{�X��J�ڔ���
	if (m_bBossTransition == false)
	{
		// ��J�ڔ���
		BossTransition();
	}
	if (m_pPlayer)
	{
		m_pPlayer->PlayerControl();
	}

	// �Q�[���̐ݒ�
	SetGame();
}

//=======================================================================================
// �`�揈��
//=======================================================================================
void CGame::Draw(void)
{

}

//=======================================================================================
// �Q�[���̐ݒ�
//=======================================================================================
void CGame::SetGame(void)
{
}

//=======================================================================================
// �v���C���[�̐���
//=======================================================================================
void CGame::CreatePlayer(void)
{
	// �v���C���[�̐���
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CPlayer::Create(PLAYER_POS, PALYER_ROT);
		CPlayer_Life::Create(LIFE_POS, ZeroVector3);			// ���C�t����
	}
}

//=======================================================================================
// �}�b�v�̐���
//=======================================================================================
void CGame::CreateMap(void)
{
	// �n�ʂ̐���
	CreateGround();

	// �}�b�v����
	m_pMap = CMap::Create(ZeroVector3, ZeroVector3, CMap::TYPE_NORMAL);
}

//=======================================================================================
// �n�ʂ̐���
//=======================================================================================
void CGame::CreateGround(void)
{
	// �n�ʂ̐���
	CWater::Create();
}
//=======================================================================================
// �G�̐����t�@�C���ǂݍ���
//=======================================================================================
void CGame::RoadEnemyFile(string pEnemyFile)
{
	// FILE�|�C���^
	FILE *pFile = nullptr;

	// �t�@�C���I�[�v��
	pFile = fopen(pEnemyFile.c_str(), "r");

	string aHeadData;
	string aModeName;

	// !nullcheck
	if (pFile != nullptr)
	{
		do
		{
			// ��������N���A����
			aHeadData.clear();

			//���ǂݍ���Ń��[�h���𒊏o
			getline((ifstream)pFile, aHeadData);

			// ���
			aModeName = aHeadData;

			// ENEMY_NUM�̏ꍇ
			if (aHeadData.find("ENEMY_NUM") != string::npos)
			{
				// �����̕���
				aModeName = CLibrary::split(aHeadData, ' ', 2);

				// �G���̐ݒ�
				sscanf(aHeadData.c_str(), "%*s %*s %d", &m_nEnemyNum);

				// �������m��
				m_pEnemyFileData = new ENEMY_FILE_DATA[m_nEnemyNum];
			}
			//  ENEMY_SET�̏ꍇ
			if (aModeName.compare(string("ENEMY_SET")) == 0)
			{
				// 0�ɖ߂�
				m_nEnemyNum = ZERO_INT;

				// END_ENEMY_SET��ǂݍ��ނ܂ŌJ��Ԃ�
				while (aModeName.compare(string("END_ENEMY_SET")) != 0)
				{
					// ���ǂݍ���Ń��[�h���𒊏o
					getline((ifstream)pFile, aHeadData);

					// �����̕���
					aModeName = CLibrary::split(aHeadData, ' ', 0);

					// PARAMETER_SET�̏ꍇ
					if (aModeName.compare(string("PARAMETER_SET")) == 0)
					{
						// END_PARAMETER_SET��ǂݍ��ނ܂ŌJ��Ԃ�
						while (aModeName.compare(string("END_PARAMETER_SET")) != 0)
						{
							// ���ǂݍ���Ń��[�h���𒊏o
							getline((ifstream)pFile, aHeadData);
							aModeName = CLibrary::split(aHeadData, ' ', 1);

							// NUMBER�̏ꍇ
							if (aModeName.find(string("TYPE")) == 0)
							{
								// �G��ޏ��̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %d", &m_pEnemyFileData[m_nEnemyNum].Type);

							}
							// POS�̏ꍇ
							if (aModeName.find(string("POS")) == 0)
							{
								//�ʒu�̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_pEnemyFileData[m_nEnemyNum].Pos.x,
									&m_pEnemyFileData[m_nEnemyNum].Pos.y, &m_pEnemyFileData[m_nEnemyNum].Pos.z);
							}
							// ROT�̏ꍇ
							if (aModeName.find(string("ROT")) == 0)
							{
								//�����̐ݒ�
								sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_pEnemyFileData[m_nEnemyNum].Rot.x,
									&m_pEnemyFileData[m_nEnemyNum].Rot.y, &m_pEnemyFileData[m_nEnemyNum].Rot.z);
							}
						}
						// �C���f�b�N�X���P�i�߂�
						m_nEnemyNum++;
					}
				}
			}

		} while (aModeName.find("END_SCRIPT") == string::npos);

		//�t�@�C���N���[�Y
		::fclose(pFile);
	}
	// pFile��null�̏ꍇ
	else
	{
		// ���s�����ꍇ���b�Z�[�W�{�b�N�X��\��
		MessageBox(nullptr, "�q�G�����L�[�t�@�C�����J���̂Ɏ��s���܂���", "�x��", MB_OK | MB_ICONEXCLAMATION);
	}
}
//=======================================================================================
// �G�����֐�
// Author : Sugawara Tsukasa
//=======================================================================================
void CGame::CreateEnemy_Obstacle(string pEnemyFile)
{
	// �G�̃e�L�X�g�t�@�C���ǂݍ���
	RoadEnemyFile(pEnemyFile);

	// !nullcheck
	if (m_pEnemyFileData != nullptr)
	{
		// �G�����J��Ԃ�
		for (int nCnt = ZERO_INT; nCnt < m_nEnemyNum; nCnt++)
		{
			// �G�̎��
			switch (m_pEnemyFileData[nCnt].Type)
			{
				// �G�D�̏ꍇ
			case ENEMY_OBSTACLE_TYPE_SHIP:
				// �G�D����
				CEnemy_Ship::Create(m_pEnemyFileData[nCnt].Pos, D3DXToRadian(m_pEnemyFileData[nCnt].Rot));
				break;
				// �G�D�̏ꍇ
			case ENEMY_OBSTACLE_TYPE_SCAFFOLDING:
				// �E����
				CEnemy_Scaffolding::Create(m_pEnemyFileData[nCnt].Pos, D3DXToRadian(m_pEnemyFileData[nCnt].Rot));
				break;
				// �����̏ꍇ
			case ENEMY_OBSTACLE_TYPE_TORPEDO:
				// ��������
				CTorpedo::Create(m_pEnemyFileData[nCnt].Pos, D3DXToRadian(m_pEnemyFileData[nCnt].Rot));
				break;
				// ��̏ꍇ
			case ENEMY_OBSTACLE_TYPE_ROCK:
				// �␶��
				CRock::Create(m_pEnemyFileData[nCnt].Pos, D3DXToRadian(m_pEnemyFileData[nCnt].Rot));
				break;
				// ��O�̏ꍇ
			default:
				break;
			}
		}

		// �������j��
		delete[] m_pEnemyFileData;

		// nullptr��
		m_pEnemyFileData = nullptr;

		// �G��
		m_nEnemyNum = ZERO_INT;
	}
}

//=======================================================================================
// �v���C���[�̏��
// Author : SugawaraTsukasa
//=======================================================================================
void CGame::DrawPlayerPos(void)
{
	// �v���C���[�̈ʒu�擾
	D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();

	// ��������
	CDebugProc::Print("POS:X%.1f Y%.1f Z%.1f", PlayerPos.x, PlayerPos.y, PlayerPos.z);
}
//=======================================================================================
// �{�X�}�b�v����
// Author : SugawaraTsukasa
//=======================================================================================
void CGame::CreateBossMap(void)
{
	// !nullcheck
	if (m_pMap != nullptr)
	{
		// �I������
		m_pMap->Uninit();

		// nullptr��
		m_pMap = nullptr;
	}
	// nullptr�̏ꍇ
	if (m_pMap == nullptr)
	{
		// �}�b�v����
		m_pMap = CMap::Create(ZeroVector3, ZeroVector3, CMap::TYPE_BOSS);

		// �{�X����
		CBoss_Shark::Create(ENEMY_POS, ENEMY_ROT);

		// �ʒu�ύX
		m_pPlayer->SetPos(ZeroVector3);

		// true��
		m_bBoss = true;
	}
}
//=======================================================================================
// �{�X�J�ڏ���
// Author : SugawaraTsukasa
//=======================================================================================
void CGame::BossTransition(void)
{
	// !nullcheck
	if (m_pPlayer != nullptr)
	{
		// �ʒu�擾
		D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();

		// �ʒu�擾
		D3DXVECTOR3 PlayerSize = m_pPlayer->GetSize();

		// �ʒu
		if (CCollision::CollisionRectangleAndRectangle(PlayerPos, BOSS_TRANSITION_POS, PlayerSize, BOSS_TARNSITION_SIZE) == true)
		{
			// �{�X����
			CreateBossMap();

			// true��
			m_bBossTransition = true;
		}
	}
}