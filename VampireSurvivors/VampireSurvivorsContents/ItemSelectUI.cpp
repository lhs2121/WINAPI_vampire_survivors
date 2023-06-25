#include "ItemSelectUI.h"
#include "ContentsEnum.h"
#include "PlayLevel.h"
#include "ItemButton.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>


void ItemSelectUI::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("ItemSelectPanel.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("UI\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemSelectPanel.bmp"));

	}

	{
		ItemSelectPanel = CreateUIRenderer(RenderOrder::PlayUI);
		ItemSelectPanel->SetRenderPos({ 545,345 });
		ItemSelectPanel->SetTexture("ItemSelectPanel.bmp");
	}

	{
		Button1 = CreateCollision(CollisionOrder::PlayUI);
		Button1->SetCollisionScale({ 388,166 });

		Button2 = CreateCollision(CollisionOrder::PlayUI);
		Button2->SetCollisionScale({ 388,166 });

		Button3 = CreateCollision(CollisionOrder::PlayUI);
		Button3->SetCollisionScale({ 388,166 });

		Mouse = CreateCollision(CollisionOrder::PlayUI);
		Mouse->SetCollisionScale({ 50,50 });

	}

	Off();
}


void ItemSelectUI::Update(float _Delta)
{
	Mouse->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + GameEngineWindow::MainWindow.GetMousePos());

	if (true == Button1->CollisonCheck(Mouse, CollisionType::Rect, CollisionType::Rect) && Button1->IsUpdate())
	{
		if (GameEngineInput::IsDown(VK_LBUTTON))
		{
			ItemButton1->OnClick();
			GameEngineTime::MainTimer.SetAllTimeScale(1);
			PlayLevel* lv = static_cast<PlayLevel*>(GetLevel());
			lv->SpawnCheck = true;
			Off();
		}
	}

	if (true == Button2->CollisonCheck(Mouse, CollisionType::Rect, CollisionType::Rect) && Button2->IsUpdate())
	{
		if (GameEngineInput::IsDown(VK_LBUTTON))
		{
			ItemButton2->OnClick();
			GameEngineTime::MainTimer.SetAllTimeScale(1);
			PlayLevel* lv = static_cast<PlayLevel*>(GetLevel());
			lv->SpawnCheck = true;
			Off();
		}
	}

	if (true == Button3->CollisonCheck(Mouse, CollisionType::Rect, CollisionType::Rect) && Button3->IsUpdate())
	{
		if (GameEngineInput::IsDown(VK_LBUTTON))
		{
			ItemButton3->OnClick();
			GameEngineTime::MainTimer.SetAllTimeScale(1);
			PlayLevel* lv = static_cast<PlayLevel*>(GetLevel());
			lv->SpawnCheck = true;
			Off();
		}
	}

}

void ItemSelectUI::On()
{
	ItemSelectPanel->On();

	ItemButton1 = GetLevel()->CreateActor<ItemButton>(UpdateOrder::PlayUI);
	ItemButton1->SetPos({ 545,145 });
	ItemButton1->SetTexture();
	ItemButton1->On();

	ItemButton2 = GetLevel()->CreateActor<ItemButton>(UpdateOrder::PlayUI);
	ItemButton2->SetPos({ 545,345 });
	ItemButton2->SetTexture();
	ItemButton2->On();

	ItemButton3 = GetLevel()->CreateActor<ItemButton>(UpdateOrder::PlayUI);
	ItemButton3->SetPos({ 545,545 });
	ItemButton3->SetTexture();
	ItemButton3->On();


	Button1->On();
	Button1->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + ItemButton1->GetPos());

	Button2->On();
	Button2->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + ItemButton2->GetPos());

	Button3->On();
	Button3->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + ItemButton3->GetPos());
}
void ItemSelectUI::Off()
{
	ItemSelectPanel->Off();

	if (ItemButton1 != nullptr)
	{
		ItemButton1->Off();
	}

	if (ItemButton2 != nullptr)
	{
		ItemButton2->Off();
	}

	if (ItemButton3 != nullptr)
	{
		ItemButton3->Off();
	}

	Button1->Off();
	Button2->Off();
	Button3->Off();
}

void ItemSelectUI::SetItemPanel()
{

}