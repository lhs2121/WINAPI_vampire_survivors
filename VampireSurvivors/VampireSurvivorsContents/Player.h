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
protected:

private:
	static Player* MainPlayer;
	
	class GameEngineRenderer* Renderer;

	class GameEngineCollision* Collision;
	class GameEngineCollision* InnerCollision;

	class Knife* KnifeActor;
	

	float speed = 100;

	void (Player::*WeaponFunc[6])(float _Delta);
	void KnifeFunc(float _Delta);
	

	void LevelStart() override;
	void Start() override;
	void Update(float _Delta) override;
};

