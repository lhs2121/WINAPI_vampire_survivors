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

	void SetType(WeaponType _Type);
private:
	class GameEngineRenderer* Renderer;
	class GameEngineCollision* Collision;

	bool IsReady = false;

	float XRangeRatio;
	float UpSpeed = 500;
	float XSpeed = 100;
	float YSpeed = 200;
	float Angle;
	float Speed = 200;

	float4 dir;
	float4 Scale;
	WeaponType Type;

	int HitCount = 0;
	float DeathTime = 3;
	float SumDeltaTime = 0;

	void Knife_Attack(float _Delta);
	void MagicWand_Attack(float _Delta);
	void Axe_Attack(float _Delta);
	void Runetracer_Attack(float _Delta);

	void Start() override;
	void Update(float _Delta) override;


};

