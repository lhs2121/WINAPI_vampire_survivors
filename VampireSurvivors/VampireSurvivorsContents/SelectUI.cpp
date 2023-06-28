#include "SelectUI.h"
#include "ContentsEnum.h"
#include "PlayLevel.h"
#include "SelectBox.h"
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

SelectUI* SelectUI::UI = nullptr;

void SelectUI::Start()
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
		SelectBox1 = GetLevel()->CreateActor<SelectBox>(UpdateOrder::PlayUI);
		SelectBox1->SetPos({ 545,210 });

		SelectBox2 = GetLevel()->CreateActor<SelectBox>(UpdateOrder::PlayUI);
		SelectBox2->SetPos({ 545,325 });

		SelectBox3 = GetLevel()->CreateActor<SelectBox>(UpdateOrder::PlayUI);
		SelectBox3->SetPos({ 545,440 });

		SelectBox4 = GetLevel()->CreateActor<SelectBox>(UpdateOrder::PlayUI);
		SelectBox4->SetPos({ 545,555 });
	}


	Off();
}

void SelectUI::Update(float _Delta)
{
	Mouse->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + GameEngineWindow::MainWindow.GetMousePos());

	if (true == Collision1->CollisonCheck(Mouse, CollisionType::Rect, CollisionType::Rect) && Collision1->IsUpdate())
	{
		if (GameEngineInput::IsDown(VK_LBUTTON))
		{
			SelectBox1->OnClick();
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
			SelectBox2->OnClick();
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
			SelectBox3->OnClick();
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
			SelectBox4->OnClick();
			GameEngineTime::MainTimer.SetAllTimeScale(1);
			PlayLevel* lv = static_cast<PlayLevel*>(GetLevel());
			lv->SpawnCheck = true;
			Off();
		}
	}

}
void SelectUI::GetRandomNumbers(int _min, int _max)
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
void SelectUI::RandomTypeSetting()
{
	WeaponType type[3] = { WeaponType::Null };

	if (false == StatusUI::UI->IsFullWeapon())
	{
		GetRandomNumbers(0, 6);
		type[0] = static_cast<WeaponType>(numbers[0]);
		type[1] = static_cast<WeaponType>(numbers[1]);
		type[2] = static_cast<WeaponType>(numbers[2]);
	}
	else if (true == StatusUI::UI->IsFullWeapon())
	{
		GetRandomNumbers(0, static_cast<int>(StatusUI::UI->MyWeapon.size() - 1));

		for (int i = 0; i < 3; i++)
		{
			type[i] = StatusUI::UI->MyWeapon[numbers[i]];

			if (WeaponStats::AllStats[type[i]].isMaxLevel)
			{
				type[i] = WeaponType::Null;
			}
		}
	}

	RandomType.push_back(type[0]);
	RandomType.push_back(type[1]);
	RandomType.push_back(type[2]);
}
void SelectUI::ButtonSetting()
{
	RandomTypeSetting();

	SelectBox1->SetWeaponEffect(RandomType[0]);
	SelectBox2->SetWeaponEffect(RandomType[1]);
	SelectBox3->SetWeaponEffect(RandomType[2]);


	SelectBox1->On();
	SelectBox2->On();
	SelectBox3->On();

	Collision1->On();
	Collision2->On();
	Collision3->On();

	Collision1->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + SelectBox1->GetPos());
	Collision2->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + SelectBox2->GetPos());
	Collision3->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + SelectBox3->GetPos());

	RandomType.clear();
	/*
	if (true == IsLucky)
	{
		SelectBox4->SetWeaponEffect(RandomType[0]);
		SelectBox4->On();
		Collision4->On();
		Collision4->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + SelectBox3->GetPos());
	}
	*/
}

void SelectUI::On()
{
	ItemSelectPanel->On();
	Text_LevelUp->On();
	ButtonSetting();
	StatusUI::UI->On();
}

void SelectUI::Off()
{
	ItemSelectPanel->Off();
	Text_LevelUp->Off();
	Collision1->Off();
	Collision2->Off();
	Collision3->Off();
	Collision4->Off();
	SelectBox1->Off();
	SelectBox2->Off();
	SelectBox3->Off();
	SelectBox4->Off();
	StatusUI::UI->Off();
}

