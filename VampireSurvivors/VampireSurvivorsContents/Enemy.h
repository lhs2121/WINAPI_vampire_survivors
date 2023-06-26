#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "PlayActor.h"
#include <vector>
// ���� :
class Enemy : public PlayActor
{
public:

	static std::vector<GameEngineCollision*> AllMonsterCollision;
	
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
		showDamageOnMonster(_Damage);
	}

protected:

private:
	class GameEngineRenderer* Renderer;
	class GameEngineCollision* Collision;
	class GameEngineRenderer* Damage;
	void showDamageOnMonster(float _Damage);

	float hp = 20;
	int ItemdropRate = 80;
	float speed;
	float4 dir;

	bool move = true;
	bool collisioncheck = true;
	int value = 0;

	void Start() override;
	void Update(float _Delta) override;

	void Move(float _Delta);
	void CollisionCheck(float _Delta);
	void DropExp();
	void WallCheck();

};

