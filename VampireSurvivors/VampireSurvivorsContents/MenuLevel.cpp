#include "MenuLevel.h"
#include "TitleBackGround.h"
#include "Button.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineWindow.h>

MenuLevel::MenuLevel()
{

}

MenuLevel::~MenuLevel()
{

}


void MenuLevel::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("introBG.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\BackGround\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("introBG.bmp"));

	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("start.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\BackGround\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("start.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("collection.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\BackGround\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("collection.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("upgrade.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\BackGround\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("upgrade.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("makers.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\BackGround\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("makers.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("unlock.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\BackGround\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("unlock.bmp"));
	}

	CreateActor<TitleBackGround>(0);

	{
		StartButton = CreateActor<Button>(1);
		StartButton->Init("start.bmp", { 0 ,100 }, 1.7f);

		CollectionButton = CreateActor<Button>(1);
		CollectionButton->Init("collection.bmp", { -200,215 }, 1.7f);

		UpgradeButton = CreateActor<Button>(1);
		UpgradeButton->Init("upgrade.bmp", { 0,215 }, 1.7f);

		UnlockButton = CreateActor<Button>(1);
		UnlockButton->Init("unlock.bmp", { 200,215 }, 1.7f);

		MakersButton = CreateActor<Button>(1);
		MakersButton->Init("makers.bmp", { 0,300 });

		
	}
}

void MenuLevel::Update(float _Delta)
{

}

