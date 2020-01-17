#ifndef _MAP_H_
#define _MAP_H_
#include "mydef.h"

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

typedef STRUCT_MAP MAP;

extern MAP MapImage;

BOOL MY_MAP_READ_CSV_NUM(FILE *fp, const char *path);

BOOL MY_MAP_LOAD_BUNKATSU(MAP *, int, int, int, int, int, const char *);

void MY_PLAY_MAP_DRAW(void);//マップを表示する関数

#endif