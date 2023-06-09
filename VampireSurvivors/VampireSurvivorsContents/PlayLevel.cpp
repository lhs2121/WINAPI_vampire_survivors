#include "PlayLevel.h"
#include "BackGround.h"
#include "Player.h"
#include "Enemy.h"
#include "Exp.h"
#include "PlayerUI.h"
#include "GameOverUI.h"
#include "PlayerShooter.h"
#include "Timer.h"
#include "ContentsEnum.h"
#include "LevelUpUI.h"
#include "StatusUI.h"
#include "CandleStick.h"
#include "DebugUI.h"
#include "PauseUI.h"
#include "Mouse.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineBase/GameEngineRandom.h>

bool PlayLevel::SpawnCheck = true;
CharacterType PlayLevel::CurCharacter;
int PlayLevel::MinSpawnNum = 3;
int PlayLevel::MaxSpawnNum = 5;
float PlayLevel::SpawnCooltime = 6;

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
		GameEngineSound::SoundLoad(path.PlusFilePath("sfx_projectile.ogg"));
		GameEngineSound::SoundLoad(path.PlusFilePath("sfx_projectile_magic.ogg"));
		GameEngineSound::SoundLoad(path.PlusFilePath("sfx_projectile_magic2.ogg"));
		GameEngineSound::SoundLoad(path.PlusFilePath("sfx_morph.ogg"));
		GameEngineSound::SoundLoad(path.PlusFilePath("sfx_enemyHit.ogg"));
		GameEngineSound::SoundLoad(path.PlusFilePath("sfx_gem.ogg"));
		GameEngineSound::SoundLoad(path.PlusFilePath("sfx_levelup.ogg"));
		GameEngineSound::SoundLoad(path.PlusFilePath("sfx_bumper3.ogg"));
		GameEngineSound::SoundLoad(path.PlusFilePath("sxf_loss.ogg"));
		GameEngineSound::SoundLoad(path.PlusFilePath("sfx_gameOver.ogg"));
		GameEngineSound::SoundLoad(path.PlusFilePath("sfx_treasure_found.ogg"));
		GameEngineSound::SoundLoad(path.PlusFilePath("sfx_sounds_pause7_out.ogg"));
		GameEngineSound::SoundLoad(path.PlusFilePath("sfx_sounds_pause7_in.ogg"));
	}


	CreateActor<Mouse>(UpdateOrder::PlayUI);

	CreateActor<StatusUI>(UpdateOrder::PlayUI);

	CreateActor<GameOverUI>(UpdateOrder::PlayUI);

	BackGroundPtr = CreateActor<BackGround>(UpdateOrder::BackGround);

	BackGroundPtr->Init("dummy1.bmp", "Debugdummy1.bmp");

	PlayerPtr = CreateActor<Player>(UpdateOrder::Player);

	CreateActor<PlayerUI>(UpdateOrder::PlayUI);

	CreateActor<PlayerShooter>(UpdateOrder::Player);

	LevelUpUIPtr = CreateActor<LevelUpUI>(UpdateOrder::PlayUI);

	CreateActor<Timer>(UpdateOrder::Timer);

	CreateActor<DebugUI>(UpdateOrder::PlayUI);

	PauseUIPtr = CreateActor<PauseUI>(UpdateOrder::PlayUI);


	ItemSpawnerSpawn();
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

	if (GameEngineInput::IsDown(VK_ESCAPE))
	{
		PauseUIPtr->On();
	}

	BackGroundPtr->BackGroundLoop();

	if (SpawnCheck == true)
	{
		EnemySpawn(_delta);
	}
}

void PlayLevel::StopBGM()
{
	PlayBGM.Stop();
}
void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayBGM = GameEngineSound::SoundPlay("bgm_elrond_library.ogg");

	if (CurCharacter == CharacterType::Zenaro)
	{
		StatusUI::UI->UpdateWeapon(WeaponType::Knife);
	}
	else if (CurCharacter == CharacterType::Imelda)
	{
		StatusUI::UI->UpdateWeapon(WeaponType::MagicWand);
	}
}
void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void PlayLevel::ItemSpawnerSpawn()
{
	for (int i = -5; i < 6; i++)
	{
		CreateActor<CandleStick>(UpdateOrder::Item)->SetPos(float4(524 * (float)i, 464) + float4(0, 200));
		CreateActor<CandleStick>(UpdateOrder::Item)->SetPos(float4(1024 * (float)i, 464) + float4(0, 200));
		CreateActor<CandleStick>(UpdateOrder::Item)->SetPos(float4(524 * (float)i, 464) + float4(0, -200));
		CreateActor<CandleStick>(UpdateOrder::Item)->SetPos(float4(1024 * (float)i, 464) + float4(0, -200));
	}
}
void PlayLevel::EnemySpawn(float _Delta)
{
	static float Cooltime = SpawnCooltime;
	Cooltime -= _Delta;

	if (Cooltime < 0)
	{
		int num;
		num = GameEngineRandom::MainRandom.RandomInt(MinSpawnNum, MaxSpawnNum);

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

		Cooltime = SpawnCooltime;
	}
}

void PlayLevel::AddExp(float4 _Pos)
{
	Exp* NewExp = CreateActor<Exp>(UpdateOrder::Monster);
	NewExp->SetPos(_Pos);
	ExpGroup.push_back(NewExp);
}

void PlayLevel::ShowLevelUpUI()
{
	SpawnCheck = false;
	LevelUpUIPtr->On();
}
