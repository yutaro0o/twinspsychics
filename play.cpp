#include "DxLib.h"
#include "play.h"
#include "global.h"
#include "mydef.h"
#include "map.h"
#include "player.h"
#include "key.h"

//プレイヤーの位置は、プレイヤーの中心
int PlayerToMapNumY;
int PlayerToMapNumX;
int PlayerToMapNumY2;
int PlayerToMapNumX2;

void MY_GAME_PLAY() {
	if (AllKeyState[KEY_INPUT_RETURN] == 1)//エンターキーが押されていた時
	{
		GameSceneNow = GAME_SCENE_TITLE;//シーンをタイトル画面にする
	}
	//if (AllKeyState[KEY_INPUT_V] == 1)//Vキーが押されたとき
	//{
	//	GameSceneNow = GAME_SCENE_INVENTORY;//シーンを所持品画面にする
	//}

	if (MY_PLAY_CHECK_GAME_END() == TRUE)
	{
		GameSceneNow = (int)GAME_SCENE_END;//シーンをエンド画面にする
	}
	else
	{
		MY_PLAY_PLAYER_OPERATION();//プレイヤー1の操作
	}

	MY_PLAY_MAP_DRAW();			//マップを描画

	MY_PLAY_PLAYER_DRAW();		//プレイヤーを描画
	MY_PLAY_PLAYER_DRAW2();     //プレイヤー2を描画

	DrawString(0, 0, "プレイ画面(エンド画面に行くにはバックスペースキーを押してください)", GetColor(0, 0, 255));
	//DrawString(0, 20, "　　　　　(所持品画面に行くにはVキーを押してください)", GetColor(0, 0, 255));
	DrawFormatString(35, 40, GetColor(0, 0, 255), "X:%d", PlayerToMapNumX);
	DrawFormatString(35, 60, GetColor(0, 0, 255), "X:%d", PlayerToMapNumY);
	DrawFormatString(450, 40, GetColor(0, 0, 255), "X:%d", PlayerToMapNumX2);
	DrawFormatString(450, 60, GetColor(0, 0, 255), "X:%d", PlayerToMapNumY2);

	return;

}

//########## ゲームエンドか判定する関数 ##########
BOOL MY_PLAY_CHECK_GAME_END(VOID)
{
	//プレイヤーの位置は、プレイヤーの中心
	PlayerToMapNumY = (Myplayer.Y + Myplayer.C_Height) / MAP_SIZE_TATE;
	PlayerToMapNumX = (Myplayer.MoveDist + Myplayer.C_Width) / MAP_SIZE_YOKO;
	PlayerToMapNumY2 = (Myplayer2.Y + Myplayer2.C_Height) / MAP_SIZE_TATE;
	PlayerToMapNumX2 = (Myplayer2.MoveDist + Myplayer2.C_Width) / MAP_SIZE_YOKO;

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