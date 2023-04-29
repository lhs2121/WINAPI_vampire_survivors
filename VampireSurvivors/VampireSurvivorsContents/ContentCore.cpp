#include "ContentCore.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "EndingLevel.h"

ContentCore::ContentCore()
{
}

ContentCore::~ContentCore()
{
}

void ContentCore::Start()
{
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<EndingLevel>("EndingLevel");

	// �� ������ ȭ�鿡 ������.
	GameEngineCore::ChangeLevel("PlayLevel");
}

// �ൿ�Ѱ�.
void ContentCore::Update()
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