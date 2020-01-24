#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "mydef.h"

enum CHARA_IMAGE {
	CHARA_KIND_1 = 0,
	CHARA_KIND_2 = 3,
	CHARA_KIND_3 = 6
};//�L�����̎�ނ̗񋓌^

struct STRUCT_CHARACTOR
{
	char FilePath[128];
	int Handle[CHARA_YOKO_NUM * CHARA_TATE_NUM];//�摜�̃n���h��
	int X[CHARA_YOKO_NUM * CHARA_TATE_NUM];//���̈ʒu
	int Y[CHARA_YOKO_NUM * CHARA_TATE_NUM];//�c�̈ʒu
	int Width[CHARA_YOKO_NUM * CHARA_TATE_NUM];//���̃T�C�Y
	int Height[CHARA_YOKO_NUM * CHARA_TATE_NUM];//�c�̃T�C�Y
	int C_Width[CHARA_YOKO_NUM * CHARA_TATE_NUM];//���̒��S�ʒu
	int C_Height[CHARA_YOKO_NUM * CHARA_TATE_NUM];//�c�̒��S�ʒu
};//CHARA�\����
typedef STRUCT_CHARACTOR CHARA;

struct STRUCT_PLAYER
{
	int Handle[CHARA_MOTION_NUM];//�摜�̃n���h��
	int X;//���̈ʒu
	int Y;//�c�̈ʒu
	int Width;//���̃T�C�Y
	int Height;//�c�̃T�C�Y
	int C_Width;//���̒��S�ʒu
	int C_Height;//�c�̒��S�ʒu
	int NowHandleNum;//���݂̉摜�̃n���h��
	int NowHandleCnt;//���݂̃n���h���J�E���g
	int NowHandleCntMAX;//���݂̃n���h���J�E���gMAX

	int Speed;//���x
	int MoveDist;//�ړ�����

	BOOL CanMoveLeft; //���ɍs���邩
	BOOL CanMoveRight;//�E�ɍs���邩
	BOOL CanMoveUp;//��ɍs���邩
	BOOL CanMoveDown;//���ɍs���邩

	int atariX;//�����蔻���X�ʒu
	int atariY;//�����蔻���Y�ʒu
	int atariWidth;//�����蔻��̕�
	int atariHeight;//�����蔻��̍���
	RECT atariRect;//�����蔻��̋�`�̈�
};//PLAYER�\����
typedef STRUCT_PLAYER PLAYER;

extern CHARA CharaImage;
extern PLAYER Myplayer;
extern PLAYER Myplayer2;

BOOL MY_CHARA_LOAD_BUNKATSU(CHARA*, int, int, int, int, int, const char *);//CHARA�𕪊����ēǂݍ��ސݒ������֐�

BOOL MY_INIT_PLAYER(PLAYER *, CHARA, int *, int, int, int);//�v���C���[������������֐�

void MY_PLAY_PLAYER_OPERATION(void);
void MY_PLAY_PLAYER_OPERATION2(void);

BOOL MY_CHECK_RECT_ATARI_CHARA_MAP_ATARIBASHO(RECT, RECT map[MAP_TATE_NUM][MAP_YOKO_NUM], int *, int *);

void MY_SET_PLAYER_ATARI(PLAYER *);//�v���C���[�̓����蔻��̗̈��ݒ肷��֐�

BOOL MY_CHECK_RECT_ATARI(RECT, RECT);//�̈�̓����蔻�������֐�

BOOL MY_CHECK_RECT_ATARI_CHARA_MAP(RECT, RECT[MAP_TATE_NUM][MAP_YOKO_NUM]);//�}�b�v�Ƃ̓����蔻�������֐�

void MY_PLAY_PLAYER_DRAW(void);
void MY_PLAY_PLAYER_DRAW2(void);

BOOL MY_PLAY_INIT(void);

#endif