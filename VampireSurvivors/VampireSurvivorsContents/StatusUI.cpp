#include "StatusUI.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "WeaponStats.h"
#include <vector>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>


StatusUI* StatusUI::UI = nullptr;

void StatusUI::On()
{
	StatsPanel->On();
	TopAlpha->On();
	BottomAlpha->On();

	
	for (int i = 0; i < MyWeapon.size();  i++)
	{
		WeaponChecker[i]->On();
	}

}
void StatusUI::Off()
{
	StatsPanel->Off();
	TopAlpha->Off();
	BottomAlpha->Off();

	for (int i = 0; i < 6; i++)
	{
		WeaponChecker[i]->Off();
	}
	for (int i = 0; i < 6; i++)
	{
		AccessoryChecker[i]->Off();
	}
}
bool StatusUI::IsAllMax()
{
	int maxCount = 0;
	for (int i = 0; i < 6; i++)
	{
		if (WeaponStats::AllStats[MyWeapon[i]].isMaxLevel == true)
		{
			maxCount += 1;
		}
	}

	if (maxCount == 6)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool StatusUI::IsFullWeapon()
{
	if (MyWeapon.size() >= 6)
	{
		return true;
	}

	return false;
}


void StatusUI::Start()
{
	WeaponStats::AllStatsSetting();

	if (false == ResourcesManager::GetInst().IsLoadTexture("StatsPanel.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("UI\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("StatsPanel.bmp"));
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

	StatsPanel = CreateUIRenderer(RenderOrder::PlayUI);
	StatsPanel->SetTexture("StatsPanel.bmp");
	StatsPanel->SetRenderPos({ 110,300 });

	TopAlpha = CreateUIRenderer(RenderOrder::PlayUI);
	TopAlpha->SetTexture("TopAlpha.bmp");
	TopAlpha->SetAlpha(90);
	TopAlpha->SetRenderPos({ 110,95 });

	BottomAlpha = CreateUIRenderer(RenderOrder::PlayUI);
	BottomAlpha->SetTexture("BottomAlpha.bmp");
	BottomAlpha->SetAlpha(90);
	BottomAlpha->SetRenderPos({ 110,365 });

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
			WeaponChecker[i]->SetRenderPos(PrevPos + float4(30, 0));
		}

		WeaponChecker[i]->SetSprite("WeaponChecker.bmp", 0);
		WeaponChecker[i]->SetRenderScale({ 24,24 });

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

		PrevPos = AccessoryChecker[i]->GetRenderPos();
	}

	AddNewWeapon(WeaponType::Knife);

	Off();
}
void StatusUI::CreateWeaponSlotRenderer(WeaponType _Type)
{
	static float4 prevpos = float4::ZERO;

	GameEngineRenderer* renderer = CreateUIRenderer(RenderOrder::PlayUI);

	if (prevpos == float4::ZERO)
	{
		renderer->SetRenderPos({ 30,50 });
	}
	else
	{
		renderer->SetRenderPos(prevpos + float4(30, 0));
	}

	prevpos = renderer->GetRenderPos();

	renderer->SetRenderScale({ 24,24 });
	renderer->SetTexture(WeaponStats::AllStats[_Type].getSlotTextureName());


	WeaponStats::AllStats[_Type].setSlotNumber(WeaponIndex);
	WeaponIndex += 1;

}

void StatusUI::WeaponSlotUpgrade(WeaponType _Type)
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

void StatusUI::AddNewWeapon(WeaponType _Type)
{
	WeaponStats::AllStats[_Type].isSelected = true;
	MyWeapon.push_back(_Type);
	CreateWeaponSlotRenderer(_Type);
	WeaponSlotUpgrade(_Type);
}