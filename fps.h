#include <windows.h>
#ifndef _FPS_H_
#define _FPS_H_

struct MY_STRUCT_FPS
{
	float Show;		//表示するFPS
	DWORD sta_tm;	//0フレーム目の開始時刻
	DWORD end_tm;	//設定したフレームの終了時刻
	DWORD count;	//フレームのカウント
	float ave = FPS_CALC_AVE; //FPSを計算するための平均サンプル(mydef.h 60.0f)
	int disp = FPS_DISP;	//FPSの値

}typedef MY_FPS;

extern MY_FPS MyFPS;

BOOL MY_FPS_UPDATE();	//FPS値を計測、更新する関数
void MY_FPS_DRAW();		//FPS値を描画する関数
void MY_FPS_WAIT();		//FPS値を計測し、待つ関数

#endif