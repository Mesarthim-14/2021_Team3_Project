//=============================================================================
//
// �p�[�e�B�N������ [particle.cpp]
// Author : oguma akira
// �X�V�� : 2021/08/31
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define ANGLE_RADIAN					(D3DXToRadian((float)(rand() % 360)))	//���W�A���̊p�x
#define PARTICLE_TEXTURE_SOMKE			("data/Texture/Smoke.png")				//�p�[�e�B�N���̃e�N�X�`��
#define PARTICLE_TEXTURE_EXPLOSION		("data/Texture/Explosion_Animation.png")//�p�[�e�B�N���̃e�N�X�`��
#define PARTICLE_TEXTURE_WAVE			("data/Texture/Wave_Effect.png")		//�p�[�e�B�N���̃e�N�X�`��
#define PARTICLE_TEXTURE_WOOD_EP		("data/Texture/Wood_Animation.png")		//�p�[�e�B�N���̃e�N�X�`��
#define ALPHA_VALUE_DECREASE			(0.001f)								//�A���t�@�l�̌����l
#define MAX_GRAVITY_COUNTER_EXPLOSION	(30000)									//�����̍����̍ő�l
#define MAX_GRAVITY_COUNTER_SPLASH		(10000)									//�����Ԃ��̍����̍ő�l
#define MAX_GRAVITY_COUNTER_WAVE		(300)									//�g�̍����̍ő�l
#define PARTICLE_Fall_WAVE				(0.5f)									//�~���{��
#define MAX_TEXTURE_SIZE				(5.0f)									//�e�N�X�`���T�C�Y�̔{���ő�l
#define MIN_TEXTURE_SIZE				(0.5f)									//�e�N�X�`���T�C�Y�̔{���ŏ��l
#define ANIMETION_DEFAULT				(D3DXVECTOR2(1, 1))						//�A�j���[�V��������
#define ANIMETION_EXPLOSION				(D3DXVECTOR2(16, 4))					//�A�j���[�V��������
#define ANIMETION_WOOD					(D3DXVECTOR2(8, 4))						//�A�j���[�V�����؍�

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9	CEffect::m_apTexture[EFFECT_TEXTURE_MAX] = {};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CEffect::CEffect(PRIORITY Prioity) : CBillboard(Prioity)
{
	m_bLoop = false;//�A�j���[�V�������[�v
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
//�N���G�C�g�֐�
//=============================================================================
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, EFFECT_TYPE type, int Life)
{
	CEffect *m_pEffect = NULL;	//�������m��

								//NULL�`�F�b�N
	if (m_pEffect == NULL)
	{
		//�������m��
		m_pEffect = new CEffect;
		switch (type)
		{
			//��
		case EFFECT_TYPE::EFFECT_TYPE_1:
			m_pEffect->Smoke(pos, size, move, col, type, Life);
			break;

			//����
		case EFFECT_TYPE::EFFECT_TYPE_2:
			m_pEffect->Explosion(pos, size, col, type, Life);
			break;

			//�g
		case EFFECT_TYPE::EFFECT_TYPE_3:
			m_pEffect->Wave(pos, size, move, rot, col, type, Life);
			break;

			//�����Ԃ�
		case EFFECT_TYPE::EFFECT_TYPE_4:
			m_pEffect->Splash(pos, size, move, col, type, Life);
			break;

			//�؍�
		case EFFECT_TYPE::EFFECT_TYPE_5:
			m_pEffect->WoodExplosion(pos, size, move, col, type, Life);
			break;

		default:
			break;
		}
	}
	else
	{
		//�G���[�̃��b�Z�[�WBOX
		MessageBox(NULL, TEXT("Error in effect.cpp"),
			TEXT("effect.cppNULL�`�F�b�N�o���܂���ł����B"), MB_OK);
	}
	return m_pEffect;
}

//=============================================================================
//���G�t�F�N�g�̊֐�
//=============================================================================
void CEffect::Smoke(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, EFFECT_TYPE type, int Life)
{
	//�ϐ��錾
	D3DXVECTOR3 ActualMove = ZeroVector3;									//�ړ���
	D3DXVECTOR3 CreatePos = ZeroVector3;									//�����ʒu
	D3DXVECTOR3 RandomSize = ZeroVector3;									//�摜�̃����_���T�C�Y
	D3DXVECTOR3 MaxSize = D3DXVECTOR3(size.x * MAX_TEXTURE_SIZE, size.y * MAX_TEXTURE_SIZE, NULL);	//�ő�T�C�Y
	D3DXVECTOR3 MinSize = D3DXVECTOR3(size.x * MIN_TEXTURE_SIZE, size.y * MIN_TEXTURE_SIZE, NULL);	//�ŏ��T�C�Y

	//�p�[�e�B�N�����J��Ԃ�
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		//�p�x�v�Z
		float fAngle = ANGLE_RADIAN;
		//���a
		float fr = sqrtf((size.x) * size.x + (size.y) * size.y + (size.z) * size.z);

		//�����p�x
		ActualMove.x = ((float)cos(fAngle)* (float)cos(fr*nCnt))*move.x;
		ActualMove.y = ((float)cos(fr*nCnt))*move.y;
		ActualMove.z = ((float)sin(fAngle)* (float)cos(fr*nCnt))*move.z;

		//�ʒu
		CreatePos.x = ((float)cos(fAngle)* (float)cos(fr*nCnt))*pos.x;
		CreatePos.y = ((float)cos(fr*nCnt))*pos.y;
		CreatePos.z = ((float)sin(fAngle)* (float)cos(fr*nCnt))*pos.z;

		//�傫��
		RandomSize.x = (MinSize.x) + (int)(rand()*((MaxSize.x) - MinSize.x + 1.0) / (1.0 + RAND_MAX));
		RandomSize.y = (MinSize.y) + (int)(rand()*((MaxSize.y) - MinSize.y + 1.0) / (1.0 + RAND_MAX));

		m_bLoop = true;	//�A�j���[�V�������[�v
		Init(CreatePos, RandomSize, ActualMove, type, col, Life);
		BindTexture(m_apTexture[EFFECT_TEXTURE_1]);//�e�N�X�`�������i�[
	}
}

//=============================================================================
//�؍ރG�t�F�N�g�̊֐�
//=============================================================================
void CEffect::WoodExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, EFFECT_TYPE type, int Life)
{
	//�ϐ��錾
	D3DXVECTOR3 ActualMove = ZeroVector3;									//�ړ���
	D3DXVECTOR3 CreatePos = ZeroVector3;									//�����ʒu
	D3DXVECTOR3 RandomSize = ZeroVector3;									//�摜�̃����_���T�C�Y
	D3DXVECTOR3 MaxSize = D3DXVECTOR3(size.x * MAX_TEXTURE_SIZE, size.y * MAX_TEXTURE_SIZE, NULL);	//�ő�T�C�Y
	D3DXVECTOR3 MinSize = D3DXVECTOR3(size.x * MIN_TEXTURE_SIZE, size.y * MIN_TEXTURE_SIZE, NULL);	//�ŏ��T�C�Y

	//�p�[�e�B�N�����J��Ԃ�
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		//�p�x�v�Z
		float fAngle = ANGLE_RADIAN;
		//���a
		float fr = sqrtf((size.x) * size.x + (size.y) * size.y + (size.z) * size.z);

		//�����p�x
		ActualMove.x = ((float)cos(fAngle)* (float)cos(fr*nCnt))*move.x;
		ActualMove.y = ((float)cos(fr*nCnt))*move.y;
		ActualMove.z = ((float)sin(fAngle)* (float)cos(fr*nCnt))*move.z;

		//�ʒu
		CreatePos.x = ((float)cos(fAngle)* (float)cos(fr*nCnt))*pos.x;
		CreatePos.y = ((float)cos(fr*nCnt))*pos.y;
		CreatePos.z = ((float)sin(fAngle)* (float)cos(fr*nCnt))*pos.z;

		//�傫��
		RandomSize.x = (MinSize.x) + (int)(rand()*((MaxSize.x) - MinSize.x + 1.0) / (1.0 + RAND_MAX));
		RandomSize.y = (MinSize.y) + (int)(rand()*((MaxSize.y) - MinSize.y + 1.0) / (1.0 + RAND_MAX));

		m_bLoop = true;

		Init(CreatePos, RandomSize, ActualMove, type, col, Life);
		BindTexture(m_apTexture[EFFECT_TEXTURE_4]);//�e�N�X�`�������i�[
	}
}

//=============================================================================
//�����G�t�F�N�g�֐�
//=============================================================================
void CEffect::Explosion(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, EFFECT_TYPE type, int Life)
{
	Init(pos, size, ZeroVector3, type, col, Life);
	BindTexture(m_apTexture[EFFECT_TEXTURE_2]);//�e�N�X�`�������i�[
}

//=============================================================================
//�g�G�t�F�N�g�֐�
//=============================================================================
void CEffect::Wave(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, EFFECT_TYPE type, int Life)
{
	//�p�[�e�B�N���̈ړ��p�x
	D3DXVECTOR3 ActualMove = ZeroVector3;									//�ړ���
																			//D3DXVECTOR3 CreatePos = ZeroVector3;									//�����ʒu
																			//D3DXVECTOR3 RandomSize = ZeroVector3;									//�摜�̃����_���T�C�Y
	D3DXVECTOR3 MaxSize = D3DXVECTOR3(size.x * MAX_TEXTURE_SIZE, size.y * MAX_TEXTURE_SIZE, NULL);	//�ő�T�C�Y
	D3DXVECTOR3 MinSize = D3DXVECTOR3(size.x * MIN_TEXTURE_SIZE, size.y * MIN_TEXTURE_SIZE, NULL);	//�ŏ��T�C�Y

																									//�p�[�e�B�N�����J��Ԃ�
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		//�p�x�v�Z
		float fAngle = ANGLE_RADIAN;
		//���a
		float fr = sqrtf((size.x) * size.x + (size.y) * size.y + (size.z) * size.z);

		//�����p�x
		ActualMove.x = ((float)cos(fAngle)* (float)cos(fr*nCnt))*move.x;
		ActualMove.y = ((float)sin(fr + nCnt))*move.y;
		ActualMove.z = ((float)sin(fAngle)* (float)cos(fr*nCnt))*move.z;

		//�傫��
		//RandomSize.x = (MinSize.x) + (int)(rand()*(MaxSize.x - MinSize.x + 1.0) / (1.0 + RAND_MAX));
		//RandomSize.y = (MinSize.y) + (int)(rand()*(MaxSize.y - MinSize.y + 1.0) / (1.0 + RAND_MAX));

		m_bLoop = true;//�A�j���[�V�������[�v
		Init(pos, size, ActualMove, type, col, Life);
		BindTexture(m_apTexture[EFFECT_TEXTURE_3]);//�e�N�X�`�������i�[
	}
}

//=============================================================================
//�����Ԃ��G�t�F�N�g�̊֐�
//=============================================================================
void CEffect::Splash(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, EFFECT_TYPE type, int Life)
{
	//�p�[�e�B�N���̈ړ��p�x
	D3DXVECTOR3 ActualMove = ZeroVector3;									//�ړ���
	D3DXVECTOR3 CreatePos = ZeroVector3;									//�����ʒu
																			//D3DXVECTOR3 RandomSize = ZeroVector3;									//�摜�̃����_���T�C�Y
	D3DXVECTOR3 MaxSize = D3DXVECTOR3(size.x * MAX_TEXTURE_SIZE, size.y * MAX_TEXTURE_SIZE, NULL);	//�ő�T�C�Y
	D3DXVECTOR3 MinSize = D3DXVECTOR3(size.x * MIN_TEXTURE_SIZE, size.y * MIN_TEXTURE_SIZE, NULL);	//�ŏ��T�C�Y

	//�p�[�e�B�N�����J��Ԃ�
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		//�p�x�v�Z
		float fAngle = ANGLE_RADIAN;
		//���a
		float fr = sqrtf((size.x) * size.x + (size.y) * size.y + (size.z) * size.z);

		//�����p�x
		ActualMove.x = ((float)cos(fAngle)* (float)cos(fr*nCnt))*move.x;
		ActualMove.y = ((float)cos(fr*nCnt))*move.y;
		ActualMove.z = ((float)sin(fAngle)* (float)cos(fr*nCnt))*move.z;

		//�ʒu
		CreatePos.x = ((float)cos(fAngle)* (float)cos(fr*nCnt))*pos.x;
		CreatePos.y = ((float)cos(fr*nCnt))*pos.y;
		CreatePos.z = ((float)sin(fAngle)* (float)cos(fr*nCnt))*pos.z;

		//�傫��
		//RandomSize.x = (MinSize.x) + (int)(rand()*((MaxSize.x) - MinSize.x + 1.0) / (1.0 + RAND_MAX));
		//RandomSize.y = (MinSize.y) + (int)(rand()*((MaxSize.y) - MinSize.y + 1.0) / (1.0 + RAND_MAX));

		m_bLoop = true;//�A�j���[�V�������[�v
		Init(CreatePos, size, ActualMove, type, col, Life);
		BindTexture(m_apTexture[EFFECT_TEXTURE_3]);//�e�N�X�`�������i�[
	}
}

//=============================================================================
//�e�N�X�`���̓ǂݍ��݊֐�
//=============================================================================
HRESULT CEffect::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, PARTICLE_TEXTURE_SOMKE, &m_apTexture[EFFECT_TEXTURE_1]);
	D3DXCreateTextureFromFile(pDevice, PARTICLE_TEXTURE_EXPLOSION, &m_apTexture[EFFECT_TEXTURE_2]);
	D3DXCreateTextureFromFile(pDevice, PARTICLE_TEXTURE_WAVE, &m_apTexture[EFFECT_TEXTURE_3]);
	D3DXCreateTextureFromFile(pDevice, PARTICLE_TEXTURE_WOOD_EP, &m_apTexture[EFFECT_TEXTURE_4]);

	return S_OK;
}

//=============================================================================
//�e�N�X�`���̔j���֐�
//=============================================================================
void CEffect::Unload(void)
{
	for (int nCount = 0; nCount < EFFECT_TEXTURE_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
//�������֐�
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, EFFECT_TYPE type, D3DXCOLOR col, int Life)
{
	//�r���{�[�h�̏�����
	SetMove(move);					//�ړ���
	GetColor() = col;
	SetLife(Life);
	m_nType = type;
	CBillboard::Init(pos, size);

	//
	switch (type)
	{
		//��
	case EFFECT_TYPE::EFFECT_TYPE_1:
		CBillboard::InitAnimation(ANIMETION_DEFAULT, m_bLoop);
		break;

		//����
	case EFFECT_TYPE::EFFECT_TYPE_2:
		CBillboard::InitAnimation(ANIMETION_EXPLOSION, 0);
		break;

		//�g
	case EFFECT_TYPE::EFFECT_TYPE_3:
		CBillboard::InitAnimation(ANIMETION_DEFAULT, m_bLoop);
		break;

		//�����Ԃ�
	case EFFECT_TYPE::EFFECT_TYPE_4:
		CBillboard::InitAnimation(ANIMETION_DEFAULT, m_bLoop);
		break;

		//�؍�
	case EFFECT_TYPE::EFFECT_TYPE_5:
		CBillboard::InitAnimation(ANIMETION_WOOD, m_bLoop);
		break;

	default:
		break;
	}
	return S_OK;
}

//=============================================================================
//�X�V�֐�
//=============================================================================
void CEffect::Update(void)
{
	//��ނ��Ƃ̍����̐ݒ�ƍ~���ݒ�
	switch (m_nType)

	{
		//����
	case EFFECT_TYPE_1:
		if ((rand() % MAX_GRAVITY_COUNTER_EXPLOSION) < GetPos().y)
		{
			SetMove(D3DXVECTOR3(GetMove().x, -GetMove().y*PARTICLE_Fall_WAVE, GetMove().z));
			m_nType = EFFECT_TYPE_NONE;
		}
		break;

		//�g
	case EFFECT_TYPE_3:
		if (MAX_GRAVITY_COUNTER_WAVE< GetPos().y)
		{
			SetMove(D3DXVECTOR3(GetMove().x, -GetMove().y, GetMove().z));
			m_nType = EFFECT_TYPE_NONE;
		}
		break;

		//�����Ԃ�
	case EFFECT_TYPE_4:
		if ((rand() % MAX_GRAVITY_COUNTER_SPLASH)< GetPos().y)
		{
			SetMove(D3DXVECTOR3(GetMove().x, -GetMove().y, GetMove().z));
			m_nType = EFFECT_TYPE_NONE;
		}
		break;

		//�؍�
	case EFFECT_TYPE_5:
		if ((rand() % MAX_GRAVITY_COUNTER_EXPLOSION) < GetPos().y)
		{
			SetMove(D3DXVECTOR3(GetMove().x, -GetMove().y, GetMove().z));
			m_nType = EFFECT_TYPE_NONE;
		}
		break;

	default:
		break;
	}
	//�n�ʂ�艺�ł����
	if (GetPos().y < 0)
	{
		Uninit();

		return;
	}
	SetColor(D3DXCOLOR(GetColor().r, GetColor().g, GetColor().b, GetColor().a -= ALPHA_VALUE_DECREASE));
	CBillboard::Update();
}

//=============================================================================
//�I���֐�
//=============================================================================
void CEffect::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
//�`��֐�
//=============================================================================
void CEffect::Draw(void)
{
	CBillboard::Draw();
}

