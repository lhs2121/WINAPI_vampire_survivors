#include "MenuLevel.h"
#include "imageUI.h"
#include "Button.h"
#include "SelectPanel.h"
#include "CharactorButton.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "imageUI.h"
MenuLevel::MenuLevel()
{

}

MenuLevel::~MenuLevel()
{

}


void MenuLevel::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("start.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\MenuScene\\");

		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("start.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("collection.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("upgrade.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("unlock.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("makers.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("SelectPanel.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("Zenaro.bmp"));
	}

	{
		BackGroundImg = CreateActor<imageUI>(0);
		BackGroundImg->Init("introBG.bmp");

		StartButton = CreateActor<Button>(1);
		StartButton->Init("start.bmp", { 0 ,100 }, 1);

		CollectionButton = CreateActor<Button>(1);
		CollectionButton->Init("collection.bmp", { -180,215 }, 1);

		UpgradeButton = CreateActor<Button>(1);
		UpgradeButton->Init("upgrade.bmp", { 0,215 }, 1);

		UnlockButton = CreateActor<Button>(1);
		UnlockButton->Init("unlock.bmp", { 180,215 }, 1);

		MakersButton = CreateActor<Button>(1);
		MakersButton->Init("makers.bmp", { 0,300 }, 1);
	}

	{
		SPanel = CreateActor<SelectPanel>(2);
		SPanel->Init("SelectPanel.bmp", { 0,40 }, 2);
		

		ZenaroButton = CreateActor<CharactorButton>(1);
		ZenaroButton->Init("Zenaro.bmp", { -100,-100 }, 3);
	}

	
	StartButton->SetPanel(SPanel);
	SPanel->SetButton(ZenaroButton);
	SPanel->Off();
}

void MenuLevel::Update(float _Delta)
{

}

