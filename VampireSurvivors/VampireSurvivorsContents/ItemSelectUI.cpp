#include "ItemSelectUI.h"
#include "ContentsEnum.h"
#include "PlayLevel.h"
#include "ItemButton.h"
#include "WeaponStats.h"
#include "PlayerUI.h"
#include "StatusUI.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <random>
#include <vector>

ItemSelectUI* ItemSelectUI::UI = nullptr;

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

		Text_LevelUp = CreateUIRenderer(RenderOrder::Text);
		Text_LevelUp->SetRenderPos({ 495,90 });
		Text_LevelUp->SetText("레벨 업!", 35, "메이플스토리");
	}

	{
		float4 scale = float4(388, 100);
		Collision1 = CreateCollision(CollisionOrder::PlayUI);
		Collision1->SetCollisionScale(scale);

		Collision2 = CreateCollision(CollisionOrder::PlayUI);
		Collision2->SetCollisionScale(scale);

		Collision3 = CreateCollision(CollisionOrder::PlayUI);
		Collision3->SetCollisionScale(scale);

		Collision4 = CreateCollision(CollisionOrder::PlayUI);
		Collision4->SetCollisionScale(scale);

		Mouse = CreateCollision(CollisionOrder::PlayUI);
		Mouse->SetCollisionScale({ 50,50 });
	}
	{
		ItemButton1 = GetLevel()->CreateActor<ItemButton>(UpdateOrder::PlayUI);
		ItemButton1->SetPos({ 545,210 });

		ItemButton2 = GetLevel()->CreateActor<ItemButton>(UpdateOrder::PlayUI);
		ItemButton2->SetPos({ 545,325 });

		ItemButton3 = GetLevel()->CreateActor<ItemButton>(UpdateOrder::PlayUI);
		ItemButton3->SetPos({ 545,440 });

		ItemButton4 = GetLevel()->CreateActor<ItemButton>(UpdateOrder::PlayUI);
		ItemButton4->SetPos({ 545,555 });
	}


	Off();
}

void ItemSelectUI::Update(float _Delta)
{
	Mouse->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + GameEngineWindow::MainWindow.GetMousePos());

	if (true == Collision1->CollisonCheck(Mouse, CollisionType::Rect, CollisionType::Rect) && Collision1->IsUpdate())
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

	if (true == Collision2->CollisonCheck(Mouse, CollisionType::Rect, CollisionType::Rect) && Collision2->IsUpdate())
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

	if (true == Collision3->CollisonCheck(Mouse, CollisionType::Rect, CollisionType::Rect) && Collision3->IsUpdate())
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

	if (true == Collision4->CollisonCheck(Mouse, CollisionType::Rect, CollisionType::Rect) && Collision4->IsUpdate())
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
void ItemSelectUI::GetRandomint(int _min, int _max)
{
	numbers.clear();

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(_min, _max);

	while (numbers.size() < 3) {
		int random_num = distribution(generator);
		if (std::find(numbers.begin(), numbers.end(), random_num) == numbers.end()) {
			numbers.push_back(random_num);
		}
	}
}
void ItemSelectUI::ButtonSetting()
{
	WeaponType type[3] = { WeaponType::Null };

	if (false == StatusUI::UI->IsFullWeapon())
	{
		GetRandomint(0, 6);
		type[0] = static_cast<WeaponType>(numbers[0]);
		type[1] = static_cast<WeaponType>(numbers[1]);
		type[2] = static_cast<WeaponType>(numbers[2]);
	}
	else if (true == StatusUI::UI->IsFullWeapon())
	{
		GetRandomint(0, StatusUI::UI->MyWeapon.size() - 1);

		for (int i = 0; i < 3; i++)
		{
			type[i] = StatusUI::UI->MyWeapon[numbers[i]];

			if (WeaponStats::AllStats[type[i]].isMaxLevel)
			{
				type[i] = WeaponType::Null;
			}
		}
	}

	ItemButton1->SetWeaponEffect(type[0]);
	ItemButton2->SetWeaponEffect(type[1]);
	ItemButton3->SetWeaponEffect(type[2]);

	{
		ItemButton1->On();
		ItemButton2->On();
		ItemButton3->On();

		Collision1->On();
		Collision1->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + ItemButton1->GetPos());
		Collision2->On();
		Collision2->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + ItemButton2->GetPos());
		Collision3->On();
		Collision3->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + ItemButton3->GetPos());
	}

	if (true == IsLucky)
	{
		ItemButton4->SetWeaponEffect(type[2]);
		ItemButton4->On();
		Collision4->On();
		Collision4->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + ItemButton3->GetPos());
	}
}

void ItemSelectUI::On()
{
	ItemSelectPanel->On();
	Text_LevelUp->On();
	ButtonSetting();
	StatusUI::UI->On();
}

void ItemSelectUI::Off()
{
	ItemSelectPanel->Off();
	Text_LevelUp->Off();
	Collision1->Off();
	Collision2->Off();
	Collision3->Off();
	Collision4->Off();
	ItemButton1->Off();
	ItemButton2->Off();
	ItemButton3->Off();
	ItemButton4->Off();
	StatusUI::UI->Off();
}

