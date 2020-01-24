#include "DxLib.h"
#include "play.h"
#include "global.h"
#include "mydef.h"
#include "map.h"
#include "player.h"
#include "key.h"

void MY_GAME_PLAY() {
	if (CheckHitKey(KEY_INPUT_BACK) == 1)//�o�b�N�X�y�[�X�L�[��������Ă�����
	{
		GameSceneNow = GAME_SCENE_END;//�V�[�����v���C��ʂɂ���
	}
	if (CheckHitKey(KEY_INPUT_V) == 1)//V�L�[�������ꂽ�Ƃ�
	{
		GameSceneNow = GAME_SCENE_INVENTORY;//�V�[���������i��ʂɂ���
	}
	
	MY_PLAY_MAP_DRAW();			//�}�b�v��`��

	MY_PLAY_PLAYER_DRAW();		//�v���C���[��`��

	DrawString(0, 0, "�v���C���(�G���h��ʂɍs���ɂ̓o�b�N�X�y�[�X�L�[�������Ă�������)", GetColor(255, 255, 255));
	DrawString(0, 20, "�@�@�@�@�@(�����i��ʂɍs���ɂ�V�L�[�������Ă�������)", GetColor(255, 255, 255));

	return;

}