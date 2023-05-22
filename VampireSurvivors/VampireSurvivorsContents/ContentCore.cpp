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


	// �� ������ ȭ�鿡 ������.
	GameEngineCore::ChangeLevel("Title");
}

// �ൿ�Ѱ�.
void ContentCore::Update(float _Delta)
{
}

// �׷�����.
void ContentCore::Render()
{
}

// �����ȴ�.
void ContentCore::Release()
{
}