//=============================================================================
// �G�̍U����� [enemy_attack_arrow_polygon.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "character.h"
#include "enemy_attack_arrow_polygon.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define DOWN_COUNT	(30)								// �J�E���g
#define UP_COUNT	(60)								// �J�E���g
#define MOVE		(3.0f)								// �ړ���
#define COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �F
#define POINT_SIZE	(D3DXVECTOR3(300.0f,0.0f,400.0f))	// �T�C�Y
#define UP_POS		(D3DXVECTOR3(pos.x,700.0f,pos.z))	// �ʒu
#define DOWN_POS	(D3DXVECTOR3(pos.x,200.0f,pos.z))	// �ʒu
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Attack_Arrow_Polygon::CEnemy_Attack_Arrow_Polygon(PRIORITY Priority) : CBillboard(Priority)
{
	m_nCount		= ZERO_INT;
	m_pBullet		= nullptr;
	m_bCollision	= false;
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Attack_Arrow_Polygon::~CEnemy_Attack_Arrow_Polygon()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Attack_Arrow_Polygon * CEnemy_Attack_Arrow_Polygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CBullet *pBullet)
{
	// CEnemy_Attack_Arrow_Polygon�̃|�C���^
	CEnemy_Attack_Arrow_Polygon *pEnemy_Attack_Point_Polygon = nullptr;

	// nullcheck
	if (pEnemy_Attack_Point_Polygon == nullptr)
	{
		// �������m��
		pEnemy_Attack_Point_Polygon = new CEnemy_Attack_Arrow_Polygon;

		// !nullcheck
		if (pEnemy_Attack_Point_Polygon != nullptr)
		{
			// ���
			pEnemy_Attack_Point_Polygon->m_pBullet = pBullet;

			// ����������
			pEnemy_Attack_Point_Polygon->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pEnemy_Attack_Point_Polygon;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CEnemy_Attack_Arrow_Polygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CBillboard::Init(pos, size);

	// // Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ATTACK_ARROW));

	// �����ݒ�
	SetRot(ZeroVector3);

	// �F�ݒ�
	SetColor(COLOR);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Arrow_Polygon::Uninit(void)
{
	// !nullcheck
	if (m_pBullet != nullptr)
	{
		m_pBullet = nullptr;
	}

	// �I������
	CBillboard::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Arrow_Polygon::Update(void)
{
	// �X�V����
	CBillboard::Update();

	// �ړ�����
	Move();

	// �����蔻��
	Collision();

	// ���S��Ԃ̏ꍇ
	if (m_pBullet->GetState() == CModel::STATE_DEAD)
	{
		// �I��
		Uninit();

		return;
	}
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Arrow_Polygon::Draw(void)
{
	// �`�揈��
	CBillboard::Draw();
}
//=============================================================================
// �����蔻�菈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Arrow_Polygon::Collision(void)
{
	//�v���C���[�̃|�C���^�擾
	CPlayer *pPlayer = GET_PLAYER_PTR;

	// �ʒu
	D3DXVECTOR3 pos = GetPos();

	// �ʒu�擾
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	// �T�C�Y�擾
	D3DXVECTOR3 PlayerSize = pPlayer->GetSize();

	// �v���C���[�Əd�Ȃ��Ă�����
	if (pos.x < PlayerPos.x + PlayerSize.x / DIVIDE_2 &&
		pos.x > PlayerPos.x - PlayerSize.x / DIVIDE_2 &&
		pos.z < PlayerPos.z + PlayerSize.z / DIVIDE_2 &&
		pos.z > PlayerPos.z - PlayerSize.z / DIVIDE_2)
	{
		// false�̏ꍇ
		if (m_bCollision == false)
		{
			// true��
			m_bCollision = true;

			// �ʒu�ݒ�
			SetPos(UP_POS);
		}
	}
	// �d�Ȃ��Ă��Ȃ��ꍇ
	else
	{
		// false�̏ꍇ
		if (m_bCollision == true)
		{
			// true��
			m_bCollision = false;

			// �ʒu�ݒ�
			SetPos(DOWN_POS);
		}
	}
}
//=============================================================================
// �ړ������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Arrow_Polygon::Move(void)
{
	// �ړ�
	D3DXVECTOR3 move = ZeroVector3;

	// �C���N�������g
	m_nCount++;

	// 30�ȉ��̏ꍇ
	if (m_nCount < DOWN_COUNT)
	{
		move.y += -MOVE;
	}
	// 60�ȉ��̏ꍇ
	if (m_nCount < UP_COUNT && m_nCount > DOWN_COUNT)
	{
		move.y += MOVE;
	}
	// 60�ȏ�̏ꍇ
	if (m_nCount > UP_COUNT)
	{
		// 0��
		m_nCount = ZERO_INT;
	}

	// �ړ��ʐݒ�
	SetMove(move);
}