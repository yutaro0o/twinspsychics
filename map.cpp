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
	char FilePath[128];//�t�@�C���̃p�X
	int Handle[TILE_YOKO * TILE_TATE];
	int X[TILE_YOKO * TILE_TATE];
	int Y[TILE_YOKO * TILE_TATE];
	int Width[TILE_YOKO * TILE_TATE];
	int Height[TILE_YOKO * TILE_TATE];
	int C_Width[TILE_YOKO * TILE_TATE];
	int C_Height[TILE_YOKO * TILE_TATE];

	BOOL charaStopFlag;//�L�����̈ړ�����t���O
	BOOL GoalFlg;//���̃}�b�v���S�[��������
	int GameEndKind;//�Q�[���I���̎��
	BOOL GoalEffect1;//�S�[���������̉��o1
};

typedef STRUCT_MAP MAP;

MAP MapImage;

int ScrollCntYoko = 0;

//�}�b�v�̓����蔻��ōs���~�܂�����(��s�ڂ͏����ʒu)
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


//VOID MY_PLAY_ENEMY_MAP_COLLISION(ENEMY *);			//�G�ƃ}�b�v�Ƃ̐ڐG�֐�
//VOID MY_PLAY_MAP_DRAW(VOID);			//�}�b�v��\������֐�
//BOOL MY_CHECK_RECT_ATARI_CHARA_MAP(RECT, RECT[GAME_MAP_TATE][GAME_MAP_YOKO]);	//�}�b�v�Ƃ̓����蔻�������֐�
//BOOL MY_CHECK_RECT_ATARI_CHARA_MAP_ATARIBASHO(RECT, RECT map[GAME_MAP_TATE][GAME_MAP_YOKO], int *, int *);
//if (MY_MAP_READ_CSV_NUM(fp_map_csv, GAME_MAP_CSV_1) == FALSE) { MessageBox(NULL, GAME_MAP_CSV_1, "NotFound", MB_OK); return -1; }	//CSV��ǂݍ���
//if (MY_MAP_LOAD_BUNKATSU(&MapImage, GAME_MAP_BUN_YOKO_CNT * GAME_MAP_BUN_TATE_CNT, GAME_MAP_BUN_TATE_CNT, GAME_MAP_BUN_YOKO_CNT, 32, 32, GAME_MAP_1) == FALSE) { MessageBox(NULL, GAME_MAP_1, "NotFound", MB_OK); return -1; }	//MAP��ǂݍ���
//for (int mapCnt = 0; mapCnt < GAME_MAP_BUN_YOKO_CNT * GAME_MAP_BUN_TATE_CNT; mapCnt++)
//{
//	DeleteGraph(MapImage.Handle[mapCnt]);	//�}�b�v�̃n���h�����폜
//}
//for (int tate = 0; tate < GAME_MAP_TATE; tate++)
//{
//	for (int yoko = 0; yoko < GAME_MAP_YOKO; yoko++)
//	{
//		MapData[tate][yoko] = MapData_Init[tate][yoko];	//�}�b�v�����Ƃɖ߂�
//	}
//}
////�v���C���[�̈ʒu�́A�v���C���[�̒��S
//int PlayerToMapNumY = (Myplayer.Y + Myplayer.C_Height) / GAME_MAP_TATE_SIZE;
//int PlayerToMapNumX = (Myplayer.MoveDist + Myplayer.C_Width) / GAME_MAP_TATE_SIZE;
//
//if (PlayerToMapNumX < 0 || PlayerToMapNumX > GAME_MAP_YOKO) { return FALSE; }	//�}�b�v�̔z��O�ŃS�[���ɂȂ�o�O������
//if (PlayerToMapNumY < 0 || PlayerToMapNumY > GAME_MAP_TATE) { return FALSE; }	//�}�b�v�̔z��O�ŃS�[���ɂȂ�o�O������
//
//for (int G_Cnt = 0; G_Cnt < GAME_MAP_GOAL_KIND; G_Cnt++)
//{
//	//�v���C���[���S�[���̃��m�ƐڐG�����Ƃ�
//	if (MapData[PlayerToMapNumY][PlayerToMapNumX] == MapGoalKind[G_Cnt])
//	{
//		MapImage.GameEndKind = (int)END_KIND_CLEAR;		//�Q�[���N���A
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

	ret = LoadDivGraph(m->FilePath, bun_num, bun_x_num, bun_y_num, bun_width, bun_height, m->Handle);//�摜���������ɕ������ēǂݍ���

	if (ret == -1) { return FALSE; }//�摜�ǂݍ��݃G���[

	for (int cnt = 0; cnt < TILE_YOKO * TILE_TATE; cnt++)
	{
		//�摜�T�C�Y���擾
		GetGraphSize(
			m->Handle[cnt],		//�n���h������摜�̕��ƍ������擾����
			&m->Width[cnt],		//MAP�\���̂̕��ɉ摜�̕���ݒ肷��
			&m->Height[cnt]);	//MAP�\���̂̋t���ɉ摜�̍�����ݒ肷��
	
		m->C_Width[cnt] = m->Width[cnt] / 2;		//�摜�̉��T�C�Y�̒��S���擾
		m->C_Height[cnt] = m->Height[cnt] / 2;		//�摜�̏c�T�C�Y�̒��S���擾
	}
	m->charaStopFlag = FALSE;	//�v���C���[�̈ړ�����t���O

	return TRUE;
}

VOID MY_PLAY_MAP_DRAW(VOID)
{
	//�X�N���[������}�b�v��`��
	for (int tate = 0; tate < MAP_SIZE_TATE; tate++)
	{
		for (int yoko = 0; yoko < MAP_SIZE_YOKO; yoko++)
		{
			if ((yoko + 1) * TILE_SIZE_YOKO - ScrollCntYoko >= 0 &&
				(yoko + 0) * TILE_SIZE_YOKO - ScrollCntYoko <= GAME_WIDTH)//��ʂɉf���Ă���Ȃ��
			{
				DrawGraph(
					yoko * TILE_SIZE_YOKO - ScrollCntYoko,
					tate * TILE_SIZE_TATE,
					MapImage.Handle[MapData[tate][yoko]], TRUE);	//�}�b�v���X�N���[�����Ȃ���`��
			}
		}
	}
}
