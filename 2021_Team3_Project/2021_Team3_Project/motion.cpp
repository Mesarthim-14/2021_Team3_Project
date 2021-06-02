//=============================================================================
//
// ���[�V�����N���X [motion.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "motion.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMotion::CMotion()
{
	m_nKey = 0;
	m_apKeyInfo = nullptr;
	m_nMotionState = 0;
	m_nNumKey = 0;					// �L�[�̑���
	m_nCountMotion = 0;				// ���[�V�����J�E���^�[
	m_nMotionInterval = 0;			// ���[�V�����̃C���^�[�o��
	m_nKey = 0;						// ���݃L�[��No
	m_bMotionPlaing = false;		// ���[�V�����̍Đ�
	m_diffPos = ZeroVector3;		// �ύX���W
	m_diffRot = ZeroVector3;		// �ύX�p�x
	m_Motion.clear();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMotion::~CMotion()
{
	m_Motion.clear();
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CMotion * CMotion::Create(string cFileName)
{
	//�K�w���f���N���X�̃|�C���^�ϐ�
	CMotion *pMotion = nullptr;

	//�C���X�^���X����
	pMotion = new CMotion;

	// nullcheck
	if (pMotion != nullptr)
	{
		// �t�@�C���f�[�^�ǂݍ���
		pMotion->ReadMotionFile(cFileName);
	}
	else
	{
		return nullptr;
	}

	return pMotion;
}

//=============================================================================
// ���[�V�����̍X�V����
//=============================================================================
void CMotion::UpdateMotion(int nMaxParts, vector<CModelAnime*> apModelAnime)
{
	//���݃L�[���ő�L�[�������̏ꍇ
	if (m_nKey < m_Motion[m_nMotionState].nNumKey)
	{
		for (int nCntModel = 0; nCntModel < nMaxParts; nCntModel++)
		{
			// !nullcheck
			if (apModelAnime.at(nCntModel) != nullptr)
			{
				D3DXVECTOR3 startPos = apModelAnime.at(nCntModel)->GetPosAnime();
				D3DXVECTOR3 startRot = apModelAnime.at(nCntModel)->GetRotAnime();

				//	if (m_nCountMotion == 0)
				if (m_Motion[m_nMotionState].bLoop == false)
				{
					if (m_nKey == 0)
					{
						m_diffPos.x = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fPosX - startPos.x) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffPos.y = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fPosY - startPos.y) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffPos.z = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fPosZ - startPos.z) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;

						// 1�t���[��������̍X�V�l = (�I�_����-�J�n����) / �t���[����
						m_diffRot.x = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fRotX - startRot.x) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffRot.y = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fRotY - startRot.y) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffRot.z = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fRotZ - startRot.z) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
					}
					else
					{
						if ((m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.size() >= (size_t)m_nKey))
						{
							// 1�t���[��������̍X�V�l = (�I�_�ʒu-�J�n�ʒu) / �t���[����
							m_diffPos.x = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fPosX - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey.at(nCntModel).fPosX) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
							m_diffPos.y = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fPosY - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey.at(nCntModel).fPosY) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
							m_diffPos.z = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fPosZ - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey.at(nCntModel).fPosZ) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;

							// 1�t���[��������̍X�V�l = (�I�_����-�J�n����) / �t���[����
							m_diffRot.x = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fRotX - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey.at(nCntModel).fRotX) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
							m_diffRot.y = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fRotY - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey.at(nCntModel).fRotY) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
							m_diffRot.z = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fRotZ - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey.at(nCntModel).fRotZ) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						}
					}
				}
				else
				{
					// 1�t���[��������̍X�V�l = (�I�_�ʒu-�J�n�ʒu) / �t���[����
					m_diffPos.x = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fPosX - startPos.x) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
					m_diffPos.y = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fPosY - startPos.y) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
					m_diffPos.z = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fPosZ - startPos.z) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;

					// 1�t���[��������̍X�V�l = (�I�_����-�J�n����) / �t���[����
					m_diffRot.x = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fRotX - startRot.x) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
					m_diffRot.y = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fRotY - startRot.y) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
					m_diffRot.z = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fRotZ - startRot.z) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
				}

				// ���W�΂��ݒ�
				D3DXVECTOR3 setPos, setRot;

				// ���W�̐ݒ�
				setPos.x = m_diffPos.x + startPos.x;
				setPos.y = m_diffPos.y + startPos.y;
				setPos.z = m_diffPos.z + startPos.z;

				// �p�x�̐ݒ�
				setRot.x = m_diffRot.x + startRot.x;
				setRot.y = m_diffRot.y + startRot.y;
				setRot.z = m_diffRot.z + startRot.z;

				//�ʒu�̐ݒ�
				apModelAnime.at(nCntModel)->SetPosAnime(setPos);

				//�����̐ݒ�
				apModelAnime.at(nCntModel)->SetRotAnime(setRot);
			}
		}

		//���[�V�����J�E���^�[�̉��Z
		m_nCountMotion++;

		//���݃L�[�̍Đ��t���[���ɒB������
		if (m_nCountMotion >= m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame)
		{
			//�L�[���P�i�߂�
			m_nKey++;
			m_nCountMotion = 0;
		}
	}
	else
	{
		//���[�v����Ȃ�
		if (m_Motion[m_nMotionState].bLoop == true)
		{
			m_nKey = 0;
			m_nCountMotion = 0;
		}
		else
		{
			// �A�C�h�����[�V�����ɖ߂�
			SetMotion(0, nMaxParts, apModelAnime);
		}
	}
}

//=============================================================================
// ���[�V�����t�@�C���ǂݍ���
//=============================================================================
HRESULT CMotion::ReadMotionFile(string cFileName)
{
	FILE *pFile = nullptr;		//FILE�|�C���^
	char aHeadData[1024];
	char aModeName[1024];
	int nModelIndex = 0;	// ���f���̃C���f�b�N�X

	// �t�@�C���I�[�v��
	pFile = fopen(cFileName.c_str(), "r");

	if (pFile != nullptr)
	{
		do
		{
			//���ǂݍ���Ń��[�h���𒊏o
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aModeName);

			//���[�V�����Z�b�g
			if (strcmp(aModeName, "MOTIONSET") == 0)
			{
				// ���[�V�������̍\����
				Motion_Info Motion = {};

				if (m_Motion.size() == 7)
				{
					int nNum = 0;
				}
				//END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
				while (strcmp(aModeName, "END_MOTIONSET") != 0)
				{
					//���ǂݍ���Ń��[�h���𒊏o
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aModeName);

					//���[�v���̎擾
					if (strcmp(aModeName, "LOOP") == 0)
					{
						sscanf(aHeadData, "%*s %*s %d", (int*)&Motion.bLoop);
					}

					//�L�[���̎擾
					if (strcmp(aModeName, "NUM_KEY") == 0)
					{
						sscanf(aHeadData, "%*s %*s %d", (int*)&Motion.nNumKey);
					}

					if (strcmp(aModeName, "KEYSET") == 0)
					{
						// �L�[���̍\����
						KEY_INFO KeyInfo = {};

						//END_KEYSET�ɂȂ�܂ŌJ��Ԃ�
						while (strcmp(aModeName, "END_KEYSET") != 0)
						{
							//���ǂݍ���Ń��[�h���𒊏o
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aModeName);

							//�t���[�����̎擾
							if (strcmp(aModeName, "FRAME") == 0)
							{
								sscanf(aHeadData, "%*s %*s %d", &KeyInfo.nFrame);
							}

							//�e�L�[�̃I�t�Z�b�g���̎擾
							if (strcmp(aModeName, "KEY") == 0)
							{
								// �L�[�̍\����
								KEY key = {};

								//END_KEY�ɂȂ�܂ŌJ��Ԃ�
								while (strcmp(aModeName, "END_KEY") != 0)
								{
									//���ǂݍ���Ń��[�h���𒊏o
									fgets(aHeadData, sizeof(aHeadData), pFile);
									sscanf(aHeadData, "%s", aModeName);

									//�ʒu�̎擾
									if (strcmp(aModeName, "POS") == 0)
									{
										sscanf(aHeadData, "%*s %*s %f %f %f",
											&key.fPosX,
											&key.fPosY,
											&key.fPosZ);
									}

									//�����̎擾
									if (strcmp(aModeName, "ROT") == 0)
									{
										sscanf(aHeadData, "%*s %*s %f %f %f",
											&key.fRotX,
											&key.fRotY,
											&key.fRotZ);
									}
								}

								// �L�[�̎擾
								KeyInfo.aKey.push_back(key);
							}
						}

						// �L�[���̒ǉ�
						Motion.aKeyInfo.push_back(KeyInfo);
					}
				}

				// ���[�V�������擾
				m_Motion.push_back(Motion);
			}

		} while (strcmp(aModeName, "END_SCRIPT") != 0);

		//�t�@�C���N���[�Y
		fclose(pFile);

		return S_OK;
	}
	else
	{
		//���s�����ꍇ���b�Z�[�W�{�b�N�X��\��
		MessageBox(nullptr, "���[�V�����t�@�C�����J���̂Ɏ��s���܂���", "�x��", MB_OK | MB_ICONEXCLAMATION);

		return	E_FAIL;
	}
}

//=============================================================================
// ���[�V�����̐ݒ�
//=============================================================================
void CMotion::SetMotion(int nMotion, int nMaxParts, vector<CModelAnime*> apModelAnime)
{
	// ���̃��[�V�����ƈ������
	if (m_nMotionState != nMotion)
	{
		// �l�̏�����
		m_nKey = 0;
		m_nCountMotion = 0;
		m_nMotionInterval = 0;
		D3DXVECTOR3 pos, rot;
		m_nMotionState = nMotion;
		m_bMotionPlaing = true;

		for (size_t nCntModel = 0; nCntModel < apModelAnime.size(); nCntModel++)
		{
			if (apModelAnime.at(nCntModel) != nullptr)
			{
				//�J�n�ʒu
				pos.x = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fPosX;
				pos.y = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fPosY;
				pos.z = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fPosZ;

				//�J�n����
				rot.x = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fRotX;
				rot.y = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fRotY;
				rot.z = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey.at(nCntModel).fRotZ;

				//�ʒu�̐ݒ�
				apModelAnime.at(nCntModel)->SetPosAnime(pos);

				//�����̐ݒ�
				apModelAnime.at(nCntModel)->SetRotAnime(rot);
			}
		}
	}
}