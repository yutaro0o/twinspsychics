#include "dxlib.h"
#include "map.h"
#include "mydef.h"
#include "global.h"
#define _CRT_SECURE_NO_WARNINGS

int MapData[MAP_SIZE_TATE][MAP_SIZE_YOKO];
int MapData_Init[MAP_SIZE_TATE][MAP_SIZE_YOKO];
int MapNotDownKind[MAP_NOTDOWN_KIND];
int MapNotUpKind[MAP_NOTUP_KIND];
int MapNotLeftKind[MAP_NOTLEFT_KIND];
int MapNotRightKind[MAP_NOTRIGHT_KIND];
int MapItemKind[MAP_ITEM_KIND];

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
