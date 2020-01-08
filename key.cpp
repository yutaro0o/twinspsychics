#include "DxLib.h"
#include "key.h"
#include "global.h"

void MY_ALL_KEYDOWN_UPDATE() {

	char TempKey[256];//一時的に現在のキーの入力状態を格納する

	GetHitKeyStateAll(TempKey);//全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)//押されているキーのキーコードを押しているとき
		{
			AllKeyState[i]++;//押されている
		}
		else
		{
			AllKeyState[i] = 0; //押されていない
		}
	}
	return;

}