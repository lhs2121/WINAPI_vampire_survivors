#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameEngineLevel.h"

std::string GameEngineCore::WindowTitle = "";
std::map<std::string, class GameEngineLevel*> GameEngineCore::AllLevel;
CoreProcess* GameEngineCore::Process = nullptr;
GameEngineLevel* GameEngineCore::CurLevel = nullptr;
GameEngineLevel* GameEngineCore::NextLevel = nullptr;

GameEngineCore::GameEngineCore()
{
}

GameEngineCore::~GameEngineCore()
{
}

void GameEngineCore::CoreStart(HINSTANCE _Inst)
{
	// �����ʿ� �غ� �� �ذ�
	GameEngineWindow::MainWindow.Open(WindowTitle, _Inst);

	// ������ �غ� ���ش�.
	Process->Start();
}

void GameEngineCore::CoreUpdate()
{
	if (nullptr != NextLevel)
	{
		CurLevel = NextLevel;
		NextLevel = nullptr;
		GameEngineTime::MainTimer.Reset();
	}

	// ������Ʈ�� 
	GameEngineTime::MainTimer.Update();
	float Delta = GameEngineTime::MainTimer.GetDeltaTime();


	// �������� ������ ����� �⺻���� ������ 
	// ��ȭ�� ���� �Ϸ��� �ϴ� �����ǵ��� �ִ°�.
	// �̰� ȣ���� �ִ� PlayLevel
	CurLevel->Update(Delta);

	// TitleLevel
	CurLevel->ActorUpdate(Delta);
	GameEngineWindow::MainWindow.ClearBackBuffer();
	CurLevel->ActorRender();
	CurLevel->Render();
	GameEngineWindow::MainWindow.DoubleBuffering();

}

void GameEngineCore::CoreEnd()
{
	Process->Release();

	if (nullptr != Process)
	{
		delete Process;
		Process = nullptr;
	}

	for (std::pair<std::string, GameEngineLevel*> _Pair : AllLevel)
	{
		if (nullptr != _Pair.second)
		{
			delete _Pair.second;
			_Pair.second = nullptr;
		}
	}
}


void GameEngineCore::EngineStart(const std::string& _Title, HINSTANCE _Inst, CoreProcess* _Ptr)
{
	GameEngineDebug::LeckCheck();

	Process = _Ptr;
	WindowTitle = _Title;
	GameEngineWindow::MessageLoop(_Inst, CoreStart, CoreUpdate, CoreEnd);
}

void GameEngineCore::LevelInit(GameEngineLevel* _Level)
{
	_Level->Start();
}