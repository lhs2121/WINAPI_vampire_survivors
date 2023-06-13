#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Player : public GameEngineActor
{
	friend class BackGround;
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

	class GameEngineCollision* Collision;
	class GameEngineCollision* InnerCollision;

	class GameEngineRenderer* Renderer;

	static Player* MainPlayer;

	float speed = 100;
	void LevelStart() override;
	void Start() override;
	void Update(float _Delta) override;
};

