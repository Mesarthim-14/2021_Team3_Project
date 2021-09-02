//=============================================================================
// ���݂��G�t�F�N�g [byte_effect.cpp]
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
#include "byte_effect.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define MOVE_VALUE	(D3DXVECTOR3(0.0f,30.0f,0.0f))					// �ړ���
#define COL			(D3DXCOLOR(1.0f,0.3f,0.0f,1.0f))				// �F
#define UP_POS		(D3DXVECTOR3(pos.x,pos.y + size.y,pos.z))		// �ʒu
#define DOWN_POS	(D3DXVECTOR3(pos.x,pos.y - size.y,pos.z))		// �ʒu
#define UP_ROT		(D3DXVECTOR3(0.0f,0.0f,D3DXToRadian(0.0f)))		// ����
#define DOWN_ROT	(D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)))	// ����
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Effect::CByte_Effect(PRIORITY Priority) : CBillboard(Priority)
{
	m_SavePos	= ZeroVector3;
	m_Type		= TYPE_NONE;
	bEndByte	= false;
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Effect::~CByte_Effect()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CByte_Effect * CByte_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// CByte_Effect�̃|�C���^
	CByte_Effect *pByte_Effect = nullptr;

	// nullcheck
	if (pByte_Effect == nullptr)
	{
		// �������m��
		pByte_Effect = new CByte_Effect;

		// !nullcheck
		if (pByte_Effect != nullptr)
		{
			// ���
			pByte_Effect->m_Type = type;

			// ����������
			pByte_Effect->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pByte_Effect;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CByte_Effect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �ʒu
	D3DXVECTOR3 Pos = ZeroVector3;

	// UP�̏ꍇ
	if (m_Type == TYPE_UP)
	{
		// ���
		Pos = UP_POS;
	}
	// DOWN�̏ꍇ
	if (m_Type == TYPE_DOWN)
	{
		// ���
		Pos = DOWN_POS;
	}

	// ����������
	CBillboard::Init(Pos, size);

	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_BYTE));

	// �ʒu�ۑ�
	m_SavePos = pos;

	// ����
	D3DXVECTOR3 rot;

	// UP�̏ꍇ
	if (m_Type == TYPE_UP)
	{
		// ����
		rot = UP_ROT;
	}
	// DOWN�̏ꍇ
	if (m_Type == TYPE_DOWN)
	{
		// ����
		rot = DOWN_ROT;
	}

	// �����ݒ�
	SetRot(rot);

	// �F�ݒ�
	SetColor(COL);

	// ���Z����
	SetBlend(true);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Effect::Uninit(void)
{
	// �I������
	CBillboard::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Effect::Update(void)
{
	// �X�V����
	CBillboard::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// UP�̏ꍇ
	if (m_Type == TYPE_UP)
	{
		// �ʒu��pos.y�ȉ��̏ꍇ
		if (pos.y >= m_SavePos.y)
		{
			// �ړ�
			Move();
		}
		else
		{
			// true��
			bEndByte = true;
		}
	}
	// DOWN�̏ꍇ
	if (m_Type == TYPE_DOWN)
	{

		// �ʒu��pos.y�ȉ��̏ꍇ
		if (pos.y <= m_SavePos.y)
		{
			// �ړ�
			Move();
		}
		else
		{
			// true��
			bEndByte = true;
		}
	}
	// true�̏ꍇ
	if (bEndByte == true)
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
void CByte_Effect::Draw(void)
{
	// �`�揈��
	CBillboard::Draw();
}
//=============================================================================
// �G�t�F�N�g���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Effect::CrateEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �㐶��
	Create(pos, size, TYPE_UP);

	// ������
	Create(pos, size, TYPE_DOWN);
}
//=============================================================================
// �ړ������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CByte_Effect::Move(void)
{
	// �ړ�
	D3DXVECTOR3 move = ZeroVector3;

	// UP�̏ꍇ
	if (m_Type == TYPE_UP)
	{
		// �ړ�
		move.y = -MOVE_VALUE.y;
	}
	// DOWN�̏ꍇ
	if (m_Type == TYPE_DOWN)
	{
		// �ړ�
		move.y = MOVE_VALUE.y;
	}

	// �ړ�
	SetMove(move);
}