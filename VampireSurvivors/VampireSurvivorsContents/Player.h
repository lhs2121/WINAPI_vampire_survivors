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
	friend class PassiveStats;
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
	
	void AddHP(float _HP);

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

	int Level = 1;
	float MaxHp = 150;
	float Hp = 150;
	float speed = 120;
	float Gold = 0;
	float MaxExp = 50;
	float Exp = 0;
	
	float Damaged_Cooltime = 1;
	void LevelUp();
	void WallCheck();

	void LevelStart() override;
	void Start() override;
	void Update(float _Delta) override;
};


