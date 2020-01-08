#include "DxLib.h"
#include "title.h"
#include "global.h"
#include "mydef.h"

void MY_GAME_TITLE() {
	if (AllKeyState[KEY_INPUT_RETURN] != 0)//エンターキーが押されていた時
	{
		GameSceneNow = GAME_SCENE_PLAY;//シーンをプレイ画面にする
	}
	if (AllKeyState[KEY_INPUT_V] != 0)//Vキーが押されたとき
	{
		SetBackgroundColor(0, 0, 0);
		GameSceneNow = GAME_SCENE_METHOD;//シーンを操作説明画面にする
	}

	DrawString(0, 0, "タイトル画面(プレイ画面に進むにはエンターキーを押してください)", GetColor(255, 255, 255));
	DrawString(0, 20, "　　　　　　(操作説明画面に進むにはVキーを押してください)", GetColor(255, 255, 255));

	LoadGraphScreen(50, 0, TITLE_LOGO, FALSE);

	return;
}