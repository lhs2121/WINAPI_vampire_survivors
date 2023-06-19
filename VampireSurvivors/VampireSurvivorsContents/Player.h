#pragma once
#include <VampireSurvivorsContents/PlayActor.h>

class Weapon;
class Player : public PlayActor
{
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

	void GetDamage(float _Damage);

protected:

private:
	static Player* MainPlayer;
	
	class GameEngineRenderer* Renderer;

	class GameEngineRenderer* HpBar;
	class GameEngineRenderer* HpGauge;

	class GameEngineCollision* Collision;
	class GameEngineCollision* Collision2;
	class GameEngineCollision* Collision3;

	class Knife* KnifeActor[4];
	
	float4 KnifePos1;

	float4 KnifePos2;

	float4 PlayerDir;

	float4 HpGaugeScale;

	float MaxHp = 100;
	float Hp = 100;
	float speed = 100;

	bool OnKnifeFunc = false;

	void (Player::* WeaponFunc[6])(float _Delta);

	void KnifeFunc(float _Delta);

	void CollisionWall(float _Delta);

	void LevelStart() override;
	void Start() override;
	void Update(float _Delta) override;
};

