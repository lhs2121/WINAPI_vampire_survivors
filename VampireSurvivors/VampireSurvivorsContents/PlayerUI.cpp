#include "PlayerUI.h"
#include "Player.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

PlayerUI* PlayerUI::UI = nullptr;

PlayerUI::PlayerUI()
{
	UI = this;
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("ExpBar.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("UI\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ExpBar.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ExpGauge.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemSelectPanel.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("DeathMark.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("CoinMark.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("SlotPanel.bmp"));
	}

	{
		Text_Level = CreateUIRenderer(RenderOrder::Text);
		Text_Level->SetText("LV1", 20, "메이플스토리");
		Text_Level->SetRenderPos({ 1055,4 });

		Text_MonsterDeathCount = CreateUIRenderer(RenderOrder::Text);
		Text_MonsterDeathCount->SetText("0", 20, "메이플스토리");
		Text_MonsterDeathCount->SetRenderPos({ 900,24 });

		Text_Gold = CreateUIRenderer(RenderOrder::Text);
		Text_Gold->SetText("0", 20, "메이플스토리");
		Text_Gold->SetRenderPos({ 1045,24 });

		Text_Timer = CreateUIRenderer(RenderOrder::Text);
		Text_Timer->SetText("00 : 00", 30, "메이플스토리");
		Text_Timer->SetRenderPos({ 515,33 });
	}

	{
		DeathMark = CreateUIRenderer(RenderOrder::PlayUI);
		DeathMark->SetTexture("DeathMark.bmp");
		DeathMark->SetRenderPos({ 930,35 });

		
		CoinMark = CreateUIRenderer(RenderOrder::PlayUI);
		CoinMark->SetTexture("CoinMark.bmp");
		CoinMark->SetRenderPos({ 1076,37 });
		
	}
	{
		SlotPanel = CreateUIRenderer(RenderOrder::PlayUI);
		SlotPanel->SetTexture("SlotPanel.bmp");
		SlotPanel->SetRenderPos({ 100,58 });
	}
	{
		ExpBar = CreateUIRenderer(RenderOrder::PlayUI);
		ExpBar->SetTexture("ExpBar.bmp");
		ExpBar->SetRenderPos({ 545,12 });

		ExpGauge = CreateUIRenderer(RenderOrder::PlayUI);
		ExpGauge->SetTexture("ExpGauge.bmp");
		ExpGauge->SetRenderPos({ 545,12 });
		ExpGauge->SetRenderScale({ 0,16 });

		ExpGuageScale = ResourcesManager::GetInst().FindTexture("ExpGauge.bmp")->GetScale();
	}
	{
		
		ItemSelectPanel = CreateUIRenderer(RenderOrder::PlayUI);
		ItemSelectPanel->SetTexture("ItemSelectPanel.bmp");
		ItemSelectPanel->SetRenderPos({ 545,345 });

		ItemPanel = CreateUIRenderer(RenderOrder::PlayUI);
		ItemPanel->SetTexture("ItemPanel.bmp");
		ItemPanel->SetRenderPos({ 545,345 });

		ItemSelectPanel->Off();
		ItemPanel->Off();
	}
	
}

void PlayerUI::Update(float _Delta)
{

}

