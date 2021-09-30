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
#include "resource_manager.h"
#include "texture.h"
#include "renderer.h"
#include "player.h"
#include "sound.h"
#include "resource_manager.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define ANGLE_RADIAN					(D3DXToRadian((float)(rand() % 180)))	//���W�A���̊p�x
#define PARTICLE_TEXTURE_SOMKE			("data/Texture/Smoke.png")				//�p�[�e�B�N���̃e�N�X�`��
#define PARTICLE_TEXTURE_EXPLOSION		("data/Texture/Explosion_Animation.png")//�p�[�e�B�N���̃e�N�X�`��
#define PARTICLE_TEXTURE_WAVE			("data/Texture/Wave_Effect.png")		//�p�[�e�B�N���̃e�N�X�`��
#define PARTICLE_TEXTURE_WOOD_EP		("data/Texture/Wood_Animation.png")		//�p�[�e�B�N���̃e�N�X�`��
#define ALPHA_VALUE_DECREASE			(0.001f)								//�A���t�@�l�̌����l
#define MAX_GRAVITY_COUNTER_EXPLOSION	(1000000)									//�����̍����̍ő�l
#define MAX_GRAVITY_COUNTER_SPLASH		(100000)									//�����Ԃ��̍����̍ő�l
#define MAX_GRAVITY_COUNTER_WAVE		(3000)									//�g�̍����̍ő�l
#define MAX_TEXTURE_SIZE				(5.0f)									//�e�N�X�`���T�C�Y�̔{���ő�l
#define MIN_TEXTURE_SIZE				(0.5f)									//�e�N�X�`���T�C�Y�̔{���ŏ��l
#define FR_SIZE_VALUE					(400)									//���a�̑傫���̒l
#define ANIMETION_DEFAULT				(D3DXVECTOR2(1, 1))						//�A�j���[�V��������
#define ANIMETION_EXPLOSION				(D3DXVECTOR2(16, 4))					//�A�j���[�V��������
#define ANIMETION_WOOD					(D3DXVECTOR2(8, 4))						//�A�j���[�V�����؍�

//�������l
#define EFFECT_FALL_EXPLOSION			(D3DXVECTOR3(GetMove().x, -GetMove().y*0.5f, GetMove().z))	//����
#define EFFECT_FALL_WAVE				(D3DXVECTOR3(0.0f, -GetMove().y, 0.0f))						//�g
#define EFFECT_FALL_SPLASH				(D3DXVECTOR3(GetMove().x, -GetMove().y, GetMove().z))		//�����Ԃ�
#define EFFECT_FALL_WOOD				(D3DXVECTOR3(GetMove().x, -GetMove().y, GetMove().z))		//�؍�

//=============================================================================
//�ÓI�����o�ϐ��錾
//===================================w==========================================

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
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, EFFECT_TYPE type, int Life)
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
			m_pEffect->Wave(pos, size, move, col, type, Life);
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
			TEXT("Could not check for NULL."), MB_OK);
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

																									// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	//�p�x�v�Z
	float fAngle = ANGLE_RADIAN;

	//���a
	float fr = sqrtf((size.x) * size.x + (size.y) * size.y + (size.z) * size.z);

	//�����p�x
	ActualMove.x = (cosf(fAngle) * cosf(fr* FR_SIZE_VALUE))*move.x;
	ActualMove.y = (cosf(fr * FR_SIZE_VALUE))*move.y;
	ActualMove.z = (sinf(fAngle) * cosf(fr* FR_SIZE_VALUE))*move.z;

	//�ʒu
	CreatePos.x = (cosf(fAngle) * cosf(fr* FR_SIZE_VALUE))*pos.x;
	CreatePos.y = (cosf(fr * FR_SIZE_VALUE))*pos.y;
	CreatePos.z = (sinf(fAngle) * cosf(fr* FR_SIZE_VALUE))*pos.z;

	//�傫��
	RandomSize.x = (MinSize.x) + (int)(rand() *((MaxSize.x) - MinSize.x + 1.0) / (1.0 + RAND_MAX));
	RandomSize.y = (MinSize.y) + (int)(rand() *((MaxSize.y) - MinSize.y + 1.0) / (1.0 + RAND_MAX));

	m_bLoop = true;	//�A�j���[�V�������[�v
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_EFFECT_SMOKE));//�e�N�X�`�������i�[
	Init(CreatePos, RandomSize, ActualMove, type, col, Life);
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

																									// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	//�p�x�v�Z
	float fAngle = ANGLE_RADIAN;

	//���a
	float fr = sqrtf((size.x) * size.x + (size.y) * size.y + (size.z) * size.z);

	//�����p�x
	ActualMove.x = (cosf(fAngle) * cosf(fr* FR_SIZE_VALUE))*move.x;
	ActualMove.y = (cosf(fr* FR_SIZE_VALUE))*move.y;
	ActualMove.z = (sinf(fAngle) * cosf(fr* FR_SIZE_VALUE))*move.z;

	//�ʒu
	CreatePos.x = (cosf(fAngle) * cosf(fr* FR_SIZE_VALUE))*pos.x;
	CreatePos.y = (cosf(fr* FR_SIZE_VALUE))*pos.y;
	CreatePos.z = (sinf(fAngle) * cosf(fr* FR_SIZE_VALUE))*pos.z;

	//�傫��
	RandomSize.x = (MinSize.x) + (int)(rand()*((MaxSize.x) - MinSize.x + 1.0) / (1.0 + RAND_MAX));
	RandomSize.y = (MinSize.y) + (int)(rand()*((MaxSize.y) - MinSize.y + 1.0) / (1.0 + RAND_MAX));

	Init(CreatePos, RandomSize, ActualMove, type, col, Life);

	// �A�j���[�V�������ݒ�
	BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_EFFECT_WOOD));
	D3DXVECTOR2 TexInfo = pTexture->GetSparateTexInfo(CTexture::SEPARATE_TEX_EFFECT_WOOD);
	bool bLoop = pTexture->GetSparateTexLoop(CTexture::SEPARATE_TEX_EFFECT_WOOD);
	InitAnimation(TexInfo, bLoop);

	CSound *pSound = GET_SOUND_PTR;
	pSound->Play(CSound::SOUND_SE_BREAK);
}

//=============================================================================
//�����G�t�F�N�g�֐�
//=============================================================================
void CEffect::Explosion(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, EFFECT_TYPE type, int Life)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	Init(pos, size, ZeroVector3, type, col, Life);

	// �A�j���[�V�������ݒ�
	BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_EFFECT_EXPLOSION));
	D3DXVECTOR2 TexInfo = pTexture->GetSparateTexInfo(CTexture::SEPARATE_TEX_EFFECT_EXPLOSION);
	InitAnimation(TexInfo, 0);	
	
	CSound *pSound = GET_SOUND_PTR;
	pSound->Play(CSound::SOUND_SE_EXPLOSION);
}

//=============================================================================
//�g�G�t�F�N�g�֐�
//=============================================================================
void CEffect::Wave(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, EFFECT_TYPE type, int Life)
{
	//�p�[�e�B�N���̈ړ��p�x
	D3DXVECTOR3 ActualMove = ZeroVector3;									//�ړ���
																			//D3DXVECTOR3 CreatePos = ZeroVector3;									//�����ʒu
																			//D3DXVECTOR3 RandomSize = ZeroVector3;									//�摜�̃����_���T�C�Y
	D3DXVECTOR3 MaxSize = D3DXVECTOR3(size.x * MAX_TEXTURE_SIZE, size.y * MAX_TEXTURE_SIZE, NULL);	//�ő�T�C�Y
	D3DXVECTOR3 MinSize = D3DXVECTOR3(size.x * MIN_TEXTURE_SIZE, size.y * MIN_TEXTURE_SIZE, NULL);	//�ŏ��T�C�Y

																									// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	//�p�x�v�Z
	float fAngle = ANGLE_RADIAN;
	//���a
	float fr = sqrtf((size.x) * size.x + (size.y) * size.y + (size.z) * size.z);

	//�����p�x
	ActualMove.x = (cos(fAngle) * cos(fr* FR_SIZE_VALUE))*move.x;
	ActualMove.y = (sin(fr + FR_SIZE_VALUE))*move.y;
	ActualMove.z = (sin(fAngle) * cos(fr* FR_SIZE_VALUE))*move.z;

	//�傫��
	//RandomSize.x = (MinSize.x) + (int)(rand()*(MaxSize.x - MinSize.x + 1.0) / (1.0 + RAND_MAX));
	//RandomSize.y = (MinSize.y) + (int)(rand()*(MaxSize.y - MinSize.y + 1.0) / (1.0 + RAND_MAX));

	m_bLoop = true;//�A�j���[�V�������[�v
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_EFFECT_WAVE));//�e�N�X�`�������i�[
	Init(pos, size, ActualMove, type, col, Life);
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

																									// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	//�p�x�v�Z
	float fAngle = ANGLE_RADIAN;
	//���a
	float fr = sqrtf((size.x) * size.x + (size.y) * size.y + (size.z) * size.z);

	//�����p�x
	ActualMove.x = (cosf(fAngle) * cos(fr* FR_SIZE_VALUE))*move.x;
	ActualMove.y = (cosf(fr* FR_SIZE_VALUE))*move.y;
	ActualMove.z = (sinf(fAngle) * cos(fr* FR_SIZE_VALUE))*move.z;

	//�ʒu
	CreatePos.x = (cos(fAngle) * cos(fr* FR_SIZE_VALUE))*pos.x;
	CreatePos.y = (cos(fr* FR_SIZE_VALUE))*pos.y;
	CreatePos.z = (sin(fAngle) * cos(fr* FR_SIZE_VALUE))*pos.z;

	//�傫��
	//RandomSize.x = (MinSize.x) + (int)(rand()*((MaxSize.x) - MinSize.x + 1.0) / (1.0 + RAND_MAX));
	//RandomSize.y = (MinSize.y) + (int)(rand()*((MaxSize.y) - MinSize.y + 1.0) / (1.0 + RAND_MAX));

	m_bLoop = true;//�A�j���[�V�������[�v
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_EFFECT_WAVE));//�e�N�X�`�������i�[
	Init(pos, size, ActualMove, type, col, Life);
}

//=============================================================================
//�������֐�
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, EFFECT_TYPE type, D3DXCOLOR col, int Life)
{
	SetMove(move);					//�ړ���
	GetColor() = col;				//�J���[
	SetLife(Life);					//���C�t
	m_nType = type;					//�^�C�v
	CBillboard::Init(pos, size);	//�r���{�[�h

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
			SetMove(EFFECT_FALL_EXPLOSION);
			m_nType = EFFECT_TYPE_NONE;
		}
		break;

		//�g
	case EFFECT_TYPE_3:
		if (rand() % MAX_GRAVITY_COUNTER_WAVE< GetPos().y)
		{
			SetMove(EFFECT_FALL_WAVE);
			m_nType = EFFECT_TYPE_NONE;
		}
		break;

		//�����Ԃ�
	case EFFECT_TYPE_4:
		if ((rand() % MAX_GRAVITY_COUNTER_SPLASH)< GetPos().y)
		{
			SetMove(EFFECT_FALL_SPLASH);
			m_nType = EFFECT_TYPE_NONE;
		}
		break;

		//�؍�
	case EFFECT_TYPE_5:
		if ((rand() % MAX_GRAVITY_COUNTER_EXPLOSION) < GetPos().y)
		{
			SetMove(EFFECT_FALL_WOOD);
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

