#include "DxLib.h"
#include "mydef.h"
#include "fps.h"
#include "key.h"
#include "title.h"
#include "method.h"
#include "play.h"
#include "inventory.h"
#include "end.h"
#include "global.h"


typedef struct STRUCT_GAZOU {
	int Handle;			//�摜�̃n���h��
	char FilePath[128];	//�t�@�C���p�X
	int X;				//�����X���W
	int Y;				//�����Y���W
	int Width;			//����
	int Height;			//�c��
	int C_Width;		//���̒��S
	int C_Height;		//�c�̒��S

	int MoveSpeed;		//�摜�̃X�N���[���X�s�[�h
}GAZOU;

//�w�i�摜�̎��̂��`
GAZOU Title;
GAZOU Method;
GAZOU Play;
GAZOU Inventory;
GAZOU End;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLibe, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);//�E�B���h�E���[�h��ݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);//�w��̐��l�ŉ�ʂ�\������

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);//�^�C�g���o�[�Ȃ�

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));//�^�C�g���̕���

	if (DxLib_Init() == -1) { return -1; }//DX���C�u��������������

	SetDrawScreen(DX_SCREEN_BACK);//Draw�n�֐��͗���ʂɕ`��

	//�������[�v
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }//���b�Z�[�W�����̌��ʂ��G���[�̎��A�����I��

		if (ClearDrawScreen() != 0) { break; }//��ʂ������ł��Ȃ��������A�����I��

		MY_ALL_KEYDOWN_UPDATE();//�L�[�̏�Ԃ��擾

		//�V�[���I��
		switch (GameSceneNow)
		{
		case (int)GAME_SCENE_TITLE:	//�^�C�g����ʂ̏����J�n
			MY_GAME_TITLE();//�^�C�g����ʂ̏���
			break;//�^�C�g����ʂ̏����I��

		case (int)GAME_SCENE_METHOD://���������ʂ̏����J�n
			MY_GAME_METHOD();//���������ʂ̏���
			break;//���������ʂ̏����I��

		case (int)GAME_SCENE_PLAY://�v���C��ʂ̏����J�n
			MY_GAME_PLAY();//�v���C��ʂ̏���
			break;//�v���C��ʂ̏����I��

		case (int)GAME_SCENE_INVENTORY://�����i��ʂ̏����J�n
			MY_GAME_INVENTORY();//�����i��ʂ̏���
			break;//�����i��ʂ̏����I��

		case (int)GAME_SCENE_END://�G���h��ʂ̏����J�n
			MY_GAME_END();//�G���h��ʂ̏���
			break;//�G���h��ʂ̏����I��

		default:
			break;
		}
		MY_FPS_UPDATE();//FPS�̏���(�X�V)
		MY_FPS_DRAW();//FPS�̏���(�`��)
		ScreenFlip();//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��
		MY_FPS_WAIT();//FPS�̏���(�҂�)
	}
	DxLib_End();//DX���C�u�����g�p�̏I������

	return 0;
}