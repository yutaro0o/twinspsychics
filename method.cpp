#include "DxLib.h"
#include "method.h"
#include "global.h"



void MY_GAME_METHOD() {
	if (AllKeyState[KEY_INPUT_M] != 0)//Mキーが押されていた時
	{
		GameSceneNow = GAME_SCENE_TITLE;//タイトル画面に戻る
	}

	DrawString(0, 0, "操作説明画面(タイトル画面に戻るにはMキーを押して下さい)", GetColor(255, 255, 255));

	return;
}