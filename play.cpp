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

	if (MY_PLAY_CHECK_GAME_END() == TRUE)
	{
		GameSceneNow = (int)GAME_SCENE_END;//�V�[�����G���h��ʂɂ���
	}
	else
	{
		MY_PLAY_PLAYER_OPERATION();//�v���C���[1�̑���
		MY_PLAY_PLAYER_OPERATION2();//�v���C���[2�̑���
	}

	MY_PLAY_MAP_DRAW();			//�}�b�v��`��

	MY_PLAY_PLAYER_DRAW();		//�v���C���[��`��
	MY_PLAY_PLAYER_DRAW2();     //�v���C���[2��`��

	DrawString(0, 0, "�v���C���(�G���h��ʂɍs���ɂ̓o�b�N�X�y�[�X�L�[�������Ă�������)", GetColor(255, 255, 255));
	DrawString(0, 20, "�@�@�@�@�@(�����i��ʂɍs���ɂ�V�L�[�������Ă�������)", GetColor(255, 255, 255));

	return;

}

//########## �Q�[���G���h�����肷��֐� ##########
BOOL MY_PLAY_CHECK_GAME_END(VOID)
{
	//�v���C���[�̈ʒu�́A�v���C���[�̒��S
	int PlayerToMapNumY = (Myplayer.Y + Myplayer.C_Height) / MAP_SIZE_YOKO;
	int PlayerToMapNumX = (Myplayer.MoveDist + Myplayer.C_Width) / MAP_SIZE_TATE;
	int PlayerToMapNumY2 = (Myplayer2.Y + Myplayer2.C_Height) / MAP_SIZE_YOKO;
	int PlayerToMapNumX2 = (Myplayer2.MoveDist + Myplayer2.C_Width) / MAP_SIZE_TATE;

	if (PlayerToMapNumX < 0 || PlayerToMapNumX > MAP_YOKO_NUM) { return FALSE; }	//�}�b�v�̔z��O�ŃS�[���ɂȂ�o�O������
	if (PlayerToMapNumY < 0 || PlayerToMapNumY > MAP_TATE_NUM) { return FALSE; }	//�}�b�v�̔z��O�ŃS�[���ɂȂ�o�O������
	if (PlayerToMapNumX2 < 0 || PlayerToMapNumX2 > MAP_YOKO_NUM) { return FALSE; }	//�}�b�v�̔z��O�ŃS�[���ɂȂ�o�O������
	if (PlayerToMapNumY2 < 0 || PlayerToMapNumY2 > MAP_TATE_NUM) { return FALSE; }	//�}�b�v�̔z��O�ŃS�[���ɂȂ�o�O������


	//�v���C���[���S�[���̃��m�ƐڐG�����Ƃ�
	if (MapData[PlayerToMapNumY][PlayerToMapNumX] == MapGoalKind[0]
		&& MapData[PlayerToMapNumY2][PlayerToMapNumX2] == MapGoalKind[0])
	{
		return TRUE;
	}

	return FALSE;	//�Q�[�����s
}