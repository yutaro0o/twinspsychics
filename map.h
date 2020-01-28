#ifndef _MAP_H_
#define _MAP_H_
#include "mydef.h"

extern int MapData[MAP_TATE_NUM][MAP_YOKO_NUM];
extern int MapData_Init[MAP_TATE_NUM][MAP_YOKO_NUM];

static int MapNGKind[MAP_NG_KIND] = { 2 };
static int MapItemKind[MAP_ITEM_KIND] = {};
static int MapGoalKind[MAP_GOAL_KIND] = {4};
static int MapBeltKind[MAP_BELT_KIND] = {};

enum MAP_IMAGE {
	M_N = -1,		//MAP_NULL�̈Ӗ�
	M_B = 19,		//MAP_BLANK�̈Ӗ�
	M_G_T = 6,		//MAP_GROUND_TOP�̈Ӗ�
	M_G_N = 38,		//MAP_GROUND_NAKA�̈Ӗ�
	M_AM = 95,		//MAP_AMAZUN�̈Ӗ�
	M_END = 399		//�}�b�v�̏I��
};	//�}�b�v�̗񋓌^

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

extern MAP MapImage;

BOOL MY_MAP_READ_CSV_NUM(FILE *fp, const char *path);

BOOL MY_MAP_LOAD_BUNKATSU(MAP *, int, int, int, int, int, const char *);

void MY_PLAY_MAP_DRAW(void);//�}�b�v��\������֐�

//�}�b�v�̓����蔻��ōs���~�܂�����(��s�ڂ͏����ʒu)
extern RECT rectMap_NG[MAP_TATE_NUM][MAP_YOKO_NUM];
extern RECT rectMap_NG_First[MAP_TATE_NUM][MAP_YOKO_NUM];
extern RECT rectMap_Item[MAP_TATE_NUM][MAP_YOKO_NUM];
extern RECT rectMap_Item_First[MAP_TATE_NUM][MAP_YOKO_NUM];


#endif