#pragma once

class LHCGEngine;

/// FSM (finite state machine) �����غ���
enum class eGameState
{
	TitleScene,	// ���� ȭ��
	InGame,		// �ΰ��� ��Ȳ
	GameOver,	// ���� ���� ȭ��
	Restarting,	// ����� ȭ��

	//���� �̱���
	Menu,		// �޴�
	Cinematic,	// �ó׸�ƽ 
};

// ���� ���α׷� �Ϲ����� �κ��� ���
// �����Լ��� �κ��� ��ü�ϴ� ���� ū Ŭ����
class GameApp
{
public:
	GameApp();
	~GameApp();

public:
	void Initialize1();
	void Loop();
	void LuminesStateMachine();

	// ��� ������
private:
	
	int LuminoArray[2][2];

	// ���� ������ FSM ���� State
	eGameState g_nowState = eGameState::TitleScene;

	// �� Ŭ���� ���ο����� ����ϴ� �Լ���
	LHCGEngine* m_pCGEngine;

};

