#include "PlayLevel.h"
#include "BackGround.h"
#include "Player.h"
#include "Enemy.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

PlayLevel::PlayLevel()
{

}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::Start()
{
	GameEngineSound::SetGlobalVolume(0.1f);

	if (false == ResourcesManager::GetInst().IsLoadTexture("dummy1.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");

		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Lenemy1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Renemy1.bmp"), 5, 1);
		
		path.MoveChild("BackGround\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("dummy1.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("Debugdummy1.bmp"));

	}
	if (nullptr == GameEngineSound::FindSound("bgm_elrond_library.ogg"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\Sound\\");

		GameEngineSound::SoundLoad(path.PlusFilePath("bgm_elrond_library.ogg"));

	}

	BackGroundPtr = CreateActor<BackGround>(0);

	BackGroundPtr->Init("dummy1.bmp", "Debugdummy1.bmp");

	PlayerPtr = CreateActor<Player>(1);

	{
		
		CreateActor<Enemy>(1);
		CreateActor<Enemy>(1)->SetPos({ 100,0 });
		CreateActor<Enemy>(1)->SetPos({ 50,50 });
		CreateActor<Enemy>(1)->SetPos({ -50,50 });
		CreateActor<Enemy>(1)->SetPos({ -50,-50 });
		CreateActor<Enemy>(1)->SetPos({ 50,-50 });
	}
}



void PlayLevel::Update(float _delta)
{
	if (GameEngineInput::IsDown('C'))
	{
		CollisionDebugRenderSwitch();
	}
	BackGroundPtr->BackGroundLoop(PlayerPtr);
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineSound::SoundPlay("bgm_elrond_library.ogg");
	GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(0.5f);
}
void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}



