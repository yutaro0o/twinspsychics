#include "global.h"

int AllKeyState[256];	//キー状態の格納

int GameSceneNow = (int)GAME_SCENE_TITLE;	//最初のゲーム画面をタイトルにする

int StartTimeFps;
int CountFps;
float CalcFps;
int SampleNumFps;

