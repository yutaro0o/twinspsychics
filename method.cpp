#include "DxLib.h"
#include "method.h"
#include "global.h"



void MY_GAME_METHOD() {
	if (AllKeyState[KEY_INPUT_M] != 0)//M�L�[��������Ă�����
	{
		GameSceneNow = GAME_SCENE_TITLE;//�^�C�g����ʂɖ߂�
	}

	DrawString(0, 0, "����������(�^�C�g����ʂɖ߂�ɂ�M�L�[�������ĉ�����)", GetColor(255, 255, 255));

	return;
}