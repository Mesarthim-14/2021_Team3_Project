#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//=============================================================================
//
// �e�N�X�`���̊Ǘ��w�b�_�[ [texture.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
//�N���X�錾
//=============================================================================
class CTexture
{
public:
	// �e�N�X�`���̎��
	enum TEXTURE_TYPE_NUM
	{
		TEXTURE_TYPE_NUM_NONE = -1,		// �����l
		TEXTURE_TYPE_NUM_NORMAL,		// �ʏ�e�N�X�`��
		TEXTURE_TYPE_NUM_SEPARATE,		// �����e�N�X�`��
		TEXTURE_TYPE_NUM_VOLUME,		// �{�����[���e�N�X�`��
		TEXTURE_TYPE_NUM_CUBE,			// �L���[�u�e�N�X�`��
		TEXTURE_TYPE_NUM_MAX			// �ő�l
	};

	// �e�N�X�`���̔ԍ��̗񋓌^
	enum TEXTURE_TYPE
	{
		TEXTURE_NUM_NONE = -1,		// �����l
		TEXTURE_NUM_FLOOR,			// �n��
		TEXTURE_NUM_ATTACK_POINT,	// �U���n�_
		TEXTURE_NUM_ATTACK_ARROW,	// �U���n�_�̖��
		TEXTURE_NUM_BYTE,			// ���݂�
		TEXTURE_NUM_MAX
	};

	// �A�j���[�V�������s���e�N�X�`���̗񋓌^
	enum SEPARATE_TEX_TYPE
	{
		SEPARATE_TEX_NONE = -1,			// �����l
		SEPARATE_TEX_SHARP,				// �s���G�t�F�N�g
		SEPARATE_TEX_MAX				// �ő�l
	};

	// �A�j���[�V�������s���e�N�X�`���̍\���̏��
	struct SEPARATE_TEX_INFO
	{
		LPDIRECT3DTEXTURE9 pSeparateTexture;		// �����e�N�X�`���ւ̃|�C���^
		SEPARATE_TEX_TYPE type;						// �e�N�X�`���̎��
		D3DXVECTOR2 m_TexInfo;						// �e�N�X�`���̕������A����
		bool bLoop;									// ���[�v���邩
	};

	// �{�����[���e�N�X�`���̗񋓌^
	enum VOLUME_TEX_TYPE
	{
		VOLUME_TEX_NONE = -1,		// �����l
		VOLUME_TEX_NOISE,			// ���ʂ̃m�C�Y
		VOLUME_TEX_MAX				// �ő�l
	};

	// �L���[�u�e�N�X�`���̗񋓌^
	enum CUBE_TEX_TYPE
	{
		CUBE_TEX_NONE = -1,			// �����l
		CUBE_TEX_OCEAN,				// �C
		CUBE_TEX_MAX				// �ő�l
	};

	CTexture();		// �R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

	static CTexture *Create(void);											// �C���X�^���X����
	HRESULT SetTextureName(void);											// ����������
	void LoadAll(void);														// �S�Ẵ��[�h
	void UnLoadAll(void);													// �S�ẴA�����[�h

	// �ʏ�e�N�X�`��
	HRESULT NormalTexLoad(void);											// �e�N�X�`�����[�h
	void NormalTexUnLoad(void);												// �e�N�X�`���A�����[�h
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE Tex_Type);					// �e�N�X�`���̏��

	// �����e�N�X�`��
	HRESULT SeparateTexLoad(void);											// �����e�N�X�`�����[�h
	void SeparateTexUnLoad(void);											// �����e�N�X�`���A�����[�h
	LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type);	// �����e�N�X�`�����
	D3DXVECTOR2 GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type);			// �����e�N�X�`���@UV�̖����擾
	bool GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type);					// ���[�v���邩

	// �{�����[���e�N�X�`��
	HRESULT VolumeTexLoad(void);											// �{�����[���e�N�X�`�����[�h
	void VolumeTexUnLoad(void);												// �{�����[���e�N�X�`���A�����[�h
	LPDIRECT3DVOLUMETEXTURE9 GetVolumeTexture(VOLUME_TEX_TYPE Tex_Type);	// �{�����[���e�N�X�`���̏��

	// �L���[�u�e�N�X�`��
	HRESULT CubeTexLoad(void);												// �L���[�u�e�N�X�`�����[�h
	void CubeTexUnLoad(void);												// �L���[�u�e�N�X�`���A�����[�h
	LPDIRECT3DCUBETEXTURE9 GetCubeTexture(CUBE_TEX_TYPE Tex_Type);			// �L���[�u�e�N�X�`���̏��

private:
	LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_NUM_MAX];						// �e�N�X�`���̃|�C���^
	SEPARATE_TEX_INFO m_apSeparateTexture[SEPARATE_TEX_MAX] =
	{
		nullptr, CTexture::SEPARATE_TEX_SHARP, D3DXVECTOR2(5, 5), false,
	};
	LPDIRECT3DVOLUMETEXTURE9 m_pVolumeTexture[VOLUME_TEX_MAX];				// �{�����[���e�N�X�`��
	LPDIRECT3DCUBETEXTURE9 m_pCubeTexture[CUBE_TEX_MAX];					// �L���[�u�e�N�X�`��
	vector<string> m_aTexFileName[TEXTURE_TYPE_NUM_MAX];					// �e�N�X�`���̖��O
};
#endif
