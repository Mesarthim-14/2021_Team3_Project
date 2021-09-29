//=============================================================================
// �{�X���݂��͈� [byte_attack_range.cpp]
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
#include "game.h"
#include "player.h"
#include "collision.h"
#include "byte_attack_range.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COL			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))	// �F
#define DAMAGE		(10)								// �_���[�W
#define ATTACK_KEY	(265)								// �U���L�[
#define COL_MAX		(1.0f)								// �F�ő�
#define COL_MIN		(0.1f)								// �F�̍ŏ�
#define ADD_COL		(0.05f)								// �F�̉��Z�l
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Attack_Range::CByte_Attack_Range(PRIORITY Priority) : CScene3D(Priority)
{
	m_nCount	= ZERO_INT;
	m_bAddColor = false;
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Attack_Range::~CByte_Attack_Range()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Attack_Range * CByte_Attack_Range::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CByte_Attack_Range�̃|�C���^
	CByte_Attack_Range *pByte_Attack_Range = nullptr;

	// nullcheck
	if (pByte_Attack_Range == nullptr)
	{
		// �������m��
		pByte_Attack_Range = new CByte_Attack_Range;

		// !nullcheck
		if (pByte_Attack_Range != nullptr)
		{
			// ����������
			pByte_Attack_Range->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pByte_Attack_Range;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CByte_Attack_Range::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ������
	CScene3D::Init(pos, size);

	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_RED));

	// �F�ݒ�
	SetColor(COL);

	// ���ߒl�ݒ�
	SetAlpha(true);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Attack_Range::Uninit(void)
{
	// �I������
	CScene3D::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Attack_Range::Update(void)
{
	// �C���N�������g
	m_nCount++;

	// �F
	D3DXCOLOR col = GetColor();

	// false�̏ꍇ
	if (m_bAddColor == false)
	{
		// ���Z
		col.a -= ADD_COL;

		// �ŏ��ȉ��̏ꍇ
		if (col.a < COL_MIN)
		{
			// �ŏ��l��
			col.a = COL_MIN;

			// true��
			m_bAddColor = true;
		}
	}
	// true�̏ꍇ
	if (m_bAddColor == true)
	{
		// ���Z
		col.a += ADD_COL;

		// �ŏ��ȉ��̏ꍇ
		if (col.a > COL_MAX)
		{
			// �ŏ��l��
			col.a = COL_MAX;

			// true��
			m_bAddColor = false;
		}
	}

	// �F�ݒ�
	SetColor(col);

	// 265�ɂȂ�����
	if (m_nCount >= ATTACK_KEY)
	{
		// �����蔻�菈��
		Collision();

		// �I��
		Uninit();
		return;
	}
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Attack_Range::Draw(void)
{
	// �`�揈��
	CScene3D::Draw();
}
//=============================================================================
// �����蔻�菈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Attack_Range::Collision(void)
{
	// �v���C���[�̃|�C���^�擾
	CPlayer * pPlayer = GET_PLAYER_PTR;

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// �ʒu�擾
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

		// �T�C�Y�擾
		D3DXVECTOR3 PlayerSize = pPlayer->GetSize();

		// ��`����
		if (PlayerPos.x - (PlayerSize.x / 2) < pos.x + (size.x / 2) &&
			PlayerPos.x + (PlayerSize.x / 2) > pos.x - (size.x / 2) &&
			PlayerPos.z - (PlayerSize.z / 2) < pos.z + (size.z / 2) &&
			PlayerPos.z + (PlayerSize.z / 2) > pos.z - (size.z / 2))
		{
			// �q�b�g
			pPlayer->Hit(DAMAGE);
		}
	}
}