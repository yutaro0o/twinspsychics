#include "DxLib.h"
#include "inventory.h"
#include "global.h"


void MY_GAME_INVENTORY() {

	if (CheckHitKey(KEY_INPUT_M) == 1)//M�L�[�������ꂽ�Ƃ�
	{
		GameSceneNow = GAME_SCENE_PLAY;//�V�[�����v���C��ʂɂ���
	}

	DrawString(0, 0, "�����i���(�v���C��ʂɖ߂�ɂ�M�L�[�������Ă�������)", GetColor(255, 255, 255));

	return;

}