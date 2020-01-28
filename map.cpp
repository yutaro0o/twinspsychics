#define _CRT_SECURE_NO_WARNINGS
#include "dxlib.h"
#include "map.h"
#include "mydef.h"
#include "global.h"

int MapData[MAP_TATE_NUM][MAP_YOKO_NUM];
int MapData_Init[MAP_TATE_NUM][MAP_YOKO_NUM];

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
					rectMap_NG[tate][yoko].left = yoko * MAP_SIZE_YOKO - 1;
					rectMap_NG[tate][yoko].top = tate * MAP_SIZE_TATE + 1;
					rectMap_NG[tate][yoko].right = (yoko + 1) * MAP_SIZE_YOKO + 1;
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

void MY_PLAY_MAP_DRAW(void)
{
	//�X�N���[������}�b�v��`��
	for (int tate = 0; tate < MAP_TATE_NUM; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_NUM; yoko++)
		{
			if ((yoko + 1) * MAP_SIZE_YOKO >= 0 &&
				(yoko + 0) * MAP_SIZE_YOKO <= GAME_WIDTH)//��ʂɉf���Ă���Ȃ��
			{
				DrawGraph(
					yoko * MAP_SIZE_YOKO,
					tate * MAP_SIZE_TATE,
					MapImage.Handle[MapData[tate][yoko]], TRUE);

				DrawBox(
					rectMap_NG[tate][yoko].left,
					rectMap_NG[tate][yoko].top,
					rectMap_NG[tate][yoko].right,
					rectMap_NG[tate][yoko].bottom,
					GetColor(255, 0, 0), FALSE);	//�s���Ȃ��}�b�v
			}
		}
	}
}