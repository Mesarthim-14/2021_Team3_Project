#ifndef _BOSS_FADE_H_
#define _BOSS_FADE_H_
//=============================================================================
// �{�X�t�F�[�h [boss_fade.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene2d.h"

//=============================================================================
// �t�F�[�h�N���X
//=============================================================================
class CBoss_Fade : public CScene2D
{
public:
	//=========================================================================
	//�񋓌^��`
	//=========================================================================
	enum FADE_MODE
	{
		FADE_MODE_NONE = 0,	//�����Ȃ����
		FADE_MODE_IN,		//�t�F�[�h�C�����
		FADE_MODE_OUT,		//�t�F�[�h�A�E�g���
		FADE_MODE_MAX
	};

	CBoss_Fade(PRIORITY Priority = PRIORITY_FADE);					// �R���X�g���N�^
	~CBoss_Fade();													// �f�X�g���N�^
	static CBoss_Fade *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ���������֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V�����@
	void Draw(void);												// �`�揈��
	
private:
	FADE_MODE m_FadeMode;						//�t�F�[�h���[�h����p
};
#endif