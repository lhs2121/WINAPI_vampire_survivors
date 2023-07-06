#include "LevelUpUI.h"
#include "ContentsEnum.h"
#include "PlayLevel.h"
#include "SelectBox.h"
#include "WeaponStats.h"
#include "PlayerUI.h"
#include "StatusUI.h"
#include "Mouse.h"
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
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineBase/GameEngineTime.h>
#include <random>
#include <vector>
#include <algorithm>
#include <sstream>

LevelUpUI* LevelUpUI::UI = nullptr;

void LevelUpUI::On()
{
	GameEngineSound::SoundPlay("sfx_levelup.ogg");
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Monster, 0);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 0);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Item, 0);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Weapon, 0);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Timer, 0);

	ItemSelectPanel->On();
	Text_LevelUp->On();

	SelectBox1->On();
	SelectBox2->On();
	SelectBox3->On();

	Collision1->On();
	Collision2->On();
	Collision3->On();

	ButtonSetting();
	StatusUI::UI->On();
}

void LevelUpUI::OnBox()
{
	GameEngineSound::SoundPlay("sfx_treasure_found.ogg");
	
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Monster, 0);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 0);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Item, 0);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Weapon, 0);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Timer, 0);

	ItemSelectPanel->On();
	ItemSelectPanel->SetTexture("ItemSelectPanel.bmp");
	Box->On();
	Button->On();
	Text_Button->On();

	Text_FoundBox->SetText("���� �߰�!", 40, "�����ý��丮");
	Text_FoundBox->SetRenderPos({ 475,100 });
	Text_FoundBox->On();

	Collision4->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + Button->GetRenderPos());
	Collision4->On();

	Box->ChangeAnimation("box_bounce");
	Text_Button->SetText("����", 40, "�����ý��丮");
}

void LevelUpUI::Off()
{

	ItemSelectPanel->Off();
	Text_LevelUp->Off();
	Text_FoundBox->Off();

	Collision1->Off();
	Collision2->Off();
	Collision3->Off();
	Collision4->Off();
	Collision5->Off();

	Box->Off();
	Button->Off();
	Text_Button->Off();

	GoldMark->Off();

	SelectBox1->Off();
	SelectBox2->Off();
	SelectBox3->Off();
	StatusUI::UI->Off();
}


void LevelUpUI::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("ItemSelectPanel.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("UI\\");
		
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemSelectPanel.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("LevelUpPanel.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("box_bounce.bmp"), 8, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("box_openup.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("button.bmp"));
	}

	{
		ItemSelectPanel = CreateUIRenderer(RenderOrder::PlayUI);
		ItemSelectPanel->SetRenderPos({ 545,345 });
		ItemSelectPanel->SetTexture("ItemSelectPanel.bmp");

		Text_LevelUp = CreateUIRenderer(RenderOrder::Text);
		Text_LevelUp->SetRenderPos({ 495,90 });
		Text_LevelUp->SetText("���� ��!", 35, "�����ý��丮");
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
		Box = CreateUIRenderer(RenderOrder::PlayUI);
		Box->CreateAnimation("box_bounce", "box_bounce.bmp", 0, 7, 0.1f, true);
		Box->CreateAnimation("box_openup", "box_openup.bmp");
		Box->ChangeAnimation("box_bounce");
		Box->SetRenderPos({ 545,435 });
		Box->Off();

		Button = CreateUIRenderer(RenderOrder::PlayUI);
		Button->SetTexture("button.bmp");
		Button->SetRenderPos(Box->GetRenderPos() + float4(0, 130));
		Button->Off();

		Text_Button = CreateUIRenderer(RenderOrder::Text);
		Text_Button->SetText("����", 40, "�����ý��丮");
		Text_Button->SetRenderPos(Button->GetRenderPos() + float4(-30,-20));
		Text_Button->Off();

		Text_FoundBox = CreateUIRenderer(RenderOrder::Text);
		Text_FoundBox->SetText("���� �߰�!",40,"�����ý��丮");
		Text_FoundBox->SetRenderPos({ 475,100 });
		Text_FoundBox->Off();

		GoldMark = CreateUIRenderer(RenderOrder::Text);
		GoldMark->SetTexture("CoinMark.bmp");
		GoldMark->Off();

	}

	{
		float4 scale = float4(388, 110);

		Collision1 = CreateCollision(CollisionOrder::PlayUI);
		Collision1->SetCollisionScale(scale);

		Collision2 = CreateCollision(CollisionOrder::PlayUI);
		Collision2->SetCollisionScale(scale);

		Collision3 = CreateCollision(CollisionOrder::PlayUI);
		Collision3->SetCollisionScale(scale);

		Collision4 = CreateCollision(CollisionOrder::PlayUI);
		Collision4->SetCollisionScale({ 192,51 });
		Collision4->Off();

		Collision5 = CreateCollision(CollisionOrder::PlayUI);
		Collision5->SetCollisionScale({ 192,51 });
		Collision5->SetCollisionPos(Button->GetRenderPos());
		Collision5->Off();;
	}

	Off();
}

void LevelUpUI::Update(float _Delta)
{
	if (true == Collision1->CollisonCheck(Mouse::UI->GetMouseCol(), CollisionType::Rect, CollisionType::Rect) && Collision1->IsUpdate())
	{
		if (GameEngineInput::IsDown(VK_LBUTTON))
		{
			SelectBox1->OnClick();
			GameEngineTime::MainTimer.SetAllTimeScale(1);
			PlayLevel::ChangeSpawnState();
			Off();
		}
	}
	//1�� ��ư ��������
	else if (true == Collision2->CollisonCheck(Mouse::UI->GetMouseCol(), CollisionType::Rect, CollisionType::Rect) && Collision2->IsUpdate())
	{
		if (GameEngineInput::IsDown(VK_LBUTTON))
		{
			SelectBox2->OnClick();
			GameEngineTime::MainTimer.SetAllTimeScale(1);
			PlayLevel::ChangeSpawnState();
			Off();
		}
	}
	//2�� ��ư ��������
	else if (true == Collision3->CollisonCheck(Mouse::UI->GetMouseCol(), CollisionType::Rect, CollisionType::Rect) && Collision3->IsUpdate())
	{
		if (GameEngineInput::IsDown(VK_LBUTTON))
		{
			SelectBox3->OnClick();
			GameEngineTime::MainTimer.SetAllTimeScale(1);
			PlayLevel::ChangeSpawnState();
			Off();
		}
	}

	if (true == Collision4->CollisonCheck(Mouse::UI->GetMouseCol(), CollisionType::Rect, CollisionType::Rect) && Collision4->IsUpdate())
	{
		if (GameEngineInput::IsDown(VK_LBUTTON))
		{
			Collision4->Off();
			Collision5->On();
			Collision5->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos() + Button->GetRenderPos());
			
			Box->ChangeAnimation("box_openup");

			Text_Button->SetText("�ݱ�", 40, "�����ý��丮");

			int gold = GameEngineRandom::MainRandom.RandomInt(100, 300);
			PlayerUI::UI->AddGold(gold);

			std::stringstream text;
			text << gold;
			Text_FoundBox->SetText(text.str(), 40, "�����ý��丮");
			Text_FoundBox->SetRenderPos(Text_FoundBox->GetRenderPos() + float4(30, 0));
			GoldMark->SetRenderPos(Text_FoundBox->GetRenderPos() + float4(80, 20));
			GoldMark->On();

			WeaponType Type = GetRandomTypeBox();
			switch (Type)
			{
			case WeaponType::Knife:
				ItemSelectPanel->SetSprite("LevelUpPanel.bmp", 0);
				StatusUI::UI->UpdateWeapon(WeaponType::Knife);
				break;
			case WeaponType::MagicWand:
				ItemSelectPanel->SetSprite("LevelUpPanel.bmp", 1);
				StatusUI::UI->UpdateWeapon(WeaponType::MagicWand);
				break;
			case WeaponType::Axe:
				ItemSelectPanel->SetSprite("LevelUpPanel.bmp", 2);
				StatusUI::UI->UpdateWeapon(WeaponType::Axe);
				break;
			case WeaponType::Runetracer:
				ItemSelectPanel->SetSprite("LevelUpPanel.bmp", 3);
				StatusUI::UI->UpdateWeapon(WeaponType::Runetracer);
				break;
			case WeaponType::FireWand:
				ItemSelectPanel->SetSprite("LevelUpPanel.bmp", 4);
				StatusUI::UI->UpdateWeapon(WeaponType::FireWand);
				break;
			case WeaponType::Cross:
				ItemSelectPanel->SetSprite("LevelUpPanel.bmp", 5);
				StatusUI::UI->UpdateWeapon(WeaponType::Cross);
				break;
			case WeaponType::Whip:
				ItemSelectPanel->SetSprite("LevelUpPanel.bmp", 6);
				StatusUI::UI->UpdateWeapon(WeaponType::Whip);
				break;
			case WeaponType::Null:
				GameEngineTime::MainTimer.SetAllTimeScale(1);
				Off();
				break;
			default:
				break;
			}
		}
	}
	else if (true == Collision5->CollisonCheck(Mouse::UI->GetMouseCol(), CollisionType::Rect, CollisionType::Rect) && Collision5->IsUpdate())
	{
		if (GameEngineInput::IsDown(VK_LBUTTON))
		{
			GameEngineTime::MainTimer.SetAllTimeScale(1);
			Off();
		}
	}
	//3�� ��ư ��������

}

void LevelUpUI::ButtonSetting()
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

	TempWeaponGroup.clear();
	TempPassiveGroup.clear();
}

void LevelUpUI::RandomTypeSetting()
{
	TempWeaponGroup = { WeaponType::Knife,WeaponType::MagicWand ,WeaponType::Axe ,WeaponType::Runetracer ,
		WeaponType::FireWand,WeaponType::Cross ,WeaponType::Whip };

	if (true == StatusUI::UI->IsAllMaxWeapon())
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

void LevelUpUI::RandomTypeSetting2()
{
	TempPassiveGroup = { PassiveType::Blackheart, PassiveType::Redheart, PassiveType::Book,
		PassiveType::Glove, PassiveType::Candle, PassiveType::Expball, PassiveType::Crown, PassiveType::Spinach,
		PassiveType::Wing, PassiveType::Clover };

	if (true == StatusUI::UI->IsAllMaxPassvie())
	{
		return;
	}
	else if (false == StatusUI::UI->IsFullPassvie())
	{
		RandomType[0].second = GetRandomType3();
		RandomType[1].second = GetRandomType3();
		RandomType[2].second = GetRandomType3();
	}
	else if (true == StatusUI::UI->IsFullPassvie())
	{
		RandomType[0].second = GetRandomType4();
		RandomType[1].second = GetRandomType4();
		RandomType[2].second = GetRandomType4();
	}
}

WeaponType LevelUpUI::GetRandomType()
{
	if (TempWeaponGroup.size() < 1)
	{
		return WeaponType::Null;
	}

	WeaponType type = getRandomElement(TempWeaponGroup, 0, static_cast<int>(TempWeaponGroup.size() - 1));

	if (WeaponStats::AllStats[type].isBoxed == true)
	{
		remove(TempWeaponGroup, type);
		type = GetRandomType();
	}

	WeaponStats::AllStats[type].isBoxed = true;

	return type;
}

WeaponType LevelUpUI::GetRandomType2()
{
	if (TempWeaponGroup.size() < 1)
	{
		return WeaponType::Null;
	}

	WeaponType type = getRandomElement(TempWeaponGroup, 0, static_cast<int>(TempWeaponGroup.size() - 1));

	if (WeaponStats::AllStats[type].isBoxed == true || false == WeaponStats::AllStats[type].isSelected || true == WeaponStats::AllStats[type].isMaxLevel)
	{
		remove(TempWeaponGroup, type);
		type = GetRandomType2();
	}

	WeaponStats::AllStats[type].isBoxed = true;

	return type;
}
PassiveType LevelUpUI::GetRandomType3()
{
	if (TempPassiveGroup.size() < 1)
	{
		return PassiveType::Null;
	}

	PassiveType type = getRandomElement2(TempPassiveGroup, 0, static_cast<int>(TempPassiveGroup.size() - 1));

	if (PassiveStats::AllPassive[type].isBoxed == true)
	{
		remove2(TempPassiveGroup, type);
		type = GetRandomType3();
	}

	PassiveStats::AllPassive[type].isBoxed = true;

	return type;
}
PassiveType LevelUpUI::GetRandomType4()
{
	if (TempPassiveGroup.size() < 1)
	{
		return PassiveType::Null;
	}

	PassiveType type = getRandomElement2(TempPassiveGroup, 0, static_cast<int>(TempPassiveGroup.size() - 1));

	if (PassiveStats::AllPassive[type].isBoxed == true || false == PassiveStats::AllPassive[type].isSelected || true == PassiveStats::AllPassive[type].isMaxLevel)
	{
		remove2(TempPassiveGroup, type);
		type = GetRandomType4();
	}

	PassiveStats::AllPassive[type].isBoxed = true;

	return type;
}

WeaponType LevelUpUI::GetRandomTypeBox()
{
	if (true == StatusUI::UI->IsAllMaxWeapon())
	{
		return WeaponType::Null;
	}

	std::vector<WeaponType> temp = { WeaponType::Knife,WeaponType::MagicWand ,WeaponType::Axe ,WeaponType::Runetracer ,
		WeaponType::FireWand,WeaponType::Cross ,WeaponType::Whip };

	if (temp.size() < 1)
	{
		return WeaponType::Null;
	}

	WeaponType type = getRandomElement(temp, 0, static_cast<int>(temp.size() - 1));

	if (false == WeaponStats::AllStats[type].isSelected || true == WeaponStats::AllStats[type].isMaxLevel)
	{
		remove(temp, type);
		type = GetRandomTypeBox();
	}

	temp.clear();

	return type;
}