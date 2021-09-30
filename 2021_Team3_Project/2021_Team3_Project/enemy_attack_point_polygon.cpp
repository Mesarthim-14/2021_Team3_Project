//=============================================================================
// �G�̍U���n�_ [enemy_attack_point_polygon.cpp]
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
#include "player.h"
#include "game.h"
#include "enemy_attack_point_polygon.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define ADD_ROT		(D3DXToRadian(1.0f))				// �������Z�l
#define ANGLE_MAX	(D3DXToRadian(360.0f))				// �p�x�̍ő�
#define ANGLE_MIN	(D3DXToRadian(0.0f))				// �p�x�̍ŏ�
#define COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �F
#define ALPHA		(100)								// ���ߒl
#define SIZE		(D3DXVECTOR3(300.0f,0.0f,400.0f))	// �T�C�Y
#define UP_POS		(D3DXVECTOR3(pos.x,500.0f,pos.z))	// �ʒu
#define DOWN_POS	(D3DXVECTOR3(pos.x,10.0f,pos.z))		// �ʒu
#define PARENT_NUM	(0)									// �e�̃i���o�[
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Attack_Point_Polygon::CEnemy_Attack_Point_Polygon(PRIORITY Priority) : CScene3D(Priority)
{
	m_pBullet		= nullptr;
	m_bCollision	= false;
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Attack_Point_Polygon::~CEnemy_Attack_Point_Polygon()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CEnemy_Attack_Point_Polygon * CEnemy_Attack_Point_Polygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CBullet *pBullet)
{
	// CEnemy_Attack_Point_Polygon�̃|�C���^
	CEnemy_Attack_Point_Polygon *pEnemy_Attack_Point_Polygon = nullptr;

	// nullcheck
	if (pEnemy_Attack_Point_Polygon == nullptr)
	{
		// �������m��
		pEnemy_Attack_Point_Polygon = new CEnemy_Attack_Point_Polygon;

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
HRESULT CEnemy_Attack_Point_Polygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CScene3D::Init(pos, size);

	// // Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ATTACK_POINT));

	// �����ݒ�
	SetRot(ZeroVector3);

	// �F�ݒ�
	SetColor(COLOR);

	// ���ߒl�ݒ�
	SetAlpha(true);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Point_Polygon::Uninit(void)
{
	// !nullcheck
	if (m_pBullet != nullptr)
	{
		m_pBullet = nullptr;
	}

	// �I������
	CScene3D::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Point_Polygon::Update(void)
{
	// �X�V����
	CScene3D::Update();

	// ��������
	UpdateRot();

	// �����蔻��
	Collision();

	// ���S��Ԃ̏ꍇ
	if (m_pBullet->GetState() == CModel::STATE_DEAD)
	{
		// �I������
		Uninit();

		return;
	}
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Point_Polygon::Draw(void)
{
	// �`�揈��
	CScene3D::Draw();
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Point_Polygon::UpdateRot(void)
{
	// �����擾
	D3DXVECTOR3 rot = GetRot();

	// �������Z
	rot.y += ADD_ROT;

	// 360�ȏ�̏ꍇ
	if (rot.x >= ANGLE_MAX)
	{
		// ���������ɖ߂�
		rot.y = ANGLE_MIN;
	}

	// �����ݒ�
	SetRot(rot);
}
//=============================================================================
// �����蔻�菈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CEnemy_Attack_Point_Polygon::Collision(void)
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