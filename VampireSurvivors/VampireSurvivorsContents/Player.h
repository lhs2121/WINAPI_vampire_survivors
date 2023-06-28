#pragma once
#include <VampireSurvivorsContents/PlayActor.h>
#include "WeaponStats.h"
#include "ContentsEnum.h"
enum class DirState
{
	Left,
	Right
};

class GameEngineRenderer;
class Player : public PlayActor
{
public:

	static Player* GetMainPlayer()
	{
		return MainPlayer;
	}

	GameEngineCollision* GetCollsion()
	{
		return Collision;
	}

	GameEngineCollision* GetCollsion2()
	{
		return Collision2;
	}
	
	float4 GetPlayerDir()
	{
		return PlayerDir;
	}

	DirState GetPlayerDirState()
	{
		return dirstate;
	}

	float4 GetFirePos();

	float4 GetMinDistance();

	

	void ApplyDamage(float _Damage);

	void AddExp(float _Exp);

	Player();
	~Player();
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

private:
	static Player* MainPlayer;

	GameEngineRenderer* Renderer;

	GameEngineRenderer* HpBar;
	GameEngineRenderer* HpGauge;

	GameEngineCollision* Collision;
	GameEngineCollision* Collision2;
	GameEngineCollision* Detector;

	float4 FirePos[3];
	float4 PlayerDir;
	float4 HpGaugeScale;

	DirState dirstate = DirState::Right;

	float MaxHp = 100;
	float Hp = 100;
	float speed = 100;
	float Gold = 0;
	float MaxExp = 50;
	float Exp = 0;
	int Level = 1;


	void LevelUp();

	void WallCheck();
	void LevelStart() override;
	void Start() override;
	void Update(float _Delta) override;
};


