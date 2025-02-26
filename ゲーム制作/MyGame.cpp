#include "DxLib.h"
#include "resource.h"

#define GAME_WIDTH	1024	//画面の横
#define GAME_HEIGHT 576		//画面の縦	
#define GAME_COLOR	32		//画面のカラービット

#define GAME_WINDOW_BAR 0
#define GAME_WINDOW_NAME "レトロアクション"

#define GAME_FPS	60	//FPSの数値

#define MOUSE_BUTTON_CODE	129	//0x0000〜0x0080まで

#define PATH_MAX	255

#define GAME_GR 5

#define PLAYER_JUMP_MAX		60	//ジャンプするフレーム秒
#define PLAYER_JUMP_POWER		1	//１フレームのジャンプ量

//エラーメッセージ(タイトル画像)
#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")

#define IMAGE_BACK_PATH			TEXT(".\\IMAGE\\背景_a.png")
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\マリオっぽいキャラ.png")	//プレイヤーの画像

#define IMAGE_TITLE_BK_PATH			TEXT(".\\IMAGE\\タイトル.png")						//タイトル背景の画像
#define IMAGE_TITLE_ROGO_PATH		TEXT(".\\IMAGE\\タイトル_レトロアクション_3.png")	//タイトルロゴの画像
#define IMAGE_TITLE_ROGO_ROTA		0.005	//拡大率
#define IMAGE_TITLE_ROGO_ROTA_MAX	1.0		//拡大率MAX
#define IMAGE_TITLE_ROGO_X_SPEED	0		//X移動速度
#define IMAGE_TITLE_START_PATH		TEXT(".\\IMAGE\\PUSH ENTER KEY.png")					//タイトルスタートの画像
#define IMAGE_TITLE_START_CNT		1		//点滅カウンタ
#define IMAGE_TITLE_START_CNT_MAX	30		//点滅カウンタMAX

#define IMAGE_END_COMP_PATH		TEXT(".\\IMAGE\\ゲームクリア.png")	//エンドコンプ画像
//#define IMAGE_END_COMP_CNT		1			//点滅カウンタ
//#define IMAGE_END_COMP_CNT_MAX	30			//点滅カウンタMAX

#define IMAGE_END_FAIL_PATH		TEXT(".\\IMAGE\\ゲームオーバー.png")	//エンドフォール画像
//#define IMAGE_END_FAIL_CNT		1			//点滅カウンタ
//#define IMAGE_END_FAIL_CNT_MAX	30			//点滅カウンタMAX

//エラーメッセージ(タイトルBGM)
#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")

#define MUSIC_BGM_TITLE_PATH	TEXT(".\\MUSIC\\レトロゲーム風ピコピコ.mp3")	//タイトルのBGM
#define MUSIC_PUSH_ENTER_PATH	TEXT(".\\MUSIC\\システム決定音_9.mp3")
#define MUSIC_BGM_COMP_PATH			TEXT(".\\MUSIC\\Game Clear.mp3")				//コンプリートBGM
#define MUSIC_BGM_FAIL_PATH			TEXT(".\\MUSIC\\Game Over.mp3")					//フォールトBGM
#define MUSIC_PUSH_SPACE_PATH	TEXT(".\\MUSIC\\レトロジャンプ.mp3")

#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")

#define MUSIC_BGM_PATH	TEXT(".\\MUSIC\\NES-Action-D02-2(Stage1-Loop130).mp3")

#define GAME_MAP_TATE_MAX	9
#define GAME_MAP_YOKO_MAX	16
#define GAME_MAP_KIND_MAX	2

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\MAP\\map1.png")

#define MAP_DIV_WIDTH	64
#define MAP_DIV_HEIGHT	64
#define MAP_DIV_TATE	10
#define MAP_DIV_YOKO	4
#define MAP_DIV_NUM		MAP_DIV_TATE * MAP_DIV_YOKO

#define START_ERR_TITLE		TEXT("スタート位置エラー")
#define START_ERR_CAPTION	TEXT("スタート位置が決まっていません")

#define GOAL_ERR_TITLE		TEXT("ゴール位置エラー")
#define GOAL_ERR_CAPTION	TEXT("ゴール位置が決まっていません")

#define ANA_ERR_TITLE		TEXT("穴位置エラー")
#define ANA_ERR_CAPTION		TEXT("穴位置が決まっていません")

#define TOGE_ERR_TITLE		TEXT("トゲ位置エラー")
#define TOGE_ERR_CAPTION	TEXT("トゲ位置が決まっていません")

#define MOUSE_R_CLICK_TITLE		TEXT("ゲーム中断")
#define MOUSE_R_CLICK_CAPTION	TEXT("ゲームを中断し、タイトル画面に戻りますか？")

enum GAME_MAP_KIND
{
	n = -1,
	t = 0,
	y = 1,
	s = 2,
	w = 3,
	o = 5,
	f = 7,
	g = 17,
	d = 18,
};	//マップの種類

enum GAME_MAP_KIND2
{
	N = -1,
	T = 0,
	Y = 1,
	S = 2,
	W = 3,
	O = 5,
	F = 7,
	G = 17,
	D = 18,
};	//マップの種類

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_PLAY2,
	GAME_SCENE_END
};

enum GAME_END {
	GAME_END_COMP,	//コンプリート
	GAME_END_FAIL	//フォールト
};	//ゲームの終了状態

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 3
};	//キャラクターのスピード

typedef struct STRUCT_I_POINT
{
	int x = -1;
	int y = -1;
}iPOINT;

typedef struct STRUCT_MOUSE
{
	int InputValue = 0;	//GetMouseInputの値を入れる
	int WheelValue = 0;	//マウスホイールの回転量(奥はプラス値 / 手前はマイナス値)
	iPOINT Point;		//マウスの座標が入る
	iPOINT OldPoint;	//マウスの座標(直前)が入る
	int OldButton[MOUSE_BUTTON_CODE] = { 0 };	//マウスのボタン入力(直前)が入る
	int Button[MOUSE_BUTTON_CODE] = { 0 };	//マウスのボタン入力が入る
}MOUSE;

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];
	int handle;
	int x;
	int y;
	int width;
	int height;
}IMAGE;

typedef struct STRUCT_CHARA
{
	IMAGE image;				//IMAGE構造体
	int speed;					//速さ
	int CenterX;				//中心X
	int CenterY;				//中心Y
	BOOL IsJump;
	int JumpPower;
	//int x;
	//int y;
	//int mapX;
	int mapY;
	//int width;
	//int height;

	//int choseiX;
	//int choseiY;
	//int choseiWidth;
	//int choseiHeight;

	//int JumpTimeCnt;
	int BeforeJumpY;

	RECT coll;					//当たり判定
	iPOINT collBeforePt;		//当たる前の座標

}CHARA;	//キャラクター構造体

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];
	int handle;
}MUSIC;

typedef struct STRUCT_IMAGE_ROTA
{
	IMAGE image;
	double angle;
	double angleMAX;
	double rate;
	double rateMAX;
}IMAGE_ROTA;

typedef struct STRUCT_IMAGE_BLINK
{
	IMAGE image;
	int Cnt;
	int CntMAX;
	BOOL IsDraw;
}IMAGE_BLINK;

typedef struct STRUCT_MAP_IMAGE
{
	char path[PATH_MAX];				//パス
	int handle[MAP_DIV_NUM];			//分割したの弾の画像ハンドルを取得
	int kind[MAP_DIV_NUM];				//マップの種類
	int width;							//幅
	int height;							//高さ
}MAPCHIP;	//MAP_IMAGE構造体

typedef struct STRUCT_MAP
{
	GAME_MAP_KIND kind;			//マップの種類
	GAME_MAP_KIND2 kind2;			//マップの種類
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
}MAP;	//MAP構造体

int StartTimeFps;
int CountFps;
float CalcFps;
int SampleNumFps = GAME_FPS;

char AllKeyState[256] = { '\0' };
char OldAllKeyState[256] = { '\0' };

int JumpPower;
int JumpFlag;
int Jump;

int key;
int OldX, OldY;
int ScrollX, ScrollY;

int PlayerX, PlayerY;

int Move;
int MoveX, MoveY;
int MoveCounter;

MOUSE mouse;

int GameScene;

int GameEndKind;					//ゲームの終了状態
RECT GoalRect = { -1, -1, -1, -1 };	//ゴールの当たり判定
RECT Goal2Rect = { -1, -1, -1, -1 };//ゴール2の当たり判定
RECT AnaRect  = { -1, -1, -1, -1 };	//穴の当たり判定
RECT Ana2Rect = { -1, -1, -1, -1 };	//穴の当たり判定
RECT TogeRect = { -1, -1, -1, -1 };	//トゲの当たり判定

IMAGE ImageBack;
CHARA player;			//ゲームのキャラ
IMAGE ImageTitleBK;
IMAGE_ROTA ImageTitleROGO;
IMAGE_BLINK ImageTitleSTART;

IMAGE_BLINK ImageEndCOMP;				//エンドコンプの画像
IMAGE_BLINK ImageEndFAIL;				//エンドフォールの画像

MUSIC BGM_TITLE;
MUSIC BGM_PUSH;
MUSIC BGM;
MUSIC BGM_SPACE;
MUSIC BGM_COMP;		//コンプリートのBGM
MUSIC BGM_FAIL;		//フォールトのBGM

GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5
		t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 0(32)
		t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 1(96)
		t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 2(160)
		t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 3(224)
		t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 4(288)
		t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,f,	// 5(352)
		s,t,t,d,t,t,t,t,t,t,t,t,o,t,t,g,	// 6(416)
		y,y,y,t,y,y,y,y,y,y,y,y,t,y,y,y,	// 7(480)
		w,w,w,t,w,w,w,w,w,w,w,w,t,w,w,w		// 8
		
};	//ゲームのマップ

GAME_MAP_KIND2 mapData2[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5
		T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,	// 0(32)
		T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,	// 1(96)
		T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,	// 2(160)
		T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,	// 3(224)
		T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,	// 4(288)
		T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,F,	// 5(352)
		S,T,T,D,T,T,D,T,T,T,O,T,T,T,T,G,	// 6(416)
		Y,Y,Y,Y,Y,Y,Y,Y,Y,Y,Y,Y,Y,Y,Y,Y,	// 7(480)
		W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W		// 8

};	//ゲームのマップ

//ゲームマップの初期化
GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
GAME_MAP_KIND2 mapDataInit2[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//マップチップの画像を管理
MAPCHIP mapChip;

//マップの場所を管理
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
MAP map2[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//スタートの位置
iPOINT startPt{ -1,-1 };
iPOINT startPt2{ -1,-1 };

//マップの当たり判定
RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

VOID MY_FPS_UPDATE(VOID);
VOID MY_FPS_DRAW(VOID);
VOID MY_FPS_WAIT(VOID);

VOID MY_ALL_KEYDOWN_UPDATE(VOID);
BOOL MY_KEY_DOWN(int);
BOOL MY_KEY_UP(int);
BOOL MY_KEYDOWN_KEEP(int, int);

VOID MY_START(VOID);
VOID MY_START_PROC(VOID);
VOID MY_START_DRAW(VOID);

VOID MY_PLAY(VOID);
VOID MY_PLAY_PROC(VOID);
VOID MY_PLAY_DRAW(VOID);

VOID MY_PLAY2(VOID);
VOID MY_PLAY2_PROC(VOID);
VOID MY_PLAY2_DRAW(VOID);

VOID MY_END(VOID);
VOID MY_END_PROC(VOID);
VOID MY_END_DRAW(VOID);

BOOL MY_LOAD_IMAGE(VOID);
VOID MY_DELETE_IMAGE(VOID);

BOOL MY_LOAD_MUSIC(VOID);		//音楽をまとめて読み込む関数
VOID MY_DELETE_MUSIC(VOID);		//音楽をまとめて削除する関数

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT);
BOOL MY_CHECK_RECT_COLL(RECT, RECT);

VOID MY_PLAY_MOVE_JUMP(VOID);

BOOL MY_CHECK_CHARA_GROUND(CHARA p);								//プレイヤーが地面と接しているか当たり判定をする関数

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCndShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);
	SetWindowStyleMode(GAME_WINDOW_BAR);
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));
	SetAlwaysRunFlag(TRUE);

	if (DxLib_Init() == -1) { return-1; }

	if (MY_LOAD_IMAGE() == FALSE) { return-1; }

	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	GameScene = GAME_SCENE_START;

	SetDrawScreen(DX_SCREEN_BACK);

	////プレイヤーの最初の位置を、スタート位置にする
	//for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	//{
	//	for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
	//	{
	//		//スタート位置を探す
	//		if (mapData[tate][yoko] == s)
	//		{
	//			//スタート位置を計算
	//			startPt.x = mapChip.width * yoko + mapChip.width / 2;	//中心X座標を取得
	//			startPt.y = mapChip.height * tate + mapChip.height / 2;	//中心Y座標を取得
	//			break;
	//		}
	//	}
	//	//スタートが決まっていれば、ループ終了
	//	if (startPt.x != -1 && startPt.y != -1) { break; }
	//}

	//プレイヤーの最初の位置を、スタート位置にする
	//ゴールの位置もついでに検索する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//スタート位置を探す
			if (mapData[tate][yoko] == s)
			{
				//スタート位置を計算
				startPt.x = mapChip.width * yoko + mapChip.width / 2;	//中心X座標を取得
				startPt.y = mapChip.height * tate + mapChip.height / 2;	//中心Y座標を取得
			}

			//スタート2位置を探す
			if (mapData[tate][yoko] == S)
			{
				//スタート位置を計算
				startPt2.x = mapChip.width * yoko + mapChip.width / 2;		//中心X座標を取得
				startPt2.y = mapChip.height * tate + mapChip.height / 2;	//中心Y座標を取得
			}

			//ゴール位置を探す
			if (mapData[tate][yoko] == g)
			{
				GoalRect.left = mapChip.width * yoko;
				GoalRect.top = mapChip.height * tate;
				GoalRect.right = mapChip.width * (yoko + 1);
				GoalRect.bottom = mapChip.height * (tate + 1);
			}

			//ゴール2位置を探す
			if (mapData[tate][yoko] == G)
			{
				Goal2Rect.left = mapChip.width * yoko;
				Goal2Rect.top = mapChip.height * tate;
				Goal2Rect.right = mapChip.width * (yoko + 1);
				Goal2Rect.bottom = mapChip.height * (tate + 1);
			}

			//穴の位置を探す
			if (mapData[tate][yoko] == o)
			{
				AnaRect.left = mapChip.width * yoko;
				AnaRect.top = mapChip.height * tate;
				AnaRect.right = mapChip.width * (yoko + 1);
				AnaRect.bottom = mapChip.height * (tate + 1);
			}

			//穴2の位置を探す
			if (mapData[tate][yoko] == O)
			{
				Ana2Rect.left = mapChip.width * yoko;
				Ana2Rect.top = mapChip.height * tate;
				Ana2Rect.right = mapChip.width * (yoko + 1);
				Ana2Rect.bottom = mapChip.height * (tate + 1);
			}

			//トゲの位置を探す
			if (mapData[tate][yoko] == d)
			{
				TogeRect.left = mapChip.width * yoko;
				TogeRect.top = mapChip.height * tate;
				TogeRect.right = mapChip.width * (yoko + 1);
				TogeRect.bottom = mapChip.height * (tate + 1);
			}

		}
	}

	//スタートが決まっていなければ
	if (startPt.x == -1 && startPt.y == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);	return -1;
	}

	//ゴールが決まっていなければ
	if (GoalRect.left == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), GOAL_ERR_CAPTION, GOAL_ERR_TITLE, MB_OK);	return -1;
	}

	//ゴール2が決まっていなければ
	if (Goal2Rect.left == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), GOAL_ERR_CAPTION, GOAL_ERR_TITLE, MB_OK);	return -1;
	}

	//穴が決まっていなければ
	if (AnaRect.left == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), ANA_ERR_CAPTION, ANA_ERR_TITLE, MB_OK);	return -1;
	}

	//トゲが決まっていなければ
	if (TogeRect.left == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), TOGE_ERR_CAPTION, TOGE_ERR_TITLE, MB_OK);	return -1;
	}

	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }
		if (ClearDrawScreen() != 0) { break; }
		
		MY_ALL_KEYDOWN_UPDATE();

		MY_FPS_UPDATE();

		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();
			break;
		case GAME_SCENE_PLAY2:
			MY_PLAY2();
			break;
		case GAME_SCENE_END:
			MY_END();
			break;
		}

		ScreenFlip();
	}

	MY_DELETE_IMAGE();

	MY_DELETE_MUSIC();

	DxLib_End();

	return 0;
}

VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1フレーム目なら時刻を記憶
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60フレーム目なら平均を計算
	{
		int now = GetNowCount();
		//現在の時間から、0フレーム目の時間を引き、FPSの数値で割る＝1FPS辺りの平均時間が計算される
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//かかった時間
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//待つべき時間

	if (waitTime > 0)		//指定のFPS値よりも早い場合
	{
		WaitTimer(waitTime);	//待つ
	}
	return;
}

VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	char TempKey[256];

	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey);

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)
		{
			AllKeyState[i]++;
		}
		else
		{
			AllKeyState[i] = 0;
		}
	}
	return;
}

BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1
		&& AllKeyState[KEY_INPUT_] == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{
	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//スタート画面
VOID MY_START(VOID)
{
	MY_START_PROC();
	MY_START_DRAW();

	return;
}

//スタート画面の処理
VOID MY_START_PROC(VOID)
{
	if (CheckSoundMem(BGM_TITLE.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_TITLE.handle);
		PlaySoundMem(BGM_TITLE.handle, DX_PLAYTYPE_LOOP);
	}

	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		PlaySoundMem(BGM_PUSH.handle, DX_PLAYTYPE_BACK);

		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
			StopSoundMem(BGM_TITLE.handle);	//BGMを止める
		}

		SetMouseDispFlag(FALSE);			//マウスカーソルを非表示

		//プレイヤーの中心位置を計算する
		player.CenterX = startPt.x;
		player.CenterY = startPt.y;

		//プレイヤーの画像の位置を設定する
		player.image.x = player.CenterX;
		player.image.y = player.CenterY;

		//ゲームの終了状態を初期化する
		GameEndKind = GAME_END_FAIL;

		GameScene = GAME_SCENE_PLAY;
	}

	if (ImageTitleROGO.rate < ImageTitleROGO.rateMAX)
	{
		ImageTitleROGO.rate += IMAGE_TITLE_ROGO_ROTA;
	}

	if (ImageTitleROGO.image.x < GAME_WIDTH / 2)
	{
		ImageTitleROGO.image.x += IMAGE_TITLE_ROGO_X_SPEED;
	}
	else
	{
		if (ImageTitleSTART.Cnt < ImageTitleSTART.CntMAX)
		{
			ImageTitleSTART.Cnt += IMAGE_TITLE_START_CNT;
		}
		else
		{
			if (ImageTitleSTART.IsDraw == FALSE)
			{
				ImageTitleSTART.IsDraw = TRUE;
			}
			else if (ImageTitleSTART.IsDraw == TRUE)
			{
				ImageTitleSTART.IsDraw = FALSE;
			}
			ImageTitleSTART.Cnt = 0;
		}
	}

	if (MY_KEY_DOWN(KEY_INPUT_RSHIFT) == TRUE)
	{
		PlaySoundMem(BGM_PUSH.handle, DX_PLAYTYPE_BACK);

		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
			StopSoundMem(BGM_TITLE.handle);	//BGMを止める
		}

		SetMouseDispFlag(FALSE);			//マウスカーソルを非表示

		//プレイヤーの中心位置を計算する
		player.CenterX = startPt2.x;
		player.CenterY = startPt2.y;

		//プレイヤーの画像の位置を設定する
		player.image.x = player.CenterX;
		player.image.y = player.CenterY;

		//ゲームの終了状態を初期化する
		GameEndKind = GAME_END_FAIL;

		GameScene = GAME_SCENE_PLAY2;
	}

	if (ImageTitleROGO.rate < ImageTitleROGO.rateMAX)
	{
		ImageTitleROGO.rate += IMAGE_TITLE_ROGO_ROTA;
	}

	if (ImageTitleROGO.image.x < GAME_WIDTH / 2)
	{
		ImageTitleROGO.image.x += IMAGE_TITLE_ROGO_X_SPEED;
	}
	else
	{
		if (ImageTitleSTART.Cnt < ImageTitleSTART.CntMAX)
		{
			ImageTitleSTART.Cnt += IMAGE_TITLE_START_CNT;
		}
		else
		{
			if (ImageTitleSTART.IsDraw == FALSE)
			{
				ImageTitleSTART.IsDraw = TRUE;
			}
			else if (ImageTitleSTART.IsDraw == TRUE)
			{
				ImageTitleSTART.IsDraw = FALSE;
			}
			ImageTitleSTART.Cnt = 0;
		}
	}

	return;
}

//スタート画面の描画
VOID MY_START_DRAW(VOID)
{
	DrawGraph(ImageTitleBK.x, ImageTitleBK.y, ImageTitleBK.handle, TRUE);

	DrawRotaGraph(
		ImageTitleROGO.image.x, ImageTitleROGO.image.y,
		ImageTitleROGO.rate,
		ImageTitleROGO.angle,
		ImageTitleROGO.image.handle, TRUE);

	if (ImageTitleSTART.IsDraw == TRUE)
	{
		DrawGraph(ImageTitleSTART.image.x, ImageTitleSTART.image.y, ImageTitleSTART.image.handle, TRUE);
	}

	//DrawString(0, 0, "スタート画面(エンターキーを押して)", GetColor(255, 255, 255));
	return;
}

//プレイ画面
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();
	MY_PLAY_DRAW();

	return;
}

//プレイ画面の処理
VOID MY_PLAY_PROC(VOID)
{
	/*if (MY_KEY_DOWN(KEY_INPUT_LCONTROL) == TRUE)
	{
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);
		}

		GameScene = GAME_SCENE_END;

		return;
	}*/

	if (CheckSoundMem(BGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 50, BGM.handle);

		//DX_PLAYTYPE_NORMAL
		//DX_PLAYTYPE_BACK
		//DX_PLAYTYPE_LOOP
		PlaySoundMem(BGM.handle, DX_PLAYTYPE_LOOP);
	}

	//マウスを右クリックすると、タイトル画面に戻る
	if (mouse.Button[MOUSE_INPUT_RIGHT] == TRUE)
	{
		//クリックした座標を取得しておく
		iPOINT R_ClickPt = mouse.Point;

		//マウスを表示
		SetMouseDispFlag(TRUE);

		//終了ダイアログを表示
		int Ret = MessageBox(GetMainWindowHandle(), MOUSE_R_CLICK_CAPTION, MOUSE_R_CLICK_TITLE, MB_YESNO);

		if (Ret == IDYES)		//YESなら、ゲームを中断する
		{
			//強制的にタイトル画面に飛ぶ
			GameScene = GAME_SCENE_START;
			return;

		}
		else if (Ret == IDNO)	//NOなら、ゲームを続行する
		{
			//マウスの位置を、クリックする前に戻す
			SetMousePoint(R_ClickPt.x, R_ClickPt.y);

			//マウスを非表示にする。
			SetMouseDispFlag(FALSE);
		}
	}

	//当たり判定が追いつかないので、画像の位置を当たり判定に使用する
	//当たり判定の領域は、画像よりも少し縮小する。縮小加減は、お好みで。
	RECT PlayerRect;
	PlayerRect.left = player.image.x + 40;
	PlayerRect.top = player.image.y + 40;
	PlayerRect.right = player.image.x + player.image.width - 40;
	PlayerRect.bottom = player.image.y + player.image.height - 40;

	//ゴールに触れているかチェック
	if (MY_CHECK_RECT_COLL(PlayerRect, GoalRect) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);			//マウスカーソルを表示

		GameEndKind = GAME_END_COMP;	//ミッションコンプリート！

		GameScene = GAME_SCENE_END;

		return;	//強制的にエンド画面に飛ぶ
	}

	//穴に触れているかチェック
	if (MY_CHECK_RECT_COLL(PlayerRect, AnaRect) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);			//マウスカーソルを表示

		GameEndKind = GAME_END_FAIL;	//ミッションコンプリート！

		GameScene = GAME_SCENE_END;

		return;	//強制的にエンド画面に飛ぶ
	}

	//穴に触れているかチェック
	if (MY_CHECK_RECT_COLL(PlayerRect, Ana2Rect) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);			//マウスカーソルを表示

		GameEndKind = GAME_END_FAIL;	//ミッションコンプリート！

		GameScene = GAME_SCENE_END;

		return;	//強制的にエンド画面に飛ぶ
	}

	//トゲに触れているかチェック
	if (MY_CHECK_RECT_COLL(PlayerRect, TogeRect) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);			//マウスカーソルを表示

		GameEndKind = GAME_END_FAIL;	//ミッションコンプリート！

		GameScene = GAME_SCENE_END;

		return;	//強制的にエンド画面に飛ぶ
	}

	//プレイヤーが画面外に出たら
	if (player.image.x > GAME_WIDTH || player.image.y > GAME_HEIGHT
		|| player.image.x + player.image.width < 0 || player.image.y + player.image.height < 0)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);			//マウスカーソルを表示

		GameEndKind = GAME_END_FAIL;	//ミッションフォールト！

		GameScene = GAME_SCENE_END;

		return;	//強制的にエンド画面に飛ぶ
	}

	// 移動中ではない場合キー入力を受け付ける
	if (Move == 0)
	{
		player.speed = 2;
		if (MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
		{
			player.CenterX -= player.speed;
			Move = 1;
		}
		if (MY_KEY_DOWN(KEY_INPUT_D) == TRUE)
		{
			player.CenterX += player.speed;
			Move = 1;
		}

		// 進入不可能なマップだった場合は移動できない
		if (Move == 1)
		{
			if (mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX] == 0)
			{
				Move = 0;
			}
			else
			{
				MoveCounter = 0;
			}
		}

		// 停止中は画面のスクロールは行わない
		ScrollX = 0;
		ScrollY = 0;
	}

	// 移動中の場合は移動処理を行う
	if (Move == 1)
	{
		MoveCounter++;

		// 移動処理が終了したら停止中にする
		if (MoveCounter == GAME_FPS)
		{
			Move = 0;

			// プレイヤーの位置を変更する
			player.CenterX += MoveX;

			// 停止中は画面のスクロールは行わない
			ScrollX = 0;
			ScrollY = 0;
		}
		else
		{
			// 経過時間からスクロール量を算出する
			ScrollX = -(2 * GAME_WIDTH * MoveCounter / GAME_FPS);
		}
	}

	/*int JumpPower = 10;

	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		player.CenterY -= JumpPower;
	}
	else
	{
		player.speed = 2;
		if (MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
		{
			player.CenterX -= player.speed;
			Move = 1;
		}
		if (MY_KEY_DOWN(KEY_INPUT_D) == TRUE)
		{
			player.CenterX += player.speed;
			Move = 1;
		}

		int GR = 5;
		player.CenterY += GR;
	}*/

	/*JumpFlag = 0;

	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		if (JumpFlag == 0)
		{
			player.CenterY -= 15;
		}
		JumpFlag = 1;
	}
	else
	{
		JumpFlag = 0;
	}

	player.CenterY += JumpPower;
	JumpPower += 1;

	if (player.CenterY > 480)
	{
		player.CenterY = 480;
		JumpPower = 0;
	}*/

	player.CenterY -= JumpPower;

	// 落下加速度を加える
	JumpPower -= 1;

	// もし地面についていたら止まる
	if (player.CenterY > 416)
	{
		player.CenterY = 416;
		JumpPower = 0;
	}

	// ジャンプボタンを押していて、地面についていたらジャンプ
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) && player.CenterY == 416)
	{
		PlaySoundMem(BGM_SPACE.handle, DX_PLAYTYPE_BACK);

		JumpPower = 15;
	}

	// 画面を初期化する
	ClearDrawScreen();

	//当たり判定
	player.coll.left = player.CenterX - mapChip.width / 2 + 5;
	player.coll.top = player.CenterY - mapChip.height / 2 + 5;
	player.coll.right = player.CenterX + mapChip.width / 2 - 5;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;

	BOOL IsMove = TRUE;

	//プレイヤーとマップがあたっていたら
	if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	{
		/*[キー操作ここから]*/
		player.CenterX = player.collBeforePt.x;
		player.CenterY = player.collBeforePt.y;
		
		//SetMousePoint(player.collBeforePt.x, player.collBeforePt.y);

		IsMove = FALSE;
	}

	//プレイヤーの位置に置き換える
	player.image.x = player.CenterX - player.image.width / 2;
	player.image.y = player.CenterY - player.image.height / 2;

	//画面外にプレイヤーが行かないようにする
	if (player.image.x < 0) { player.image.x = 0; }
	if (player.image.x + player.image.width > GAME_WIDTH) { player.image.x = GAME_WIDTH - player.image.width; }
	if (player.image.y < 0) { player.image.y = 0; }
	if (player.image.y + player.image.height > GAME_HEIGHT) { player.image.y = GAME_HEIGHT - player.image.height; }

	//プレイヤーの当たる以前の位置を設定する
	player.collBeforePt.x = player.CenterX;
	player.collBeforePt.y = player.CenterY;

	return;
}

//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{
	DrawGraph(ImageBack.x, ImageBack.y, ImageBack.handle, TRUE);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップを描画
			DrawGraph(
				map[tate][yoko].x,
				map[tate][yoko].y,
				mapChip.handle[map[tate][yoko].kind],
				TRUE);
		}
	}	
	
	//当たり判定の描画（デバッグ用）
	/*for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//壁ならば
			if (mapData[tate][yoko] == y)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
			}

			//通路ならば
			if (mapData[tate][yoko] == t)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 255, 0), FALSE);
			}
		}
	}*/

	//ゴール,穴,穴2,トゲの描画（デバッグ用）
	/*DrawBox(GoalRect.left, GoalRect.top, GoalRect.right, GoalRect.bottom, GetColor(255, 255, 0), TRUE);
	DrawBox(AnaRect.left, AnaRect.top, AnaRect.right, AnaRect.bottom, GetColor(255, 0, 0), TRUE);
	DrawBox(Ana2Rect.left, Ana2Rect.top, Ana2Rect.right, Ana2Rect.bottom, GetColor(255, 0, 0), TRUE);
	DrawBox(TogeRect.left, TogeRect.top, TogeRect.right, TogeRect.bottom, GetColor(0, 255, 0), TRUE);
	*/
	//プレイヤーのを描画する
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);
	
	//当たり判定の描画（デバッグ用）
	/*DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);*/

	//DrawString(0, 0, "プレイ画面(左のコントロールキーを押して)", GetColor(255, 255, 255));
	return;
}

VOID MY_PLAY2(VOID)
{
	MY_PLAY2_PROC();
	MY_PLAY2_DRAW();

	return;
}

//プレイ2画面の処理
VOID MY_PLAY2_PROC(VOID)
{
	/*if (MY_KEY_DOWN(KEY_INPUT_LCONTROL) == TRUE)
	{
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);
		}

		GameScene = GAME_SCENE_END;

		return;
	}*/

	if (CheckSoundMem(BGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 50, BGM.handle);

		//DX_PLAYTYPE_NORMAL
		//DX_PLAYTYPE_BACK
		//DX_PLAYTYPE_LOOP
		PlaySoundMem(BGM.handle, DX_PLAYTYPE_LOOP);
	}

	//マウスを右クリックすると、タイトル画面に戻る
	if (mouse.Button[MOUSE_INPUT_RIGHT] == TRUE)
	{
		//クリックした座標を取得しておく
		iPOINT R_ClickPt = mouse.Point;

		//マウスを表示
		SetMouseDispFlag(TRUE);

		//終了ダイアログを表示
		int Ret = MessageBox(GetMainWindowHandle(), MOUSE_R_CLICK_CAPTION, MOUSE_R_CLICK_TITLE, MB_YESNO);

		if (Ret == IDYES)		//YESなら、ゲームを中断する
		{
			//強制的にタイトル画面に飛ぶ
			GameScene = GAME_SCENE_START;
			return;

		}
		else if (Ret == IDNO)	//NOなら、ゲームを続行する
		{
			//マウスの位置を、クリックする前に戻す
			SetMousePoint(R_ClickPt.x, R_ClickPt.y);

			//マウスを非表示にする。
			SetMouseDispFlag(FALSE);
		}
	}

	//当たり判定が追いつかないので、画像の位置を当たり判定に使用する
	//当たり判定の領域は、画像よりも少し縮小する。縮小加減は、お好みで。
	RECT PlayerRect;
	PlayerRect.left = player.image.x + 40;
	PlayerRect.top = player.image.y + 40;
	PlayerRect.right = player.image.x + player.image.width - 40;
	PlayerRect.bottom = player.image.y + player.image.height - 40;

	//ゴール2に触れているかチェック
	if (MY_CHECK_RECT_COLL(PlayerRect, Goal2Rect) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);			//マウスカーソルを表示

		GameEndKind = GAME_END_COMP;	//ミッションコンプリート！

		GameScene = GAME_SCENE_END;

		return;	//強制的にエンド画面に飛ぶ
	}

	//穴に触れているかチェック
	if (MY_CHECK_RECT_COLL(PlayerRect, AnaRect) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);			//マウスカーソルを表示

		GameEndKind = GAME_END_FAIL;	//ミッションコンプリート！

		GameScene = GAME_SCENE_END;

		return;	//強制的にエンド画面に飛ぶ
	}

	//穴に触れているかチェック
	if (MY_CHECK_RECT_COLL(PlayerRect, Ana2Rect) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);			//マウスカーソルを表示

		GameEndKind = GAME_END_FAIL;	//ミッションコンプリート！

		GameScene = GAME_SCENE_END;

		return;	//強制的にエンド画面に飛ぶ
	}

	//トゲに触れているかチェック
	if (MY_CHECK_RECT_COLL(PlayerRect, TogeRect) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);			//マウスカーソルを表示

		GameEndKind = GAME_END_FAIL;	//ミッションコンプリート！

		GameScene = GAME_SCENE_END;

		return;	//強制的にエンド画面に飛ぶ
	}

	//プレイヤーが画面外に出たら
	if (player.image.x > GAME_WIDTH || player.image.y > GAME_HEIGHT
		|| player.image.x + player.image.width < 0 || player.image.y + player.image.height < 0)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);			//マウスカーソルを表示

		GameEndKind = GAME_END_FAIL;	//ミッションフォールト！

		GameScene = GAME_SCENE_END;

		return;	//強制的にエンド画面に飛ぶ
	}

	// 移動中ではない場合キー入力を受け付ける
	if (Move == 0)
	{
		player.speed = 2;
		if (MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
		{
			player.CenterX -= player.speed;
			Move = 1;
		}
		if (MY_KEY_DOWN(KEY_INPUT_D) == TRUE)
		{
			player.CenterX += player.speed;
			Move = 1;
		}

		// 進入不可能なマップだった場合は移動できない
		if (Move == 1)
		{
			if (mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX] == 0)
			{
				Move = 0;
			}
			else
			{
				MoveCounter = 0;
			}
		}

		// 停止中は画面のスクロールは行わない
		ScrollX = 0;
		ScrollY = 0;
	}

	// 移動中の場合は移動処理を行う
	if (Move == 1)
	{
		MoveCounter++;

		// 移動処理が終了したら停止中にする
		if (MoveCounter == GAME_FPS)
		{
			Move = 0;

			// プレイヤーの位置を変更する
			player.CenterX += MoveX;

			// 停止中は画面のスクロールは行わない
			ScrollX = 0;
			ScrollY = 0;
		}
		else
		{
			// 経過時間からスクロール量を算出する
			ScrollX = -(2 * GAME_WIDTH * MoveCounter / GAME_FPS);
		}
	}

	/*int JumpPower = 10;

	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		player.CenterY -= JumpPower;
	}
	else
	{
		player.speed = 2;
		if (MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
		{
			player.CenterX -= player.speed;
			Move = 1;
		}
		if (MY_KEY_DOWN(KEY_INPUT_D) == TRUE)
		{
			player.CenterX += player.speed;
			Move = 1;
		}

		int GR = 5;
		player.CenterY += GR;
	}*/

	/*JumpFlag = 0;

	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		if (JumpFlag == 0)
		{
			player.CenterY -= 15;
		}
		JumpFlag = 1;
	}
	else
	{
		JumpFlag = 0;
	}

	player.CenterY += JumpPower;
	JumpPower += 1;

	if (player.CenterY > 480)
	{
		player.CenterY = 480;
		JumpPower = 0;
	}*/

	player.CenterY -= JumpPower;

	// 落下加速度を加える
	JumpPower -= 1;

	// もし地面についていたら止まる
	if (player.CenterY > 416)
	{
		player.CenterY = 416;
		JumpPower = 0;
	}

	// ジャンプボタンを押していて、地面についていたらジャンプ
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) && player.CenterY == 416)
	{
		PlaySoundMem(BGM_SPACE.handle, DX_PLAYTYPE_BACK);

		JumpPower = 15;
	}

	// 画面を初期化する
	ClearDrawScreen();

	//当たり判定
	player.coll.left = player.CenterX - mapChip.width / 2 + 5;
	player.coll.top = player.CenterY - mapChip.height / 2 + 5;
	player.coll.right = player.CenterX + mapChip.width / 2 - 5;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;

	BOOL IsMove = TRUE;

	//プレイヤーとマップがあたっていたら
	if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	{
		/*[キー操作ここから]*/
		player.CenterX = player.collBeforePt.x;
		player.CenterY = player.collBeforePt.y;

		//SetMousePoint(player.collBeforePt.x, player.collBeforePt.y);

		IsMove = FALSE;
	}

	//プレイヤーの位置に置き換える
	player.image.x = player.CenterX - player.image.width / 2;
	player.image.y = player.CenterY - player.image.height / 2;

	//画面外にプレイヤーが行かないようにする
	if (player.image.x < 0) { player.image.x = 0; }
	if (player.image.x + player.image.width > GAME_WIDTH) { player.image.x = GAME_WIDTH - player.image.width; }
	if (player.image.y < 0) { player.image.y = 0; }
	if (player.image.y + player.image.height > GAME_HEIGHT) { player.image.y = GAME_HEIGHT - player.image.height; }

	//プレイヤーの当たる以前の位置を設定する
	player.collBeforePt.x = player.CenterX;
	player.collBeforePt.y = player.CenterY;

	return;
}

//プレイ画面の描画
VOID MY_PLAY2_DRAW(VOID)
{
	DrawGraph(ImageBack.x, ImageBack.y, ImageBack.handle, TRUE);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップを描画
			DrawGraph(
				map2[tate][yoko].x,
				map2[tate][yoko].y,
				mapChip.handle[map2[tate][yoko].kind2],
				TRUE);
		}
	}

	//当たり判定の描画（デバッグ用）
	/*for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//壁ならば
			if (mapData2[tate][yoko] == Y)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
			}

			//通路ならば
			if (mapData2[tate][yoko] == T)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 255, 0), FALSE);
			}
		}
	}*/

	//ゴール,穴,穴2,トゲの描画（デバッグ用）
	/*DrawBox(GoalRect.left, GoalRect.top, GoalRect.right, GoalRect.bottom, GetColor(255, 255, 0), TRUE);
	DrawBox(AnaRect.left, AnaRect.top, AnaRect.right, AnaRect.bottom, GetColor(255, 0, 0), TRUE);
	DrawBox(Ana2Rect.left, Ana2Rect.top, Ana2Rect.right, Ana2Rect.bottom, GetColor(255, 0, 0), TRUE);
	DrawBox(TogeRect.left, TogeRect.top, TogeRect.right, TogeRect.bottom, GetColor(0, 255, 0), TRUE);
	*/
	//プレイヤーのを描画する
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

	//当たり判定の描画（デバッグ用）
	/*DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);*/

	//DrawString(0, 0, "プレイ画面(左のコントロールキーを押して)", GetColor(255, 255, 255));
	return;
}

//エンド画面
VOID MY_END(VOID)
{
	MY_END_PROC();
	MY_END_DRAW();

	return;
}

//エンド画面の処理
VOID MY_END_PROC(VOID)
{
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM_COMP.handle) != 0)
		{
			StopSoundMem(BGM_COMP.handle);	//BGMを止める
		}

		//BGMが流れているなら
		if (CheckSoundMem(BGM_FAIL.handle) != 0)
		{
			StopSoundMem(BGM_FAIL.handle);	//BGMを止める
		}

		GameScene = GAME_SCENE_START;

		return;
	}

	switch (GameEndKind)
	{
	case GAME_END_COMP:
		//コンプリートのとき

		//BGMが流れていないなら
		if (CheckSoundMem(BGM_COMP.handle) == 0)
		{
			//BGMの音量を下げる
			ChangeVolumeSoundMem(255 * 70 / 100, BGM_COMP.handle);	//50%の音量にする
			PlaySoundMem(BGM_COMP.handle, DX_PLAYTYPE_LOOP);
		}

		////コンプリートを点滅
		//if (ImageEndCOMP.Cnt < ImageEndCOMP.CntMAX)
		//{
		//	ImageEndCOMP.Cnt += IMAGE_END_COMP_CNT;
		//}
		//else
		//{
		//	//描画する/しないを決める
		//	if (ImageEndCOMP.IsDraw == FALSE)
		//	{
		//		ImageEndCOMP.IsDraw = TRUE;
		//	}
		//	else if (ImageEndCOMP.IsDraw == TRUE)
		//	{
		//		ImageEndCOMP.IsDraw = FALSE;
		//	}
		//	ImageEndCOMP.Cnt = 0;
		//}
		break;

	case GAME_END_FAIL:
		//フォールトのとき

		//BGMが流れていないなら
		if (CheckSoundMem(BGM_FAIL.handle) == 0)
		{
			//BGMの音量を下げる
			ChangeVolumeSoundMem(255 * 70 / 100, BGM_FAIL.handle);	//50%の音量にする
			PlaySoundMem(BGM_FAIL.handle, DX_PLAYTYPE_LOOP);
		}

		////フォールトを点滅
		//if (ImageEndFAIL.Cnt < ImageEndFAIL.CntMAX)
		//{
		//	ImageEndFAIL.Cnt += IMAGE_END_FAIL_CNT;
		//}
		//else
		//{
		//	//描画する/しないを決める
		//	if (ImageEndFAIL.IsDraw == FALSE)
		//	{
		//		ImageEndFAIL.IsDraw = TRUE;
		//	}
		//	else if (ImageEndFAIL.IsDraw == TRUE)
		//	{
		//		ImageEndFAIL.IsDraw = FALSE;
		//	}
		//	ImageEndFAIL.Cnt = 0;
		//}
		break;
	}

	return;
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{
	//DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 0, 255), TRUE);

	MY_PLAY_DRAW();	//プレイ画面を描画

	//ゲームの終了状態により、描画を変える
	switch (GameEndKind)
	{
	case GAME_END_COMP:
		//コンプリートのとき

		////点滅
		//if (ImageEndCOMP.IsDraw == TRUE)
		//{
			//コンプリートの描画
			DrawGraph(ImageEndCOMP.image.x, ImageEndCOMP.image.y, ImageEndCOMP.image.handle, TRUE);
		//}
		break;

	case GAME_END_FAIL:
		//フォールトのとき

		////点滅
		//if (ImageEndFAIL.IsDraw == TRUE)
		//{
			//フォールトの描画
			DrawGraph(ImageEndFAIL.image.x, ImageEndFAIL.image.y, ImageEndFAIL.image.handle, TRUE);
		//}
		break;

	}

	DrawString(0, 0, "エンド画面(エスケープーキーを押して)", GetColor(255, 255, 255));
	return;
}

//画像の読み込み
BOOL MY_LOAD_IMAGE(VOID)
{
	//タイトル背景
	strcpy_s(ImageTitleBK.path, IMAGE_TITLE_BK_PATH);			//パスの設定
	ImageTitleBK.handle = LoadGraph(ImageTitleBK.path);			//読み込み
	if (ImageTitleBK.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleBK.handle, &ImageTitleBK.width, &ImageTitleBK.height);	//画像の幅と高さを取得
	ImageTitleBK.x = GAME_WIDTH / 2 - ImageTitleBK.width / 2;		//左右中央揃え
	ImageTitleBK.y = GAME_HEIGHT / 2 - ImageTitleBK.height / 2;		//上下中央揃え

	//タイトルロゴ
	strcpy_s(ImageTitleROGO.image.path, IMAGE_TITLE_ROGO_PATH);					//パスの設定
	ImageTitleROGO.image.handle = LoadGraph(ImageTitleROGO.image.path);			//読み込み
	if (ImageTitleROGO.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleROGO.image.handle, &ImageTitleROGO.image.width, &ImageTitleROGO.image.height);	//画像の幅と高さを取得
	ImageTitleROGO.image.x = 512;							//光っている部分から描画したい
	ImageTitleROGO.image.y = GAME_HEIGHT / 3;				//中央寄せ
	ImageTitleROGO.angle = DX_PI * 2;						//回転率
	ImageTitleROGO.angleMAX = DX_PI * 2;					//回転率MAX
	ImageTitleROGO.rate = 0.0;								//拡大率
	ImageTitleROGO.rateMAX = IMAGE_TITLE_ROGO_ROTA_MAX;		//拡大率MAX

	//タイトルスタート
	strcpy_s(ImageTitleSTART.image.path, IMAGE_TITLE_START_PATH);					//パスの設定
	ImageTitleSTART.image.handle = LoadGraph(ImageTitleSTART.image.path);			//読み込み
	if (ImageTitleSTART.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_START_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleSTART.image.handle, &ImageTitleSTART.image.width, &ImageTitleSTART.image.height);	//画像の幅と高さを取得
	ImageTitleSTART.image.x = GAME_WIDTH / 2 - ImageTitleSTART.image.width / 2;					//左右中央揃え
	ImageTitleSTART.image.y = ImageTitleROGO.image.y + ImageTitleROGO.image.height / 2 + 10;	//ロゴの下に表示
	ImageTitleSTART.Cnt = 0;								//カウンタ
	ImageTitleSTART.CntMAX = IMAGE_TITLE_START_CNT_MAX;		//カウンタMAX
	ImageTitleSTART.IsDraw = FALSE;							//描画させない

	//プレイ背景
	strcpy_s(ImageBack.path, IMAGE_BACK_PATH);			//パスの設定
	ImageBack.handle = LoadGraph(ImageBack.path);			//読み込み
	if (ImageBack.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_BACK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageBack.handle, &ImageBack.width, &ImageBack.height);	//画像の幅と高さを取得
	ImageBack.x = GAME_WIDTH / 2 - ImageBack.width / 2;		//左右中央揃え
	ImageBack.y = GAME_HEIGHT / 2 - ImageBack.height / 2;		//上下中央揃え

	//プレイヤーの画像
	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);		//パスの設定
	player.image.handle = LoadGraph(player.image.path);	//読み込み
	if (player.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);	//画像の幅と高さを取得
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;		//左右中央揃え
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;		//上下中央揃え
	player.CenterX = player.image.x + player.image.width / 2;		//画像の横の中心を探す
	player.CenterY = player.image.y + player.image.height / 2;		//画像の縦の中心を探す
	player.speed = CHARA_SPEED_LOW;									//スピードを設定

	//マップ1
	//マップの画像を分割する
	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,										//赤弾のパス
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,			//赤弾を分割する数
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,						//画像を分割するの幅と高さ
		&mapChip.handle[0]);								//分割した画像が入るハンドル

	if (mapRes == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//幅と高さを取得
	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップデータ初期化用に情報をコピー
			mapDataInit[tate][yoko] = mapData[tate][yoko];

			//マップの種類をコピー
			map[tate][yoko].kind = mapData[tate][yoko];

			//マップの幅と高さをコピー
			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;

			//マップの座標を設定
			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;
		}
	}

	//マップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップの当たり判定を設定
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}

	//マップ2
	//マップの画像を分割する
	int mapRes2 = LoadDivGraph(
		GAME_MAP_PATH,										//赤弾のパス
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,			//赤弾を分割する数
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,						//画像を分割するの幅と高さ
		&mapChip.handle[0]);								//分割した画像が入るハンドル

	if (mapRes == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//幅と高さを取得
	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップデータ初期化用に情報をコピー
			mapDataInit2[tate][yoko] = mapData2[tate][yoko];

			//マップの種類をコピー
			map2[tate][yoko].kind2 = mapData2[tate][yoko];

			//マップの幅と高さをコピー
			map2[tate][yoko].width = mapChip.width;
			map2[tate][yoko].height = mapChip.height;

			//マップの座標を設定
			map2[tate][yoko].x = yoko * map2[tate][yoko].width;
			map2[tate][yoko].y = tate * map2[tate][yoko].height;
		}
	}

	//マップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップの当たり判定を設定
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}


	//エンドコンプ
	strcpy_s(ImageEndCOMP.image.path, IMAGE_END_COMP_PATH);					//パスの設定
	ImageEndCOMP.image.handle = LoadGraph(ImageEndCOMP.image.path);			//読み込み
	if (ImageEndCOMP.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_END_COMP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndCOMP.image.handle, &ImageEndCOMP.image.width, &ImageEndCOMP.image.height);	//画像の幅と高さを取得
	ImageEndCOMP.image.x = GAME_WIDTH / 2 - ImageTitleBK.width / 2;		//左右中央揃え
	ImageEndCOMP.image.y = GAME_HEIGHT / 2 - ImageTitleBK.height / 2;		//上下中央揃え
																									//ImageEndCOMP.image.x = GAME_WIDTH / 2 - ImageEndCOMP.image.width / 2;			//左右中央揃え
	//ImageEndCOMP.image.y = GAME_HEIGHT / 2 - ImageEndCOMP.image.height / 2;			//上下中央揃え
	//ImageEndCOMP.Cnt = 0;									//カウンタ
	//ImageEndCOMP.CntMAX = IMAGE_END_COMP_CNT_MAX;			//カウンタMAX
	//ImageEndCOMP.IsDraw = FALSE;							//描画させない

	//エンドフォール
	strcpy_s(ImageEndFAIL.image.path, IMAGE_END_FAIL_PATH);				//パスの設定
	ImageEndFAIL.image.handle = LoadGraph(ImageEndFAIL.image.path);			//読み込み
	if (ImageEndFAIL.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_END_FAIL_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndFAIL.image.handle, &ImageEndFAIL.image.width, &ImageEndFAIL.image.height);	//画像の幅と高さを取得
	ImageEndFAIL.image.x = GAME_WIDTH / 2 - ImageTitleBK.width / 2;		//左右中央揃え
	ImageEndFAIL.image.y = GAME_HEIGHT / 2 - ImageTitleBK.height / 2;		//上下中央揃え
																										//ImageEndFAIL.image.x = GAME_WIDTH / 2 - ImageEndFAIL.image.width / 2;			//左右中央揃え
	//ImageEndFAIL.image.y = GAME_HEIGHT / 2 - ImageEndFAIL.image.height / 2;			//上下中央揃え
	//ImageEndFAIL.Cnt = 0;									//カウンタ
	//ImageEndFAIL.CntMAX = IMAGE_END_FAIL_CNT_MAX;			//カウンタMAX
	//ImageEndFAIL.IsDraw = FALSE;							//描画させない

	return TRUE;
}

//画像をまとめて削除する関数
VOID MY_DELETE_IMAGE(VOID)
{
	DeleteGraph(ImageBack.handle);
	DeleteGraph(player.image.handle);
	DeleteGraph(ImageTitleBK.handle);
	DeleteGraph(ImageTitleROGO.image.handle);
	DeleteGraph(ImageTitleSTART.image.handle);
	DeleteGraph(ImageEndCOMP.image.handle);
	DeleteGraph(ImageEndFAIL.image.handle);

	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }

	return;
}

//音楽の読み込み
BOOL MY_LOAD_MUSIC(VOID)
{
	//タイトルのBGM
	strcpy_s(BGM_TITLE.path, MUSIC_BGM_TITLE_PATH);				//パスの設定
	BGM_TITLE.handle = LoadSoundMem(BGM_TITLE.path);			//読み込み
	if (BGM_TITLE.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_TITLE_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//PUSH ENTER KEYの音
	strcpy_s(BGM_PUSH.path, MUSIC_PUSH_ENTER_PATH);				//パスの設定
	BGM_PUSH.handle = LoadSoundMem(BGM_PUSH.path);			//読み込み
	if (BGM_PUSH.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_PUSH_ENTER_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//プレイ画面のBGM
	strcpy_s(BGM.path, MUSIC_BGM_PATH);				//パスの設定
	BGM.handle = LoadSoundMem(BGM.path);			//読み込み
	if (BGM.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(BGM_SPACE.path, MUSIC_PUSH_SPACE_PATH);				//パスの設定
	BGM_SPACE.handle = LoadSoundMem(BGM_SPACE.path);			//読み込み
	if (BGM_SPACE.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_PUSH_SPACE_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//コンプリートBGM
	strcpy_s(BGM_COMP.path, MUSIC_BGM_COMP_PATH);				//パスの設定
	BGM_COMP.handle = LoadSoundMem(BGM_COMP.path);				//読み込み
	if (BGM_COMP.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_COMP_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//フォールトのBGM
	strcpy_s(BGM_FAIL.path, MUSIC_BGM_FAIL_PATH);				//パスの設定
	BGM_FAIL.handle = LoadSoundMem(BGM_FAIL.path);				//読み込み
	if (BGM_FAIL.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_FAIL_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//音楽をまとめて削除する関数
VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM_TITLE.handle);	//タイトルのBGM
	DeleteSoundMem(BGM_PUSH.handle);	//PUSH ENTER KEYの音
	DeleteSoundMem(BGM.handle);			//プレイ画面のBGM
	DeleteSoundMem(BGM_SPACE.handle);
	DeleteSoundMem(BGM_COMP.handle);
	DeleteSoundMem(BGM_FAIL.handle);

	return;
}

//マップとプレイヤーの当たり判定をする関数
BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player)
{
	//マップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//プレイヤーとマップが当たっているとき
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//壁のときは、プレイヤーとマップが当たっている
				if (map[tate][yoko].kind == y) { return TRUE; }
				if (map[tate][yoko].kind == w) { return TRUE; }
				if (map2[tate][yoko].kind2 == Y) { return TRUE; }
				if (map2[tate][yoko].kind2 == W) { return TRUE; }
			}
		}
	}

	return FALSE;
}

//領域の当たり判定をする関数
BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)
	{
		return TRUE;	//当たっている
	}

	return FALSE;		//当たっていない
}

//VOID MY_PLAY_MOVE_JUMP(VOID)
//{
//	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
//	{
//		if (MY_CHECK_CHARA_GROUND(player) == TRUE)
//		{
//			if (player.IsJump == FALSE)
//			{
//				player.IsJump = TRUE;
//				player.BeforeJumpY = player.CenterY;
//				player.BeforeJumpY = player.CenterY;
//				player.JumpPower = -10;
//			}
//		}
//	}
//
//	if (player.IsJump == TRUE)
//	{
//		player.mapY -= GAME_GR;											//重力に負けない！
//		int  y_temp = player.mapY;										//現在のY座標を記録
//		player.mapY += (player.mapY - player.BeforeJumpY) + player.JumpPower;	//上に向かう数値を計算させる
//		player.JumpPower = 1;												//初速度を１にする
//		player.BeforeJumpY = y_temp;										//以前の位置に記録
//		player.y = player.mapY;
//
//		//地面に当たっていれば
//		if (MY_CHECK_CHARA_GROUND(player) == TRUE)
//		{
//			//ジャンプ終了
//			player.IsJump = FALSE;
//		}
//	}
//}

//プレイヤーが地面と接しているか当たり判定をする関数
//BOOL MY_CHECK_CHARA_GROUND(CHARA p)
//{
//	//グリフィンがいる位置を配列的に計算する
//	//int ArrX_L = (p.mapX + player.choseiX) / MAP_DIV_WIDTH;				//X位置（左）
//	int yoko = (p.mapX + p.width + p.choseiWidth) / MAP_DIV_WIDTH;	//X位置（右）
//	int tate = (p.mapY + p.height + p.choseiHeight) / MAP_DIV_HEIGHT;//Y位置(下の埋まっている位置)
//
//	//画面外の値を取得しない
//	//if (ArrX_L < 0) { ArrX_L = 0; }
//	if (yoko >= GAME_MAP_YOKO_MAX) { yoko = GAME_MAP_YOKO_MAX - 1; }
//
//	//プレイヤーとマップが当たっているとき
//	//壁のときは、プレイヤーとマップが当たっている
//	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
//	{
//		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
//		{
//				//壁のときは、プレイヤーとマップが当たっている
//				if (map[tate][yoko].kind == y)
//				{
//					return TRUE;
//				}
//		}
//	}
//
//	return FALSE;
//}
