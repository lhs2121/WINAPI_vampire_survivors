#include "PlayLevel.h"
#include "BackGround.h"
#include "Player.h"
#include "Enemy.h"
#include "Exp.h"
#include "PlayerUI.h"
#include "PlayerShooter.h"
#include "Timer.h"
#include "ContentsEnum.h"
#include "ItemSelectUI.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineBase/GameEngineRandom.h>

bool PlayLevel::SpawnCheck = true;

PlayLevel::PlayLevel()
{
	ExpGroup.reserve(500);
}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::Start()
{
	GameEngineSound::SetGlobalVolume(0.1f);

	if (nullptr == GameEngineSound::FindSound("bgm_elrond_library.ogg"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\Sound\\");

		GameEngineSound::SoundLoad(path.PlusFilePath("bgm_elrond_library.ogg"));

	}

	BackGroundPtr = CreateActor<BackGround>(UpdateOrder::BackGround);

	BackGroundPtr->Init("dummy1.bmp", "Debugdummy1.bmp");

	PlayerPtr = CreateActor<Player>(UpdateOrder::Player);

	CreateActor<PlayerUI>(UpdateOrder::PlayUI);

	CreateActor<PlayerShooter>(UpdateOrder::Player);

	ItemSelectUIPtr = CreateActor<ItemSelectUI>(UpdateOrder::PlayUI);

	CreateActor<Timer>(UpdateOrder::Timer);

}



void PlayLevel::Update(float _delta)
{
	if (GameEngineInput::IsDown('C'))
	{
		CollisionDebugRenderSwitch();
	}

	if (GameEngineInput::IsDown('X'))
	{
		BackGroundPtr->SwitchRender();
	}

	if (GameEngineInput::IsPress('O'))
	{
		GameEngineWindow::MainWindow.SetDoubleBufferingCopyScaleRatio(1);
	}

	if (GameEngineInput::IsPress('P'))
	{
		GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(0.001f);
	}


	BackGroundPtr->BackGroundLoop();

	if (SpawnCheck == true)
	{
		EnemySpawn(_delta);
	}

}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineSound::SoundPlay("bgm_elrond_library.ogg");
}
void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}
void PlayLevel::EnemySpawn(float _Delta)
{
	static float Cooltime = 0;
	Cooltime -= _Delta;

	if (Cooltime < 0)
	{
		int num;
		num = GameEngineRandom::MainRandom.RandomInt(5, 12);

		Enemy* PrevEnemy = nullptr;
		Enemy* PrevEnemy2 = nullptr;

		for (int i = 0; i < num; i++)
		{
			Enemy* NewEnemy = CreateActor<Enemy>(UpdateOrder::Monster);
			Enemy* NewEnemy2 = CreateActor<Enemy>(UpdateOrder::Monster);

			NewEnemy->SetPos({ float4(PlayerPtr->GetPos().X , 0) + float4(560,300) });
			NewEnemy2->SetPos({ float4(PlayerPtr->GetPos().X , 0) + float4(-560,300) });

			if (PrevEnemy != nullptr)
			{
				NewEnemy->SetPos(PrevEnemy->GetPos() + float4(0, 50));
				NewEnemy2->SetPos(PrevEnemy2->GetPos() + float4(0, 50));
			}

			PrevEnemy = NewEnemy;
			PrevEnemy2 = NewEnemy2;
		}

		Cooltime = 6;
	}
}

void PlayLevel::AddExp(float4 _Pos)
{
	Exp* NewExp = CreateActor<Exp>(UpdateOrder::Monster);
	NewExp->SetPos(_Pos);
	ExpGroup.push_back(NewExp);
}

void PlayLevel::ShowItemSelectUI()
{
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Monster, 0);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 0);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Item, 0);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Weapon, 0);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Timer, 0);

	SpawnCheck = false;

	ItemSelectUIPtr->On();
}
