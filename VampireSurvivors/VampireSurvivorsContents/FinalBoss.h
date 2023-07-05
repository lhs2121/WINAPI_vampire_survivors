#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class FinalBoss : public GameEngineActor
{
public:
	// constrcuter destructer
	FinalBoss() {}
	~FinalBoss() {}

	// delete Function
	FinalBoss(const FinalBoss& _Other) = delete;
	FinalBoss(FinalBoss&& _Other) noexcept = delete;
	FinalBoss& operator=(const FinalBoss& _Other) = delete;
	FinalBoss& operator=(FinalBoss&& _Other) noexcept = delete;


private:

	class GameEngineRenderer* Renderer;
	class GameEngineCollision* Collision;

	float hp = 10;
	float4 dir;
	int value;

	void Start();
	void Update(float _Delta);
};

