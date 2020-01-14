#include "global.h"
#include "dxlib.h"
#include "mydef.h"

int AllKeyState[256];	//�L�[��Ԃ̊i�[

int GameSceneNow = (int)GAME_SCENE_TITLE;	//�ŏ��̃Q�[����ʂ��^�C�g���ɂ���

int StartTimeFps;
int CountFps;
float CalcFps;
int SampleNumFps;

FILE *fp_map_csv;

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
