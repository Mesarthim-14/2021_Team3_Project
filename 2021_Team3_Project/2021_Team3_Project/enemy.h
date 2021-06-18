#ifndef _ENEMY_H_
#define _ENEMY_H_
//=============================================================================
//
// �G�l�~�[�N���X�w�b�_�[ [enemy.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"
#include "modelanime.h"

//=============================================================================
// �G�l�~�[�N���X
//=============================================================================
class CEnemy : public CCharacter
{
public:
	//=============================================================================
	//�@���[�V������Ԃ̗񋓌^
	//=============================================================================
	enum ENEMY_MOTION_STATE
	{
		ENEMY_MOTION_NONE = -1,
		ENEMY_MOTION_IDOL,			// �A�C�h�����[�V����
		ENEMY_MOTION_MAX,			// ���[�V�����ő吔
	};

	CEnemy(PRIORITY Priority = PRIORITY_ENEMY);				// �R���X�g���N�^
	~CEnemy();													// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	void UpdateState(void);										// �v���C���[�̏��
	static CEnemy*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// �N���G�C�g

	virtual void UpdateMotionState(void);						// ���[�V�������
	virtual void Death(void);									// ���񂾂Ƃ��̏���
	virtual void Attack(void);									// �U���̏���
	virtual void Move(void);									// �ړ��̏���

private:
};
#endif