#include "DxLib.h"
#include "end.h"
#include "global.h"


void MY_GAME_END() {
	if (CheckHitKey(KEY_INPUT_DELETE) == 1)//デリートキーが押されていた時
	{
		GameSceneNow = GAME_SCENE_TITLE;
	}

	DrawString(0, 0, "エンド画面(デリートキーを押して下さい)", GetColor(255, 255, 255));

	return;
}