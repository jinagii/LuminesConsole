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

	/// ���α׷� �ʱ�ȭ

	// ���� �Լ� �õ�
	srand(time(NULL));

	// �׷��Ƚ� �ʱ�ȭ
	if (m_pCGEngine->Initialize() == FALSE)
	{
		return;
	}

	// Ŀ�� ������ ���� - ���� 
	m_pCGEngine->LHSetCursor(20, FALSE);

	// ��ũ�� ������ ����
	set_screen_size(60, 40);

	// ���� ���� Ÿ��Ʋ
	g_nowState = eGameState::TitleScene;

}

void GameApp::Loop()
{
	/// ���� ���ѹݺ� (���ο� ����)
	while (true)
	{
		// ���� ���� ���, ��Ȳ�� ���� Scene�� �� ������ ���
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
			// ���� �ȳ� ����
			InitiateGame();

			// ����Ű �Է� ������
			if (IsAnyKeyPressed() == true)
			{
				// ���� �ʱ�ȭ
				ClearMap();

				// �ʱ� ��̳� ����
				CreateLumino(LuminoArray);

				g_nowState = eGameState::InGame;
			}
		}
		break;

		// �ΰ��� ����
		case eGameState::InGame:
		{
			// �� ������ Ȯ��
			CheckBlockSquare(Map);

			// �� �����̱�			
			MoveBlock(LuminoArray);

			// �� ������ ä���
			BlockFillEmpty(Map);

			// ��ĳ�� �޽� - �� �ı�
			ScanningPulse();

			// �� �׸���
			DrawMap();

			// ��̳� �׸���
			DrawLumino(LuminoArray);

			// ���� �׸���
			DrawScore();

			// ���� ���� ��ȯ
			if (IsGameOver() == true)
			{
				g_nowState = eGameState::GameOver;
			}
		}
		break;

		// ���� ���� ����
		case eGameState::GameOver:
		{
			// GameOver / Restart ���� ȭ�� ���
			QuitOrRestart();

			// �ƹ� Ű�� �Է¹����� �����
			if (IsAnyKeyPressed() == true)
			{
				// ������� ���� �۾�
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
