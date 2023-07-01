#include "PlayerUI.h"
#include "Player.h"
#include "Enemy.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <sstream>


PlayerUI* PlayerUI::UI = nullptr;

PlayerUI::PlayerUI()
{
	UI = this;
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::AddGold(int _Gold)
{
	Gold += _Gold;

	std::stringstream Goldstr;
	Goldstr << Gold;

	Text_Gold->SetText(Goldstr.str(), 20, "메이플스토리");
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
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("DeathMark.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("CoinMark.bmp"));
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

		DeathMark = CreateUIRenderer(RenderOrder::PlayUI);
		DeathMark->SetTexture("DeathMark.bmp");
		DeathMark->SetRenderPos({ 930,35 });

		CoinMark = CreateUIRenderer(RenderOrder::PlayUI);
		CoinMark->SetTexture("CoinMark.bmp");
		CoinMark->SetRenderPos({ 1076,37 });

		ExpBar = CreateUIRenderer(RenderOrder::PlayUI);
		ExpBar->SetTexture("ExpBar.bmp");
		ExpBar->SetRenderPos({ 545,12 });

		ExpGauge = CreateUIRenderer(RenderOrder::PlayUI);
		ExpGauge->SetTexture("ExpGauge.bmp");
		ExpGauge->SetRenderPos({ 545,12 });
		ExpGauge->SetRenderScale({ 0,16 });

		ExpGuageScale = ResourcesManager::GetInst().FindTexture("ExpGauge.bmp")->GetScale();
	}
	
}

void PlayerUI::Update(float _Delta)
{
	static bool isExecuted1 = false;
	static bool isExecuted2 = false;
	static bool isExecuted3 = false;
	static bool isExecuted4 = false;

	if (isExecuted1 == false && Enemy::DeathCount >= 10)
	{
		Text_MonsterDeathCount->SetRenderPos({ 895,24 });
		isExecuted1 = true;
	}
	if (isExecuted2 == false && Enemy::DeathCount >= 100)
	{
		Text_MonsterDeathCount->SetRenderPos({ 885,24 });
		isExecuted2 = true;
	}
	if (isExecuted3 == false && Enemy::DeathCount >= 1000)
	{
		Text_MonsterDeathCount->SetRenderPos({ 875,24 });
		isExecuted3 = true;
	}
	if (isExecuted4 == false && Enemy::DeathCount >= 10000)
	{
		Text_MonsterDeathCount->SetRenderPos({ 865,24 });
		isExecuted4 = true;
	}
}

