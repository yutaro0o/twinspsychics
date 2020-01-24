#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "mydef.h"

enum CHARA_IMAGE {
	CHARA_KIND_1 = 0,
	CHARA_KIND_2 = 3,
	CHARA_KIND_3 = 6
};//キャラの種類の列挙型

struct STRUCT_CHARACTOR
{
	char FilePath[128];
	int Handle[CHARA_YOKO_NUM * CHARA_TATE_NUM];//画像のハンドル
	int X[CHARA_YOKO_NUM * CHARA_TATE_NUM];//横の位置
	int Y[CHARA_YOKO_NUM * CHARA_TATE_NUM];//縦の位置
	int Width[CHARA_YOKO_NUM * CHARA_TATE_NUM];//横のサイズ
	int Height[CHARA_YOKO_NUM * CHARA_TATE_NUM];//縦のサイズ
	int C_Width[CHARA_YOKO_NUM * CHARA_TATE_NUM];//横の中心位置
	int C_Height[CHARA_YOKO_NUM * CHARA_TATE_NUM];//縦の中心位置
};//CHARA構造体
typedef STRUCT_CHARACTOR CHARA;

struct STRUCT_PLAYER
{
	int Handle[CHARA_MOTION_NUM];//画像のハンドル
	int X;//横の位置
	int Y;//縦の位置
	int Width;//横のサイズ
	int Height;//縦のサイズ
	int C_Width;//横の中心位置
	int C_Height;//縦の中心位置
	int NowHandleNum;//現在の画像のハンドル
	int NowHandleCnt;//現在のハンドルカウント
	int NowHandleCntMAX;//現在のハンドルカウントMAX

	int Speed;//速度
	int MoveDist;//移動距離

	BOOL CanMoveLeft; //左に行けるか
	BOOL CanMoveRight;//右に行けるか
	BOOL CanMoveUp;//上に行けるか
	BOOL CanMoveDown;//下に行けるか

	int atariX;//当たり判定のX位置
	int atariY;//当たり判定のY位置
	int atariWidth;//当たり判定の幅
	int atariHeight;//当たり判定の高さ
	RECT atariRect;//当たり判定の矩形領域
};//PLAYER構造体
typedef STRUCT_PLAYER PLAYER;

extern CHARA CharaImage;
extern PLAYER Myplayer;
extern PLAYER Myplayer2;

BOOL MY_CHARA_LOAD_BUNKATSU(CHARA*, int, int, int, int, int, const char *);//CHARAを分割して読み込む設定をする関数

BOOL MY_INIT_PLAYER(PLAYER *, CHARA, int *, int, int, int);//プレイヤーを初期化する関数

void MY_PLAY_PLAYER_OPERATION(void);
void MY_PLAY_PLAYER_OPERATION2(void);

BOOL MY_CHECK_RECT_ATARI_CHARA_MAP_ATARIBASHO(RECT, RECT map[MAP_TATE_NUM][MAP_YOKO_NUM], int *, int *);

void MY_SET_PLAYER_ATARI(PLAYER *);//プレイヤーの当たり判定の領域を設定する関数

BOOL MY_CHECK_RECT_ATARI(RECT, RECT);//領域の当たり判定をする関数

BOOL MY_CHECK_RECT_ATARI_CHARA_MAP(RECT, RECT[MAP_TATE_NUM][MAP_YOKO_NUM]);//マップとの当たり判定をする関数

void MY_PLAY_PLAYER_DRAW(void);
void MY_PLAY_PLAYER_DRAW2(void);

BOOL MY_PLAY_INIT(void);

#endif