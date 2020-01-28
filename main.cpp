#include "DxLib.h"
#include "mydef.h"
#include "global.h"
#include "map.h"
#include "player.h"
#include "fps.h"
#include "key.h"
#include "title.h"
#include "method.h"
#include "play.h"
#include "inventory.h"
#include "end.h"

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

MAP MapImage;
CHARA CharaImage;
PLAYER MyPlayer;
PLAYER MyPlayer2;

BOOL IsWM_CREATE = FALSE; //WM_CREATEが正常に動作したか判断する

BOOL IsActiveCheck = FALSE;//画面のアクティブ✔有効か

int StopActiveStartTime = 0;//非アクティブ化の開始時間
int StopActiveStopTime = 0;//非アクティブ化の終了時間
int StopActiveTotalTime = 0;//非アクティブ化の経過時間

//プロトタイプ宣言
LRESULT CALLBACK MY_WNDPROC(HWND, UINT, WPARAM, LPARAM); //自作ウィンドウプロシージャ



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLibe, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);//ウィンドウモードを設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);//指定の数値で画面を表示する

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);//タイトルバーなし

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));//タイトルの文字

	SetHookWinProc(MY_WNDPROC);

	if (DxLib_Init() == -1) { return -1; }//DXライブラリ初期化処理

	SetDrawScreen(DX_SCREEN_BACK);//Draw系関数は裏画面に描画

	if (MY_MAP_READ_CSV_NUM(fp_map_csv, MAP_CSV_TEST) == FALSE) { MessageBox(NULL, MAP_CSV_TEST, "NotFound", MB_OK); return -1; }

	if (MY_MAP_LOAD_BUNKATSU(&MapImage, TILE_YOKO * TILE_TATE, TILE_YOKO, TILE_TATE, MAP_SIZE_YOKO, MAP_SIZE_TATE, MAP_PNG) == FALSE) { MessageBox(NULL, MAP_PNG, "NotFound", MB_OK); return -1; }

	if (MY_CHARA_LOAD_BUNKATSU(&CharaImage, CHARA_YOKO_NUM * CHARA_TATE_NUM, CHARA_YOKO_NUM, CHARA_TATE_NUM, CHARA_SIZE_YOKO, CHARA_SIZE_TATE, CHARA_1) == FALSE) { MessageBox(NULL, CHARA_1, "NotFound", MB_OK); return -1; }//GAME_CHARA_1を読み込む



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

	for (int mapCnt = 0; mapCnt < MAP_YOKO_NUM * MAP_TATE_NUM; mapCnt++)
	{
		DeleteGraph(MapImage.Handle[mapCnt]);//マップのハンドルを削除
	}

	for (int charaCnt = 0; charaCnt < CHARA_YOKO_NUM * CHARA_TATE_NUM; charaCnt++)
	{
		DeleteGraph(CharaImage.Handle[charaCnt]);//キャラのハンドルを削除
	}

	DxLib_End();//DXライブラリ使用の終了処理

	return 0;
}

LRESULT CALLBACK MY_WNDPROC(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	int closeMsgRet = 0;//閉じるメッセージボックスの戻り値

	switch (msg)
	{
	case WM_CREATE://ウィンドウの生成＆初期化
		IsWM_CREATE = TRUE;//WM_CREATE正常終了
		return 0;
	case WM_CLOSE://閉じるボタンを押したとき
		DestroyWindow(hwnd);//画面を破棄
		break;
	case WM_RBUTTONDOWN://マウスの右ボタンを押したとき
		closeMsgRet = MessageBox(hwnd, TEXT("ゲームを終了しますか？"), TEXT("終了メッセージ"), MB_YESNO);
		if (closeMsgRet == IDYES)
		{
			SendMessage(hwnd, WM_CLOSE, 0, 0);//WM_CLOSEメッセージをキューに追加
		}
		else if (closeMsgRet == IDNO)
		{
			break;//終了させない
		}
	case WM_ACTIVATE:
		if (IsActiveCheck == TRUE)//画面のアクティブ✔有効化
		{
			switch (wp)
			{
			case WA_INACTIVE://非アクティブ化
				StopActiveStartTime = GetNowCount();
				break;
			case WA_ACTIVE://キーボードなどでアクティブ化
				StopActiveStopTime = GetNowCount();
				break;
			case WA_CLICKACTIVE:
				StopActiveStopTime = GetNowCount();
				break;
			default:
				break;
			}
		}
		return 0;

	case WM_LBUTTONDOWN://マウスの左ボタンを押したとき
		PostMessage(hwnd, WM_NCLBUTTONDOWN, (WPARAM)HTCAPTION, lp);//WM_NCLBUTTONDOWN(タイトルバーでマウスの左ボタンを押した)メッセージをすぐに発行
		break;

	case WM_DESTROY://ウィンドウが破棄された(なくなった)とき
		PostQuitMessage(0);//メッセージキューにWM_QUITを送る
		return 0;
	}
	//デフォルトのウィンドウプロシージャ関数を呼び出す
	return DefWindowProc(hwnd, msg, wp, lp);
}