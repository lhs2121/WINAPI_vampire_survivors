#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Knife : public GameEngineActor
{
	friend class Player;
public:
	
	Knife(){}
	~Knife(){}

	
	Knife(const Knife& _Other) = delete;
	Knife(Knife&& _Other) noexcept = delete;
	Knife& operator=(const Knife& _Other) = delete;
	Knife& operator=(Knife&& _Other) noexcept = delete;



protected:

private:
	class GameEngineRenderer* Renderer;
	class GameEngineCollision* Collision;

	float speed;

	void Start() override;


	void On() override;
	void Off() override;
};

