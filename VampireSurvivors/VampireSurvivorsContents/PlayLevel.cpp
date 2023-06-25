#include "PlayLevel.h"
#include "BackGround.h"
#include "Player.h"
#include "Enemy.h"
#include "Exp.h"
#include "PlayerUI.h"
#include "PlayerShooter.h"
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
		GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(-0.01f);
	}
	if (GameEngineInput::IsPress('P'))
	{
		GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(0.01f);
	}
	if (GameEngineInput::IsDown('Y'))
	{
		SpawnCheck = !SpawnCheck;
	}

	BackGroundPtr->BackGroundLoop(PlayerPtr);

	if (SpawnCheck == true)
	{
		EnemySpawn(_delta);
	}
	
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineSound::SoundPlay("bgm_elrond_library.ogg");
	//GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(0.5f);

	{
		int num;
		num = GameEngineRandom::MainRandom.RandomInt(9, 15);

		Enemy* prevEnemy = nullptr;

		for (int i = 0; i < num; i++)
		{
			Enemy* NewEnemy = CreateActor<Enemy>(UpdateOrder::Monster);

			NewEnemy->SetPos({ float4(PlayerPtr->GetPos().X , 0) + float4(500,-200) });

			if (prevEnemy != nullptr)
			{
				NewEnemy->SetPos(prevEnemy->GetPos() + float4(0, 35));
			}

			prevEnemy = NewEnemy;
		}
	}
	//처음 오른쪽 몬스터 스폰
	{
		int num;
		num = GameEngineRandom::MainRandom.RandomInt(9, 15);

		Enemy* prevEnemy = nullptr;

		for (int i = 0; i < num; i++)
		{
			Enemy* NewEnemy = CreateActor<Enemy>(UpdateOrder::Monster);

			NewEnemy->SetPos({ float4(PlayerPtr->GetPos().X , 0) + float4(-500,-200) });

			if (prevEnemy != nullptr)
			{
				NewEnemy->SetPos(prevEnemy->GetPos() + float4(0, 35));
			}

			prevEnemy = NewEnemy;
		}
	}
	//처음 왼쪽 몬스터 스폰
}
void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}
void PlayLevel::EnemySpawn(float _Delta)
{
	static float sumDelta;
	sumDelta += _Delta;
	if (sumDelta > 6)
	{
		{
			int num;
			num = GameEngineRandom::MainRandom.RandomInt(5, 12);

			Enemy* prevEnemy = nullptr;

			for (int i = 0; i < num; i++)
			{
				Enemy* NewEnemy = CreateActor<Enemy>(UpdateOrder::Monster);

				NewEnemy->SetPos({ float4(PlayerPtr->GetPos().X , 0) + float4(500,-200) });

				if (prevEnemy != nullptr)
				{
					NewEnemy->SetPos(prevEnemy->GetPos() + float4(0, 35));
				}

				prevEnemy = NewEnemy;
			}
		}
		{
			int num;
			num = GameEngineRandom::MainRandom.RandomInt(5, 12);

			Enemy* prevEnemy = nullptr;

			for (int i = 0; i < num; i++)
			{
				Enemy* NewEnemy = CreateActor<Enemy>(UpdateOrder::Monster);

				NewEnemy->SetPos({ float4(PlayerPtr->GetPos().X , 0) + float4(-500,-200) });

				if (prevEnemy != nullptr)
				{
					NewEnemy->SetPos(prevEnemy->GetPos() + float4(0, 35));
				}

				prevEnemy = NewEnemy;
			}
		}

		sumDelta = 0;
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


	SpawnCheck = false;

	ItemSelectUIPtr->On();
}
