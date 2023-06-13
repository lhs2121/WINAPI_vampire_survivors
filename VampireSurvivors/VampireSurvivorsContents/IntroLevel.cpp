#include "IntroLevel.h"
#include "IntroImage.h"
#include "PressAnyKey.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>

IntroLevel::IntroLevel()
{

}

IntroLevel::~IntroLevel()
{

}


void IntroLevel::Start()
{
	if (nullptr == GameEngineSound::FindSound("sfx_titleIntro.ogg"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("sfx_titleIntro.ogg"));

	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("introBG.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\MenuScene\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("introBG.bmp"));

	}

	CreateActor<IntroImage>(0);

	CreateActor<PressAnyKey>(1);

	
}

void IntroLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_RETURN))
	{
		GameEngineCore::ChangeLevel("MenuLevel");
	} 
}

void IntroLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineSound::SoundPlay("sfx_titleIntro.ogg");
}
