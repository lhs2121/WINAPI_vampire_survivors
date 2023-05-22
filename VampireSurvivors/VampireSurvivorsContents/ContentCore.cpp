#include "ContentCore.h"
#include "Title.h"
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

	GameEngineCore::CreateLevel<Title>("Title");


	// 이 레벨이 화면에 보여라.
	GameEngineCore::ChangeLevel("Title");
}

// 행동한고.
void ContentCore::Update(float _Delta)
{
}

// 그려지고.
void ContentCore::Render()
{
}

// 정리된다.
void ContentCore::Release()
{
}