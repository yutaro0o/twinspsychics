#include "DxLib.h"
#include "key.h"
#include "global.h"

void MY_ALL_KEYDOWN_UPDATE() {

	char TempKey[256];//�ꎞ�I�Ɍ��݂̃L�[�̓��͏�Ԃ��i�[����

	GetHitKeyStateAll(TempKey);//�S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)//������Ă���L�[�̃L�[�R�[�h�������Ă���Ƃ�
		{
			AllKeyState[i]++;//������Ă���
		}
		else
		{
			AllKeyState[i] = 0; //������Ă��Ȃ�
		}
	}
	return;

}