#include "dxlib.h"
#include "map.h"
#include "mydef.h"
#include "global.h"
#define _CRT_SECURE_NO_WARNINGS

int MapData[MAP_TILE_TATE][MAP_TILE_YOKO];
int MapData_Init[MAP_TILE_TATE][MAP_TILE_YOKO];

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
		result = fscanf(fp, "%d,", &MapData[LoopCnt / MAP_TILE_YOKO][LoopCnt % MAP_TILE_YOKO]);

		MapData_Init[LoopCnt / MAP_TILE_YOKO][LoopCnt % MAP_TILE_YOKO] = MapData[LoopCnt / MAP_TILE_YOKO][LoopCnt % MAP_TILE_YOKO];

		LoopCnt++;
	}

	fclose(fp);

	int cnt;

	for (int tate = 0; tate < MAP_TILE_TATE; tate++)
	{
		for (int yoko = 0; yoko < MAP_TILE_YOKO; yoko++)
		{
			for (cnt = 0; cnt < GAME_MAP_NOTDOWN_KIND; cnt++)
			{
				if (MapData[tate][yoko] == MapNotDownKind[cnt])
				{
					rectMap_DownNG[tate][yoko].left = yoko * MAP_TILE_SIZE_YOKO + 1;
					rectMap_DownNG[tate][yoko].top = tate * MAP_TILE_SIZE_TATE + 1;
					rectMap_DownNG[tate][yoko].right = (yoko + 1) * MAP_TILE_SIZE_YOKO - 1;
					rectMap_DownNG[tate][yoko].bottom = (tate + 1) * MAP_TILE_SIZE_TATE - 1;
					rectMap_DownNG_First[tate][yoko] = rectMap_DownNG[tate][yoko];
				}
			}
			for (cnt = 0; cnt < GAME_MAP_NOTLEFT_KIND; cnt++)
			{
				if (MapData[tate][yoko] == MapNotLeftKind[cnt])
				{
					rectMap_LeftNG[tate][yoko].left = yoko * MAP_TILE_SIZE_YOKO + 1;
					rectMap_LeftNG[tate][yoko].top = tate * MAP_TILE_SIZE_TATE + 1;
					rectMap_LeftNG[tate][yoko].right = (yoko + 1) * MAP_TILE_SIZE_YOKO - 1;
					rectMap_LeftNG[tate][yoko].bottom = (tate + 1) * MAP_TILE_SIZE_TATE - 1;
					rectMap_LeftNG_First[tate][yoko] = rectMap_LeftNG[tate][yoko];
				}
			}
			for (cnt = 0; cnt < GAME_MAP_NOTRIGHT_KIND; cnt++)
			{
				if (MapData[tate][yoko] == MapNotRightKind[cnt])
				{
					rectMap_RightNG[tate][yoko].left = yoko * MAP_TILE_SIZE_YOKO + 1;
					rectMap_RightNG[tate][yoko].top = tate * MAP_TILE_SIZE_TATE + 1;
					rectMap_RightNG[tate][yoko].right = (yoko + 1) * MAP_TILE_SIZE_YOKO - 1;
					rectMap_RightNG[tate][yoko].bottom = (tate + 1) * MAP_TILE_SIZE_TATE - 1;
					rectMap_RightNG_First[tate][yoko] = rectMap_RightNG[tate][yoko];
				}
			}
			for (cnt = 0; cnt < GAME_MAP_NOTUP_KIND; cnt++)
			{
				if (MapData[tate][yoko] == MapNotUpKind[cnt])
				{
					rectMap_UpNG[tate][yoko].left = yoko * MAP_TILE_SIZE_YOKO + 1;
					rectMap_UpNG[tate][yoko].top = tate * MAP_TILE_SIZE_TATE + 1;
					rectMap_UpNG[tate][yoko].right = (yoko + 1) * MAP_TILE_SIZE_YOKO - 1;
					rectMap_UpNG[tate][yoko].bottom = (tate + 1) * MAP_TILE_SIZE_TATE - 1;
					rectMap_UpNG_First[tate][yoko] = rectMap_UpNG[tate][yoko];
				}
			}
		}
	}

	return TRUE;
}
