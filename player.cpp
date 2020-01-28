#include "Dxlib.h"
#include "player.h"
#include "mydef.h"
#include "global.h"
#include "map.h"

int PlayerImageNum1[CHARA_MOTION_NUM] = {
	0, 1, 2,
	12, 13, 14,
	24, 25, 26,
	36, 37, 38
};

int PlayerImageNum2[CHARA_MOTION_NUM] = {
	3, 4, 5,
	15, 16, 17,
	27, 28, 29,
	39, 40, 41
};

PLAYER Myplayer;
PLAYER Myplayer2;

RECT rectMap_NG[MAP_TATE_NUM][MAP_YOKO_NUM];
RECT rectMap_NG_First[MAP_TATE_NUM][MAP_YOKO_NUM];

RECT rectMap_Item[MAP_TATE_NUM][MAP_YOKO_NUM];
RECT rectMap_Item_First[MAP_TATE_NUM][MAP_YOKO_NUM];

BOOL MY_CHARA_LOAD_BUNKATSU(CHARA *c, int bun_num, int bun_x_num, int bun_y_num, int bun_width, int bun_height, const char *path)
{
	int ret = 0;
	wsprintf(c->FilePath, path);//�t�@�C���p�X���R�s�[

	ret = LoadDivGraph(c->FilePath, bun_num, bun_x_num, bun_y_num, bun_width, bun_height, c->Handle);

	if (ret == -1) { return FALSE; }//�摜�ǂݍ��݃G���[
	
	for (int cnt = 0; cnt < MAP_YOKO_NUM * MAP_TATE_NUM; cnt++)
	{
		GetGraphSize(//�摜�T�C�Y���擾
			c->Handle[cnt], //�n���h������A�摜�̕��ƍ������擾���āE�E�E
			&c->Width[cnt], //MAP�\���̂̕��ɁA�摜�̕���ݒ肷��
			&c->Height[cnt]); //MAP�\���̂̋t���ɉ摜�̍�����ݒ肷��

		c->C_Width[cnt] = c->Width[cnt] / 2;//�摜�̉��T�C�Y�̒��S���擾
		c->C_Height[cnt] = c->Height[cnt] / 2;//�摜�̂��ăT�C�Y�̒��S���擾
	}
	return TRUE;
}

BOOL MY_INIT_PLAYER(PLAYER *p, CHARA c, int *num, int x, int y, int speed)
{
	//*(num + 0)�͔z��̐擪�A�h���X
	for (int mot = 0; mot < CHARA_MOTION_NUM; mot++)
	{
		p->Handle[mot] = c.Handle[*(num + mot)];//�摜�̃n���h��������
	}
	p->X = x;
	p->Y = y;
	p->Width = c.Width[*(num + 0)];//�ŏ��̉摜�̉�����ݒ肷��
	p->Height = c.Height[*(num + 0)];//�ŏ��̉摜�̍�����ݒ肷��
	p->C_Width = c.C_Width[*(num + 0)];//�ŏ��̉摜�̉����̒��S��ݒ肷��
	p->C_Height = c.C_Height[*(num + 0)];//�ŏ��̉摜�̍����̒��S��ݒ肷��

	//�}�b�v�������Ɠ����傫���ɂ���
	p->Width = MAP_SIZE_YOKO;
	p->Height = MAP_SIZE_TATE;
	p->C_Width = MAP_SIZE_YOKO / 2;
	p->C_Height = MAP_SIZE_TATE / 2;

	p->NowHandleNum = 0;//���ʌ����̍ŏ��̉摜
	p->NowHandleCnt = 0;//�摜�J�E���^��������

	p->NowHandleCntMAX = 4;//�摜�J�E���^MAX��������
	//�p�����[�^�ݒ�
	p->Speed = speed;

	p->MoveDist = x;//���̋������}�b�v�̍ŏ����瓮���������Ƃ��Đݒ肷��
	
	p->CanMoveLeft = TRUE;//���Ɉړ��ł���
	p->CanMoveRight = TRUE;//�E�Ɉړ��ł���
	p->CanMoveUp = TRUE;//��Ɉړ��ł���
	p->CanMoveDown = TRUE;//���Ɉړ��ł���

	//�����蔻��̈ʒu��ǂ������ɗv����
	p->atariX = 3;
	p->atariY = 3;
	p->atariWidth = 29;
	p->atariHeight = 29;

	//MY_SET_PLAYER_ATARI(p);//�v���C���[�̓����蔻��̗̈��ݒ肷��

	return TRUE;
}
BOOL MY_INIT_PLAYER2(PLAYER *p, CHARA c, int *num, int x, int y, int speed)
{
	//*(num + 0)�͔z��̐擪�A�h���X
	for (int mot = 0; mot < CHARA_MOTION_NUM; mot++)
	{
		p->Handle[mot] = c.Handle[*(num + mot)];//�摜�̃n���h��������
	}
	p->X = x;
	p->Y = y;
	p->Width = c.Width[*(num + 0)];//�ŏ��̉摜�̉�����ݒ肷��
	p->Height = c.Height[*(num + 0)];//�ŏ��̉摜�̍�����ݒ肷��
	p->C_Width = c.C_Width[*(num + 0)];//�ŏ��̉摜�̉����̒��S��ݒ肷��
	p->C_Height = c.C_Height[*(num + 0)];//�ŏ��̉摜�̍����̒��S��ݒ肷��

	//�}�b�v�������Ɠ����傫���ɂ���
	p->Width = MAP_SIZE_YOKO;
	p->Height = MAP_SIZE_TATE;
	p->C_Width = MAP_SIZE_YOKO / 2;
	p->C_Height = MAP_SIZE_TATE / 2;

	p->NowHandleNum = 0;//���ʌ����̍ŏ��̉摜
	p->NowHandleCnt = 0;//�摜�J�E���^��������

	p->NowHandleCntMAX = 4;//�摜�J�E���^MAX��������
	//�p�����[�^�ݒ�
	p->Speed = speed;

	p->MoveDist = x;//���̋������}�b�v�̍ŏ����瓮���������Ƃ��Đݒ肷��

	p->CanMoveLeft = TRUE;//���Ɉړ��ł���
	p->CanMoveRight = TRUE;//�E�Ɉړ��ł���
	p->CanMoveUp = TRUE;//��Ɉړ��ł���
	p->CanMoveDown = TRUE;//���Ɉړ��ł���

	//�����蔻��̈ʒu��ǂ������ɗv����
	p->atariX = 3;
	p->atariY = 3;
	p->atariWidth = 29;
	p->atariHeight = 29;

	//MY_SET_PLAYER_ATARI(p);//�v���C���[�̓����蔻��̗̈��ݒ肷��

	return TRUE;
}

void MY_PLAY_PLAYER_OPERATION(void)
{
	BOOL IsKeyDown = FALSE;

	if ((AllKeyState[KEY_INPUT_LEFT] != 0 || AllKeyState[KEY_INPUT_A] != 0 ) && IsKeyDown == FALSE)//�����L�[��������Ă�����
	{
		IsKeyDown = TRUE;//�L�[�������ꂽ

		if (Myplayer.NowHandleCnt < Myplayer.NowHandleCntMAX)
		{
			Myplayer.NowHandleCnt++;
			Myplayer2.NowHandleCnt++;
		}
		else
		{
			Myplayer.NowHandleCnt = 0;
			if (Myplayer.NowHandleNum >= 3 && Myplayer.NowHandleNum < 5)
			{
				Myplayer.NowHandleNum++; //���̍������̉摜
				Myplayer2.NowHandleNum++;
			}
			else
			{
				Myplayer.NowHandleNum = 3;//��ԍŏ��̍������̉摜
				Myplayer2.NowHandleNum = 3;
			}
		}
		//�������ɂ܂�������
		Myplayer.CanMoveLeft = TRUE;
		Myplayer2.CanMoveLeft = TRUE;

		MY_SET_PLAYER_ATARI(&Myplayer);//�v���C���[�̓����蔻��̗̈��ݒ�
		MY_SET_PLAYER_ATARI(&Myplayer2);

		Myplayer.atariRect.left -= 4;//�����A�����蔻��̗̈�����ɂ��炷
		Myplayer2.atariRect.left -= 4;
		Myplayer.atariRect.right -= 4;//�����A�����蔻��̗̈�����ɂ��炷
		Myplayer2.atariRect.right -= 4;

		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer.atariRect, rectMap_NG) == TRUE)//���ɍs���Ȃ����̂Ɠ���������
		{
			Myplayer.CanMoveLeft = FALSE;//���ɍs���Ȃ�
		}
		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer2.atariRect, rectMap_NG) == TRUE)//���ɍs���Ȃ����̂Ɠ���������
		{
			Myplayer2.CanMoveLeft = FALSE;//���ɍs���Ȃ�
		}
		if (Myplayer.CanMoveLeft == TRUE)//���Ɉړ��ł���Ƃ�
		{
			if (MapImage.charaStopFlag == FALSE)//�v���C���[���ړ��ł���Ƃ�
			{
				if (Myplayer.X > 0)
				{
					Myplayer.X -= Myplayer.Speed;//�v���C���[�����Ɉړ�
				}
			}
			if (Myplayer.MoveDist > 0)
			{
				Myplayer.MoveDist -= Myplayer.Speed;//�������������v�Z
			}
		}
		if (Myplayer2.CanMoveLeft == TRUE)//���Ɉړ��ł���Ƃ�
		{
			if (MapImage.charaStopFlag == FALSE)//�v���C���[���ړ��ł���Ƃ�
			{
				if (Myplayer2.X > 0)
				{
					Myplayer2.X -= Myplayer2.Speed;//�v���C���[�����Ɉړ�
				}
			}
			if (Myplayer2.MoveDist > 0)
			{
				Myplayer2.MoveDist -= Myplayer2.Speed;//�������������v�Z
			}
		}
	}
	if ((AllKeyState[KEY_INPUT_RIGHT] != 0 || AllKeyState[KEY_INPUT_D] != 0) && IsKeyDown == FALSE)//�E���L�[��������Ă�����
	{
		IsKeyDown = TRUE;//�L�[�������ꂽ

		if (Myplayer.NowHandleCnt < Myplayer.NowHandleCntMAX)
		{
			Myplayer.NowHandleCnt++;
			Myplayer2.NowHandleCnt++;
		}
		else
		{
			Myplayer.NowHandleCnt = 0;

			if (Myplayer.NowHandleNum >= 6 && Myplayer.NowHandleNum < 8)
			{
				Myplayer.NowHandleNum++;//���̉E�����̉摜
				Myplayer2.NowHandleNum++;
			}
			else
			{
				Myplayer.NowHandleNum = 6;//��ԍŏ��̉E�����̉摜
				Myplayer2.NowHandleNum = 6;
			}
		}

		//�E�����ɁA�܂�������
		Myplayer.CanMoveRight = TRUE;
		Myplayer2.CanMoveRight = TRUE;

		MY_SET_PLAYER_ATARI(&Myplayer);//�v���C���[�̓����蔻��̗̈��ݒ�
		MY_SET_PLAYER_ATARI(&Myplayer2);
		Myplayer.atariRect.left += 4; //�����A�v���C���[�̓����蔻��̗̈���E�ɂ��炷
		Myplayer2.atariRect.left += 4;
		Myplayer.atariRect.right += 4; //�����A�v���C���[�̓����蔻��̗̈���E�ɂ��炷
		Myplayer2.atariRect.right += 4;

		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer.atariRect, rectMap_NG) == TRUE)//�E�ɍs���Ȃ����̂Ɠ���������
		{
			Myplayer.CanMoveRight = FALSE;//�E�ɍs���Ȃ�
		}
		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer2.atariRect, rectMap_NG) == TRUE)//�E�ɍs���Ȃ����̂Ɠ���������
		{
			Myplayer2.CanMoveRight = FALSE;//�E�ɍs���Ȃ�
		}
		if (Myplayer.CanMoveRight == TRUE)//�E�Ɉړ��ł���Ƃ�
		{
			if (MapImage.charaStopFlag == FALSE)//�v���C���[���ړ��ł���Ƃ��i�J�n�ʒu�j
			{
				if (Myplayer.X + Myplayer.Width < GAME_WIDTH)
				{
					Myplayer.X += Myplayer.Speed;//�v���C���[���E�Ɉړ�
				}
			}

			if (Myplayer.MoveDist < MAP_SIZE_YOKO * MAP_YOKO_NUM)
			{
				Myplayer.MoveDist += Myplayer.Speed;//�������������v�Z
			}
		}
		if (Myplayer2.CanMoveRight == TRUE)//�E�Ɉړ��ł���Ƃ�
		{
			if (MapImage.charaStopFlag == FALSE)//�v���C���[���ړ��ł���Ƃ��i�J�n�ʒu�j
			{
				if (Myplayer2.X + Myplayer2.Width < GAME_WIDTH)
				{
					Myplayer2.X += Myplayer2.Speed;//�v���C���[���E�Ɉړ�
				}
			}

			if (Myplayer2.MoveDist < MAP_SIZE_YOKO * MAP_YOKO_NUM)
			{
				Myplayer2.MoveDist += Myplayer2.Speed;//�������������v�Z
			}
		}

	}
	if ((AllKeyState[KEY_INPUT_UP] != 0 || AllKeyState[KEY_INPUT_W] != 0) && IsKeyDown == FALSE)//����L�[��������Ă�����
	{
		IsKeyDown = TRUE;//�L�[�������ꂽ

		if (Myplayer.NowHandleCnt < Myplayer.NowHandleCntMAX)
		{
			Myplayer.NowHandleCnt++;
			Myplayer2.NowHandleCnt++;
		}
		else
		{
			Myplayer.NowHandleCnt = 0;
			if (Myplayer.NowHandleNum >= 9 && Myplayer.NowHandleNum < 11)
			{
				Myplayer.NowHandleNum++; //���̏�����̉摜
				Myplayer2.NowHandleNum++;
			}
			else
			{
				Myplayer.NowHandleNum = 9;//��ԍŏ��̏�����̉摜
				Myplayer2.NowHandleNum = 9;
			}
		}
		//������ɂ܂�������
		Myplayer.CanMoveUp = TRUE;
		Myplayer2.CanMoveUp = TRUE;

		MY_SET_PLAYER_ATARI(&Myplayer);//�v���C���[�̓����蔻��̗̈��ݒ�
		MY_SET_PLAYER_ATARI(&Myplayer2);
		Myplayer.atariRect.top -= 4;//�����A�����蔻��̗̈����ɂ��炷
		Myplayer2.atariRect.top -= 4;
		Myplayer.atariRect.bottom -= 4;//�����A�����蔻��̗̈����ɂ��炷
		Myplayer2.atariRect.bottom -= 4;

		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer.atariRect, rectMap_NG) == TRUE)//��ɍs���Ȃ����̂Ɠ���������
		{
			Myplayer.CanMoveUp = FALSE;//��ɍs���Ȃ�
		}
		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer2.atariRect, rectMap_NG) == TRUE)//��ɍs���Ȃ����̂Ɠ���������
		{
			Myplayer2.CanMoveUp = FALSE;//��ɍs���Ȃ�
		}
		if (Myplayer.CanMoveUp == TRUE)//��Ɉړ��ł���Ƃ�
		{
			if (MapImage.charaStopFlag == FALSE)//�v���C���[���ړ��ł���Ƃ�
			{
				if (Myplayer.Y > 0)
				{
					Myplayer.Y -= Myplayer.Speed;//�v���C���[����Ɉړ�
				}
			}
		}
		if (Myplayer2.CanMoveUp == TRUE)//��Ɉړ��ł���Ƃ�
		{
			if (MapImage.charaStopFlag == FALSE)//�v���C���[���ړ��ł���Ƃ�
			{
				if (Myplayer2.Y > 0)
				{
					Myplayer2.Y -= Myplayer2.Speed;//�v���C���[����Ɉړ�
				}
			}
		}
	}
	if ((AllKeyState[KEY_INPUT_DOWN] != 0 || AllKeyState[KEY_INPUT_S] != 0) && IsKeyDown == FALSE)//�����L�[��������Ă�����
	{
		IsKeyDown = TRUE;//�L�[�������ꂽ

		if (Myplayer.NowHandleCnt < Myplayer.NowHandleCntMAX)
		{
			Myplayer.NowHandleCnt++;
			Myplayer2.NowHandleCnt++;
		}
		else
		{
			Myplayer.NowHandleCnt = 0;
			Myplayer2.NowHandleCnt = 0;

			if (Myplayer.NowHandleNum >= 0 && Myplayer.NowHandleNum < 2)
			{
				Myplayer.NowHandleNum++;//���̉E�����̉摜
				Myplayer2.NowHandleNum++;
			}
			else
			{
				Myplayer.NowHandleNum = 0;//��ԍŏ��̉E�����̉摜
				Myplayer2.NowHandleNum = 0;
			}
		}

		//�������ɁA�܂�������
		Myplayer.CanMoveDown = TRUE;
		Myplayer2.CanMoveDown = TRUE;

		MY_SET_PLAYER_ATARI(&Myplayer);//�v���C���[�̓����蔻��̗̈��ݒ�
		MY_SET_PLAYER_ATARI(&Myplayer2);
		Myplayer.atariRect.top += 4; //�����A�v���C���[�̓����蔻��̗̈�����ɂ��炷
		Myplayer2.atariRect.top += 4;
		Myplayer.atariRect.bottom += 4; //�����A�v���C���[�̓����蔻��̗̈�����ɂ��炷
		Myplayer2.atariRect.bottom += 4;

		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer.atariRect, rectMap_NG) == TRUE)//���ɍs���Ȃ����̂Ɠ���������
		{
			Myplayer.CanMoveDown = FALSE;//���ɍs���Ȃ�
		}
		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer2.atariRect, rectMap_NG) == TRUE)//���ɍs���Ȃ����̂Ɠ���������
		{
			Myplayer2.CanMoveDown = FALSE;//���ɍs���Ȃ�
		}
		if (Myplayer.CanMoveDown == TRUE)//���Ɉړ��ł���Ƃ�
		{
			if (MapImage.charaStopFlag == FALSE)//�v���C���[���ړ��ł���Ƃ��i�J�n�ʒu�j
			{
				if (Myplayer.Y + Myplayer.Height < GAME_HEIGHT)
				{
					Myplayer.Y += Myplayer.Speed;//�v���C���[�����Ɉړ�
				}
			}
		}
		if (Myplayer2.CanMoveDown == TRUE)//���Ɉړ��ł���Ƃ�
		{
			if (MapImage.charaStopFlag == FALSE)//�v���C���[���ړ��ł���Ƃ��i�J�n�ʒu�j
			{
				if (Myplayer2.Y + Myplayer2.Height < GAME_HEIGHT)
				{
					Myplayer2.Y += Myplayer2.Speed;//�v���C���[�����Ɉړ�
				}
			}
		}
	}
}


BOOL MY_CHECK_RECT_ATARI_CHARA_MAP_ATARIBASHO(RECT chara, RECT map[MAP_TATE_NUM][MAP_YOKO_NUM], int *atariX, int *atariY)
{
	for (int tate = 0; tate < MAP_TATE_NUM; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_NUM; yoko++)
		{
			//�L�����N�^�[�̓������Ă���ꏊ���擾
			if (MY_CHECK_RECT_ATARI(chara, map[tate][yoko]) == TRUE)
			{
				*atariY = tate;//atariY�̃A�h���X���w��������̏ꏊ�ɁA�����������̂̏c�̈ʒu������
				*atariX = yoko;//atariX�̃A�h���X���w��������̏ꏊ�ɁA�����������̂̉��̈ʒu������

				return TRUE;
			}
		}
	}
	return FALSE;//�������Ă��Ȃ�
}

void MY_SET_PLAYER_ATARI(PLAYER *p)
{
	//�����蔻��̗̈�̐ݒ�
	p->atariRect.left = p->X + p->atariX + 2;						//���݂�X�ʒu + �����蔻���X�ʒu
	p->atariRect.top = p->Y + p->atariY + 2;							//���݂�Y�ʒu + �����蔻���X�ʒu
	p->atariRect.right = p->X + p->atariWidth - 2;					//���݂�X�ʒu + �����蔻���X�ʒu + �����蔻��̕�
	p->atariRect.bottom = p->Y + p->atariY + p->atariHeight - 2;	//���݂�Y�ʒu + �����蔻���X�ʒu + �����蔻��̍���
	return;
}

//�̈�̓����蔻�������֐�
BOOL MY_CHECK_RECT_ATARI(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top)
	{
		return TRUE;//�������Ă���
	}
	return FALSE;
}

//�L�����N�^�[�ƃ}�b�v�̓����蔻�������֐�
BOOL MY_CHECK_RECT_ATARI_CHARA_MAP(RECT chara, RECT map[MAP_TATE_NUM][MAP_YOKO_NUM])
{
	for (int tate = 0; tate < MAP_TATE_NUM; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_NUM; yoko++)
		{
			if (MY_CHECK_RECT_ATARI(chara, map[tate][yoko]) == TRUE)
			{
				return TRUE;
			}
		}
	}
	return FALSE;//�������ĂȂ�
}

//�v���C���[1��\������֐�
void MY_PLAY_PLAYER_DRAW(void)
{
	//�v���C���[���g�債�ĕ`��
	DrawExtendGraph(
		Myplayer.X,
		Myplayer.Y,
		Myplayer.X + Myplayer.Width,
		Myplayer.Y + Myplayer.Height,
		Myplayer.Handle[Myplayer.NowHandleNum], TRUE);

	DrawBox(
		Myplayer.atariRect.left,
		Myplayer.atariRect.top,
		Myplayer.atariRect.right,
		Myplayer.atariRect.bottom,
		GetColor(0, 0, 255), FALSE);	//�g���`��
	
	return;
}
//�v���C���[2��\������֐�
void MY_PLAY_PLAYER_DRAW2(void)
{
	//�v���C���[���g�債�ĕ`��
	DrawExtendGraph(
		Myplayer2.X,
		Myplayer2.Y,
		Myplayer2.X + Myplayer2.Width,
		Myplayer2.Y + Myplayer2.Height,
		Myplayer2.Handle[Myplayer2.NowHandleNum], TRUE);

	DrawBox(
		Myplayer2.atariRect.left,
		Myplayer2.atariRect.top,
		Myplayer2.atariRect.right,
		Myplayer2.atariRect.bottom,
		GetColor(0, 255, 0), FALSE);	//�g���`��

	return;
}

//�������֐�
BOOL MY_PLAY_INIT(void)
{
	if (MY_INIT_PLAYER(&Myplayer, CharaImage, &PlayerImageNum1[0], CHARA1_X * MAP_SIZE_YOKO, CHARA1_Y * MAP_SIZE_TATE, CHARA_SPEED) == FALSE) { MessageBox(NULL, "CHARA_INIT", "NotFound", MB_OK); return FALSE; }
	if (MY_INIT_PLAYER(&Myplayer2, CharaImage, &PlayerImageNum2[0], CHARA2_X * MAP_SIZE_YOKO, CHARA2_Y * MAP_SIZE_TATE, CHARA_SPEED) == FALSE) { MessageBox(NULL, "CHARA_INIT", "NotFound", MB_OK); return FALSE; }

	return TRUE;
}