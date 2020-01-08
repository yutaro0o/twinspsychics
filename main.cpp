#include "DxLib.h"
#include "mydef.h"
#include "fps.h"
#include "key.h"
#include "title.h"
#include "method.h"
#include "play.h"
#include "inventory.h"
#include "end.h"
#include "global.h"


typedef struct STRUCT_GAZOU {
	int Handle;			//画像のハンドル
	char FilePath[128];	//ファイルパス
	int X;				//左上のX座標
	int Y;				//左上のY座標
	int Width;			//横幅
	int Height;			//縦幅
	int C_Width;		//横の中心
	int C_Height;		//縦の中心

	int MoveSpeed;		//画像のスクロールスピード
}GAZOU;

//背景画像の実体を定義
GAZOU Title;
GAZOU Method;
GAZOU Play;
GAZOU Inventory;
GAZOU End;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLibe, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);//ウィンドウモードを設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);//指定の数値で画面を表示する

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);//タイトルバーなし

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));//タイトルの文字

	if (DxLib_Init() == -1) { return -1; }//DXライブラリ初期化処理

	SetDrawScreen(DX_SCREEN_BACK);//Draw系関数は裏画面に描画

	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }//メッセージ処理の結果がエラーの時、強制終了

		if (ClearDrawScreen() != 0) { break; }//画面を消去できなかった時、強制終了

		MY_ALL_KEYDOWN_UPDATE();//キーの状態を取得

		//シーン選択
		switch (GameSceneNow)
		{
		case (int)GAME_SCENE_TITLE:	//タイトル画面の処理開始
			MY_GAME_TITLE();//タイトル画面の処理
			break;//タイトル画面の処理終了

		case (int)GAME_SCENE_METHOD://操作説明画面の処理開始
			MY_GAME_METHOD();//操作説明画面の処理
			break;//操作説明画面の処理終了

		case (int)GAME_SCENE_PLAY://プレイ画面の処理開始
			MY_GAME_PLAY();//プレイ画面の処理
			break;//プレイ画面の処理終了

		case (int)GAME_SCENE_INVENTORY://所持品画面の処理開始
			MY_GAME_INVENTORY();//所持品画面の処理
			break;//所持品画面の処理終了

		case (int)GAME_SCENE_END://エンド画面の処理開始
			MY_GAME_END();//エンド画面の処理
			break;//エンド画面の処理終了

		default:
			break;
		}
		MY_FPS_UPDATE();//FPSの処理(更新)
		MY_FPS_DRAW();//FPSの処理(描画)
		ScreenFlip();//モニタのリフレッシュレートの速さで裏画面を再描画
		MY_FPS_WAIT();//FPSの処理(待つ)
	}
	DxLib_End();//DXライブラリ使用の終了処理

	return 0;
}