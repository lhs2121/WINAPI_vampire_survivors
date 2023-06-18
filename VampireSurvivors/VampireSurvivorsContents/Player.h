#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Weapon;
class Player : public GameEngineActor
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

	GameEngineCollision* GetInnerCollsion()
	{
		return InnerCollision;
	}

	void GetDamage(float _Damage);

protected:

private:
	static Player* MainPlayer;
	
	class GameEngineRenderer* Renderer;

	class GameEngineRenderer* HpBackGround;
	class GameEngineRenderer* HpBar;

	class GameEngineCollision* Collision;
	class GameEngineCollision* InnerCollision;

	class Knife* KnifeActor;
	class Knife* KnifeActor2;
	
	float4 KnifePos1;
	float4 KnifePos2;

	float4 PlayerDir;

	float4 HpBarScale;

	float MaxHp = 100;
	float Hp = 100;
	float speed = 100;

	void (Player::*WeaponFunc[6])(float _Delta);

	bool OnKnifeFunc = false;
	void KnifeFunc(float _Delta);
	

	void LevelStart() override;
	void Start() override;
	void Update(float _Delta) override;
};

