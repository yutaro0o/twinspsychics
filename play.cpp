#include "DxLib.h"
#include "play.h"
#include "global.h"
#include "mydef.h"
#include "map.h"

void MY_GAME_PLAY() {
	if (AllKeyState[KEY_INPUT_BACK] != 0)//�G���^�[�L�[��������Ă�����
	{
		GameSceneNow = GAME_SCENE_END;//�V�[�����v���C��ʂɂ���
	}
	if (AllKeyState[KEY_INPUT_V] != 0)//V�L�[�������ꂽ�Ƃ�
	{
		GameSceneNow = GAME_SCENE_INVENTORY;//�V�[���������i��ʂɂ���
	}


	DrawString(0, 0, "�v���C���(�G���h��ʂɍs���ɂ̓o�b�N�X�y�[�X�L�[�������Ă�������)", GetColor(255, 255, 255));
	DrawString(0, 20, "�@�@�@�@�@(�����i��ʂɍs���ɂ�V�L�[�������Ă�������)", GetColor(255, 255, 255));

	return;

}