#include "DxLib.h"
#include "mydef.h"
#include "fps.h"

MY_FPS MyFPS;

BOOL MY_FPS_UPDATE() {
	//1フレーム目なら時刻を記憶
	if (MyFPS.count == 0)
	{
		//Windowsが起動してから現在までの時刻をミリ秒で取得
		MyFPS.sta_tm = GetTickCount();
	}
	//50フレーム目なら平均を計算する
	if (MyFPS.count == MyFPS.ave)
	{
		//Windowsが起動してから現在までの時刻をミリ秒で取得
		MyFPS.end_tm = GetTickCount();
		//平均的なFPS値を計算
		MyFPS.Show = 1000.0f / ((MyFPS.end_tm - MyFPS.sta_tm) / MyFPS.ave);
		//次のFPS計算の準備
		MyFPS.sta_tm = MyFPS.end_tm;
		//カウント初期化
		MyFPS.count = 0;
	}
	MyFPS.count++;
	return true;
}

void MY_FPS_DRAW() {
	//文字列を描画
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(0, 0, 255), "FPS:%.1f", MyFPS.Show);
	return;
}

void MY_FPS_WAIT() {
	//現在の時刻をミリ秒で取得
	DWORD now_tm = GetTickCount();
	//1フレーム目から実際にかかった時間を計算
	DWORD keika_tm = now_tm - MyFPS.sta_tm;
	//待つべき時間 = かかるべき時間 - 実際にかかった時間
	DWORD wait_tm = (MyFPS.count * 1000 / MyFPS.disp) - (keika_tm);
	//待つべき時間があった場合
	if (wait_tm > 0 && wait_tm < 2000)
	{
		Sleep(wait_tm);//wait_tmミリ秒分、処理を中断する
	}
	return;
}