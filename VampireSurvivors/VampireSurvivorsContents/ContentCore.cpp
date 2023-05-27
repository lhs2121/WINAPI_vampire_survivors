#include "ContentCore.h"
#include "TitleLevel.h"
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

	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");

	GameEngineCore::ChangeLevel("TitleLevel");

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