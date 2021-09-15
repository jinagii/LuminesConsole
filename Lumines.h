#pragma once

// ���� ����
//
// �⺻ �� 2���� �迭 ũ�� 18 x 11 (���� ��, �ٴ� ����)
//   �� :		   -1  /   ����� :		0  
//  ���� �� :		1  /  �� �� :		2	
// ���� ���� �� :  	3  /  ���� �� �� : 4	<- ���� ������Ʈ ����
// ��ĵ�� ���� �� : 5 / ��ĵ�� �� �� : 6	<- ���� ������Ʈ ����
//
// 1. ��ܿ��� 2x2 ���� ������
// 2. ���� �� ����� 2x2�� ���̸� ����
// 3. �ֱ������� -> �������� ��ĵ�� �� 
// 4. 2x2�� ���� ����� ��ĵ �� �� ����� 
// 5. �� ���� ���� ����� �ִٸ� �Ʒ��� ä����
// 
// �߰��Ѱ�
// - �� ����(�׸���)
// - �浹���� (�� �� ��ϰ� ����) 
// - ���� ��� ���� 
// - ��� ȸ��, ������
// - ���̵� ���� �� ���� ����
// - �� ������ ���� ���°�
// - 2x2 ���� �� ��� ���� ó�� (2x2 �̻� ������ ��ϱ��� ó��...?!)
// - �ֱ������� -> �����̴� ��ĵ ����� 
// - ���� ��� �Ͷ߸���
// - ���� ���� �� ����� ä��� Ȯ�� �ʿ�
// - ���ӿ��� ó��
// - ���� �߰��ϱ�

// �� ���� ����
#define MAPWIDTH 18
#define MAPHEIGHT 11

// ������ ����
#define SCANNINGPULSE -2
#define	WALL	   -1
#define EMPTY		0
#define	REDBLOCK	1
#define WHITEBLOCK	2
#define SET_REDBLOCK	3
#define SET_WHITEBLOCK	4
#define SCANNED_BLOCK	5
#define SCAN_WHITEBLOCK 6

// ���̽�ƽ ����
#define ROTATE 101
#define LEFT 102
#define RIGHT 103
#define DROP 104
#define NONE 999


void InitCGEngine(LHCGEngine* pEngine);

void InitiateGame();

void CreateLumino(int LuminoArray[][2]);

void BlockRotate(int lumino[][2]);

void DrawMap();

void DrawOneBlock(int x, int y, int type);

int JoyStick();

void DrawLumino(int LuminoArray[][2]);

void MoveBlock(int LuminoArray[][2]);

void RemoveAfterImage();

void DetectBottom(int LuminoArray[][2]);

bool DetectSideLeft(int posX, int posY);

bool DetectSideRight(int posX, int posY);

void BlockFillEmpty(int Map[][MAPWIDTH]);

void CheckBlockSquare(int Map[][MAPWIDTH]);

void ScanningPulse();

void DestroySetBlock();

void DrawScore();

void GravityDownBlock(int LuminoArray[][2]);

bool IsGameOver();

void QuitOrRestart();

bool IsAnyKeyPressed();

void ClearMap();