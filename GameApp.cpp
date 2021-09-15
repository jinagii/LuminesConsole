#include "ConsoleLib.h"
#include <stdio.h>
#include "Lumines.h"
#include <time.h>
#include "GameApp.h"

extern int Map[MAPHEIGHT][MAPWIDTH];

GameApp::GameApp()
	:LuminoArray()
{
	m_pCGEngine = NULL;
}

GameApp::~GameApp()
{

}


void GameApp::Initialize1()
{
	m_pCGEngine = new LHCGEngine();

	InitCGEngine(m_pCGEngine);

	/// 프로그램 초기화

	// 랜덤 함수 시드
	srand(time(NULL));

	// 그래픽스 초기화
	if (m_pCGEngine->Initialize() == FALSE)
	{
		return;
	}

	// 커서 사이즈 변경 - 삭제 
	m_pCGEngine->LHSetCursor(20, FALSE);

	// 스크린 사이즈 변경
	set_screen_size(60, 40);

	// 시작 씬은 타이틀
	g_nowState = eGameState::TitleScene;

}

void GameApp::Loop()
{
	/// 게임 무한반복 (새로운 게임)
	while (true)
	{
		// 유한 상태 기계, 상황에 따라서 Scene을 매 프레임 재생
		LuminesStateMachine();
	}
}

void GameApp::LuminesStateMachine()
{
	switch (g_nowState)
	{
		// 
		case eGameState::TitleScene:
		{
			// 게임 안내 문구
			InitiateGame();

			// 방향키 입력 받으면
			if (IsAnyKeyPressed() == true)
			{
				// 맵을 초기화
				ClearMap();

				// 초기 루미노 생성
				CreateLumino(LuminoArray);

				g_nowState = eGameState::InGame;
			}
		}
		break;

		// 인게임 시작
		case eGameState::InGame:
		{
			// 블럭 스퀘어 확인
			CheckBlockSquare(Map);

			// 블럭 움직이기			
			MoveBlock(LuminoArray);

			// 빈 공간을 채우기
			BlockFillEmpty(Map);

			// 스캐닐 펄스 - 블럭 파괴
			ScanningPulse();

			// 맵 그리기
			DrawMap();

			// 루미노 그리기
			DrawLumino(LuminoArray);

			// 점수 그리기
			DrawScore();

			// 게임 오버 전환
			if (IsGameOver() == true)
			{
				g_nowState = eGameState::GameOver;
			}
		}
		break;

		// 게임 오버 상태
		case eGameState::GameOver:
		{
			// GameOver / Restart 여부 화면 출력
			QuitOrRestart();

			// 아무 키나 입력받으면 재시작
			if (IsAnyKeyPressed() == true)
			{
				// 재시작을 위한 작업
				system("cls");

				g_nowState = eGameState::TitleScene;
			}
		}
		break;

		//case eGameState::Restarting:
		//{
		//	system("cls");

		//	g_nowState = eGameState::TitleScene;
		//}
		//break;		

		default:
		{
		}
		break;
	}
}
