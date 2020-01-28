#include "DxLib.h"
#include "end.h"
#include "global.h"
#include "map.h"
#include "mydef.h"

void MY_GAME_END() {
	if (AllKeyState[KEY_INPUT_RETURN] == 1)//エンターキーが押されていた時
	{
		GameSceneNow = GAME_SCENE_TITLE;
	}

	DrawString(0, 0, "エンド画面(デリートキーを押して下さい)", GetColor(255, 255, 255));

	return;
}