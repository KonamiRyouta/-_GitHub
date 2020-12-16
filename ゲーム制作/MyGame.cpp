#include"DxLib.h"

#define GAME_WIDTH	1024	//画面の横
#define GAME_HEIGHT 576		//画面の縦	
#define GAME_COLOR	32		//画面のカラービット

#define GAME_WINDOW_BAR 0
#define GAME_WINDOW_NAME "レトロアクション"

#define GAME_FPS	60	//FPSの数値

#define MOUSE_BUTTON_CODE	129	//0x0000～0x0080まで

#define PATH_MAX	255

//エラーメッセージ(タイトル画像)
#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")

#define IMAGE_BACK_PATH			TEXT(".\\IMAGE\\背景_a.png")
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\キャラ2.png")	//プレイヤーの画像

#define IMAGE_TITLE_BK_PATH			TEXT(".\\IMAGE\\タイトル.png")						//タイトル背景の画像
#define IMAGE_TITLE_ROGO_PATH		TEXT(".\\IMAGE\\タイトル_レトロアクション_3.png")	//タイトルロゴの画像
#define IMAGE_TITLE_ROGO_ROTA		0.005	//拡大率
#define IMAGE_TITLE_ROGO_ROTA_MAX	1.0		//拡大率MAX
#define IMAGE_TITLE_ROGO_X_SPEED	0		//X移動速度
#define IMAGE_TITLE_START_PATH		TEXT(".\\IMAGE\\PUSH ENTER KEY.png")					//タイトルスタートの画像
#define IMAGE_TITLE_START_CNT		1		//点滅カウンタ
#define IMAGE_TITLE_START_CNT_MAX	30		//点滅カウンタMAX

//エラーメッセージ(タイトルBGM)
#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")

#define MUSIC_BGM_TITLE_PATH	TEXT(".\\MUSIC\\レトロゲーム風ピコピコ.mp3")	//タイトルのBGM
#define MUSIC_PUSH_ENTER_PATH	TEXT(".\\MUSIC\\システム決定音_9.mp3")

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

#define MOUSE_R_CLICK_TITLE		TEXT("ゲーム中断")
#define MOUSE_R_CLICK_CAPTION	TEXT("ゲームを中断し、タイトル画面に戻りますか？")

enum GAME_MAP_KIND
{
	n = -1,
	t = 0,
	y = 1,
	s = 2,
	k = 3,
	o = 5
};	//マップの種類


enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END
};

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

int PlayerX, PlayerY;
int JumpPower;

MOUSE mouse;

int GameScene;

IMAGE ImageBack;
CHARA player;			//ゲームのキャラ
IMAGE ImageTitleBK;
IMAGE_ROTA ImageTitleROGO;
IMAGE_BLINK ImageTitleSTART;

MUSIC BGM_TITLE;
MUSIC BGM_PUSH;
MUSIC BGM;

GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,
		t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 0
		t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 1
		t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 2
		t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 3
		t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 4
		t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 5
		t,t,t,t,t,y,t,t,t,t,t,t,t,t,t,t,	// 6
		s,t,t,y,y,y,t,t,t,t,y,t,t,t,t,t,	// 7
		y,y,y,k,k,k,y,y,y,y,y,o,o,y,y,y,	// 8

	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,
		//t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 0
		//t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 1
		//t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 2
		//t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 3
		//t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 4
		//t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 5
		//t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 6
		//t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,	// 7
		//y,y,y,y,y,y,y,y,y,y,y,o,o,y,y,y,	// 8

};	//ゲームのマップ

//ゲームマップの初期化
GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//マップチップの画像を管理
MAPCHIP mapChip;

//マップの場所を管理
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//スタートの位置
iPOINT startPt{ -1,-1 };

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

VOID MY_END(VOID);
VOID MY_END_PROC(VOID);
VOID MY_END_DRAW(VOID);

BOOL MY_LOAD_IMAGE(VOID);
VOID MY_DELETE_IMAGE(VOID);

BOOL MY_LOAD_MUSIC(VOID);		//音楽をまとめて読み込む関数
VOID MY_DELETE_MUSIC(VOID);		//音楽をまとめて削除する関数

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT);
BOOL MY_CHECK_RECT_COLL(RECT, RECT);

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

	//プレイヤーの最初の位置を、スタート位置にする
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
				break;
			}
		}
		//スタートが決まっていれば、ループ終了
		if (startPt.x != -1 && startPt.y != -1) { break; }
	}

	//スタートが決まっていなければ
	if (startPt.x == -1 && startPt.y == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);	return -1;
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
				ImageTitleSTART.IsDraw == FALSE;
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

	DrawString(0, 0, "スタート画面(エンターキーを押して)", GetColor(255, 255, 255));
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
	if (MY_KEY_DOWN(KEY_INPUT_LCONTROL) == TRUE)
	{
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);
		}

		GameScene = GAME_SCENE_END;

		return;
	}

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

	player.speed = 2;
	if (MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
	{
		player.CenterX -= player.speed;
	}
	if (MY_KEY_DOWN(KEY_INPUT_D) == TRUE)
	{
		player.CenterX += player.speed;
	}

	// 落下処理
	player.CenterY -= JumpPower;

	// 落下加速度を加える
	JumpPower -= 1;

	// もし地面についていたら止まる
	if (player.CenterY > 480)
	{
		player.CenterY = 480;
		JumpPower = 0;
	}

	// ジャンプボタンを押していて、地面についていたらジャンプ
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) && player.CenterY == 480)
	{
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

	//当たり判定が追いつかないので、画像の位置を当たり判定に使用する
	//当たり判定の領域は、画像よりも少し縮小する。縮小加減は、お好みで。
	RECT PlayerRect;
	PlayerRect.left = player.image.x + 40;
	PlayerRect.top = player.image.y + 40;
	PlayerRect.right = player.image.x + player.image.width - 40;
	PlayerRect.bottom = player.image.y + player.image.height - 40;

	//プレイヤーが画面外に出たら
	if (player.image.x > GAME_WIDTH || player.image.y > GAME_HEIGHT
		|| player.image.x + player.image.width < 0 || player.image.y + player.image.height < 0)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGMを止める
		}

		//SetMouseDispFlag(TRUE);			//マウスカーソルを表示

		//GameEndKind = GAME_END_FAIL;	//ミッションフォールト！

		GameScene = GAME_SCENE_END;

		return;	//強制的にエンド画面に飛ぶ
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
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
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
	}

	//プレイヤーのを描画する
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);
	
	//当たり判定の描画（デバッグ用）
	DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);

	DrawString(0, 0, "プレイ画面(左のコントロールキーを押して)", GetColor(255, 255, 255));
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
		GameScene = GAME_SCENE_START;
	}

	return;
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{
	DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 0, 255), TRUE);

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
	ImageTitleSTART.Cnt = 0.0;								//カウンタ
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

	return TRUE;
}

//音楽をまとめて削除する関数
VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM_TITLE.handle);	//タイトルのBGM
	DeleteSoundMem(BGM_PUSH.handle);	//PUSH ENTER KEYの音
	DeleteSoundMem(BGM.handle);			//プレイ画面のBGM

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
