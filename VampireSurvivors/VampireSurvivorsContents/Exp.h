#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Exp : public GameEngineActor
{
public:

	Exp() {}
	~Exp() {}


	Exp(const Exp& _Other) = delete;
	Exp(Exp&& _Other) noexcept = delete;
	Exp& operator=(const Exp& _Other) = delete;
	Exp& operator=(Exp&& _Other) noexcept = delete;

	void SetCollisionScale(float4 _Scale);

protected:

private:
	class GameEngineRenderer* Renderer;
	class GameEngineCollision* Collision;

	bool isItemTaken = false;
	float sumdelta = 0;

	float OutWardSpeed = 250;
	float InWardSpeed = 0;

	float ExpValue = 21;

	float4 CollisionScale = {50,50};

	void Start() override;
	void Update(float _Delta) override;
};

