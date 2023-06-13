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



protected:

private:

	class GameEngineCollision* Collison;

	class GameEngineRenderer* Renderer;

	
	void Start() override;
	void Update(float _Delta) override;
};

