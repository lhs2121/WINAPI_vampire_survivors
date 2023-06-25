#include "ItemButton.h"
#include "ContentsEnum.h"
#include "PlayerShooter.h"
#include "WeaponStats.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <sstream>

void ItemButton::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("ItemPanel_Knife.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("UI\\");
		path.MoveChild("ItemPanel\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Knife.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_MagicWand.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Axe.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Runetracer.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_FireWand.bmp"));
	}



	Panel = CreateUIRenderer(RenderOrder::PlayUI);
	NewText = CreateUIRenderer(RenderOrder::Text);
	WeaponNameText = CreateUIRenderer(RenderOrder::Text);
	DetailText = CreateUIRenderer(RenderOrder::Text);

	WeaponNameText->SetRenderPos({ -125,-50 });
	NewText->SetRenderPos({ 100,-50 });
	DetailText->SetRenderPos({ -185,0 });

	SetTexture();
}
void ItemButton::Update(float _Delta)
{

}
void ItemButton::SetTexture()
{
	int num = GameEngineRandom::MainRandom.RandomInt(0, 3);
	num = 0;
	
	CurType = static_cast<WeaponType>(num);
	Curlevel = WeaponStats::AllStats[CurType].getLevel();
	


	switch (CurType)
	{
	case WeaponType::Knife:
		Panel->SetTexture("ItemPanel_Knife.bmp");
		WeaponNameText->SetText("�ܰ�", 20, "�����ý��丮");
		switch (Curlevel)
		{
		case 0:
			DetailText->SetText("�ٶ󺸴� �������� �ܰ��� ��ô�մϴ�.", 20, "�����ý��丮");
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			break;
		case 1:
			DetailText->SetText("����ü�� 1�� �� �߻��մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:2", 20, "�����ý��丮");
			break;
		case 2:
			DetailText->SetText("����ü�� 1�� �� �߻��մϴ�. �⺻���ذ� 5 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:3", 20, "�����ý��丮");
			break;
		case 3:
			DetailText->SetText("����ü�� 1�� �� �߻��մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:4", 20, "�����ý��丮");
			break;
		case 4:
			DetailText->SetText("�ٶ󺸴� �������� �ܰ��� ��ô�մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:5", 20, "�����ý��丮");
			break;
		case 5:
			DetailText->SetText("�ٶ󺸴� �������� �ܰ��� ��ô�մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:6", 20, "�����ý��丮");
			break;
		case 6:
			DetailText->SetText("�ٶ󺸴� �������� �ܰ��� ��ô�մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:7", 20, "�����ý��丮");
			break;
		case 7:
			DetailText->SetText("�ٶ󺸴� �������� �ܰ��� ��ô�մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:8", 20, "�����ý��丮");
			break;
		default:
			break;
		}

		break;
	case WeaponType::MagicWand:
		Panel->SetTexture("ItemPanel_MagicWand.bmp");
		break;
	case WeaponType::Axe:
		Panel->SetTexture("ItemPanel_Axe.bmp");
		break;
	case WeaponType::Runetracer:
		Panel->SetTexture("ItemPanel_Runetracer.bmp");
		break;
	default:
		break;
	}
}

void ItemButton::Off()
{
	Panel->Off();
	NewText->Off();
	WeaponNameText->Off();
	DetailText->Off();
}
void ItemButton::On()
{
	Panel->On();
	NewText->On();
	WeaponNameText->On();
	DetailText->On();
}

void ItemButton::OnClick()
{
	WeaponStats::AllStats[CurType].addLevel(1);
}