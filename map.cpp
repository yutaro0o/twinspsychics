#define _CRT_SECURE_NO_WARNINGS
#include "dxlib.h"
#include "map.h"
#include "mydef.h"
#include "global.h"

int MapData[MAP_TATE_NUM][MAP_YOKO_NUM];
int MapData_Init[MAP_TATE_NUM][MAP_YOKO_NUM];

int ScrollCntYoko = 0;

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
		result = fscanf(fp, "%d,", &MapData[LoopCnt / MAP_YOKO_NUM][LoopCnt % MAP_YOKO_NUM]);

		MapData_Init[LoopCnt / MAP_YOKO_NUM][LoopCnt % MAP_YOKO_NUM] = MapData[LoopCnt / MAP_YOKO_NUM][LoopCnt % MAP_YOKO_NUM];

		LoopCnt++;
	}

	fclose(fp);

	int cnt;

	for (int tate = 0; tate < MAP_TATE_NUM; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_NUM; yoko++)
		{
			for (cnt = 0; cnt < MAP_NG_KIND; cnt++)
			{
				if (MapData[tate][yoko] == MapNGKind[cnt])
				{
					rectMap_NG[tate][yoko].left = yoko * MAP_SIZE_YOKO + 1;
					rectMap_NG[tate][yoko].top = tate * MAP_SIZE_TATE + 1;
					rectMap_NG[tate][yoko].right = (yoko + 1) * MAP_SIZE_YOKO - 1;
					rectMap_NG[tate][yoko].bottom = (tate + 1) * MAP_SIZE_TATE - 1;
					rectMap_NG_First[tate][yoko] = rectMap_NG[tate][yoko];
				}
			}
			for (cnt = 0; cnt < MAP_NG_KIND; cnt++)
			{
				if (MapData[tate][yoko] == MapNGKind[cnt])
				{
					rectMap_NG[tate][yoko].left = yoko * MAP_SIZE_YOKO + 1;
					rectMap_NG[tate][yoko].top = tate * MAP_SIZE_TATE + 1;
					rectMap_NG[tate][yoko].right = (yoko + 1) * MAP_SIZE_YOKO - 1;
					rectMap_NG[tate][yoko].bottom = (tate + 1) * MAP_SIZE_TATE - 1;
					rectMap_NG_First[tate][yoko] = rectMap_NG[tate][yoko];
				}
			}
			for (cnt = 0; cnt < MAP_NG_KIND; cnt++)
			{
				if (MapData[tate][yoko] == MapNGKind[cnt])
				{
					rectMap_NG[tate][yoko].left = yoko * MAP_SIZE_YOKO + 1;
					rectMap_NG[tate][yoko].top = tate * MAP_SIZE_TATE + 1;
					rectMap_NG[tate][yoko].right = (yoko + 1) * MAP_SIZE_YOKO - 1;
					rectMap_NG[tate][yoko].bottom = (tate + 1) * MAP_SIZE_TATE - 1;
					rectMap_NG_First[tate][yoko] = rectMap_NG[tate][yoko];
				}
			}
			for (cnt = 0; cnt < MAP_NG_KIND; cnt++)
			{
				if (MapData[tate][yoko] == MapNGKind[cnt])
				{
					rectMap_NG[tate][yoko].left = yoko * MAP_SIZE_YOKO + 1;
					rectMap_NG[tate][yoko].top = tate * MAP_SIZE_TATE + 1;
					rectMap_NG[tate][yoko].right = (yoko + 1) * MAP_SIZE_YOKO - 1;
					rectMap_NG[tate][yoko].bottom = (tate + 1) * MAP_SIZE_TATE - 1;
					rectMap_NG_First[tate][yoko] = rectMap_NG[tate][yoko];
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

void MY_PLAY_MAP_DRAW(void)
{
	//スクロールするマップを描画
	for (int tate = 0; tate < MAP_TATE_NUM; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_NUM; yoko++)
		{
			if ((yoko + 1) * MAP_SIZE_YOKO - ScrollCntYoko >= 0 &&
				(yoko + 0) * MAP_SIZE_YOKO - ScrollCntYoko <= GAME_WIDTH)//画面に映っているならば
			{
				DrawGraph(
					yoko * MAP_SIZE_YOKO - ScrollCntYoko,
					tate * MAP_SIZE_TATE,
					MapImage.Handle[MapData[tate][yoko]], TRUE);	//マップをスクロールしながら描画
			}
		}
	}
}