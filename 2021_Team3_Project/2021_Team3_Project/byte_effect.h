//=============================================================================
// �{�X���݂��G�t�F�N�g [byte_effect.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _BYTE_EFFECT_H_
#define _BYTE_EFFECT_H_
//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "scene3d.h"
//=============================================================================
// �}�b�v�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CByte_Effect : public CScene3D
{
public:
	// �񋓌^
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_UP,
		TYPE_DOWN,
		TYPE_MAX
	}TYPE;
	CByte_Effect(PRIORITY Priority = PRIORITY_3D_UI);											// �R���X�g���N�^
	~CByte_Effect();																			// �f�X�g���N�^
	static CByte_Effect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, TYPE type);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);											// ����������
	void Uninit(void);																			// �I������
	void Update(void);																			// �X�V����
	void Draw(void);																			// �`�揈��

	static void CrateEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXVECTOR3 rot);					// �G�t�F�N�g���������֐�
private:
	void Move(void);	// �ړ������֐�

	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3 m_SavePos;	// �ʒu�ۑ��p
	TYPE m_Type;			// ���
	bool bEndByte;			// �I��
};
#endif