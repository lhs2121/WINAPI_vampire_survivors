#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "PlayActor.h"

enum class EnemyType
{
	enemy1,
	enemy2,
	enemy3,

};

class Enemy : public PlayActor
{
public:
	static EnemyType CurSpawnEnemyType;
	
	static int DeathCount;
	// constrcuter destructer
	Enemy();
	~Enemy();
	 
	// delete Function
	Enemy(const Enemy& _Other) = delete;
	Enemy(Enemy&& _Other) noexcept = delete;
	Enemy& operator=(const Enemy& _Other) = delete;
	Enemy& operator=(Enemy&& _Other) noexcept = delete;

	void ApplyDamage(float _Damage)
	{
		hp -= _Damage;
	}

private:
	EnemyType type;
	class GameEngineRenderer* Renderer;
	class GameEngineCollision* Collision;
	class GameEngineRenderer* Damage;

	float hp = 20;
	int ItemdropRate = 80;
	float speed;
	float4 dir;

	float Yspeed = 100;
	float increasement = 1;
	const float maxspeed = 100.0f;
	const float minspeed = -100.0f;


	bool move = true;
	bool collisioncheck = true;
	int value = 0;

	void Start() override;
	void Update(float _Delta) override;

	void Move(float _Delta);
	void Move2(float _Delta);
	void CollisionCheck(float _Delta);
	void DropExp();
	void WallCheck();

};

