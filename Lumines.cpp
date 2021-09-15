#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <playsoundapi.h>
#include "ConsoleLib.h"
#include "Lumines.h"

int posX = 8;
int posY = 0;
int RotateIndex = 0;
int JoystickIndex = 0;
int scanningPulseTimer = 0;
int BlockDownTimer = 0;
int scoreCount = 0;

// 맵 배열 18x11
int Map[MAPHEIGHT][MAPWIDTH] = {
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1} };

LHCGEngine* g_pCGEngine;

void InitCGEngine(LHCGEngine* pEngine)
{
	g_pCGEngine = pEngine;
}

void InitiateGame()
{
	PlaySound("intro.wav", NULL, SND_ASYNC | SND_LOOP);

	g_pCGEngine->LHPutAttrCharEx(5, 1, "◆◆◆◆◆◆◆◆◆◆◆◆◆◆", BG_BLACK, FG_YELLOW);
	g_pCGEngine->LHPutAttrCharEx(5, 2, "◆◆◆◆◆LUMINES.◆◆◆◆◆", BG_BLACK, FG_YELLOW);
	g_pCGEngine->LHPutAttrCharEx(5, 3, "◆◆◆◆◆◆◆◆◆◆◆◆◆◆", BG_BLACK, FG_YELLOW);
	g_pCGEngine->LHPutAttrCharEx(5, 5, " ┌───┬───────┬─────┬─────┐", BG_BLACK, FG_WHITE);
	g_pCGEngine->LHPutAttrCharEx(5, 6, " │ ↑│ Rotate│ ↓↔│ Move│", BG_BLACK, FG_WHITE);
	g_pCGEngine->LHPutAttrCharEx(5, 7, " └───┴───────┴─────┴─────┘", BG_BLACK, FG_WHITE);
	g_pCGEngine->LHPutAttrCharEx(5, 9, "  Press arrow key to START", BG_BLACK, FG_LGRAY);
	
	scoreCount = 0;

	_getch();
	  
	system("cls");
}

// 루미노 생성 함수 
void CreateLumino(int LuminoArray[][2])
{
	posX = 8;		// 위치 재설정 후 생성
	posY = 0;
	int RandomLumino[2][2];

	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			RandomLumino[y][x] = (rand() % 2) + 1;	//랜덤으로 색상 대입
		}
	}

	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			LuminoArray[y][x] = RandomLumino[y][x];
		}
	}
}

// 블록 회전하기
void BlockRotate(int lumino[][2])
{
	int temp[2][2];

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			temp[i][j] = lumino[2 - 1 - j][i];
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			lumino[i][j] = temp[i][j];
		}
	}
}

// 맵 그리기
void DrawMap()
{
	for (int y = 0; y < MAPHEIGHT; y++)
	{
		for (int x = 0; x < MAPWIDTH; x++)
		{
			DrawOneBlock(x, y, Map[y][x]);
		}
	}
	scanningPulseTimer++;
	BlockDownTimer++;
}

// 색 넣는 함수
void DrawOneBlock(int x, int y, int type)
{
	switch (type)
	{
	case SCANNINGPULSE:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "■", BG_YELLOW, FG_YELLOW); break;
	case WALL:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "▣", BG_BLACK, FG_BLUE); break;
	case EMPTY:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "  ", BG_BLACK, FG_WHITE); break;
	case REDBLOCK:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "■", BG_BLACK, FG_RED); break;
	case WHITEBLOCK:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "■", BG_BLACK, FG_WHITE); break;
	case SET_REDBLOCK:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "□", BG_BLACK, FG_RED); break;
	case SET_WHITEBLOCK:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "□", BG_BLACK, FG_WHITE); break;
	case SCANNED_BLOCK:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "▩", BG_BLACK, FG_YELLOW); break;
	case SCAN_WHITEBLOCK:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "★", BG_BLACK, FG_PURPLE); break;
	}
}

// 키 입력 받는 함수
int JoyStick()
{
	if (GetAsyncKeyState(VK_UP)) { return ROTATE; }
	if (GetAsyncKeyState(VK_LEFT)) { return LEFT; }
	if (GetAsyncKeyState(VK_RIGHT)) { return RIGHT; }
	if (GetAsyncKeyState(VK_DOWN)) { return DROP; }
	return NONE;
}

// 루미노 색 입히기
void DrawLumino(int LuminoArray[][2])
{
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			DrawOneBlock(posX + x, posY + y, LuminoArray[y][x]);
		}
	}
}

// 블럭 움직이기 + 벽 감지
// 벽 충돌 감지
// 1. 블럭이 움직일수있는 범위
// 2. 블럭이 벽에 닿는것을 감지? (벽에 가기전에 막기 or 벽을 넘어가면 되돌리기)
void MoveBlock(int LuminoArray[][2])
{	
	Sleep(100);

	JoystickIndex = JoyStick();

	GravityDownBlock(LuminoArray);

	if (JoystickIndex == NONE)
	{
		return;
	}

	switch (JoystickIndex)
	{
	case ROTATE:
	{
		PlaySound("rotate.wav", NULL, SND_ASYNC);

		BlockRotate(LuminoArray);
		break;
	}
	case LEFT:
		if (DetectSideLeft(posX, posY) == true)
		{
			PlaySound("rotate.wav", NULL, SND_ASYNC);

			RemoveAfterImage();
			posX--;
		}
		break;

	case RIGHT:
		if (DetectSideRight(posX, posY) == true)
		{
			PlaySound("rotate.wav", NULL, SND_ASYNC);

			RemoveAfterImage();
			posX++;
		}
		break;

	case DROP:			// 드롭할때 바닥 감지 
		PlaySound("rotate.wav", NULL, SND_ASYNC);

		DetectBottom(LuminoArray);
		break;

	default:
		break;
	}
}

// 잔상 지우기
void RemoveAfterImage()
{
	// posX, posY 를 블랙으로 칠한다
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			DrawOneBlock(posX + x, posY + y, 0); //빈칸(0)을 대입한다
		}
	}
}

// 바닥 블럭 감지 
void DetectBottom(int LuminoArray[][2])
{
	if (Map[posY + 2][posX] != EMPTY || Map[posY + 2][posX + 1] != EMPTY)// 빈곳이 아닐때 바닥인지
	{
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 2; x++)		// 루미노 색번호를 맵에 대입
			{
				Map[posY + y][posX + x] = LuminoArray[y][x];
			}
		}
		PlaySound("bottom.wav", NULL, SND_ASYNC);
		CreateLumino(LuminoArray);	// 새로운 루미노 생성
	}
	else	// 바닥이 아닐경우 움직임
	{
		RemoveAfterImage();
		posY++; 
	}
}

// 왼쪽 충돌 감지
bool DetectSideLeft(int posX, int posY)
{
	if (Map[posY + 1][posX - 1] != EMPTY)
	{
		return false;
	}
	return true;
}

// 오른쪽 충돌 감지
bool DetectSideRight(int posX, int posY)
{
	if (Map[posY + 1][posX + 2] != EMPTY)
	{
		return false;
	}
	return true;
}

// 블럭 반으로 가르기 = 빈 공간 중력으로 채우기?
// - Map의 0(EMPTY)들을 조사
// - EMPTY의 위쪽을 조사
// - 위쪽이 EMPTY가 아니라면 위치를 바꿈
void BlockFillEmpty(int Map[][MAPWIDTH])	//맵의 구성은 바뀌나 색칠이 안됨
{
	for (int y = 1; y < MAPHEIGHT - 1; y++)
	{
		for (int x = 1; x < MAPWIDTH - 1; x++)
		{
			if (Map[y][x] == 0)
			{
				Map[y][x] = Map[y - 1][x];
				Map[y - 1][x] = 0;
			}
		}
	}
}

// 블록 굳음 확인 함수
// - 빨간(흰)블록이나 굳은 빨강(흰)블록을 검사
// - 2x2모이면 굳은 빨강(흰)블록으로 바꿈
void CheckBlockSquare(int Map[][MAPWIDTH])
{
	for (int y = 0; y < MAPHEIGHT - 2; y++)
	{
		for (int x = 1; x < MAPWIDTH - 2; x++)
		{
			if ((Map[y][x] == WHITEBLOCK || Map[y][x] == SET_WHITEBLOCK) &&		// 흰 블록을 검사
				(Map[y][x + 1] == WHITEBLOCK || Map[y][x + 1] == SET_WHITEBLOCK) &&
				(Map[y + 1][x] == WHITEBLOCK || Map[y + 1][x] == SET_WHITEBLOCK) &&
				(Map[y + 1][x + 1] == WHITEBLOCK || Map[y + 1][x + 1] == SET_WHITEBLOCK))
			{
				Map[y][x] = SET_WHITEBLOCK;			// 색을 바꿈
				Map[y][x + 1] = SET_WHITEBLOCK;
				Map[y + 1][x] = SET_WHITEBLOCK;
				Map[y + 1][x + 1] = SET_WHITEBLOCK;
			}
		}
	}

	for (int y = 0; y < MAPHEIGHT - 2; y++)
	{
		for (int x = 1; x < MAPWIDTH - 2; x++)
		{
			if ((Map[y][x] == REDBLOCK || Map[y][x] == SET_REDBLOCK) &&		// 빨간 블록을 검사
				(Map[y][x + 1] == REDBLOCK || Map[y][x + 1] == SET_REDBLOCK) &&
				(Map[y + 1][x] == REDBLOCK || Map[y + 1][x] == SET_REDBLOCK) &&
				(Map[y + 1][x + 1] == REDBLOCK || Map[y + 1][x + 1] == SET_REDBLOCK))
			{
				Map[y][x] = SET_REDBLOCK;		// 색을 바꿈
				Map[y][x + 1] = SET_REDBLOCK;
				Map[y + 1][x] = SET_REDBLOCK;
				Map[y + 1][x + 1] = SET_REDBLOCK;
			}
		}
	}
}

// 스캔 펄스 움직이는 효과
// 맵을 스캔하는 함수 
// Y축을 기준으로 -> 방향으로 이동
// SET_된 블록들을 제거 (EMPTY로 바꿈)
void ScanningPulse()
{
	static int x = 1;

	if (scanningPulseTimer >= 3)	//맵을 3바퀴 그리고 if로 들어옴
	{
		if (Map[MAPHEIGHT - 1][MAPWIDTH - 2] == SCANNINGPULSE)	// 마지막 펄스블록을 벽으로 바꿈
		{
			Map[MAPHEIGHT - 1][MAPWIDTH - 2] = WALL;

			DestroySetBlock();			
		}

		if (Map[MAPHEIGHT - 1][x - 1] == SCANNINGPULSE)		// 이전 펄스 블록을 벽으로 바꿈
		{
			Map[MAPHEIGHT - 1][x - 1] = WALL;
		}
		
		Map[MAPHEIGHT - 1][x] = SCANNINGPULSE;		// 펄스 블록으로 전환

		for (int y = 0; y < MAPHEIGHT - 1; y++)
		{
			if (Map[y][x] == SET_WHITEBLOCK || Map[y][x] == SET_REDBLOCK)
			{
				PlaySound("setblock.wav", NULL, SND_ASYNC);

				Map[y][x] = SCANNED_BLOCK;			// 색을 바꿈				
			}
		}

		x++;		// X 축 방향으로 이동				

		scanningPulseTimer = 0;		// 타이머 리셋

		if (x == 17)		// 마지막 펄스가 벽에 닿으면 리셋
		{
			x = 1;			
		}
	}
}

// 블럭 파괴 함수 - EMPTY로 바꾸기
void DestroySetBlock() 
{
	for (int y = 0; y < MAPHEIGHT - 1; y++)
	{
		for (int x = 0; x < MAPWIDTH - 1; x++)
		{
			if (Map[y][x] == SCANNED_BLOCK) 
			{				
				PlaySound("destroy.wav", NULL, SND_ASYNC);

				Map[y][x] = EMPTY;			// 색을 바꿈	
				scoreCount++;
			}
		}
	}
}

/// int 형 프린트 하는 함수 어떻게?
void DrawScore()
{
	g_pCGEngine->LHPutAttrCharEx(1,11 , "◆SCORE◆", BG_BLACK, FG_YELLOW);
	
	char score_text[255] = "";
	sprintf_s(score_text, "%d", scoreCount);
	g_pCGEngine->LHPutAttrCharEx(6, 12, score_text, BG_BLACK, FG_YELLOW);
}

// 블럭 자동 드롭
void GravityDownBlock(int LuminoArray[][2])
{
	if (BlockDownTimer >= 10)
	{
		RemoveAfterImage();

		DetectBottom(LuminoArray);
				
		BlockDownTimer = 0;
	}
}

// 게임 오버 함수 
// 생성 위치 밑에 블럭이 있으면 게임 오버?
bool IsGameOver()
{
	if (Map[1][8] != EMPTY)
	{
		return true;
	}

	return false;
}

/// Quit 하는 함수와 restart 하는 함수 
void QuitOrRestart()
{	
	system("cls");

	PlaySound("gameover.wav", NULL, SND_ASYNC);

	g_pCGEngine->LHPutAttrCharEx(5, 1, "◆◆◆◆◆◆◆◆◆◆◆◆◆◆", BG_BLACK, FG_LRED);
	g_pCGEngine->LHPutAttrCharEx(5, 2, "◆◆◆◆◆GAME OVER.◆◆◆◆", BG_BLACK, FG_LRED);
	g_pCGEngine->LHPutAttrCharEx(5, 3, "◆◆◆◆◆◆◆◆◆◆◆◆◆◆", BG_BLACK, FG_LRED);

	DrawScore(); /// 점수 보기

	g_pCGEngine->LHPutAttrCharEx(5, 6, "Press arrow key to Restart", BG_BLACK, FG_LGRAY);
	
	Sleep(1000);
}

// 아무 키나 입력 받으면
bool IsAnyKeyPressed()
{
	if (JoyStick() != NONE)
	{
		return true;
	}

	return false;
}

// 맵 초기화 함수
void ClearMap()
{
	for (int y = 0; y < MAPHEIGHT; y++)
	{
		Map[y][0] = -1;
	}

	for (int y = 0; y < MAPHEIGHT; y++)
	{
		Map[y][MAPWIDTH - 1] = -1;
	}

	for (int x = 0; x < MAPWIDTH; x++)
	{
		Map[MAPHEIGHT - 1][x] = -1;
	}

	for (int y = 0; y < MAPHEIGHT-1; y++)
	{
		for (int x = 1; x < MAPWIDTH-2; x++)
		{
			Map[y][x] = 0;
		}
	}
}
