//=============================================================================
// �e [bullet.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "character.h"
#include "collision.h"
#include "bullet.h"
#include "effect.h"
#include "sound.h"

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define GRAVITY		(0.1f)								// �d��
#define SIZE		(D3DXVECTOR3(80.0f,80.0f,80.0f))	// �T�C�Y
#define POS_Y_MIN	(0.0f)								// Y���W�ŏ��l
//�����Ԃ�
#define SPLASH_POS			(D3DXVECTOR3(GetPos().x, 1,GetPos().z))			
#define SPLASH_SIZE			(D3DXVECTOR3(10.0f, 10.0f, 0.0f))		
#define SPLASH_MOVE			(D3DXVECTOR3(10.0f, 20.0f, 10.0f))		
#define SPLASH_COLOR		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))		
#define SPLASH_LIFE			(1000)									
#define SPLASH_MAX			(20)
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CBullet::CBullet(PRIORITY Priority) : CModel(Priority)
{
	m_XfileNum = CXfile::XFILE_NUM_BULLET;
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CBullet�̃|�C���^
	CBullet *pBullet = nullptr;

	// nullcheck
	if (pBullet == nullptr)
	{
		// �������m��
		pBullet = new CBullet;

		// !nullcheck
		if (pBullet != nullptr)
		{
			// ����������
			pBullet->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pBullet;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(m_XfileNum);

		// ���f���̏���n��
		BindModel(model);

		// �e�̐ݒ�
	//	SetShadowInfo(model);
	}

	// �T�C�Y�ݒ�
	SetSize(SIZE);

	// ����������
	CModel::Init(pos, rot);

	CSound *pSound = GET_SOUND_PTR;
	pSound->Play(CSound::SOUND_SE_SHOT);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Uninit(void)
{
	// �I������
	CModel::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Update(void)
{
	// �X�V����
	CModel::Update();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �ړ�
	move.y -= GRAVITY;

	// �ړ��ʐݒ�
	SetMove(move);

	// y��0�ȉ��̏ꍇ
	if (pos.y <= POS_Y_MIN)
	{
		//�����Ԃ�
		CreateSplash();

		// �j��
		Death();
	}
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}
//=======================================================================================
// �����Ԃ������֐�
// Author : Oguma Akira
//=======================================================================================
void CBullet::CreateSplash(void)
{
	for (int nCntEffcet = 0; nCntEffcet < SPLASH_MAX; nCntEffcet++)
	{
		// �p�[�e�B�N������
		CEffect::Create(SPLASH_POS, SPLASH_SIZE, SPLASH_MOVE, SPLASH_COLOR,
			CEffect::EFFECT_TYPE(CEffect::EFFECT_TYPE_4), SPLASH_LIFE);
	}
}
//=============================================================================
// ���S�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBullet::Death(void)
{
	// ���S��Ԃ�
	SetState(STATE_DEAD);

	// �I������
	Uninit();

	return;
}
