#include "global.h"
#include "dxlib.h"
#include "mydef.h"

int AllKeyState[256];	//キー状態の格納

int GameSceneNow = (int)GAME_SCENE_TITLE;	//最初のゲーム画面をタイトルにする

int StartTimeFps;
int CountFps;
float CalcFps;
int SampleNumFps;

FILE *fp_map_csv;

struct STRUCT_MAP
{
	char FilePath[128];//ファイルのパス
	int Handle[TILE_YOKO * TILE_TATE];
	int X[TILE_YOKO * TILE_TATE];
	int Y[TILE_YOKO * TILE_TATE];
	int Width[TILE_YOKO * TILE_TATE];
	int Height[TILE_YOKO * TILE_TATE];
	int C_Width[TILE_YOKO * TILE_TATE];
	int C_Height[TILE_YOKO * TILE_TATE];

	BOOL charaStopFlag;//キャラの移動制御フラグ
	BOOL GoalFlg;//このマップをゴールしたか
	int GameEndKind;//ゲーム終了の種類
	BOOL GoalEffect1;//ゴールした時の演出1
};
