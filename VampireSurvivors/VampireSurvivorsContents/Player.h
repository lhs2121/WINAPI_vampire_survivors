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

	void GetDamage(float _Damage);

protected:

private:
	static Player* MainPlayer;
	
	class GameEngineRenderer* Renderer;

	class GameEngineRenderer* HpBackGround;
	class GameEngineRenderer* HpBar;

	class GameEngineCollision* Collision;
	class GameEngineCollision* Collision2;



	class Knife* KnifeActor[4];
	
	float4 KnifePos1;
	float4 KnifePos2;

	float4 PlayerDir;

	float4 HpBarScale;

	float MaxHp = 100;
	float Hp = 100;
	float speed = 1000;

	void (Player::*WeaponFunc[6])(float _Delta);

	bool OnKnifeFunc = false;
	void KnifeFunc(float _Delta);
	void CollisionWall(float _Delta);

	void LevelStart() override;
	void Start() override;
	void Update(float _Delta) override;
};

