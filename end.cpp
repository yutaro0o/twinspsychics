#include "DxLib.h"
#include "end.h"
#include "global.h"
#include "map.h"
#include "mydef.h"

void MY_GAME_END() {
	if (CheckHitKey(KEY_INPUT_DELETE) == 1)//�f���[�g�L�[��������Ă�����
	{
		GameSceneNow = GAME_SCENE_TITLE;
	}

	DrawString(0, 0, "�G���h���(�f���[�g�L�[�������ĉ�����)", GetColor(255, 255, 255));

	return;
}