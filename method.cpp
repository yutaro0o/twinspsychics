#include "DxLib.h"
#include "method.h"
#include "global.h"
#include "mydef.h"


void MY_GAME_METHOD() {
	if (AllKeyState[KEY_INPUT_V] == 1)//V�L�[��������Ă�����
	{
		GameSceneNow = GAME_SCENE_TITLE;//�^�C�g����ʂɖ߂�
	}

	DrawRotaGraph(GAME_WIDTH / 2, GAME_HEIGHT / 2, 0.6, 0.0, LoadGraph("images/material/method.jpg"), FALSE);
	
	return;
}