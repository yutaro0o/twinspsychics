#include "DxLib.h"
#include "title.h"
#include "global.h"
#include "mydef.h"

void MY_GAME_TITLE() {
	if (AllKeyState[KEY_INPUT_RETURN] != 0)//�G���^�[�L�[��������Ă�����
	{
		GameSceneNow = GAME_SCENE_PLAY;//�V�[�����v���C��ʂɂ���
	}
	if (AllKeyState[KEY_INPUT_V] != 0)//V�L�[�������ꂽ�Ƃ�
	{
		SetBackgroundColor(0, 0, 0);
		GameSceneNow = GAME_SCENE_METHOD;//�V�[���𑀍������ʂɂ���
	}

	DrawString(0, 0, "�^�C�g�����(�v���C��ʂɐi�ނɂ̓G���^�[�L�[�������Ă�������)", GetColor(255, 255, 255));
	DrawString(0, 20, "�@�@�@�@�@�@(���������ʂɐi�ނɂ�V�L�[�������Ă�������)", GetColor(255, 255, 255));

	LoadGraphScreen(50, 0, TITLE_LOGO, FALSE);

	return;
}