#include "ItemSelectUI.h"
#include "ContentsEnum.h"
#include "PlayLevel.h"
#include "ItemButton.h"
#include "WeaponStats.h"
#include "PlayerUI.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

ItemSelectUI* ItemSelectUI::SelectUI = nullptr;

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
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("PlayetStatsPanel.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("TopAlpha.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("BottomAlpha.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("WeaponChecker.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("AccessoryChecker.bmp"), 6, 1);

		path.MoveChild("ItemSlotImage\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("knifeslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("wandslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("axeslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("runeslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("firewandslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("crossslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("whipslot.bmp"));

	}

	{
		StatsPanel = CreateUIRenderer(RenderOrder::PlayUI);
		StatsPanel->SetTexture("PlayetStatsPanel.bmp");
		StatsPanel->SetRenderPos({ 110,300 });

		TopAlpha = CreateUIRenderer(RenderOrder::PlayUI);
		TopAlpha->SetTexture("TopAlpha.bmp");
		TopAlpha->SetAlpha(90);
		TopAlpha->SetRenderPos({ 110,95 });
		TopAlpha->Off();

		BottomAlpha = CreateUIRenderer(RenderOrder::PlayUI);
		BottomAlpha->SetTexture("BottomAlpha.bmp");
		BottomAlpha->SetAlpha(90);
		BottomAlpha->SetRenderPos({ 110,365 });
		BottomAlpha->Off();

		float4 PrevPos = float4::ZERO;

		for (int i = 0; i < 6; i++)
		{
			WeaponChecker[i] = CreateUIRenderer(RenderOrder::PlayUI);

			if (PrevPos == float4::ZERO)
			{
				WeaponChecker[i]->SetRenderPos({ 30,80 });
			}
			else
			{
				WeaponChecker[i]->SetRenderPos(PrevPos+float4(30,0));
			}
			
			WeaponChecker[i]->SetSprite("WeaponChecker.bmp", 0);
			WeaponChecker[i]->SetRenderScale({ 24,24 });
			WeaponChecker[i]->Off();

			PrevPos = WeaponChecker[i]->GetRenderPos();
		}

		PrevPos = float4::ZERO;

		for (int i = 0; i < 6; i++)
		{
			AccessoryChecker[i] = CreateUIRenderer(RenderOrder::PlayUI);

			if (PrevPos == float4::ZERO)
			{
				AccessoryChecker[i]->SetRenderPos({ 30,145 });
			}
			else
			{
				AccessoryChecker[i]->SetRenderPos(PrevPos + float4(30, 0));
			}

			AccessoryChecker[i]->SetSprite("AccessoryChecker.bmp", 0);
			AccessoryChecker[i]->SetRenderScale({ 24,24 });
			AccessoryChecker[i]->Off();

			PrevPos = AccessoryChecker[i]->GetRenderPos();
		}

	}

	{
		ItemSelectPanel = CreateUIRenderer(RenderOrder::PlayUI);
		ItemSelectPanel->SetRenderPos({ 545,345 });
		ItemSelectPanel->SetTexture("ItemSelectPanel.bmp");

	
		Text = CreateUIRenderer(RenderOrder::Text);
		Text->SetRenderPos({ 495,90 });
		Text->SetText("레벨 업!", 35, "메이플스토리");

	}

	{
		float4 scale = float4(388, 100);
		Button1 = CreateCollision(CollisionOrder::PlayUI);
		Button1->SetCollisionScale(scale);

		Button2 = CreateCollision(CollisionOrder::PlayUI);
		Button2->SetCollisionScale(scale);

		Button3 = CreateCollision(CollisionOrder::PlayUI);
		Button3->SetCollisionScale(scale);

		Button4 = CreateCollision(CollisionOrder::PlayUI);
		Button4->SetCollisionScale(scale);

		Mouse = CreateCollision(CollisionOrder::PlayUI);
		Mouse->SetCollisionScale({ 50,50 });

	}

	Off();
}

void ItemSelectUI::CreateWeaponSlotRenderer(WeaponType _Type)
{

	static float4 prevpos = float4::ZERO;

	GameEngineRenderer* renderer = CreateUIRenderer(RenderOrder::PlayUI);

	if (prevpos == float4::ZERO)
	{
		renderer->SetRenderPos({ 30,50 });
	}
	else
	{
		renderer->SetRenderPos(prevpos+float4(30,0));
	}
	
	prevpos = renderer->GetRenderPos();

	renderer->SetRenderScale({ 24,24 });
	renderer->SetTexture(WeaponStats::AllStats[_Type].getSlotTextureName());

	WeaponRenderer.push_back(renderer);
	WeaponRenderer[WeaponNum]->Off();

	WeaponStats::AllStats[_Type].setSlotNumber(WeaponNum);
	WeaponNum += 1;

}

void ItemSelectUI::WeaponSlotUpgrade(WeaponType _Type)
{
	
	int num = WeaponStats::AllStats[_Type].getSlotNumber();

	if (WeaponUpgradeNum[num] == 8)
	{
		return;
	}

	WeaponChecker[num]->SetSprite("WeaponChecker.bmp", WeaponUpgradeNum[num] + 1);
	WeaponChecker[num]->Off();
	WeaponUpgradeNum[num] += 1;
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

	if (true == Button4->CollisonCheck(Mouse, CollisionType::Rect, CollisionType::Rect) && Button4->IsUpdate())
	{
		if (GameEngineInput::IsDown(VK_LBUTTON))
		{
			ItemButton4->OnClick();
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
	StatsPanel->On();
	TopAlpha->On();
	BottomAlpha->On();
	Text->On();

	PlayerUI::UI->SlotPanel->Off();
	for (int i = 0; i < WeaponRenderer.size(); i++)
	{
		WeaponRenderer[i]->On();
	}
	for (int i = 0; i < WeaponNum; i++)
	{
		WeaponChecker[i]->On();
	}

	{
		ItemButton1 = GetLevel()->CreateActor<ItemButton>(UpdateOrder::PlayUI);
		ItemButton1->SetPos({ 545,210 });
		ItemButton1->SetTexture();
		ItemButton1->On();

		Button1->On();
		Button1->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + ItemButton1->GetPos());
	}


	{
		ItemButton2 = GetLevel()->CreateActor<ItemButton>(UpdateOrder::PlayUI);
		ItemButton2->SetPos({ 545,325 });
		ItemButton2->SetTexture();
		ItemButton2->On();

		Button2->On();
		Button2->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + ItemButton2->GetPos());
	}


	{
		ItemButton3 = GetLevel()->CreateActor<ItemButton>(UpdateOrder::PlayUI);
		ItemButton3->SetPos({ 545,440 });
		ItemButton3->SetTexture();
		ItemButton3->On();

		Button3->On();
		Button3->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + ItemButton3->GetPos());
	}

	{
		if (true == IsLucky)
		{
			ItemButton4 = GetLevel()->CreateActor<ItemButton>(UpdateOrder::PlayUI);
			ItemButton4->SetPos({ 545,555 });
			ItemButton4->SetTexture();
			ItemButton4->On();

			Button4->On();
			Button4->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + ItemButton3->GetPos());
		}

	}

}
void ItemSelectUI::Off()
{
	ItemSelectPanel->Off();
	StatsPanel->Off();
	Text->Off();
	TopAlpha->Off();
	BottomAlpha->Off();
	PlayerUI::UI->SlotPanel->On();
	for (int i = 0; i < WeaponRenderer.size(); i++)
	{
		WeaponRenderer[i]->Off();

	}
	for (int i = 0; i < 6; i++)
	{
		WeaponChecker[i]->Off();
		AccessoryChecker[i]->Off();
	}


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

	if (ItemButton4 != nullptr)
	{
		ItemButton4->Off();
	}

	Button1->Off();
	Button2->Off();
	Button3->Off();
	Button4->Off();
}

