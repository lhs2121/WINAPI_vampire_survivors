#include "ContentCore.h"
#include "IntroLevel.h"
#include "MenuLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

ContentCore::ContentCore()
{
}

ContentCore::~ContentCore()
{
}

void ContentCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 1090, 690 });

	GameEngineCore::CreateLevel<IntroLevel>("IntroLevel");

	GameEngineCore::CreateLevel<MenuLevel>("MenuLevel");

	GameEngineCore::ChangeLevel("IntroLevel");

}

// �ൿ�Ѱ�.
void ContentCore::Update(float _Delta)
{
}

// �׷�����.
void ContentCore::Render(float _Delta)
{
}

// �����ȴ�.
void ContentCore::Release()
{
}