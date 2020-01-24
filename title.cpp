#include "DxLib.h"
#include "title.h"
#include "global.h"
#include "mydef.h"
#include "map.h"
#include "player.h"

void MY_GAME_TITLE() {
	if (CheckHitKey(KEY_INPUT_RETURN) == 1)//エンターキーが押されていた時
	{
		if (MY_PLAY_INIT() == TRUE)
		{
			for (int tate = 0; tate < MAP_TATE_NUM; tate++)
			{
				for (int yoko = 0; yoko < MAP_YOKO_NUM; yoko++)
				{
					MapData[tate][yoko] = MapData_Init[tate][yoko];	//マップをもとに戻す
				}
			}
			GameSceneNow = GAME_SCENE_PLAY;//シーンをプレイ画面にする
		}
	}
	if (CheckHitKey(KEY_INPUT_V) == 1)//Vキーが押されたとき
	{
		SetBackgroundColor(0, 0, 0);
		GameSceneNow = GAME_SCENE_METHOD;//シーンを操作説明画面にする
	}
	DrawBox(0, 0, 800, 450, GetColor(255, 255, 255), TRUE);

	DrawRotaGraph(GAME_WIDTH / 2, GAME_HEIGHT / 2, 0.8, 0.0, LoadGraph(TITLE_LOGO), FALSE);

	DrawString(0, 0, "タイトル画面(プレイ画面に進むにはエンターキーを押してください)", GetColor(0, 0, 255));
	DrawString(0, 20, "　　　　　　(操作説明画面に進むにはVキーを押してください)", GetColor(0, 0, 255));

	return;
}