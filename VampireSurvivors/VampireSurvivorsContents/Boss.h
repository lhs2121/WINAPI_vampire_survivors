#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class Boss : public GameEngineActor
{
public:
	// constrcuter destructer
	Boss(){}
	~Boss(){}

	// delete Function
	Boss(const Boss& _Other) = delete;
	Boss(Boss&& _Other) noexcept = delete;
	Boss& operator=(const Boss& _Other) = delete;
	Boss& operator=(Boss&& _Other) noexcept = delete;


private:

	class GameEngineRenderer* Renderer;
	class GameEngineCollision* Collision;

	float hp = 1000;
	float4 dir;
	float Damaged_Cooltime = 0.3f;
	int value;

	void Start();
	void Update(float _Delta);
};

