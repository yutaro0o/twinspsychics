extern int AllKeyState[256];	//キー状態の格納

enum GAME_SCENE {
	GAME_SCENE_TITLE,		//タイトル画面
	GAME_SCENE_METHOD,		//操作説明画面
	GAME_SCENE_PLAY,		//プレイ画面
	GAME_SCENE_INVENTORY,	//所持品画面
	GAME_SCENE_END			//エンド画面
};

extern int GameSceneNow;


