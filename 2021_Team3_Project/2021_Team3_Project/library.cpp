//=============================================================================
//
// ライブラリ処理 [library.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "library.h"

//=============================================================================
// 文字列を分割し、取り出すクラス
//=============================================================================
string CLibrary::split(string str, char del, int nNum)
{
	// ローカル変数宣言
	int first = 0;								// 何番目の文字か
	int last = str.find_first_of(del);			// 指定の文字までの数
	int t_last = str.find_first_of('\t');		// タブまでの文字数
	int nCount = 0;								// 文字列のカウント
	int nCount_t = 0;							// タブのカウント
	string result;								// 返す文字列

	// 変数strの文字列数まで
	while (first < (int)str.size())
	{
		if (last == -1 && t_last == 0)
		{
			int nCount_t = 0;
			
			while (str.find_first_of('\t', nCount_t) == 0)
			{
				// \tのカウント
				nCount_t++;

			}
			// 指定の番号から取得
			string subStr(str, first + nCount_t, str.size());

			// 指定された分割数のとき
			if (nCount == nNum)
			{
				// 文字列を返す
				result = subStr;
				break;
			}
		}
		else if (t_last == 0)
		{
			int nNum = t_last;

			while (nNum == 0)
			{
				// \tのカウント
				nCount_t++;

				nNum = str.find_first_of('\t', nCount_t-1);		// タブまでの文字数

			}

			first += nCount_t;
		}

		// 距離の比較
		if (last < t_last)
		{
			// 指定の番号から取得
			string subStr(str, first, last - first);

			// 指定された分割数のとき
			if (nCount == nNum)
			{
				// 文字列を返す
				result = subStr;
				break;
			}

			// 指定の文字数分
			first = last + 1;
		}
		else
		{
			// 指定の番号から取得
			string subStr(str, first, t_last - first);

			// 指定された分割数のとき
			if (nCount == nNum)
			{
				// 文字列を返す
				result = subStr;
				break;
			}

			// タブ分文字数を進める
			first = t_last + 1;
		}

		// 距離の取得
		last = str.find_first_of(del, first);		// 指定の文字数までの数
		t_last = str.find_first_of('\t', first);	// タブまでの文字数

		// 距離の比較
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

		// 回数のカウント
		nCount++;
	}

	return result;
}
