#include"DxLib.h"

#define GAME_WIDTH	1000	//��ʂ̉�
#define GAME_HEIGHT 600		//��ʂ̏c	
#define GAME_COLOR	32		//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR 0
#define GAME_WINDOW_NAME "���g���A�N�V����"

#define GAME_FPS	60	//FPS�̐��l

#define PATH_MAX	255

//�G���[���b�Z�[�W(�^�C�g���摜)
#define IMAGE_LOAD_ERR_TITLE	TEXT("�摜�ǂݍ��݃G���[")

#define IMAGE_TITLE_BK_PATH			TEXT(".\\IMAGE\\�^�C�g��.png")						//�^�C�g���w�i�̉摜
#define IMAGE_TITLE_ROGO_PATH		TEXT(".\\IMAGE\\�^�C�g��_���g���A�N�V����_3.png")	//�^�C�g�����S�̉摜
#define IMAGE_TITLE_ROGO_ROTA		0.005	//�g�嗦
#define IMAGE_TITLE_ROGO_ROTA_MAX	1.0		//�g�嗦MAX
#define IMAGE_TITLE_ROGO_X_SPEED	0		//X�ړ����x
#define IMAGE_TITLE_START_PATH		TEXT(".\\IMAGE\\PUSH ENTER KEY.png")					//�^�C�g���X�^�[�g�̉摜
#define IMAGE_TITLE_START_CNT		1		//�_�ŃJ�E���^
#define IMAGE_TITLE_START_CNT_MAX	30		//�_�ŃJ�E���^MAX

//�G���[���b�Z�[�W(�^�C�g��BGM)
#define MUSIC_LOAD_ERR_TITLE	TEXT("���y�ǂݍ��݃G���[")

#define MUSIC_BGM_TITLE_PATH	TEXT(".\\MUSIC\\���g���Q�[�����s�R�s�R.mp3")	//�^�C�g����BGM

#define MUSIC_LOAD_ERR_TITLE	TEXT("���y�ǂݍ��݃G���[")

#define MUSIC_BGM_PATH	TEXT(".\\MUSIC\\NES-Action-D02-2(Stage1-Loop130).mp3")

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END
};

typedef struct STRUCT_I_POINT
{
	int x = -1;
	int y = -1;
}iPOINT;

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];
	int handle;
	int x;
	int y;
	int width;
	int height;
}IMAGE;

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

int StartTimeFps;
int CountFps;
float CalcFps;
int SampleNumFps = GAME_FPS;

char AllKeyState[256] = { '\0' };
char OldAllKeyState[256] = { '\0' };

int GameScene;

IMAGE ImageTitleBK;
IMAGE_ROTA ImageTitleROGO;
IMAGE_BLINK ImageTitleSTART;

MUSIC BGM_TITLE;

MUSIC BGM;

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

BOOL MY_LOAD_MUSIC(VOID);		//���y���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_MUSIC(VOID);		//���y���܂Ƃ߂č폜����֐�

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
		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
			StopSoundMem(BGM_TITLE.handle);	//BGM���~�߂�
		}

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
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
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

	return;
}

//�v���C��ʂ̕`��
VOID MY_PLAY_DRAW(VOID)
{
	DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 255, 0), TRUE);

	DrawString(0, 0, "�v���C���(�X�y�[�X�[�L�[��������)", GetColor(255, 255, 255));
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
		GameScene = GAME_SCENE_START;
	}

	return;
}

//�G���h��ʂ̕`��
VOID MY_END_DRAW(VOID)
{
	DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 0, 255), TRUE);

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
	ImageTitleROGO.image.x = 500;							//�����Ă��镔������`�悵����
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
	ImageTitleSTART.Cnt = 0.0;								//�J�E���^
	ImageTitleSTART.CntMAX = IMAGE_TITLE_START_CNT_MAX;		//�J�E���^MAX
	ImageTitleSTART.IsDraw = FALSE;							//�`�悳���Ȃ�

	return TRUE;
}

//�摜���܂Ƃ߂č폜����֐�
VOID MY_DELETE_IMAGE(VOID)
{
	DeleteGraph(ImageTitleBK.handle);
	DeleteGraph(ImageTitleROGO.image.handle);
	DeleteGraph(ImageTitleSTART.image.handle);

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

	strcpy_s(BGM.path, MUSIC_BGM_PATH);				//�p�X�̐ݒ�
	BGM.handle = LoadSoundMem(BGM.path);			//�ǂݍ���
	if (BGM.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//���y���܂Ƃ߂č폜����֐�
VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM_TITLE.handle);
	DeleteSoundMem(BGM.handle);

	return;
}
