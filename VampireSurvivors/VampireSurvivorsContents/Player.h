#pragma once
#include <VampireSurvivorsContents/PlayActor.h>

class Weapon;
class GameEngineRenderer;
class Player : public PlayActor
{
	friend class PlayerUI;

public:

	Player();
	~Player();


	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

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

	GameEngineCollision* GetCollsion3()
	{
		return Collision3;
	}

	void ApplyDamage(float _Damage);
	void AddExp(float _Exp);

private:
	static Player* MainPlayer;

	GameEngineRenderer* Renderer;

	GameEngineRenderer* HpBar;
	GameEngineRenderer* HpGauge;

	GameEngineCollision* Collision;
	GameEngineCollision* Collision2;
	GameEngineCollision* Collision3;

	class Knife* KnifeActor[4];

	float4 KnifePos1;

	float4 KnifePos2;

	float4 PlayerDir;

	float4 HpGaugeScale;

	float MaxHp = 100;
	float Hp = 100;

	float speed = 100;

	float Gold = 0;

	float MaxExp = 50;
	float Exp = 0;

	int Level = 1;

	bool OnKnifeFunc = false;

	void (Player::* WeaponFunc[6])(float _Delta);

	void KnifeFunc(float _Delta);

	void CollisionWall(float _Delta);

	void LevelUp();

	void LevelStart() override;
	void Start() override;
	void Update(float _Delta) override;
};

