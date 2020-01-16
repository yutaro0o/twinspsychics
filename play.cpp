#include "DxLib.h"
#include "play.h"
#include "global.h"
#include "mydef.h"
#include "map.h"

void MY_GAME_PLAY() {
	if (CheckHitKey(KEY_INPUT_BACK) == 1)//エンターキーが押されていた時
	{
		GameSceneNow = GAME_SCENE_END;//シーンをプレイ画面にする
	}
	if (CheckHitKey(KEY_INPUT_V) == 1)//Vキーが押されたとき
	{
		GameSceneNow = GAME_SCENE_INVENTORY;//シーンを所持品画面にする
	}

	MY_PLAY_MAP_DRAW();

	DrawString(0, 0, "プレイ画面(エンド画面に行くにはバックスペースキーを押してください)", GetColor(255, 255, 255));
	DrawString(0, 20, "　　　　　(所持品画面に行くにはVキーを押してください)", GetColor(255, 255, 255));

	return;

}