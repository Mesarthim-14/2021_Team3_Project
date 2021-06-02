//=============================================================================
//
// ���C�u�������� [library.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "library.h"

//=============================================================================
// ������𕪊����A���o���N���X
//=============================================================================
string CLibrary::split(string str, char del, int nNum)
{
	// ���[�J���ϐ��錾
	int first = 0;								// ���Ԗڂ̕�����
	int last = str.find_first_of(del);			// �w��̕����܂ł̐�
	int t_last = str.find_first_of('\t');		// �^�u�܂ł̕�����
	int nCount = 0;								// ������̃J�E���g
	int nCount_t = 0;							// �^�u�̃J�E���g
	string result;								// �Ԃ�������

	// �ϐ�str�̕����񐔂܂�
	while (first < (int)str.size())
	{
		if (last == -1 && t_last == 0)
		{
			int nCount_t = 0;
			
			while (str.find_first_of('\t', nCount_t) == 0)
			{
				// \t�̃J�E���g
				nCount_t++;

			}
			// �w��̔ԍ�����擾
			string subStr(str, first + nCount_t, str.size());

			// �w�肳�ꂽ�������̂Ƃ�
			if (nCount == nNum)
			{
				// �������Ԃ�
				result = subStr;
				break;
			}
		}
		else if (t_last == 0)
		{
			int nNum = t_last;

			while (nNum == 0)
			{
				// \t�̃J�E���g
				nCount_t++;

				nNum = str.find_first_of('\t', nCount_t-1);		// �^�u�܂ł̕�����

			}

			first += nCount_t;
		}

		// �����̔�r
		if (last < t_last)
		{
			// �w��̔ԍ�����擾
			string subStr(str, first, last - first);

			// �w�肳�ꂽ�������̂Ƃ�
			if (nCount == nNum)
			{
				// �������Ԃ�
				result = subStr;
				break;
			}

			// �w��̕�������
			first = last + 1;
		}
		else
		{
			// �w��̔ԍ�����擾
			string subStr(str, first, t_last - first);

			// �w�肳�ꂽ�������̂Ƃ�
			if (nCount == nNum)
			{
				// �������Ԃ�
				result = subStr;
				break;
			}

			// �^�u����������i�߂�
			first = t_last + 1;
		}

		// �����̎擾
		last = str.find_first_of(del, first);		// �w��̕������܂ł̐�
		t_last = str.find_first_of('\t', first);	// �^�u�܂ł̕�����

		// �����̔�r
		if (last < t_last)
		{
			if (last == string::npos)
			{
				last = str.size();
			}
		}
		else
		{
			if (t_last == string::npos)
			{
				t_last = str.size();
			}
		}

		// �񐔂̃J�E���g
		nCount++;
	}

	return result;
}
