#include "CharactorSelectUI.h"
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCore.h>

CharactorSelectUI::CharactorSelectUI()
{

}

CharactorSelectUI::~CharactorSelectUI()
{

}


void CharactorSelectUI::Start()
{
	SetPos({ 545,345 });
	
	{
		StartButton = CreateRenderer(1);
		CollectionButton = CreateRenderer(1);
		UpgradeButton = CreateRenderer(1);
		UnlockButton = CreateRenderer(1);
		MakersButton = CreateRenderer(1);

		SelectPanel = CreateRenderer(2);
		CharactorButton1 = CreateRenderer(3);
	}

	{
		StartButton->SetRenderPos({ 0 ,100 });
		CollectionButton->SetRenderPos({ -180,215 });
		UpgradeButton->SetRenderPos({ 0,215 });
		UnlockButton->SetRenderPos({ 180,215 });
		MakersButton->SetRenderPos({ 0,300 });

		SelectPanel->SetRenderPos({ 0,40 });
		CharactorButton1->SetRenderPos({ -190,-100 });

	}

	{
		StartButton->SetTexture("start.bmp");
		CollectionButton->SetTexture("collection.bmp");
		UpgradeButton->SetTexture("upgrade.bmp");
		UnlockButton->SetTexture("unlock.bmp");
		MakersButton->SetTexture("makers.bmp");

		SelectPanel->SetTexture("SelectPanel.bmp");
		CharactorButton1->SetTexture("Zenaro.bmp");
	}

	{
		SelectPanel->Off();
		CharactorButton1->Off();
	}

	{
		StartCol = CreateCollision(0);
		StartCol->SetCollisionPos(StartButton->GetRenderPos());
		StartCol->SetCollisionScale(ResourcesManager::GetInst().FindTexture("start.bmp")->GetScale());

		CharactorCol = CreateCollision(0);
		CharactorCol->SetCollisionPos(CharactorButton1->GetRenderPos());
		CharactorCol->SetCollisionScale(ResourcesManager::GetInst().FindTexture("Zenaro.bmp")->GetScale());
		CharactorCol->Off();

		Mouse = CreateCollision(0);
		Mouse->SetCollisionScale({ 5,5 });
	}
}

void CharactorSelectUI::Update(float _Delta)
{
	Mouse->SetCollisionPos(GameEngineWindow::MainWindow.GetMousePos() + MouseOffset);

	if (true == StartCol->CollisonCheck(Mouse, CollisionType::Rect, CollisionType::Rect) && false == SelectPanel->IsUpdate())
	{
		if (GameEngineInput::IsDown(VK_LBUTTON))
		{
			SelectPanel->On();
			CharactorButton1->On();
			CharactorCol->On();
		}
	}
	
	if (true == CharactorCol->CollisonCheck(Mouse, CollisionType::Rect, CollisionType::Rect) && true == SelectPanel->IsUpdate())
	{
		if (GameEngineInput::IsDown(VK_LBUTTON))
		{
			GameEngineCore::ChangeLevel("PlayLevel");
		}
	}
	
	
}