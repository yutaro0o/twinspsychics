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

