#include"DxLib.h"

#define GAME_WIDTH	1024	//��ʂ̉�
#define GAME_HEIGHT 576		//��ʂ̏c	
#define GAME_COLOR	32		//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR 0
#define GAME_WINDOW_NAME "���g���A�N�V����"

#define GAME_FPS	60	//FPS�̐��l

#define MOUSE_BUTTON_CODE	129	//0x0000�`0x0080�܂�

#define PATH_MAX	255

#define GAME_GR 5

#define PLAYER_JUMP_MAX		60	//�W�����v����t���[���b
#define PLAYER_JUMP_POWER		1	//�P�t���[���̃W�����v��

//�G���[���b�Z�[�W(�^�C�g���摜)
#define IMAGE_LOAD_ERR_TITLE	TEXT("�摜�ǂݍ��݃G���[")

#define IMAGE_BACK_PATH			TEXT(".\\IMAGE\\�w�i_a.png")
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\�}���I���ۂ��L����.png")	//�v���C���[�̉摜

#define IMAGE_TITLE_BK_PATH			TEXT(".\\IMAGE\\�^�C�g��.png")						//�^�C�g���w�i�̉摜
#define IMAGE_TITLE_ROGO_PATH		TEXT(".\\IMAGE\\�^�C�g��_���g���A�N�V����_3.png")	//�^�C�g�����S�̉摜
#define IMAGE_TITLE_ROGO_ROTA		0.005	//�g�嗦
#define IMAGE_TITLE_ROGO_ROTA_MAX	1.0		//�g�嗦MAX
#define IMAGE_TITLE_ROGO_X_SPEED	0		//X�ړ����x
#define IMAGE_TITLE_START_PATH		TEXT(".\\IMAGE\\PUSH ENTER KEY.png")					//�^�C�g���X�^�[�g�̉摜
#define IMAGE_TITLE_START_CNT		1		//�_�ŃJ�E���^
#define IMAGE_TITLE_START_CNT_MAX	30		//�_�ŃJ�E���^MAX

#define IMAGE_END_COMP_PATH		TEXT(".\\IMAGE\\�Q�[���N���A.png")	//�G���h�R���v�摜
//#define IMAGE_END_COMP_CNT		1			//�_�ŃJ�E���^
//#define IMAGE_END_COMP_CNT_MAX	30			//�_�ŃJ�E���^MAX

#define IMAGE_END_FAIL_PATH		TEXT(".\\IMAGE\\�Q�[���I�[�o�[.png")	//�G���h�t�H�[���摜
//#define IMAGE_END_FAIL_CNT		1			//�_�ŃJ�E���^
//#define IMAGE_END_FAIL_CNT_MAX	30			//�_�ŃJ�E���^MAX

//�G���[���b�Z�[�W(�^�C�g��BGM)
#define MUSIC_LOAD_ERR_TITLE	TEXT("���y�ǂݍ��݃G���[")

#define MUSIC_BGM_TITLE_PATH	TEXT(".\\MUSIC\\���g���Q�[�����s�R�s�R.mp3")	//�^�C�g����BGM
#define MUSIC_PUSH_ENTER_PATH	TEXT(".\\MUSIC\\�V�X�e�����艹_9.mp3")
#define MUSIC_BGM_COMP_PATH			TEXT(".\\MUSIC\\Game Clear.mp3")				//�R���v���[�gBGM
#define MUSIC_BGM_FAIL_PATH			TEXT(".\\MUSIC\\Game Over.mp3")					//�t�H�[���gBGM

#define MUSIC_LOAD_ERR_TITLE	TEXT("���y�ǂݍ��݃G���[")

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

#define START_ERR_TITLE		TEXT("�X�^�[�g�ʒu�G���[")
#define START_ERR_CAPTION	TEXT("�X�^�[�g�ʒu�����܂��Ă��܂���")

#define GOAL_ERR_TITLE		TEXT("�S�[���ʒu�G���[")
#define GOAL_ERR_CAPTION	TEXT("�S�[���ʒu�����܂��Ă��܂���")

#define ANA_ERR_TITLE		TEXT("���ʒu�G���[")
#define ANA_ERR_CAPTION		TEXT("���ʒu�����܂��Ă��܂���")

#define TOGE_ERR_TITLE		TEXT("�g�Q�ʒu�G���[")
#define TOGE_ERR_CAPTION	TEXT("�g�Q�ʒu�����܂��Ă��܂���")

#define MOUSE_R_CLICK_TITLE		TEXT("�Q�[�����f")
#define MOUSE_R_CLICK_CAPTION	TEXT("�Q�[���𒆒f���A�^�C�g����ʂɖ߂�܂����H")

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
};	//�}�b�v�̎��

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
};	//�}�b�v�̎��

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_PLAY2,
	GAME_SCENE_END
};

enum GAME_END {
	GAME_END_COMP,	//�R���v���[�g
	GAME_END_FAIL	//�t�H�[���g
};	//�Q�[���̏I�����

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 3
};	//�L�����N�^�[�̃X�s�[�h

typedef struct STRUCT_I_POINT
{
	int x = -1;
	int y = -1;
}iPOINT;

typedef struct STRUCT_MOUSE
{
	int InputValue = 0;	//GetMouseInput�̒l������
	int WheelValue = 0;	//�}�E�X�z�C�[���̉�]��(���̓v���X�l / ��O�̓}�C�i�X�l)
	iPOINT Point;		//�}�E�X�̍��W������
	iPOINT OldPoint;	//�}�E�X�̍��W(���O)������
	int OldButton[MOUSE_BUTTON_CODE] = { 0 };	//�}�E�X�̃{�^������(���O)������
	int Button[MOUSE_BUTTON_CODE] = { 0 };	//�}�E�X�̃{�^�����͂�����
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
	IMAGE image;				//IMAGE�\����
	int speed;					//����
	int CenterX;				//���SX
	int CenterY;				//���SY
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

	RECT coll;					//�����蔻��
	iPOINT collBeforePt;		//������O�̍��W

}CHARA;	//�L�����N�^�[�\����

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
	char path[PATH_MAX];				//�p�X
	int handle[MAP_DIV_NUM];			//���������̒e�̉摜�n���h�����擾
	int kind[MAP_DIV_NUM];				//�}�b�v�̎��
	int width;							//��
	int height;							//����
}MAPCHIP;	//MAP_IMAGE�\����

typedef struct STRUCT_MAP
{
	GAME_MAP_KIND kind;			//�}�b�v�̎��
	GAME_MAP_KIND2 kind2;			//�}�b�v�̎��
	int x;						//X�ʒu
	int y;						//Y�ʒu
	int width;					//��
	int height;					//����
}MAP;	//MAP�\����

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

int GameEndKind;					//�Q�[���̏I�����
RECT GoalRect = { -1, -1, -1, -1 };	//�S�[���̓����蔻��
RECT Goal2Rect = { -1, -1, -1, -1 };//�S�[��2�̓����蔻��
RECT AnaRect  = { -1, -1, -1, -1 };	//���̓����蔻��
RECT Ana2Rect = { -1, -1, -1, -1 };	//���̓����蔻��
RECT TogeRect = { -1, -1, -1, -1 };	//�g�Q�̓����蔻��

IMAGE ImageBack;
CHARA player;			//�Q�[���̃L����
IMAGE ImageTitleBK;
IMAGE_ROTA ImageTitleROGO;
IMAGE_BLINK ImageTitleSTART;

IMAGE_BLINK ImageEndCOMP;				//�G���h�R���v�̉摜
IMAGE_BLINK ImageEndFAIL;				//�G���h�t�H�[���̉摜

MUSIC BGM_TITLE;
MUSIC BGM_PUSH;
MUSIC BGM;
MUSIC BGM_COMP;		//�R���v���[�g��BGM
MUSIC BGM_FAIL;		//�t�H�[���g��BGM

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
		
};	//�Q�[���̃}�b�v

GAME_MAP_KIND2 mapData2[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5
		T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,	// 0(32)
		T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,	// 1(96)
		T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,	// 2(160)
		T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,	// 3(224)
		T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,	// 4(288)
		T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,F,	// 5(352)
		S,T,T,D,T,T,D,T,O,T,T,T,O,T,T,G,	// 6(416)
		Y,Y,Y,Y,Y,Y,Y,Y,T,Y,Y,Y,T,Y,Y,Y,	// 7(480)
		W,W,W,W,W,W,W,W,T,W,W,W,T,W,W,W		// 8

};	//�Q�[���̃}�b�v

//�Q�[���}�b�v�̏�����
GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
GAME_MAP_KIND2 mapDataInit2[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//�}�b�v�`�b�v�̉摜���Ǘ�
MAPCHIP mapChip;

//�}�b�v�̏ꏊ���Ǘ�
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
MAP map2[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//�X�^�[�g�̈ʒu
iPOINT startPt{ -1,-1 };
iPOINT startPt2{ -1,-1 };

//�}�b�v�̓����蔻��
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

BOOL MY_LOAD_MUSIC(VOID);		//���y���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_MUSIC(VOID);		//���y���܂Ƃ߂č폜����֐�

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT);
BOOL MY_CHECK_RECT_COLL(RECT, RECT);

VOID MY_PLAY_MOVE_JUMP(VOID);

BOOL MY_CHECK_CHARA_GROUND(CHARA p);								//�v���C���[���n�ʂƐڂ��Ă��邩�����蔻�������֐�

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

	////�v���C���[�̍ŏ��̈ʒu���A�X�^�[�g�ʒu�ɂ���
	//for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	//{
	//	for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
	//	{
	//		//�X�^�[�g�ʒu��T��
	//		if (mapData[tate][yoko] == s)
	//		{
	//			//�X�^�[�g�ʒu���v�Z
	//			startPt.x = mapChip.width * yoko + mapChip.width / 2;	//���SX���W���擾
	//			startPt.y = mapChip.height * tate + mapChip.height / 2;	//���SY���W���擾
	//			break;
	//		}
	//	}
	//	//�X�^�[�g�����܂��Ă���΁A���[�v�I��
	//	if (startPt.x != -1 && startPt.y != -1) { break; }
	//}

	//�v���C���[�̍ŏ��̈ʒu���A�X�^�[�g�ʒu�ɂ���
	//�S�[���̈ʒu�����łɌ�������
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�X�^�[�g�ʒu��T��
			if (mapData[tate][yoko] == s)
			{
				//�X�^�[�g�ʒu���v�Z
				startPt.x = mapChip.width * yoko + mapChip.width / 2;	//���SX���W���擾
				startPt.y = mapChip.height * tate + mapChip.height / 2;	//���SY���W���擾
			}

			//�X�^�[�g2�ʒu��T��
			if (mapData[tate][yoko] == S)
			{
				//�X�^�[�g�ʒu���v�Z
				startPt2.x = mapChip.width * yoko + mapChip.width / 2;		//���SX���W���擾
				startPt2.y = mapChip.height * tate + mapChip.height / 2;	//���SY���W���擾
			}

			//�S�[���ʒu��T��
			if (mapData[tate][yoko] == g)
			{
				GoalRect.left = mapChip.width * yoko;
				GoalRect.top = mapChip.height * tate;
				GoalRect.right = mapChip.width * (yoko + 1);
				GoalRect.bottom = mapChip.height * (tate + 1);
			}

			//�S�[��2�ʒu��T��
			if (mapData[tate][yoko] == G)
			{
				Goal2Rect.left = mapChip.width * yoko;
				Goal2Rect.top = mapChip.height * tate;
				Goal2Rect.right = mapChip.width * (yoko + 1);
				Goal2Rect.bottom = mapChip.height * (tate + 1);
			}

			//���̈ʒu��T��
			if (mapData[tate][yoko] == o)
			{
				AnaRect.left = mapChip.width * yoko;
				AnaRect.top = mapChip.height * tate;
				AnaRect.right = mapChip.width * (yoko + 1);
				AnaRect.bottom = mapChip.height * (tate + 1);
			}

			//��2�̈ʒu��T��
			if (mapData[tate][yoko] == O)
			{
				Ana2Rect.left = mapChip.width * yoko;
				Ana2Rect.top = mapChip.height * tate;
				Ana2Rect.right = mapChip.width * (yoko + 1);
				Ana2Rect.bottom = mapChip.height * (tate + 1);
			}

			//�g�Q�̈ʒu��T��
			if (mapData[tate][yoko] == d)
			{
				TogeRect.left = mapChip.width * yoko;
				TogeRect.top = mapChip.height * tate;
				TogeRect.right = mapChip.width * (yoko + 1);
				TogeRect.bottom = mapChip.height * (tate + 1);
			}

		}
	}

	//�X�^�[�g�����܂��Ă��Ȃ����
	if (startPt.x == -1 && startPt.y == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);	return -1;
	}

	//�S�[�������܂��Ă��Ȃ����
	if (GoalRect.left == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), GOAL_ERR_CAPTION, GOAL_ERR_TITLE, MB_OK);	return -1;
	}

	//�S�[��2�����܂��Ă��Ȃ����
	if (Goal2Rect.left == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), GOAL_ERR_CAPTION, GOAL_ERR_TITLE, MB_OK);	return -1;
	}

	//�������܂��Ă��Ȃ����
	if (AnaRect.left == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), ANA_ERR_CAPTION, ANA_ERR_TITLE, MB_OK);	return -1;
	}

	//�g�Q�����܂��Ă��Ȃ����
	if (TogeRect.left == -1)
	{
		//�G���[���b�Z�[�W�\��
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
	if (CountFps == 0) //1�t���[���ڂȂ玞�����L��
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60�t���[���ڂȂ畽�ς��v�Z
	{
		int now = GetNowCount();
		//���݂̎��Ԃ���A0�t���[���ڂ̎��Ԃ������AFPS�̐��l�Ŋ��遁1FPS�ӂ�̕��ώ��Ԃ��v�Z�����
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//������������
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//�҂ׂ�����

	if (waitTime > 0)		//�w���FPS�l���������ꍇ
	{
		WaitTimer(waitTime);	//�҂�
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

//�X�^�[�g���
VOID MY_START(VOID)
{
	MY_START_PROC();
	MY_START_DRAW();

	return;
}

//�X�^�[�g��ʂ̏���
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
			StopSoundMem(BGM_TITLE.handle);	//BGM���~�߂�
		}

		SetMouseDispFlag(FALSE);			//�}�E�X�J�[�\�����\��

		//�v���C���[�̒��S�ʒu���v�Z����
		player.CenterX = startPt.x;
		player.CenterY = startPt.y;

		//�v���C���[�̉摜�̈ʒu��ݒ肷��
		player.image.x = player.CenterX;
		player.image.y = player.CenterY;

		//�Q�[���̏I����Ԃ�����������
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
			StopSoundMem(BGM_TITLE.handle);	//BGM���~�߂�
		}

		SetMouseDispFlag(FALSE);			//�}�E�X�J�[�\�����\��

		//�v���C���[�̒��S�ʒu���v�Z����
		player.CenterX = startPt2.x;
		player.CenterY = startPt2.y;

		//�v���C���[�̉摜�̈ʒu��ݒ肷��
		player.image.x = player.CenterX;
		player.image.y = player.CenterY;

		//�Q�[���̏I����Ԃ�����������
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

//�X�^�[�g��ʂ̕`��
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

	DrawString(0, 0, "�X�^�[�g���(�G���^�[�L�[��������)", GetColor(255, 255, 255));
	return;
}

//�v���C���
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();
	MY_PLAY_DRAW();

	return;
}

//�v���C��ʂ̏���
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

	//�}�E�X���E�N���b�N����ƁA�^�C�g����ʂɖ߂�
	if (mouse.Button[MOUSE_INPUT_RIGHT] == TRUE)
	{
		//�N���b�N�������W���擾���Ă���
		iPOINT R_ClickPt = mouse.Point;

		//�}�E�X��\��
		SetMouseDispFlag(TRUE);

		//�I���_�C�A���O��\��
		int Ret = MessageBox(GetMainWindowHandle(), MOUSE_R_CLICK_CAPTION, MOUSE_R_CLICK_TITLE, MB_YESNO);

		if (Ret == IDYES)		//YES�Ȃ�A�Q�[���𒆒f����
		{
			//�����I�Ƀ^�C�g����ʂɔ��
			GameScene = GAME_SCENE_START;
			return;

		}
		else if (Ret == IDNO)	//NO�Ȃ�A�Q�[���𑱍s����
		{
			//�}�E�X�̈ʒu���A�N���b�N����O�ɖ߂�
			SetMousePoint(R_ClickPt.x, R_ClickPt.y);

			//�}�E�X���\���ɂ���B
			SetMouseDispFlag(FALSE);
		}
	}

	//�����蔻�肪�ǂ����Ȃ��̂ŁA�摜�̈ʒu�𓖂��蔻��Ɏg�p����
	//�����蔻��̗̈�́A�摜���������k������B�k�������́A���D�݂ŁB
	RECT PlayerRect;
	PlayerRect.left = player.image.x + 40;
	PlayerRect.top = player.image.y + 40;
	PlayerRect.right = player.image.x + player.image.width - 40;
	PlayerRect.bottom = player.image.y + player.image.height - 40;

	//�S�[���ɐG��Ă��邩�`�F�b�N
	if (MY_CHECK_RECT_COLL(PlayerRect, GoalRect) == TRUE)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGM���~�߂�
		}

		SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

		GameEndKind = GAME_END_COMP;	//�~�b�V�����R���v���[�g�I

		GameScene = GAME_SCENE_END;

		return;	//�����I�ɃG���h��ʂɔ��
	}

	//���ɐG��Ă��邩�`�F�b�N
	if (MY_CHECK_RECT_COLL(PlayerRect, AnaRect) == TRUE)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGM���~�߂�
		}

		SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

		GameEndKind = GAME_END_FAIL;	//�~�b�V�����R���v���[�g�I

		GameScene = GAME_SCENE_END;

		return;	//�����I�ɃG���h��ʂɔ��
	}

	//���ɐG��Ă��邩�`�F�b�N
	if (MY_CHECK_RECT_COLL(PlayerRect, Ana2Rect) == TRUE)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGM���~�߂�
		}

		SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

		GameEndKind = GAME_END_FAIL;	//�~�b�V�����R���v���[�g�I

		GameScene = GAME_SCENE_END;

		return;	//�����I�ɃG���h��ʂɔ��
	}

	//�g�Q�ɐG��Ă��邩�`�F�b�N
	if (MY_CHECK_RECT_COLL(PlayerRect, TogeRect) == TRUE)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGM���~�߂�
		}

		SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

		GameEndKind = GAME_END_FAIL;	//�~�b�V�����R���v���[�g�I

		GameScene = GAME_SCENE_END;

		return;	//�����I�ɃG���h��ʂɔ��
	}

	//�v���C���[����ʊO�ɏo����
	if (player.image.x > GAME_WIDTH || player.image.y > GAME_HEIGHT
		|| player.image.x + player.image.width < 0 || player.image.y + player.image.height < 0)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGM���~�߂�
		}

		SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

		GameEndKind = GAME_END_FAIL;	//�~�b�V�����t�H�[���g�I

		GameScene = GAME_SCENE_END;

		return;	//�����I�ɃG���h��ʂɔ��
	}

	// �ړ����ł͂Ȃ��ꍇ�L�[���͂��󂯕t����
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

		// �i���s�\�ȃ}�b�v�������ꍇ�͈ړ��ł��Ȃ�
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

		// ��~���͉�ʂ̃X�N���[���͍s��Ȃ�
		ScrollX = 0;
		ScrollY = 0;
	}

	// �ړ����̏ꍇ�͈ړ��������s��
	if (Move == 1)
	{
		MoveCounter++;

		// �ړ��������I���������~���ɂ���
		if (MoveCounter == GAME_FPS)
		{
			Move = 0;

			// �v���C���[�̈ʒu��ύX����
			player.CenterX += MoveX;

			// ��~���͉�ʂ̃X�N���[���͍s��Ȃ�
			ScrollX = 0;
			ScrollY = 0;
		}
		else
		{
			// �o�ߎ��Ԃ���X�N���[���ʂ��Z�o����
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

	// ���������x��������
	JumpPower -= 1;

	// �����n�ʂɂ��Ă�����~�܂�
	if (player.CenterY > 416)
	{
		player.CenterY = 416;
		JumpPower = 0;
	}

	// �W�����v�{�^���������Ă��āA�n�ʂɂ��Ă�����W�����v
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) && player.CenterY == 416)
	{
		JumpPower = 15;
	}

	// ��ʂ�����������
	ClearDrawScreen();

	//�����蔻��
	player.coll.left = player.CenterX - mapChip.width / 2 + 5;
	player.coll.top = player.CenterY - mapChip.height / 2 + 5;
	player.coll.right = player.CenterX + mapChip.width / 2 - 5;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;

	BOOL IsMove = TRUE;

	//�v���C���[�ƃ}�b�v���������Ă�����
	if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	{
		/*[�L�[���삱������]*/
		player.CenterX = player.collBeforePt.x;
		player.CenterY = player.collBeforePt.y;
		
		//SetMousePoint(player.collBeforePt.x, player.collBeforePt.y);

		IsMove = FALSE;
	}

	//�v���C���[�̈ʒu�ɒu��������
	player.image.x = player.CenterX - player.image.width / 2;
	player.image.y = player.CenterY - player.image.height / 2;

	//��ʊO�Ƀv���C���[���s���Ȃ��悤�ɂ���
	if (player.image.x < 0) { player.image.x = 0; }
	if (player.image.x + player.image.width > GAME_WIDTH) { player.image.x = GAME_WIDTH - player.image.width; }
	if (player.image.y < 0) { player.image.y = 0; }
	if (player.image.y + player.image.height > GAME_HEIGHT) { player.image.y = GAME_HEIGHT - player.image.height; }

	//�v���C���[�̓�����ȑO�̈ʒu��ݒ肷��
	player.collBeforePt.x = player.CenterX;
	player.collBeforePt.y = player.CenterY;

	return;
}

//�v���C��ʂ̕`��
VOID MY_PLAY_DRAW(VOID)
{
	DrawGraph(ImageBack.x, ImageBack.y, ImageBack.handle, TRUE);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v��`��
			DrawGraph(
				map[tate][yoko].x,
				map[tate][yoko].y,
				mapChip.handle[map[tate][yoko].kind],
				TRUE);
		}
	}	
	
	//�����蔻��̕`��i�f�o�b�O�p�j
	/*for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�ǂȂ��
			if (mapData[tate][yoko] == y)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
			}

			//�ʘH�Ȃ��
			if (mapData[tate][yoko] == t)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 255, 0), FALSE);
			}
		}
	}*/

	//�S�[��,��,��2,�g�Q�̕`��i�f�o�b�O�p�j
	/*DrawBox(GoalRect.left, GoalRect.top, GoalRect.right, GoalRect.bottom, GetColor(255, 255, 0), TRUE);
	DrawBox(AnaRect.left, AnaRect.top, AnaRect.right, AnaRect.bottom, GetColor(255, 0, 0), TRUE);
	DrawBox(Ana2Rect.left, Ana2Rect.top, Ana2Rect.right, Ana2Rect.bottom, GetColor(255, 0, 0), TRUE);
	DrawBox(TogeRect.left, TogeRect.top, TogeRect.right, TogeRect.bottom, GetColor(0, 255, 0), TRUE);
	*/
	//�v���C���[�̂�`�悷��
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);
	
	//�����蔻��̕`��i�f�o�b�O�p�j
	/*DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);*/

	//DrawString(0, 0, "�v���C���(���̃R���g���[���L�[��������)", GetColor(255, 255, 255));
	return;
}

VOID MY_PLAY2(VOID)
{
	MY_PLAY2_PROC();
	MY_PLAY2_DRAW();

	return;
}

//�v���C2��ʂ̏���
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

	//�}�E�X���E�N���b�N����ƁA�^�C�g����ʂɖ߂�
	if (mouse.Button[MOUSE_INPUT_RIGHT] == TRUE)
	{
		//�N���b�N�������W���擾���Ă���
		iPOINT R_ClickPt = mouse.Point;

		//�}�E�X��\��
		SetMouseDispFlag(TRUE);

		//�I���_�C�A���O��\��
		int Ret = MessageBox(GetMainWindowHandle(), MOUSE_R_CLICK_CAPTION, MOUSE_R_CLICK_TITLE, MB_YESNO);

		if (Ret == IDYES)		//YES�Ȃ�A�Q�[���𒆒f����
		{
			//�����I�Ƀ^�C�g����ʂɔ��
			GameScene = GAME_SCENE_START;
			return;

		}
		else if (Ret == IDNO)	//NO�Ȃ�A�Q�[���𑱍s����
		{
			//�}�E�X�̈ʒu���A�N���b�N����O�ɖ߂�
			SetMousePoint(R_ClickPt.x, R_ClickPt.y);

			//�}�E�X���\���ɂ���B
			SetMouseDispFlag(FALSE);
		}
	}

	//�����蔻�肪�ǂ����Ȃ��̂ŁA�摜�̈ʒu�𓖂��蔻��Ɏg�p����
	//�����蔻��̗̈�́A�摜���������k������B�k�������́A���D�݂ŁB
	RECT PlayerRect;
	PlayerRect.left = player.image.x + 40;
	PlayerRect.top = player.image.y + 40;
	PlayerRect.right = player.image.x + player.image.width - 40;
	PlayerRect.bottom = player.image.y + player.image.height - 40;

	//�S�[��2�ɐG��Ă��邩�`�F�b�N
	if (MY_CHECK_RECT_COLL(PlayerRect, Goal2Rect) == TRUE)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGM���~�߂�
		}

		SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

		GameEndKind = GAME_END_COMP;	//�~�b�V�����R���v���[�g�I

		GameScene = GAME_SCENE_END;

		return;	//�����I�ɃG���h��ʂɔ��
	}

	//���ɐG��Ă��邩�`�F�b�N
	if (MY_CHECK_RECT_COLL(PlayerRect, AnaRect) == TRUE)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGM���~�߂�
		}

		SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

		GameEndKind = GAME_END_FAIL;	//�~�b�V�����R���v���[�g�I

		GameScene = GAME_SCENE_END;

		return;	//�����I�ɃG���h��ʂɔ��
	}

	//���ɐG��Ă��邩�`�F�b�N
	if (MY_CHECK_RECT_COLL(PlayerRect, Ana2Rect) == TRUE)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGM���~�߂�
		}

		SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

		GameEndKind = GAME_END_FAIL;	//�~�b�V�����R���v���[�g�I

		GameScene = GAME_SCENE_END;

		return;	//�����I�ɃG���h��ʂɔ��
	}

	//�g�Q�ɐG��Ă��邩�`�F�b�N
	if (MY_CHECK_RECT_COLL(PlayerRect, TogeRect) == TRUE)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGM���~�߂�
		}

		SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

		GameEndKind = GAME_END_FAIL;	//�~�b�V�����R���v���[�g�I

		GameScene = GAME_SCENE_END;

		return;	//�����I�ɃG���h��ʂɔ��
	}

	//�v���C���[����ʊO�ɏo����
	if (player.image.x > GAME_WIDTH || player.image.y > GAME_HEIGHT
		|| player.image.x + player.image.width < 0 || player.image.y + player.image.height < 0)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGM���~�߂�
		}

		SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

		GameEndKind = GAME_END_FAIL;	//�~�b�V�����t�H�[���g�I

		GameScene = GAME_SCENE_END;

		return;	//�����I�ɃG���h��ʂɔ��
	}

	// �ړ����ł͂Ȃ��ꍇ�L�[���͂��󂯕t����
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

		// �i���s�\�ȃ}�b�v�������ꍇ�͈ړ��ł��Ȃ�
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

		// ��~���͉�ʂ̃X�N���[���͍s��Ȃ�
		ScrollX = 0;
		ScrollY = 0;
	}

	// �ړ����̏ꍇ�͈ړ��������s��
	if (Move == 1)
	{
		MoveCounter++;

		// �ړ��������I���������~���ɂ���
		if (MoveCounter == GAME_FPS)
		{
			Move = 0;

			// �v���C���[�̈ʒu��ύX����
			player.CenterX += MoveX;

			// ��~���͉�ʂ̃X�N���[���͍s��Ȃ�
			ScrollX = 0;
			ScrollY = 0;
		}
		else
		{
			// �o�ߎ��Ԃ���X�N���[���ʂ��Z�o����
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

	// ���������x��������
	JumpPower -= 1;

	// �����n�ʂɂ��Ă�����~�܂�
	if (player.CenterY > 416)
	{
		player.CenterY = 416;
		JumpPower = 0;
	}

	// �W�����v�{�^���������Ă��āA�n�ʂɂ��Ă�����W�����v
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) && player.CenterY == 416)
	{
		JumpPower = 15;
	}

	// ��ʂ�����������
	ClearDrawScreen();

	//�����蔻��
	player.coll.left = player.CenterX - mapChip.width / 2 + 5;
	player.coll.top = player.CenterY - mapChip.height / 2 + 5;
	player.coll.right = player.CenterX + mapChip.width / 2 - 5;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;

	BOOL IsMove = TRUE;

	//�v���C���[�ƃ}�b�v���������Ă�����
	if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	{
		/*[�L�[���삱������]*/
		player.CenterX = player.collBeforePt.x;
		player.CenterY = player.collBeforePt.y;

		//SetMousePoint(player.collBeforePt.x, player.collBeforePt.y);

		IsMove = FALSE;
	}

	//�v���C���[�̈ʒu�ɒu��������
	player.image.x = player.CenterX - player.image.width / 2;
	player.image.y = player.CenterY - player.image.height / 2;

	//��ʊO�Ƀv���C���[���s���Ȃ��悤�ɂ���
	if (player.image.x < 0) { player.image.x = 0; }
	if (player.image.x + player.image.width > GAME_WIDTH) { player.image.x = GAME_WIDTH - player.image.width; }
	if (player.image.y < 0) { player.image.y = 0; }
	if (player.image.y + player.image.height > GAME_HEIGHT) { player.image.y = GAME_HEIGHT - player.image.height; }

	//�v���C���[�̓�����ȑO�̈ʒu��ݒ肷��
	player.collBeforePt.x = player.CenterX;
	player.collBeforePt.y = player.CenterY;

	return;
}

//�v���C��ʂ̕`��
VOID MY_PLAY2_DRAW(VOID)
{
	DrawGraph(ImageBack.x, ImageBack.y, ImageBack.handle, TRUE);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v��`��
			DrawGraph(
				map2[tate][yoko].x,
				map2[tate][yoko].y,
				mapChip.handle[map2[tate][yoko].kind2],
				TRUE);
		}
	}

	//�����蔻��̕`��i�f�o�b�O�p�j
	/*for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�ǂȂ��
			if (mapData2[tate][yoko] == Y)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
			}

			//�ʘH�Ȃ��
			if (mapData2[tate][yoko] == T)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 255, 0), FALSE);
			}
		}
	}*/

	//�S�[��,��,��2,�g�Q�̕`��i�f�o�b�O�p�j
	/*DrawBox(GoalRect.left, GoalRect.top, GoalRect.right, GoalRect.bottom, GetColor(255, 255, 0), TRUE);
	DrawBox(AnaRect.left, AnaRect.top, AnaRect.right, AnaRect.bottom, GetColor(255, 0, 0), TRUE);
	DrawBox(Ana2Rect.left, Ana2Rect.top, Ana2Rect.right, Ana2Rect.bottom, GetColor(255, 0, 0), TRUE);
	DrawBox(TogeRect.left, TogeRect.top, TogeRect.right, TogeRect.bottom, GetColor(0, 255, 0), TRUE);
	*/
	//�v���C���[�̂�`�悷��
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

	//�����蔻��̕`��i�f�o�b�O�p�j
	/*DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);*/

	//DrawString(0, 0, "�v���C���(���̃R���g���[���L�[��������)", GetColor(255, 255, 255));
	return;
}

//�G���h���
VOID MY_END(VOID)
{
	MY_END_PROC();
	MY_END_DRAW();

	return;
}

//�G���h��ʂ̏���
VOID MY_END_PROC(VOID)
{
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM_COMP.handle) != 0)
		{
			StopSoundMem(BGM_COMP.handle);	//BGM���~�߂�
		}

		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM_FAIL.handle) != 0)
		{
			StopSoundMem(BGM_FAIL.handle);	//BGM���~�߂�
		}

		GameScene = GAME_SCENE_START;

		return;
	}

	switch (GameEndKind)
	{
	case GAME_END_COMP:
		//�R���v���[�g�̂Ƃ�

		//BGM������Ă��Ȃ��Ȃ�
		if (CheckSoundMem(BGM_COMP.handle) == 0)
		{
			//BGM�̉��ʂ�������
			ChangeVolumeSoundMem(255 * 70 / 100, BGM_COMP.handle);	//50%�̉��ʂɂ���
			PlaySoundMem(BGM_COMP.handle, DX_PLAYTYPE_LOOP);
		}

		////�R���v���[�g��_��
		//if (ImageEndCOMP.Cnt < ImageEndCOMP.CntMAX)
		//{
		//	ImageEndCOMP.Cnt += IMAGE_END_COMP_CNT;
		//}
		//else
		//{
		//	//�`�悷��/���Ȃ������߂�
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
		//�t�H�[���g�̂Ƃ�

		//BGM������Ă��Ȃ��Ȃ�
		if (CheckSoundMem(BGM_FAIL.handle) == 0)
		{
			//BGM�̉��ʂ�������
			ChangeVolumeSoundMem(255 * 70 / 100, BGM_FAIL.handle);	//50%�̉��ʂɂ���
			PlaySoundMem(BGM_FAIL.handle, DX_PLAYTYPE_LOOP);
		}

		////�t�H�[���g��_��
		//if (ImageEndFAIL.Cnt < ImageEndFAIL.CntMAX)
		//{
		//	ImageEndFAIL.Cnt += IMAGE_END_FAIL_CNT;
		//}
		//else
		//{
		//	//�`�悷��/���Ȃ������߂�
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

//�G���h��ʂ̕`��
VOID MY_END_DRAW(VOID)
{
	//DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 0, 255), TRUE);

	MY_PLAY_DRAW();	//�v���C��ʂ�`��

	//�Q�[���̏I����Ԃɂ��A�`���ς���
	switch (GameEndKind)
	{
	case GAME_END_COMP:
		//�R���v���[�g�̂Ƃ�

		////�_��
		//if (ImageEndCOMP.IsDraw == TRUE)
		//{
			//�R���v���[�g�̕`��
			DrawGraph(ImageEndCOMP.image.x, ImageEndCOMP.image.y, ImageEndCOMP.image.handle, TRUE);
		//}
		break;

	case GAME_END_FAIL:
		//�t�H�[���g�̂Ƃ�

		////�_��
		//if (ImageEndFAIL.IsDraw == TRUE)
		//{
			//�t�H�[���g�̕`��
			DrawGraph(ImageEndFAIL.image.x, ImageEndFAIL.image.y, ImageEndFAIL.image.handle, TRUE);
		//}
		break;

	}

	DrawString(0, 0, "�G���h���(�G�X�P�[�v�[�L�[��������)", GetColor(255, 255, 255));
	return;
}

//�摜�̓ǂݍ���
BOOL MY_LOAD_IMAGE(VOID)
{
	//�^�C�g���w�i
	strcpy_s(ImageTitleBK.path, IMAGE_TITLE_BK_PATH);			//�p�X�̐ݒ�
	ImageTitleBK.handle = LoadGraph(ImageTitleBK.path);			//�ǂݍ���
	if (ImageTitleBK.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleBK.handle, &ImageTitleBK.width, &ImageTitleBK.height);	//�摜�̕��ƍ������擾
	ImageTitleBK.x = GAME_WIDTH / 2 - ImageTitleBK.width / 2;		//���E��������
	ImageTitleBK.y = GAME_HEIGHT / 2 - ImageTitleBK.height / 2;		//�㉺��������

	//�^�C�g�����S
	strcpy_s(ImageTitleROGO.image.path, IMAGE_TITLE_ROGO_PATH);					//�p�X�̐ݒ�
	ImageTitleROGO.image.handle = LoadGraph(ImageTitleROGO.image.path);			//�ǂݍ���
	if (ImageTitleROGO.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleROGO.image.handle, &ImageTitleROGO.image.width, &ImageTitleROGO.image.height);	//�摜�̕��ƍ������擾
	ImageTitleROGO.image.x = 512;							//�����Ă��镔������`�悵����
	ImageTitleROGO.image.y = GAME_HEIGHT / 3;				//������
	ImageTitleROGO.angle = DX_PI * 2;						//��]��
	ImageTitleROGO.angleMAX = DX_PI * 2;					//��]��MAX
	ImageTitleROGO.rate = 0.0;								//�g�嗦
	ImageTitleROGO.rateMAX = IMAGE_TITLE_ROGO_ROTA_MAX;		//�g�嗦MAX

	//�^�C�g���X�^�[�g
	strcpy_s(ImageTitleSTART.image.path, IMAGE_TITLE_START_PATH);					//�p�X�̐ݒ�
	ImageTitleSTART.image.handle = LoadGraph(ImageTitleSTART.image.path);			//�ǂݍ���
	if (ImageTitleSTART.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_START_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleSTART.image.handle, &ImageTitleSTART.image.width, &ImageTitleSTART.image.height);	//�摜�̕��ƍ������擾
	ImageTitleSTART.image.x = GAME_WIDTH / 2 - ImageTitleSTART.image.width / 2;					//���E��������
	ImageTitleSTART.image.y = ImageTitleROGO.image.y + ImageTitleROGO.image.height / 2 + 10;	//���S�̉��ɕ\��
	ImageTitleSTART.Cnt = 0;								//�J�E���^
	ImageTitleSTART.CntMAX = IMAGE_TITLE_START_CNT_MAX;		//�J�E���^MAX
	ImageTitleSTART.IsDraw = FALSE;							//�`�悳���Ȃ�

	//�v���C�w�i
	strcpy_s(ImageBack.path, IMAGE_BACK_PATH);			//�p�X�̐ݒ�
	ImageBack.handle = LoadGraph(ImageBack.path);			//�ǂݍ���
	if (ImageBack.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_BACK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageBack.handle, &ImageBack.width, &ImageBack.height);	//�摜�̕��ƍ������擾
	ImageBack.x = GAME_WIDTH / 2 - ImageBack.width / 2;		//���E��������
	ImageBack.y = GAME_HEIGHT / 2 - ImageBack.height / 2;		//�㉺��������

	//�v���C���[�̉摜
	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);		//�p�X�̐ݒ�
	player.image.handle = LoadGraph(player.image.path);	//�ǂݍ���
	if (player.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);	//�摜�̕��ƍ������擾
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;		//���E��������
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;		//�㉺��������
	player.CenterX = player.image.x + player.image.width / 2;		//�摜�̉��̒��S��T��
	player.CenterY = player.image.y + player.image.height / 2;		//�摜�̏c�̒��S��T��
	player.speed = CHARA_SPEED_LOW;									//�X�s�[�h��ݒ�

	//�}�b�v1
	//�}�b�v�̉摜�𕪊�����
	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,										//�Ԓe�̃p�X
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,			//�Ԓe�𕪊����鐔
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,						//�摜�𕪊�����̕��ƍ���
		&mapChip.handle[0]);								//���������摜������n���h��

	if (mapRes == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//���ƍ������擾
	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v�f�[�^�������p�ɏ����R�s�[
			mapDataInit[tate][yoko] = mapData[tate][yoko];

			//�}�b�v�̎�ނ��R�s�[
			map[tate][yoko].kind = mapData[tate][yoko];

			//�}�b�v�̕��ƍ������R�s�[
			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;

			//�}�b�v�̍��W��ݒ�
			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;
		}
	}

	//�}�b�v�̓����蔻���ݒ肷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v�̓����蔻���ݒ�
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}

	//�}�b�v2
	//�}�b�v�̉摜�𕪊�����
	int mapRes2 = LoadDivGraph(
		GAME_MAP_PATH,										//�Ԓe�̃p�X
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,			//�Ԓe�𕪊����鐔
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,						//�摜�𕪊�����̕��ƍ���
		&mapChip.handle[0]);								//���������摜������n���h��

	if (mapRes == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//���ƍ������擾
	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v�f�[�^�������p�ɏ����R�s�[
			mapDataInit2[tate][yoko] = mapData2[tate][yoko];

			//�}�b�v�̎�ނ��R�s�[
			map2[tate][yoko].kind2 = mapData2[tate][yoko];

			//�}�b�v�̕��ƍ������R�s�[
			map2[tate][yoko].width = mapChip.width;
			map2[tate][yoko].height = mapChip.height;

			//�}�b�v�̍��W��ݒ�
			map2[tate][yoko].x = yoko * map2[tate][yoko].width;
			map2[tate][yoko].y = tate * map2[tate][yoko].height;
		}
	}

	//�}�b�v�̓����蔻���ݒ肷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v�̓����蔻���ݒ�
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}


	//�G���h�R���v
	strcpy_s(ImageEndCOMP.image.path, IMAGE_END_COMP_PATH);					//�p�X�̐ݒ�
	ImageEndCOMP.image.handle = LoadGraph(ImageEndCOMP.image.path);			//�ǂݍ���
	if (ImageEndCOMP.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_END_COMP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndCOMP.image.handle, &ImageEndCOMP.image.width, &ImageEndCOMP.image.height);	//�摜�̕��ƍ������擾
	ImageEndCOMP.image.x = GAME_WIDTH / 2 - ImageTitleBK.width / 2;		//���E��������
	ImageEndCOMP.image.y = GAME_HEIGHT / 2 - ImageTitleBK.height / 2;		//�㉺��������
																									//ImageEndCOMP.image.x = GAME_WIDTH / 2 - ImageEndCOMP.image.width / 2;			//���E��������
	//ImageEndCOMP.image.y = GAME_HEIGHT / 2 - ImageEndCOMP.image.height / 2;			//�㉺��������
	//ImageEndCOMP.Cnt = 0;									//�J�E���^
	//ImageEndCOMP.CntMAX = IMAGE_END_COMP_CNT_MAX;			//�J�E���^MAX
	//ImageEndCOMP.IsDraw = FALSE;							//�`�悳���Ȃ�

	//�G���h�t�H�[��
	strcpy_s(ImageEndFAIL.image.path, IMAGE_END_FAIL_PATH);				//�p�X�̐ݒ�
	ImageEndFAIL.image.handle = LoadGraph(ImageEndFAIL.image.path);			//�ǂݍ���
	if (ImageEndFAIL.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_END_FAIL_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndFAIL.image.handle, &ImageEndFAIL.image.width, &ImageEndFAIL.image.height);	//�摜�̕��ƍ������擾
	ImageEndFAIL.image.x = GAME_WIDTH / 2 - ImageTitleBK.width / 2;		//���E��������
	ImageEndFAIL.image.y = GAME_HEIGHT / 2 - ImageTitleBK.height / 2;		//�㉺��������
																										//ImageEndFAIL.image.x = GAME_WIDTH / 2 - ImageEndFAIL.image.width / 2;			//���E��������
	//ImageEndFAIL.image.y = GAME_HEIGHT / 2 - ImageEndFAIL.image.height / 2;			//�㉺��������
	//ImageEndFAIL.Cnt = 0;									//�J�E���^
	//ImageEndFAIL.CntMAX = IMAGE_END_FAIL_CNT_MAX;			//�J�E���^MAX
	//ImageEndFAIL.IsDraw = FALSE;							//�`�悳���Ȃ�

	return TRUE;
}

//�摜���܂Ƃ߂č폜����֐�
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

//���y�̓ǂݍ���
BOOL MY_LOAD_MUSIC(VOID)
{
	//�^�C�g����BGM
	strcpy_s(BGM_TITLE.path, MUSIC_BGM_TITLE_PATH);				//�p�X�̐ݒ�
	BGM_TITLE.handle = LoadSoundMem(BGM_TITLE.path);			//�ǂݍ���
	if (BGM_TITLE.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_TITLE_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//PUSH ENTER KEY�̉�
	strcpy_s(BGM_PUSH.path, MUSIC_PUSH_ENTER_PATH);				//�p�X�̐ݒ�
	BGM_PUSH.handle = LoadSoundMem(BGM_PUSH.path);			//�ǂݍ���
	if (BGM_PUSH.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_PUSH_ENTER_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�v���C��ʂ�BGM
	strcpy_s(BGM.path, MUSIC_BGM_PATH);				//�p�X�̐ݒ�
	BGM.handle = LoadSoundMem(BGM.path);			//�ǂݍ���
	if (BGM.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�R���v���[�gBGM
	strcpy_s(BGM_COMP.path, MUSIC_BGM_COMP_PATH);				//�p�X�̐ݒ�
	BGM_COMP.handle = LoadSoundMem(BGM_COMP.path);				//�ǂݍ���
	if (BGM_COMP.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_COMP_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�t�H�[���g��BGM
	strcpy_s(BGM_FAIL.path, MUSIC_BGM_FAIL_PATH);				//�p�X�̐ݒ�
	BGM_FAIL.handle = LoadSoundMem(BGM_FAIL.path);				//�ǂݍ���
	if (BGM_FAIL.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_FAIL_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//���y���܂Ƃ߂č폜����֐�
VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM_TITLE.handle);	//�^�C�g����BGM
	DeleteSoundMem(BGM_PUSH.handle);	//PUSH ENTER KEY�̉�
	DeleteSoundMem(BGM.handle);			//�v���C��ʂ�BGM
	DeleteSoundMem(BGM_COMP.handle);
	DeleteSoundMem(BGM_FAIL.handle);

	return;
}

//�}�b�v�ƃv���C���[�̓����蔻�������֐�
BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player)
{
	//�}�b�v�̓����蔻���ݒ肷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//�ǂ̂Ƃ��́A�v���C���[�ƃ}�b�v���������Ă���
				if (map[tate][yoko].kind == y) { return TRUE; }
				if (map[tate][yoko].kind == w) { return TRUE; }
				if (map2[tate][yoko].kind2 == Y) { return TRUE; }
				if (map2[tate][yoko].kind2 == W) { return TRUE; }
			}
		}
	}

	return FALSE;
}

//�̈�̓����蔻�������֐�
BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)
	{
		return TRUE;	//�������Ă���
	}

	return FALSE;		//�������Ă��Ȃ�
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
//		player.mapY -= GAME_GR;											//�d�͂ɕ����Ȃ��I
//		int  y_temp = player.mapY;										//���݂�Y���W���L�^
//		player.mapY += (player.mapY - player.BeforeJumpY) + player.JumpPower;	//��Ɍ��������l���v�Z������
//		player.JumpPower = 1;												//�����x���P�ɂ���
//		player.BeforeJumpY = y_temp;										//�ȑO�̈ʒu�ɋL�^
//		player.y = player.mapY;
//
//		//�n�ʂɓ������Ă����
//		if (MY_CHECK_CHARA_GROUND(player) == TRUE)
//		{
//			//�W�����v�I��
//			player.IsJump = FALSE;
//		}
//	}
//}

//�v���C���[���n�ʂƐڂ��Ă��邩�����蔻�������֐�
//BOOL MY_CHECK_CHARA_GROUND(CHARA p)
//{
//	//�O���t�B��������ʒu��z��I�Ɍv�Z����
//	//int ArrX_L = (p.mapX + player.choseiX) / MAP_DIV_WIDTH;				//X�ʒu�i���j
//	int yoko = (p.mapX + p.width + p.choseiWidth) / MAP_DIV_WIDTH;	//X�ʒu�i�E�j
//	int tate = (p.mapY + p.height + p.choseiHeight) / MAP_DIV_HEIGHT;//Y�ʒu(���̖��܂��Ă���ʒu)
//
//	//��ʊO�̒l���擾���Ȃ�
//	//if (ArrX_L < 0) { ArrX_L = 0; }
//	if (yoko >= GAME_MAP_YOKO_MAX) { yoko = GAME_MAP_YOKO_MAX - 1; }
//
//	//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
//	//�ǂ̂Ƃ��́A�v���C���[�ƃ}�b�v���������Ă���
//	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
//	{
//		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
//		{
//				//�ǂ̂Ƃ��́A�v���C���[�ƃ}�b�v���������Ă���
//				if (map[tate][yoko].kind == y)
//				{
//					return TRUE;
//				}
//		}
//	}
//
//	return FALSE;
//}
