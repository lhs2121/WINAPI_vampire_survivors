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
#include <algorithm>

SelectUI* SelectUI::UI = nullptr;

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

	SelectBox1->Off();
	SelectBox2->Off();
	SelectBox3->Off();
	StatusUI::UI->Off();
}


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
		SelectBox1 = GetLevel()->CreateActor<SelectBox>(UpdateOrder::PlayUI);
		SelectBox1->SetPos({ 545,210 });

		SelectBox2 = GetLevel()->CreateActor<SelectBox>(UpdateOrder::PlayUI);
		SelectBox2->SetPos({ 545,325 });

		SelectBox3 = GetLevel()->CreateActor<SelectBox>(UpdateOrder::PlayUI);
		SelectBox3->SetPos({ 545,440 });
	}

	{
		float4 scale = float4(388, 110);

		Collision1 = CreateCollision(CollisionOrder::PlayUI);
		Collision1->SetCollisionScale(scale);

		Collision2 = CreateCollision(CollisionOrder::PlayUI);
		Collision2->SetCollisionScale(scale);

		Collision3 = CreateCollision(CollisionOrder::PlayUI);
		Collision3->SetCollisionScale(scale);

		Mouse = CreateCollision(CollisionOrder::PlayUI);
		Mouse->SetCollisionScale({ 50,50 });
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
			PlayLevel::ChangeSpawnState();
			Off();
		}
	}
	//1번 버튼 눌렀을때
	else if (true == Collision2->CollisonCheck(Mouse, CollisionType::Rect, CollisionType::Rect) && Collision2->IsUpdate())
	{
		if (GameEngineInput::IsDown(VK_LBUTTON))
		{
			SelectBox2->OnClick();
			GameEngineTime::MainTimer.SetAllTimeScale(1);
			PlayLevel::ChangeSpawnState();
			Off();
		}
	}
	//2번 버튼 눌렀을때
	else if (true == Collision3->CollisonCheck(Mouse, CollisionType::Rect, CollisionType::Rect) && Collision3->IsUpdate())
	{
		if (GameEngineInput::IsDown(VK_LBUTTON))
		{
			SelectBox3->OnClick();
			GameEngineTime::MainTimer.SetAllTimeScale(1);
			PlayLevel::ChangeSpawnState();
			Off();
		}
	}
	//3번 버튼 눌렀을때

}

void SelectUI::ButtonSetting()
{
	WeaponStats::AllStats[WeaponType::Knife].isBoxed = false;
	WeaponStats::AllStats[WeaponType::MagicWand].isBoxed = false;
	WeaponStats::AllStats[WeaponType::Axe].isBoxed = false;
	WeaponStats::AllStats[WeaponType::Runetracer].isBoxed = false;
	WeaponStats::AllStats[WeaponType::Cross].isBoxed = false;
	WeaponStats::AllStats[WeaponType::Whip].isBoxed = false;
	WeaponStats::AllStats[WeaponType::FireWand].isBoxed = false;
	WeaponStats::AllStats[WeaponType::Null].isBoxed = false;

	PassiveStats::AllPassive[PassiveType::Blackheart].isBoxed = false;
	PassiveStats::AllPassive[PassiveType::Redheart].isBoxed = false;
	PassiveStats::AllPassive[PassiveType::Candle].isBoxed = false;
	PassiveStats::AllPassive[PassiveType::Clover].isBoxed = false;
	PassiveStats::AllPassive[PassiveType::Crown].isBoxed = false;
	PassiveStats::AllPassive[PassiveType::Spinach].isBoxed = false;
	PassiveStats::AllPassive[PassiveType::Book].isBoxed = false;
	PassiveStats::AllPassive[PassiveType::Expball].isBoxed = false;
	PassiveStats::AllPassive[PassiveType::Glove].isBoxed = false;
	PassiveStats::AllPassive[PassiveType::Wing].isBoxed = false;


	RandomType[0] = std::make_pair(WeaponType::Null, PassiveType::Null);
	RandomType[1] = std::make_pair(WeaponType::Null, PassiveType::Null);
	RandomType[2] = std::make_pair(WeaponType::Null, PassiveType::Null);

	RandomTypeSetting();
	RandomTypeSetting2();

	SelectBox1->SetEffect(RandomType[0].first, RandomType[0].second);
	SelectBox2->SetEffect(RandomType[1].first, RandomType[1].second);
	SelectBox3->SetEffect(RandomType[2].first, RandomType[2].second);

	Collision1->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + SelectBox1->GetPos());
	Collision2->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + SelectBox2->GetPos());
	Collision3->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + SelectBox3->GetPos());

	SelectBox1->On();
	SelectBox2->On();
	SelectBox3->On();

	Collision1->On();
	Collision2->On();
	Collision3->On();

	TempWeaponGroup.clear();
	TempPassiveGroup.clear();
}

void SelectUI::RandomTypeSetting()
{
	TempWeaponGroup = { WeaponType::Knife,WeaponType::MagicWand ,WeaponType::Axe ,WeaponType::Runetracer ,
		WeaponType::FireWand,WeaponType::Cross ,WeaponType::Whip };

	if (true == StatusUI::UI->IsAllMax())
	{
		return;
	}
	else if (false == StatusUI::UI->IsFullWeapon())
	{
		RandomType[0].first = GetRandomType();
		RandomType[1].first = GetRandomType();
		RandomType[2].first = GetRandomType();
	}
	else if (true == StatusUI::UI->IsFullWeapon())
	{
		RandomType[0].first = GetRandomType2();
		RandomType[1].first = GetRandomType2();
		RandomType[2].first = GetRandomType2();
	}
}

void SelectUI::RandomTypeSetting2()
{
	TempPassiveGroup = { PassiveType::Blackheart, PassiveType::Redheart, PassiveType::Book,
		PassiveType::Glove, PassiveType::Candle, PassiveType::Expball, PassiveType::Crown, PassiveType::Spinach,
		PassiveType::Wing, PassiveType::Clover };

	if (true == StatusUI::UI->IsAllMax2())
	{
		return;
	}
	else if (false == StatusUI::UI->IsFullpassvie())
	{
		RandomType[0].second = GetRandomType3();
		RandomType[1].second = GetRandomType3();
		RandomType[2].second = GetRandomType3();
	}
	else if (true == StatusUI::UI->IsFullpassvie())
	{
		RandomType[0].second = GetRandomType4();
		RandomType[1].second = GetRandomType4();
		RandomType[2].second = GetRandomType4();
	}
}
WeaponType SelectUI::GetRandomType()
{
	if (TempWeaponGroup.size() < 1)
	{
		return WeaponType::Null;
	}

	WeaponType type = getRandomElement(TempWeaponGroup, 0, TempWeaponGroup.size() - 1);

	if (WeaponStats::AllStats[type].isBoxed == true)
	{
		remove(TempWeaponGroup, type);
		type = GetRandomType();
	}

	WeaponStats::AllStats[type].isBoxed = true;

	return type;
}

WeaponType SelectUI::GetRandomType2()
{
	if (TempWeaponGroup.size() < 1)
	{
		return WeaponType::Null;
	}

	WeaponType type = getRandomElement(TempWeaponGroup, 0, TempWeaponGroup.size() - 1);

	if (WeaponStats::AllStats[type].isBoxed == true || false == WeaponStats::AllStats[type].isSelected || true == WeaponStats::AllStats[type].isMaxLevel)
	{
		remove(TempWeaponGroup, type);
		type = GetRandomType2();
	}

	WeaponStats::AllStats[type].isBoxed = true;

	return type;
}
PassiveType SelectUI::GetRandomType3()
{
	if (TempPassiveGroup.size() < 1)
	{
		return PassiveType::Null;
	}

	PassiveType type = getRandomElement2(TempPassiveGroup, 0, TempPassiveGroup.size() - 1);

	if (PassiveStats::AllPassive[type].isBoxed == true)
	{
		remove2(TempPassiveGroup, type);
		type = GetRandomType3();
	}

	PassiveStats::AllPassive[type].isBoxed = true;

	return type;
}
PassiveType SelectUI::GetRandomType4()
{
	if (TempPassiveGroup.size() < 1)
	{
		return PassiveType::Null;
	}

	PassiveType type = getRandomElement2(TempPassiveGroup, 0, TempPassiveGroup.size() - 1);

	if (PassiveStats::AllPassive[type].isBoxed == true || false == PassiveStats::AllPassive[type].isSelected || true == PassiveStats::AllPassive[type].isMaxLevel)
	{
		remove2(TempPassiveGroup, type);
		type = GetRandomType4();
	}

	PassiveStats::AllPassive[type].isBoxed = true;

	return type;
}