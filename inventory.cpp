#include "DxLib.h"
#include "inventory.h"
#include "global.h"


void MY_GAME_INVENTORY() {

	if (AllKeyState[KEY_INPUT_V] == 1)//Vキーが押されたとき
	{
		GameSceneNow = GAME_SCENE_PLAY;//シーンをプレイ画面にする
	}

	DrawString(0, 0, "所持品画面(プレイ画面に戻るにはMキーを押してください)", GetColor(255, 255, 255));

	return;

}