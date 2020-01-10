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
	DrawBox(0, 0, 800, 450, GetColor(255, 255, 255), TRUE);

	DrawRotaGraph(GAME_WIDTH / 2, GAME_HEIGHT / 2, 0.8, 0.0, LoadGraph(TITLE_LOGO), FALSE);

	DrawString(0, 0, "�^�C�g�����(�v���C��ʂɐi�ނɂ̓G���^�[�L�[�������Ă�������)", GetColor(0, 0, 255));
	DrawString(0, 20, "�@�@�@�@�@�@(���������ʂɐi�ނɂ�V�L�[�������Ă�������)", GetColor(0, 0, 255));

	return;
}