#include <windows.h>
#ifndef _FPS_H_
#define _FPS_H_

struct MY_STRUCT_FPS
{
	float Show;		//�\������FPS
	DWORD sta_tm;	//0�t���[���ڂ̊J�n����
	DWORD end_tm;	//�ݒ肵���t���[���̏I������
	DWORD count;	//�t���[���̃J�E���g
	float ave = FPS_CALC_AVE; //FPS���v�Z���邽�߂̕��σT���v��(mydef.h 60.0f)
	int disp = FPS_DISP;	//FPS�̒l

}typedef MY_FPS;

extern MY_FPS MyFPS;

BOOL MY_FPS_UPDATE();	//FPS�l���v���A�X�V����֐�
void MY_FPS_DRAW();		//FPS�l��`�悷��֐�
void MY_FPS_WAIT();		//FPS�l���v�����A�҂֐�

#endif