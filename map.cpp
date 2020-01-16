#define _CRT_SECURE_NO_WARNINGS
#include "dxlib.h"
#include "map.h"
#include "mydef.h"
#include "global.h"

int MapData[MAP_SIZE_TATE][MAP_SIZE_YOKO];
int MapData_Init[MAP_SIZE_TATE][MAP_SIZE_YOKO];
int MapNotDownKind[MAP_NOTDOWN_KIND] = {};
int MapNotUpKind[MAP_NOTUP_KIND] = {};
int MapNotLeftKind[MAP_NOTLEFT_KIND] = {};
int MapNotRightKind[MAP_NOTRIGHT_KIND] = {};
int MapItemKind[MAP_ITEM_KIND] = {};

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

MAP MapImage;

int ScrollCntYoko = 0;

//マップの当たり判定で行き止まりを作る(二行目は初期位置)
RECT rectMap_DownNG[MAP_SIZE_TATE][MAP_SIZE_YOKO];
RECT rectMap_DownNG_First[MAP_SIZE_TATE][MAP_SIZE_YOKO];

RECT rectMap_UpNG[MAP_SIZE_TATE][MAP_SIZE_YOKO];
RECT rectMap_UpNG_First[MAP_SIZE_TATE][MAP_SIZE_YOKO];

RECT rectMap_LeftNG[MAP_SIZE_TATE][MAP_SIZE_YOKO];
RECT rectMap_LeftNG_First[MAP_SIZE_TATE][MAP_SIZE_YOKO];

RECT rectMap_RightNG[MAP_SIZE_TATE][MAP_SIZE_YOKO];
RECT rectMap_RightNG_First[MAP_SIZE_TATE][MAP_SIZE_YOKO];

RECT rectMap_Item[MAP_SIZE_TATE][MAP_SIZE_YOKO];
RECT rectMap_Item_First[MAP_SIZE_TATE][MAP_SIZE_YOKO];

BOOL MY_MAP_READ_CSV_NUM(FILE *fp, const char *path);

BOOL MY_MAP_LOAD_BUNKATSU(MAP *, int, int, int, int, int, const char *);


//VOID MY_PLAY_ENEMY_MAP_COLLISION(ENEMY *);			//敵とマップとの接触関数
//VOID MY_PLAY_MAP_DRAW(VOID);			//マップを表示する関数
//BOOL MY_CHECK_RECT_ATARI_CHARA_MAP(RECT, RECT[GAME_MAP_TATE][GAME_MAP_YOKO]);	//マップとの当たり判定をする関数
//BOOL MY_CHECK_RECT_ATARI_CHARA_MAP_ATARIBASHO(RECT, RECT map[GAME_MAP_TATE][GAME_MAP_YOKO], int *, int *);
//if (MY_MAP_READ_CSV_NUM(fp_map_csv, GAME_MAP_CSV_1) == FALSE) { MessageBox(NULL, GAME_MAP_CSV_1, "NotFound", MB_OK); return -1; }	//CSVを読み込む
//if (MY_MAP_LOAD_BUNKATSU(&MapImage, GAME_MAP_BUN_YOKO_CNT * GAME_MAP_BUN_TATE_CNT, GAME_MAP_BUN_TATE_CNT, GAME_MAP_BUN_YOKO_CNT, 32, 32, GAME_MAP_1) == FALSE) { MessageBox(NULL, GAME_MAP_1, "NotFound", MB_OK); return -1; }	//MAPを読み込む
//for (int mapCnt = 0; mapCnt < GAME_MAP_BUN_YOKO_CNT * GAME_MAP_BUN_TATE_CNT; mapCnt++)
//{
//	DeleteGraph(MapImage.Handle[mapCnt]);	//マップのハンドルを削除
//}
//for (int tate = 0; tate < GAME_MAP_TATE; tate++)
//{
//	for (int yoko = 0; yoko < GAME_MAP_YOKO; yoko++)
//	{
//		MapData[tate][yoko] = MapData_Init[tate][yoko];	//マップをもとに戻す
//	}
//}
////プレイヤーの位置は、プレイヤーの中心
//int PlayerToMapNumY = (Myplayer.Y + Myplayer.C_Height) / GAME_MAP_TATE_SIZE;
//int PlayerToMapNumX = (Myplayer.MoveDist + Myplayer.C_Width) / GAME_MAP_TATE_SIZE;
//
//if (PlayerToMapNumX < 0 || PlayerToMapNumX > GAME_MAP_YOKO) { return FALSE; }	//マップの配列外でゴールになるバグを解消
//if (PlayerToMapNumY < 0 || PlayerToMapNumY > GAME_MAP_TATE) { return FALSE; }	//マップの配列外でゴールになるバグを解消
//
//for (int G_Cnt = 0; G_Cnt < GAME_MAP_GOAL_KIND; G_Cnt++)
//{
//	//プレイヤーがゴールのモノと接触したとき
//	if (MapData[PlayerToMapNumY][PlayerToMapNumX] == MapGoalKind[G_Cnt])
//	{
//		MapImage.GameEndKind = (int)END_KIND_CLEAR;		//ゲームクリア
//		return TRUE;
//		break;
//	}
//}


BOOL MY_MAP_READ_CSV_NUM(FILE *fp, const char *path)
{
	if ((fp = fopen(path, "r")) == NULL)
	{
		return FALSE;
	}

	int result = 0;
	int LoopCnt = 0;
	while (result != EOF)
	{
		result = fscanf(fp, "%d,", &MapData[LoopCnt / MAP_SIZE_YOKO][LoopCnt % MAP_SIZE_YOKO]);

		MapData_Init[LoopCnt / MAP_SIZE_YOKO][LoopCnt % MAP_SIZE_YOKO] = MapData[LoopCnt / MAP_SIZE_YOKO][LoopCnt % MAP_SIZE_YOKO];

		LoopCnt++;
	}

	fclose(fp);

	int cnt;

	for (int tate = 0; tate < MAP_SIZE_TATE; tate++)
	{
		for (int yoko = 0; yoko < MAP_SIZE_YOKO; yoko++)
		{
			for (cnt = 0; cnt < MAP_NOTDOWN_KIND; cnt++)
			{
				if (MapData[tate][yoko] == MapNotDownKind[cnt])
				{
					rectMap_DownNG[tate][yoko].left = yoko * TILE_SIZE_YOKO + 1;
					rectMap_DownNG[tate][yoko].top = tate * TILE_SIZE_TATE + 1;
					rectMap_DownNG[tate][yoko].right = (yoko + 1) * TILE_SIZE_YOKO - 1;
					rectMap_DownNG[tate][yoko].bottom = (tate + 1) * TILE_SIZE_TATE - 1;
					rectMap_DownNG_First[tate][yoko] = rectMap_DownNG[tate][yoko];
				}
			}
			for (cnt = 0; cnt < MAP_NOTLEFT_KIND; cnt++)
			{
				if (MapData[tate][yoko] == MapNotLeftKind[cnt])
				{
					rectMap_LeftNG[tate][yoko].left = yoko * TILE_SIZE_YOKO + 1;
					rectMap_LeftNG[tate][yoko].top = tate * TILE_SIZE_TATE + 1;
					rectMap_LeftNG[tate][yoko].right = (yoko + 1) * TILE_SIZE_YOKO - 1;
					rectMap_LeftNG[tate][yoko].bottom = (tate + 1) * TILE_SIZE_TATE - 1;
					rectMap_LeftNG_First[tate][yoko] = rectMap_LeftNG[tate][yoko];
				}
			}
			for (cnt = 0; cnt < MAP_NOTRIGHT_KIND; cnt++)
			{
				if (MapData[tate][yoko] == MapNotRightKind[cnt])
				{
					rectMap_RightNG[tate][yoko].left = yoko * TILE_SIZE_YOKO + 1;
					rectMap_RightNG[tate][yoko].top = tate * TILE_SIZE_TATE + 1;
					rectMap_RightNG[tate][yoko].right = (yoko + 1) * TILE_SIZE_YOKO - 1;
					rectMap_RightNG[tate][yoko].bottom = (tate + 1) * TILE_SIZE_TATE - 1;
					rectMap_RightNG_First[tate][yoko] = rectMap_RightNG[tate][yoko];
				}
			}
			for (cnt = 0; cnt < MAP_NOTUP_KIND; cnt++)
			{
				if (MapData[tate][yoko] == MapNotUpKind[cnt])
				{
					rectMap_UpNG[tate][yoko].left = yoko * TILE_SIZE_YOKO + 1;
					rectMap_UpNG[tate][yoko].top = tate * TILE_SIZE_TATE + 1;
					rectMap_UpNG[tate][yoko].right = (yoko + 1) * TILE_SIZE_YOKO - 1;
					rectMap_UpNG[tate][yoko].bottom = (tate + 1) * TILE_SIZE_TATE - 1;
					rectMap_UpNG_First[tate][yoko] = rectMap_UpNG[tate][yoko];
				}
			}
		}
	}

	return TRUE;
}
BOOL MY_MAP_LOAD_BUNKATSU(MAP *m, int bun_num, int bun_x_num, int bun_y_num, int bun_width, int bun_height, const char *path)
{
	int ret = 0;
	wsprintf(m->FilePath, path);

	ret = LoadDivGraph(m->FilePath, bun_num, bun_x_num, bun_y_num, bun_width, bun_height, m->Handle);//画像をメモリに分割して読み込み

	if (ret == -1) { return FALSE; }//画像読み込みエラー

	for (int cnt = 0; cnt < TILE_YOKO * TILE_TATE; cnt++)
	{
		//画像サイズを取得
		GetGraphSize(
			m->Handle[cnt],		//ハンドルから画像の幅と高さを取得して
			&m->Width[cnt],		//MAP構造体の幅に画像の幅を設定する
			&m->Height[cnt]);	//MAP構造体の逆さに画像の高さを設定する
	
		m->C_Width[cnt] = m->Width[cnt] / 2;		//画像の横サイズの中心を取得
		m->C_Height[cnt] = m->Height[cnt] / 2;		//画像の縦サイズの中心を取得
	}
	m->charaStopFlag = FALSE;	//プレイヤーの移動制御フラグ

	return TRUE;
}

VOID MY_PLAY_MAP_DRAW(VOID)
{
	//スクロールするマップを描画
	for (int tate = 0; tate < MAP_SIZE_TATE; tate++)
	{
		for (int yoko = 0; yoko < MAP_SIZE_YOKO; yoko++)
		{
			if ((yoko + 1) * TILE_SIZE_YOKO - ScrollCntYoko >= 0 &&
				(yoko + 0) * TILE_SIZE_YOKO - ScrollCntYoko <= GAME_WIDTH)//画面に映っているならば
			{
				DrawGraph(
					yoko * TILE_SIZE_YOKO - ScrollCntYoko,
					tate * TILE_SIZE_TATE,
					MapImage.Handle[MapData[tate][yoko]], TRUE);	//マップをスクロールしながら描画
			}
		}
	}
}
