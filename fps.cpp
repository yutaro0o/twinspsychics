#include "DxLib.h"
#include "mydef.h"
#include "fps.h"

MY_FPS MyFPS;

BOOL MY_FPS_UPDATE() {
	//1�t���[���ڂȂ玞�����L��
	if (MyFPS.count == 0)
	{
		//Windows���N�����Ă��猻�݂܂ł̎������~���b�Ŏ擾
		MyFPS.sta_tm = GetTickCount();
	}
	//50�t���[���ڂȂ畽�ς��v�Z����
	if (MyFPS.count == MyFPS.ave)
	{
		//Windows���N�����Ă��猻�݂܂ł̎������~���b�Ŏ擾
		MyFPS.end_tm = GetTickCount();
		//���ϓI��FPS�l���v�Z
		MyFPS.Show = 1000.0f / ((MyFPS.end_tm - MyFPS.sta_tm) / MyFPS.ave);
		//����FPS�v�Z�̏���
		MyFPS.sta_tm = MyFPS.end_tm;
		//�J�E���g������
		MyFPS.count = 0;
	}
	MyFPS.count++;
	return true;
}

void MY_FPS_DRAW() {
	//�������`��
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(0, 0, 255), "FPS:%.1f", MyFPS.Show);
	return;
}

void MY_FPS_WAIT() {
	//���݂̎������~���b�Ŏ擾
	DWORD now_tm = GetTickCount();
	//1�t���[���ڂ�����ۂɂ����������Ԃ��v�Z
	DWORD keika_tm = now_tm - MyFPS.sta_tm;
	//�҂ׂ����� = ������ׂ����� - ���ۂɂ�����������
	DWORD wait_tm = (MyFPS.count * 1000 / MyFPS.disp) - (keika_tm);
	//�҂ׂ����Ԃ��������ꍇ
	if (wait_tm > 0 && wait_tm < 2000)
	{
		Sleep(wait_tm);//wait_tm�~���b���A�����𒆒f����
	}
	return;
}