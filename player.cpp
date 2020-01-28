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
	wsprintf(c->FilePath, path);//ファイルパスをコピー

	ret = LoadDivGraph(c->FilePath, bun_num, bun_x_num, bun_y_num, bun_width, bun_height, c->Handle);

	if (ret == -1) { return FALSE; }//画像読み込みエラー
	
	for (int cnt = 0; cnt < MAP_YOKO_NUM * MAP_TATE_NUM; cnt++)
	{
		GetGraphSize(//画像サイズを取得
			c->Handle[cnt], //ハンドルから、画像の幅と高さを取得して・・・
			&c->Width[cnt], //MAP構造体の幅に、画像の幅を設定する
			&c->Height[cnt]); //MAP構造体の逆さに画像の高さを設定する

		c->C_Width[cnt] = c->Width[cnt] / 2;//画像の横サイズの中心を取得
		c->C_Height[cnt] = c->Height[cnt] / 2;//画像のたてサイズの中心を取得
	}
	return TRUE;
}

BOOL MY_INIT_PLAYER(PLAYER *p, CHARA c, int *num, int x, int y, int speed)
{
	//*(num + 0)は配列の先頭アドレス
	for (int mot = 0; mot < CHARA_MOTION_NUM; mot++)
	{
		p->Handle[mot] = c.Handle[*(num + mot)];//画像のハンドルを入れる
	}
	p->X = x;
	p->Y = y;
	p->Width = c.Width[*(num + 0)];//最初の画像の横幅を設定する
	p->Height = c.Height[*(num + 0)];//最初の画像の高さを設定する
	p->C_Width = c.C_Width[*(num + 0)];//最初の画像の横幅の中心を設定する
	p->C_Height = c.C_Height[*(num + 0)];//最初の画像の高さの中心を設定する

	//マップ一つ当たりと同じ大きさにする
	p->Width = MAP_SIZE_YOKO;
	p->Height = MAP_SIZE_TATE;
	p->C_Width = MAP_SIZE_YOKO / 2;
	p->C_Height = MAP_SIZE_TATE / 2;

	p->NowHandleNum = 0;//正面向きの最初の画像
	p->NowHandleCnt = 0;//画像カウンタを初期化

	p->NowHandleCntMAX = 4;//画像カウンタMAXを初期化
	//パラメータ設定
	p->Speed = speed;

	p->MoveDist = x;//今の距離をマップの最初から動いた距離として設定する
	
	p->CanMoveLeft = TRUE;//左に移動できる
	p->CanMoveRight = TRUE;//右に移動できる
	p->CanMoveUp = TRUE;//上に移動できる
	p->CanMoveDown = TRUE;//下に移動できる

	//当たり判定の位置を良い感じに要調整
	p->atariX = 3;
	p->atariY = 3;
	p->atariWidth = 29;
	p->atariHeight = 29;

	//MY_SET_PLAYER_ATARI(p);//プレイヤーの当たり判定の領域を設定する

	return TRUE;
}
BOOL MY_INIT_PLAYER2(PLAYER *p, CHARA c, int *num, int x, int y, int speed)
{
	//*(num + 0)は配列の先頭アドレス
	for (int mot = 0; mot < CHARA_MOTION_NUM; mot++)
	{
		p->Handle[mot] = c.Handle[*(num + mot)];//画像のハンドルを入れる
	}
	p->X = x;
	p->Y = y;
	p->Width = c.Width[*(num + 0)];//最初の画像の横幅を設定する
	p->Height = c.Height[*(num + 0)];//最初の画像の高さを設定する
	p->C_Width = c.C_Width[*(num + 0)];//最初の画像の横幅の中心を設定する
	p->C_Height = c.C_Height[*(num + 0)];//最初の画像の高さの中心を設定する

	//マップ一つ当たりと同じ大きさにする
	p->Width = MAP_SIZE_YOKO;
	p->Height = MAP_SIZE_TATE;
	p->C_Width = MAP_SIZE_YOKO / 2;
	p->C_Height = MAP_SIZE_TATE / 2;

	p->NowHandleNum = 0;//正面向きの最初の画像
	p->NowHandleCnt = 0;//画像カウンタを初期化

	p->NowHandleCntMAX = 4;//画像カウンタMAXを初期化
	//パラメータ設定
	p->Speed = speed;

	p->MoveDist = x;//今の距離をマップの最初から動いた距離として設定する

	p->CanMoveLeft = TRUE;//左に移動できる
	p->CanMoveRight = TRUE;//右に移動できる
	p->CanMoveUp = TRUE;//上に移動できる
	p->CanMoveDown = TRUE;//下に移動できる

	//当たり判定の位置を良い感じに要調整
	p->atariX = 3;
	p->atariY = 3;
	p->atariWidth = 29;
	p->atariHeight = 29;

	//MY_SET_PLAYER_ATARI(p);//プレイヤーの当たり判定の領域を設定する

	return TRUE;
}

void MY_PLAY_PLAYER_OPERATION(void)
{
	BOOL IsKeyDown = FALSE;

	if ((AllKeyState[KEY_INPUT_LEFT] != 0 || AllKeyState[KEY_INPUT_A] != 0 ) && IsKeyDown == FALSE)//左矢印キーが押されていた時
	{
		IsKeyDown = TRUE;//キーを押された

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
				Myplayer.NowHandleNum++; //次の左向きの画像
				Myplayer2.NowHandleNum++;
			}
			else
			{
				Myplayer.NowHandleNum = 3;//一番最初の左向きの画像
				Myplayer2.NowHandleNum = 3;
			}
		}
		//左方向にまだ動ける
		Myplayer.CanMoveLeft = TRUE;
		Myplayer2.CanMoveLeft = TRUE;

		MY_SET_PLAYER_ATARI(&Myplayer);//プレイヤーの当たり判定の領域を設定
		MY_SET_PLAYER_ATARI(&Myplayer2);

		Myplayer.atariRect.left -= 4;//少し、当たり判定の領域を左にずらす
		Myplayer2.atariRect.left -= 4;
		Myplayer.atariRect.right -= 4;//少し、当たり判定の領域を左にずらす
		Myplayer2.atariRect.right -= 4;

		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer.atariRect, rectMap_NG) == TRUE)//左に行けないものと当たった時
		{
			Myplayer.CanMoveLeft = FALSE;//左に行けない
		}
		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer2.atariRect, rectMap_NG) == TRUE)//左に行けないものと当たった時
		{
			Myplayer2.CanMoveLeft = FALSE;//左に行けない
		}
		if (Myplayer.CanMoveLeft == TRUE)//左に移動できるとき
		{
			if (MapImage.charaStopFlag == FALSE)//プレイヤーが移動できるとき
			{
				if (Myplayer.X > 0)
				{
					Myplayer.X -= Myplayer.Speed;//プレイヤーを左に移動
				}
			}
			if (Myplayer.MoveDist > 0)
			{
				Myplayer.MoveDist -= Myplayer.Speed;//動いた距離を計算
			}
		}
		if (Myplayer2.CanMoveLeft == TRUE)//左に移動できるとき
		{
			if (MapImage.charaStopFlag == FALSE)//プレイヤーが移動できるとき
			{
				if (Myplayer2.X > 0)
				{
					Myplayer2.X -= Myplayer2.Speed;//プレイヤーを左に移動
				}
			}
			if (Myplayer2.MoveDist > 0)
			{
				Myplayer2.MoveDist -= Myplayer2.Speed;//動いた距離を計算
			}
		}
	}
	if ((AllKeyState[KEY_INPUT_RIGHT] != 0 || AllKeyState[KEY_INPUT_D] != 0) && IsKeyDown == FALSE)//右矢印キーが押されていた時
	{
		IsKeyDown = TRUE;//キーを押された

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
				Myplayer.NowHandleNum++;//次の右向きの画像
				Myplayer2.NowHandleNum++;
			}
			else
			{
				Myplayer.NowHandleNum = 6;//一番最初の右向きの画像
				Myplayer2.NowHandleNum = 6;
			}
		}

		//右方向に、まだ動ける
		Myplayer.CanMoveRight = TRUE;
		Myplayer2.CanMoveRight = TRUE;

		MY_SET_PLAYER_ATARI(&Myplayer);//プレイヤーの当たり判定の領域を設定
		MY_SET_PLAYER_ATARI(&Myplayer2);
		Myplayer.atariRect.left += 4; //少し、プレイヤーの当たり判定の領域を右にずらす
		Myplayer2.atariRect.left += 4;
		Myplayer.atariRect.right += 4; //少し、プレイヤーの当たり判定の領域を右にずらす
		Myplayer2.atariRect.right += 4;

		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer.atariRect, rectMap_NG) == TRUE)//右に行けないものと当たった時
		{
			Myplayer.CanMoveRight = FALSE;//右に行けない
		}
		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer2.atariRect, rectMap_NG) == TRUE)//右に行けないものと当たった時
		{
			Myplayer2.CanMoveRight = FALSE;//右に行けない
		}
		if (Myplayer.CanMoveRight == TRUE)//右に移動できるとき
		{
			if (MapImage.charaStopFlag == FALSE)//プレイヤーが移動できるとき（開始位置）
			{
				if (Myplayer.X + Myplayer.Width < GAME_WIDTH)
				{
					Myplayer.X += Myplayer.Speed;//プレイヤーを右に移動
				}
			}

			if (Myplayer.MoveDist < MAP_SIZE_YOKO * MAP_YOKO_NUM)
			{
				Myplayer.MoveDist += Myplayer.Speed;//動いた距離を計算
			}
		}
		if (Myplayer2.CanMoveRight == TRUE)//右に移動できるとき
		{
			if (MapImage.charaStopFlag == FALSE)//プレイヤーが移動できるとき（開始位置）
			{
				if (Myplayer2.X + Myplayer2.Width < GAME_WIDTH)
				{
					Myplayer2.X += Myplayer2.Speed;//プレイヤーを右に移動
				}
			}

			if (Myplayer2.MoveDist < MAP_SIZE_YOKO * MAP_YOKO_NUM)
			{
				Myplayer2.MoveDist += Myplayer2.Speed;//動いた距離を計算
			}
		}

	}
	if ((AllKeyState[KEY_INPUT_UP] != 0 || AllKeyState[KEY_INPUT_W] != 0) && IsKeyDown == FALSE)//上矢印キーが押されていた時
	{
		IsKeyDown = TRUE;//キーを押された

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
				Myplayer.NowHandleNum++; //次の上向きの画像
				Myplayer2.NowHandleNum++;
			}
			else
			{
				Myplayer.NowHandleNum = 9;//一番最初の上向きの画像
				Myplayer2.NowHandleNum = 9;
			}
		}
		//上方向にまだ動ける
		Myplayer.CanMoveUp = TRUE;
		Myplayer2.CanMoveUp = TRUE;

		MY_SET_PLAYER_ATARI(&Myplayer);//プレイヤーの当たり判定の領域を設定
		MY_SET_PLAYER_ATARI(&Myplayer2);
		Myplayer.atariRect.top -= 4;//少し、当たり判定の領域を上にずらす
		Myplayer2.atariRect.top -= 4;
		Myplayer.atariRect.bottom -= 4;//少し、当たり判定の領域を上にずらす
		Myplayer2.atariRect.bottom -= 4;

		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer.atariRect, rectMap_NG) == TRUE)//上に行けないものと当たった時
		{
			Myplayer.CanMoveUp = FALSE;//上に行けない
		}
		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer2.atariRect, rectMap_NG) == TRUE)//上に行けないものと当たった時
		{
			Myplayer2.CanMoveUp = FALSE;//上に行けない
		}
		if (Myplayer.CanMoveUp == TRUE)//上に移動できるとき
		{
			if (MapImage.charaStopFlag == FALSE)//プレイヤーが移動できるとき
			{
				if (Myplayer.Y > 0)
				{
					Myplayer.Y -= Myplayer.Speed;//プレイヤーを上に移動
				}
			}
		}
		if (Myplayer2.CanMoveUp == TRUE)//上に移動できるとき
		{
			if (MapImage.charaStopFlag == FALSE)//プレイヤーが移動できるとき
			{
				if (Myplayer2.Y > 0)
				{
					Myplayer2.Y -= Myplayer2.Speed;//プレイヤーを上に移動
				}
			}
		}
	}
	if ((AllKeyState[KEY_INPUT_DOWN] != 0 || AllKeyState[KEY_INPUT_S] != 0) && IsKeyDown == FALSE)//下矢印キーが押されていた時
	{
		IsKeyDown = TRUE;//キーを押された

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
				Myplayer.NowHandleNum++;//次の右向きの画像
				Myplayer2.NowHandleNum++;
			}
			else
			{
				Myplayer.NowHandleNum = 0;//一番最初の右向きの画像
				Myplayer2.NowHandleNum = 0;
			}
		}

		//下方向に、まだ動ける
		Myplayer.CanMoveDown = TRUE;
		Myplayer2.CanMoveDown = TRUE;

		MY_SET_PLAYER_ATARI(&Myplayer);//プレイヤーの当たり判定の領域を設定
		MY_SET_PLAYER_ATARI(&Myplayer2);
		Myplayer.atariRect.top += 4; //少し、プレイヤーの当たり判定の領域を下にずらす
		Myplayer2.atariRect.top += 4;
		Myplayer.atariRect.bottom += 4; //少し、プレイヤーの当たり判定の領域を下にずらす
		Myplayer2.atariRect.bottom += 4;

		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer.atariRect, rectMap_NG) == TRUE)//下に行けないものと当たった時
		{
			Myplayer.CanMoveDown = FALSE;//下に行けない
		}
		if (MY_CHECK_RECT_ATARI_CHARA_MAP(Myplayer2.atariRect, rectMap_NG) == TRUE)//下に行けないものと当たった時
		{
			Myplayer2.CanMoveDown = FALSE;//下に行けない
		}
		if (Myplayer.CanMoveDown == TRUE)//下に移動できるとき
		{
			if (MapImage.charaStopFlag == FALSE)//プレイヤーが移動できるとき（開始位置）
			{
				if (Myplayer.Y + Myplayer.Height < GAME_HEIGHT)
				{
					Myplayer.Y += Myplayer.Speed;//プレイヤーを下に移動
				}
			}
		}
		if (Myplayer2.CanMoveDown == TRUE)//下に移動できるとき
		{
			if (MapImage.charaStopFlag == FALSE)//プレイヤーが移動できるとき（開始位置）
			{
				if (Myplayer2.Y + Myplayer2.Height < GAME_HEIGHT)
				{
					Myplayer2.Y += Myplayer2.Speed;//プレイヤーを下に移動
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
			//キャラクターの当たっている場所を取得
			if (MY_CHECK_RECT_ATARI(chara, map[tate][yoko]) == TRUE)
			{
				*atariY = tate;//atariYのアドレスが指し示す先の場所に、当たったものの縦の位置を入れる
				*atariX = yoko;//atariXのアドレスが指し示す先の場所に、当たったものの横の位置を入れる

				return TRUE;
			}
		}
	}
	return FALSE;//当たっていない
}

void MY_SET_PLAYER_ATARI(PLAYER *p)
{
	//当たり判定の領域の設定
	p->atariRect.left = p->X + p->atariX + 2;						//現在のX位置 + 当たり判定のX位置
	p->atariRect.top = p->Y + p->atariY + 2;							//現在のY位置 + 当たり判定のX位置
	p->atariRect.right = p->X + p->atariWidth - 2;					//現在のX位置 + 当たり判定のX位置 + 当たり判定の幅
	p->atariRect.bottom = p->Y + p->atariY + p->atariHeight - 2;	//現在のY位置 + 当たり判定のX位置 + 当たり判定の高さ
	return;
}

//領域の当たり判定をする関数
BOOL MY_CHECK_RECT_ATARI(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top)
	{
		return TRUE;//当たっている
	}
	return FALSE;
}

//キャラクターとマップの当たり判定をする関数
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
	return FALSE;//当たってない
}

//プレイヤー1を表示する関数
void MY_PLAY_PLAYER_DRAW(void)
{
	//プレイヤーを拡大して描画
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
		GetColor(0, 0, 255), FALSE);	//枠線描画
	
	return;
}
//プレイヤー2を表示する関数
void MY_PLAY_PLAYER_DRAW2(void)
{
	//プレイヤーを拡大して描画
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
		GetColor(0, 255, 0), FALSE);	//枠線描画

	return;
}

//初期化関数
BOOL MY_PLAY_INIT(void)
{
	if (MY_INIT_PLAYER(&Myplayer, CharaImage, &PlayerImageNum1[0], CHARA1_X * MAP_SIZE_YOKO, CHARA1_Y * MAP_SIZE_TATE, CHARA_SPEED) == FALSE) { MessageBox(NULL, "CHARA_INIT", "NotFound", MB_OK); return FALSE; }
	if (MY_INIT_PLAYER(&Myplayer2, CharaImage, &PlayerImageNum2[0], CHARA2_X * MAP_SIZE_YOKO, CHARA2_Y * MAP_SIZE_TATE, CHARA_SPEED) == FALSE) { MessageBox(NULL, "CHARA_INIT", "NotFound", MB_OK); return FALSE; }

	return TRUE;
}