#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"
class Projectile : public GameEngineActor
{

public:

	Projectile() {}
	~Projectile() {}

	Projectile(const Projectile& _Other) = delete;
	Projectile(Projectile&& _Other) noexcept = delete;
	Projectile& operator=(const Projectile& _Other) = delete;
	Projectile& operator=(Projectile&& _Other) noexcept = delete;

	void Setting(float4 _dir, float4 _startPos, float _Speed, const std::string& _AnimationName,WeaponType _Type);
private:
	class GameEngineRenderer* Renderer;
	class GameEngineCollision* Collision;

	float Speed = 200;
	float4 dir;
	float4 Angle;
	float4 Scale;
	WeaponType Type;

	float DeathTime = 3;
	float SumDeltaTime = 0;

	void Knife_Attack(float _Delta);
	void MagicWand_Attack(float _Delta);

	void Start() override;
	void Update(float _Delta) override;


};

