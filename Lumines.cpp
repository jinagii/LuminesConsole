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

// �� �迭 18x11
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

	g_pCGEngine->LHPutAttrCharEx(5, 1, "�ߡߡߡߡߡߡߡߡߡߡߡߡߡ�", BG_BLACK, FG_YELLOW);
	g_pCGEngine->LHPutAttrCharEx(5, 2, "�ߡߡߡߡ�LUMINES.�ߡߡߡߡ�", BG_BLACK, FG_YELLOW);
	g_pCGEngine->LHPutAttrCharEx(5, 3, "�ߡߡߡߡߡߡߡߡߡߡߡߡߡ�", BG_BLACK, FG_YELLOW);
	g_pCGEngine->LHPutAttrCharEx(5, 5, " ��������������������������������������������������", BG_BLACK, FG_WHITE);
	g_pCGEngine->LHPutAttrCharEx(5, 6, " �� �覢 Rotate�� ��ꦢ Move��", BG_BLACK, FG_WHITE);
	g_pCGEngine->LHPutAttrCharEx(5, 7, " ��������������������������������������������������", BG_BLACK, FG_WHITE);
	g_pCGEngine->LHPutAttrCharEx(5, 9, "  Press arrow key to START", BG_BLACK, FG_LGRAY);
	
	scoreCount = 0;

	_getch();
	  
	system("cls");
}

// ��̳� ���� �Լ� 
void CreateLumino(int LuminoArray[][2])
{
	posX = 8;		// ��ġ �缳�� �� ����
	posY = 0;
	int RandomLumino[2][2];

	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			RandomLumino[y][x] = (rand() % 2) + 1;	//�������� ���� ����
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

// ��� ȸ���ϱ�
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

// �� �׸���
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

// �� �ִ� �Լ�
void DrawOneBlock(int x, int y, int type)
{
	switch (type)
	{
	case SCANNINGPULSE:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "��", BG_YELLOW, FG_YELLOW); break;
	case WALL:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_BLUE); break;
	case EMPTY:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "  ", BG_BLACK, FG_WHITE); break;
	case REDBLOCK:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_RED); break;
	case WHITEBLOCK:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_WHITE); break;
	case SET_REDBLOCK:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_RED); break;
	case SET_WHITEBLOCK:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_WHITE); break;
	case SCANNED_BLOCK:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_YELLOW); break;
	case SCAN_WHITEBLOCK:
		g_pCGEngine->LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_PURPLE); break;
	}
}

// Ű �Է� �޴� �Լ�
int JoyStick()
{
	if (GetAsyncKeyState(VK_UP)) { return ROTATE; }
	if (GetAsyncKeyState(VK_LEFT)) { return LEFT; }
	if (GetAsyncKeyState(VK_RIGHT)) { return RIGHT; }
	if (GetAsyncKeyState(VK_DOWN)) { return DROP; }
	return NONE;
}

// ��̳� �� ������
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

// �� �����̱� + �� ����
// �� �浹 ����
// 1. ���� �����ϼ��ִ� ����
// 2. ���� ���� ��°��� ����? (���� �������� ���� or ���� �Ѿ�� �ǵ�����)
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

	case DROP:			// ����Ҷ� �ٴ� ���� 
		PlaySound("rotate.wav", NULL, SND_ASYNC);

		DetectBottom(LuminoArray);
		break;

	default:
		break;
	}
}

// �ܻ� �����
void RemoveAfterImage()
{
	// posX, posY �� ������ ĥ�Ѵ�
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			DrawOneBlock(posX + x, posY + y, 0); //��ĭ(0)�� �����Ѵ�
		}
	}
}

// �ٴ� �� ���� 
void DetectBottom(int LuminoArray[][2])
{
	if (Map[posY + 2][posX] != EMPTY || Map[posY + 2][posX + 1] != EMPTY)// ����� �ƴҶ� �ٴ�����
	{
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 2; x++)		// ��̳� ����ȣ�� �ʿ� ����
			{
				Map[posY + y][posX + x] = LuminoArray[y][x];
			}
		}
		PlaySound("bottom.wav", NULL, SND_ASYNC);
		CreateLumino(LuminoArray);	// ���ο� ��̳� ����
	}
	else	// �ٴ��� �ƴҰ�� ������
	{
		RemoveAfterImage();
		posY++; 
	}
}

// ���� �浹 ����
bool DetectSideLeft(int posX, int posY)
{
	if (Map[posY + 1][posX - 1] != EMPTY)
	{
		return false;
	}
	return true;
}

// ������ �浹 ����
bool DetectSideRight(int posX, int posY)
{
	if (Map[posY + 1][posX + 2] != EMPTY)
	{
		return false;
	}
	return true;
}

// �� ������ ������ = �� ���� �߷����� ä���?
// - Map�� 0(EMPTY)���� ����
// - EMPTY�� ������ ����
// - ������ EMPTY�� �ƴ϶�� ��ġ�� �ٲ�
void BlockFillEmpty(int Map[][MAPWIDTH])	//���� ������ �ٲ ��ĥ�� �ȵ�
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

// ��� ���� Ȯ�� �Լ�
// - ����(��)����̳� ���� ����(��)����� �˻�
// - 2x2���̸� ���� ����(��)������� �ٲ�
void CheckBlockSquare(int Map[][MAPWIDTH])
{
	for (int y = 0; y < MAPHEIGHT - 2; y++)
	{
		for (int x = 1; x < MAPWIDTH - 2; x++)
		{
			if ((Map[y][x] == WHITEBLOCK || Map[y][x] == SET_WHITEBLOCK) &&		// �� ����� �˻�
				(Map[y][x + 1] == WHITEBLOCK || Map[y][x + 1] == SET_WHITEBLOCK) &&
				(Map[y + 1][x] == WHITEBLOCK || Map[y + 1][x] == SET_WHITEBLOCK) &&
				(Map[y + 1][x + 1] == WHITEBLOCK || Map[y + 1][x + 1] == SET_WHITEBLOCK))
			{
				Map[y][x] = SET_WHITEBLOCK;			// ���� �ٲ�
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
			if ((Map[y][x] == REDBLOCK || Map[y][x] == SET_REDBLOCK) &&		// ���� ����� �˻�
				(Map[y][x + 1] == REDBLOCK || Map[y][x + 1] == SET_REDBLOCK) &&
				(Map[y + 1][x] == REDBLOCK || Map[y + 1][x] == SET_REDBLOCK) &&
				(Map[y + 1][x + 1] == REDBLOCK || Map[y + 1][x + 1] == SET_REDBLOCK))
			{
				Map[y][x] = SET_REDBLOCK;		// ���� �ٲ�
				Map[y][x + 1] = SET_REDBLOCK;
				Map[y + 1][x] = SET_REDBLOCK;
				Map[y + 1][x + 1] = SET_REDBLOCK;
			}
		}
	}
}

// ��ĵ �޽� �����̴� ȿ��
// ���� ��ĵ�ϴ� �Լ� 
// Y���� �������� -> �������� �̵�
// SET_�� ��ϵ��� ���� (EMPTY�� �ٲ�)
void ScanningPulse()
{
	static int x = 1;

	if (scanningPulseTimer >= 3)	//���� 3���� �׸��� if�� ����
	{
		if (Map[MAPHEIGHT - 1][MAPWIDTH - 2] == SCANNINGPULSE)	// ������ �޽������ ������ �ٲ�
		{
			Map[MAPHEIGHT - 1][MAPWIDTH - 2] = WALL;

			DestroySetBlock();			
		}

		if (Map[MAPHEIGHT - 1][x - 1] == SCANNINGPULSE)		// ���� �޽� ����� ������ �ٲ�
		{
			Map[MAPHEIGHT - 1][x - 1] = WALL;
		}
		
		Map[MAPHEIGHT - 1][x] = SCANNINGPULSE;		// �޽� ������� ��ȯ

		for (int y = 0; y < MAPHEIGHT - 1; y++)
		{
			if (Map[y][x] == SET_WHITEBLOCK || Map[y][x] == SET_REDBLOCK)
			{
				PlaySound("setblock.wav", NULL, SND_ASYNC);

				Map[y][x] = SCANNED_BLOCK;			// ���� �ٲ�				
			}
		}

		x++;		// X �� �������� �̵�				

		scanningPulseTimer = 0;		// Ÿ�̸� ����

		if (x == 17)		// ������ �޽��� ���� ������ ����
		{
			x = 1;			
		}
	}
}

// �� �ı� �Լ� - EMPTY�� �ٲٱ�
void DestroySetBlock() 
{
	for (int y = 0; y < MAPHEIGHT - 1; y++)
	{
		for (int x = 0; x < MAPWIDTH - 1; x++)
		{
			if (Map[y][x] == SCANNED_BLOCK) 
			{				
				PlaySound("destroy.wav", NULL, SND_ASYNC);

				Map[y][x] = EMPTY;			// ���� �ٲ�	
				scoreCount++;
			}
		}
	}
}

/// int �� ����Ʈ �ϴ� �Լ� ���?
void DrawScore()
{
	g_pCGEngine->LHPutAttrCharEx(1,11 , "��SCORE��", BG_BLACK, FG_YELLOW);
	
	char score_text[255] = "";
	sprintf_s(score_text, "%d", scoreCount);
	g_pCGEngine->LHPutAttrCharEx(6, 12, score_text, BG_BLACK, FG_YELLOW);
}

// �� �ڵ� ���
void GravityDownBlock(int LuminoArray[][2])
{
	if (BlockDownTimer >= 10)
	{
		RemoveAfterImage();

		DetectBottom(LuminoArray);
				
		BlockDownTimer = 0;
	}
}

// ���� ���� �Լ� 
// ���� ��ġ �ؿ� ���� ������ ���� ����?
bool IsGameOver()
{
	if (Map[1][8] != EMPTY)
	{
		return true;
	}

	return false;
}

/// Quit �ϴ� �Լ��� restart �ϴ� �Լ� 
void QuitOrRestart()
{	
	system("cls");

	PlaySound("gameover.wav", NULL, SND_ASYNC);

	g_pCGEngine->LHPutAttrCharEx(5, 1, "�ߡߡߡߡߡߡߡߡߡߡߡߡߡ�", BG_BLACK, FG_LRED);
	g_pCGEngine->LHPutAttrCharEx(5, 2, "�ߡߡߡߡ�GAME OVER.�ߡߡߡ�", BG_BLACK, FG_LRED);
	g_pCGEngine->LHPutAttrCharEx(5, 3, "�ߡߡߡߡߡߡߡߡߡߡߡߡߡ�", BG_BLACK, FG_LRED);

	DrawScore(); /// ���� ����

	g_pCGEngine->LHPutAttrCharEx(5, 6, "Press arrow key to Restart", BG_BLACK, FG_LGRAY);
	
	Sleep(1000);
}

// �ƹ� Ű�� �Է� ������
bool IsAnyKeyPressed()
{
	if (JoyStick() != NONE)
	{
		return true;
	}

	return false;
}

// �� �ʱ�ȭ �Լ�
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
