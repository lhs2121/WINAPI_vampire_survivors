#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "PlayActor.h"

enum class EnemyType
{
	enemy1,
	enemy2,
	enemy3,
	enemy4,
	Boss1
};

class Enemy : public PlayActor
{
public:
	static EnemyType CurSpawnEnemyType[2];
	static int DeathCount;

	static void ChangeEnemyType(EnemyType _type1, EnemyType _type2)
	{
		CurSpawnEnemyType[0] = _type1;
		CurSpawnEnemyType[0] = _type2;
	}
	void ApplyDamage(float _Damage)
	{
		hp -= _Damage;
	}

	Enemy() {};
	~Enemy() {};

	Enemy(const Enemy& _Other) = delete;
	Enemy(Enemy&& _Other) noexcept = delete;
	Enemy& operator=(const Enemy& _Other) = delete;
	Enemy& operator=(Enemy&& _Other) noexcept = delete;

private:
	int value = 0;
	int ItemdropRate = 80;

	bool move = true;
	bool collisioncheck = true;

	const float maxspeed = 100.0f;
	const float minspeed = -100.0f;

	float hp = 20;
	float speed;
	float Yspeed = 100;
	float increasement = 1;

	float4 dir;
	EnemyType type;

	class GameEngineRenderer* Renderer;
	class GameEngineCollision* Collision;
	class GameEngineRenderer* Damage;

	void Move(float _Delta);
	void Move2(float _Delta);
	void CollisionCheck(float _Delta);
	void DropExp();
	void WallCheck();

	void Start() override;
	void Update(float _Delta) override;
};

