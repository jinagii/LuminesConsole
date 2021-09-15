#pragma once

class LHCGEngine;

/// FSM (finite state machine) 공부해보자
enum class eGameState
{
	TitleScene,	// 시작 화면
	InGame,		// 인게임 상황
	GameOver,	// 게임 오버 화면
	Restarting,	// 재시작 화면

	//아직 미구현
	Menu,		// 메뉴
	Cinematic,	// 시네마틱 
};

// 게임 프로그램 일반적인 부분을 담당
// 메인함수의 부분을 대체하는 가장 큰 클래스
class GameApp
{
public:
	GameApp();
	~GameApp();

public:
	void Initialize1();
	void Loop();
	void LuminesStateMachine();

	// 멤버 변수들
private:
	
	int LuminoArray[2][2];

	// 현재 동작할 FSM 게임 State
	eGameState g_nowState = eGameState::TitleScene;

	// 이 클래스 내부에서만 사용하는 함수들
	LHCGEngine* m_pCGEngine;

};

