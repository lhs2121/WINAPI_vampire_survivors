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

// 행동한고.
void ContentCore::Update(float _Delta)
{
}

// 그려지고.
void ContentCore::Render(float _Delta)
{
}

// 정리된다.
void ContentCore::Release()
{
}