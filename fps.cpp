#include "DxLib.h"
#include "mydef.h"
#include "fps.h"

MY_FPS MyFPS;

BOOL MY_FPS_UPDATE() {
	//1ƒtƒŒ[ƒ€–Ú‚È‚ç‚ğ‹L‰¯
	if (MyFPS.count == 0)
	{
		//Windows‚ª‹N“®‚µ‚Ä‚©‚çŒ»İ‚Ü‚Å‚Ì‚ğƒ~ƒŠ•b‚Åæ“¾
		MyFPS.sta_tm = GetTickCount();
	}
	//50ƒtƒŒ[ƒ€–Ú‚È‚ç•½‹Ï‚ğŒvZ‚·‚é
	if (MyFPS.count == MyFPS.ave)
	{
		//Windows‚ª‹N“®‚µ‚Ä‚©‚çŒ»İ‚Ü‚Å‚Ì‚ğƒ~ƒŠ•b‚Åæ“¾
		MyFPS.end_tm = GetTickCount();
		//•½‹Ï“I‚ÈFPS’l‚ğŒvZ
		MyFPS.Show = 1000.0f / ((MyFPS.end_tm - MyFPS.sta_tm) / MyFPS.ave);
		//Ÿ‚ÌFPSŒvZ‚Ì€”õ
		MyFPS.sta_tm = MyFPS.end_tm;
		//ƒJƒEƒ“ƒg‰Šú‰»
		MyFPS.count = 0;
	}
	MyFPS.count++;
	return true;
}

void MY_FPS_DRAW() {
	//•¶š—ñ‚ğ•`‰æ
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(0, 0, 255), "FPS:%.1f", MyFPS.Show);
	return;
}

void MY_FPS_WAIT() {
	//Œ»İ‚Ì‚ğƒ~ƒŠ•b‚Åæ“¾
	DWORD now_tm = GetTickCount();
	//1ƒtƒŒ[ƒ€–Ú‚©‚çÀÛ‚É‚©‚©‚Á‚½ŠÔ‚ğŒvZ
	DWORD keika_tm = now_tm - MyFPS.sta_tm;
	//‘Ò‚Â‚×‚«ŠÔ = ‚©‚©‚é‚×‚«ŠÔ - ÀÛ‚É‚©‚©‚Á‚½ŠÔ
	DWORD wait_tm = (MyFPS.count * 1000 / MyFPS.disp) - (keika_tm);
	//‘Ò‚Â‚×‚«ŠÔ‚ª‚ ‚Á‚½ê‡
	if (wait_tm > 0 && wait_tm < 2000)
	{
		Sleep(wait_tm);//wait_tmƒ~ƒŠ•b•ªAˆ—‚ğ’†’f‚·‚é
	}
	return;
}