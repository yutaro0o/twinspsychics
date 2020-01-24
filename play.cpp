#include "DxLib.h"
#include "play.h"
#include "global.h"
#include "mydef.h"
#include "map.h"
#include "player.h"
#include "key.h"

void MY_GAME_PLAY() {
	if (CheckHitKey(KEY_INPUT_BACK) == 1)//バックスペースキーが押されていた時
	{
		GameSceneNow = GAME_SCENE_END;//シーンをプレイ画面にする
	}
	if (CheckHitKey(KEY_INPUT_V) == 1)//Vキーが押されたとき
	{
		GameSceneNow = GAME_SCENE_INVENTORY;//シーンを所持品画面にする
	}

	if (MY_PLAY_CHECK_GAME_END() == TRUE)
	{
		GameSceneNow = (int)GAME_SCENE_END;//シーンをエンド画面にする
	}
	else
	{
		MY_PLAY_PLAYER_OPERATION();//プレイヤー1の操作
		MY_PLAY_PLAYER_OPERATION2();//プレイヤー2の操作
	}

	MY_PLAY_MAP_DRAW();			//マップを描画

	MY_PLAY_PLAYER_DRAW();		//プレイヤーを描画
	MY_PLAY_PLAYER_DRAW2();     //プレイヤー2を描画

	DrawString(0, 0, "プレイ画面(エンド画面に行くにはバックスペースキーを押してください)", GetColor(255, 255, 255));
	DrawString(0, 20, "　　　　　(所持品画面に行くにはVキーを押してください)", GetColor(255, 255, 255));

	return;

}

//########## ゲームエンドか判定する関数 ##########
BOOL MY_PLAY_CHECK_GAME_END(VOID)
{
	//プレイヤーの位置は、プレイヤーの中心
	int PlayerToMapNumY = (Myplayer.Y + Myplayer.C_Height) / MAP_SIZE_YOKO;
	int PlayerToMapNumX = (Myplayer.MoveDist + Myplayer.C_Width) / MAP_SIZE_TATE;
	int PlayerToMapNumY2 = (Myplayer2.Y + Myplayer2.C_Height) / MAP_SIZE_YOKO;
	int PlayerToMapNumX2 = (Myplayer2.MoveDist + Myplayer2.C_Width) / MAP_SIZE_TATE;

	if (PlayerToMapNumX < 0 || PlayerToMapNumX > MAP_YOKO_NUM) { return FALSE; }	//マップの配列外でゴールになるバグを解消
	if (PlayerToMapNumY < 0 || PlayerToMapNumY > MAP_TATE_NUM) { return FALSE; }	//マップの配列外でゴールになるバグを解消
	if (PlayerToMapNumX2 < 0 || PlayerToMapNumX2 > MAP_YOKO_NUM) { return FALSE; }	//マップの配列外でゴールになるバグを解消
	if (PlayerToMapNumY2 < 0 || PlayerToMapNumY2 > MAP_TATE_NUM) { return FALSE; }	//マップの配列外でゴールになるバグを解消


	//プレイヤーがゴールのモノと接触したとき
	if (MapData[PlayerToMapNumY][PlayerToMapNumX] == MapGoalKind[0]
		&& MapData[PlayerToMapNumY2][PlayerToMapNumX2] == MapGoalKind[0])
	{
		return TRUE;
	}

	return FALSE;	//ゲーム続行
}