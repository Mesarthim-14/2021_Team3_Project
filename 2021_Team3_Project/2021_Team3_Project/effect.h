//=============================================================================
//
// �p�[�e�B�N������ [particle.h]
// Author : ���F �N
// �X�V�� : 2022/03/04
//
//=============================================================================
#ifndef effect_H_
#define effect_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "billboard.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_PARTICLE (400)

//=============================================================================
//�p�[�e�B�N���N���X��`
//=============================================================================
class CEffect :public CBillboard
{
public:
	enum EFFECT_TYPE	//�p�[�e�B�N�����
	{
		EFFECT_TYPE_NONE = -1,
		EFFECT_TYPE_1,
		EFFECT_TYPE_2,
		EFFECT_TYPE_3,
		EFFECT_TYPE_4,
		EFFECT_TYPE_5,
		EFFECT_TYPE_MAX
	};

	enum EFFECT_TEXTURE	//�p�[�e�B�N���摜���
	{
		EFFECT_TEXTURE_NONE = -1,
		EFFECT_TEXTURE_1,
		EFFECT_TEXTURE_2,
		EFFECT_TEXTURE_3,
		EFFECT_TEXTURE_4,
		EFFECT_TEXTURE_MAX
	};

	CEffect();		//�R���X�g���N�^
	~CEffect();		//�f�X�g���N�^

	//�N���G�C�g�֐�
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, EFFECT_TYPE type, int Life);
	void Smoke(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, EFFECT_TYPE type, int Life);
	void WoodExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, EFFECT_TYPE type, int Life);
	void Splash(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, EFFECT_TYPE type, int Life);
	void Explosion(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, EFFECT_TYPE type, int Life);
	void Wave(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, EFFECT_TYPE type, int Life);

	static HRESULT Load(void);						//�e�N�X�`���ǂݍ���
	static void Unload(void);						//�e�N�X�`���̔j��

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, EFFECT_TYPE type, D3DXCOLOR col, int Life);//�������֐�
	void Update(void);								//�X�V�֐�
	void Uninit(void);								//�I���֐�
	void Draw(void);								//�`��֐�


private:
	static LPDIRECT3DTEXTURE9 m_apTexture[EFFECT_TEXTURE_MAX];	//�ǂݍ��ރe�N�X�`��
	D3DXMATRIX	mtxWorld;						//���[���h�v�Z�p
	D3DXVECTOR3	m_Rot;							//�v���C���[�̉�]
	bool m_bLoop;								//�A�j���[�V�������[�v
	EFFECT_TYPE m_nType;						//���
};

#endif // !PARTICLE_H_
