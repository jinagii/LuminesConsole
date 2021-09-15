#pragma once

// 구현 명세서
//
// 기본 맵 2차원 배열 크기 18 x 11 (양쪽 벽, 바닥 포함)
//   벽 :		   -1  /   빈공간 :		0  
//  검은 블럭 :		1  /  흰 블럭 :		2	
// 굳은 검은 블럭 :  	3  /  굳은 흰 블럭 : 4	<- 추후 업데이트 예정
// 스캔된 검은 블럭 : 5 / 스캔된 흰 블럭 : 6	<- 추후 업데이트 예정
//
// 1. 상단에서 2x2 블럭이 내려옴
// 2. 같은 색 블록이 2x2로 모이면 굳음
// 3. 주기적으로 -> 방향으로 스캔을 함 
// 4. 2x2의 굳은 블록이 스캔 직 후 사라짐 
// 5. 빈 공간 위에 블록이 있다면 아래로 채워짐
// 
// 추가한것
// - 맵 구성(그리기)
// - 충돌감지 (맵 과 블록간 감지) 
// - 랜덤 블록 생성 
// - 블록 회전, 움직임
// - 사이드 감지 후 멈춤 버그
// - 블럭 반으로 갈라 지는것
// - 2x2 같은 색 블록 굳음 처리 (2x2 이상 사이즈 블록굳음 처리...?!)
// - 주기적으로 -> 움직이는 스캔 만들기 
// - 굳은 블록 터뜨리기
// - 터진 공간 윗 블록이 채우기 확인 필요
// - 게임오버 처리
// - 점수 추가하기

// 맵 넓이 관련
#define MAPWIDTH 18
#define MAPHEIGHT 11

// 구성물 관련
#define SCANNINGPULSE -2
#define	WALL	   -1
#define EMPTY		0
#define	REDBLOCK	1
#define WHITEBLOCK	2
#define SET_REDBLOCK	3
#define SET_WHITEBLOCK	4
#define SCANNED_BLOCK	5
#define SCAN_WHITEBLOCK 6

// 조이스틱 관련
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