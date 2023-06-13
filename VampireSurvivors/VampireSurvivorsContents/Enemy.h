#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>
// Ό³Έν :
class Enemy : public GameEngineActor
{
public:

	static std::vector<GameEngineCollision*> AllMonsterCollision;

	// constrcuter destructer
	Enemy();
	~Enemy();

	// delete Function
	Enemy(const Enemy& _Other) = delete;
	Enemy(Enemy&& _Other) noexcept = delete;
	Enemy& operator=(const Enemy& _Other) = delete;
	Enemy& operator=(Enemy&& _Other) noexcept = delete;


protected:

private:
	class GameEngineRenderer* Renderer;
	class GameEngineCollision* Collision;

	float speed;

	void Start() override;
	void Update(float _Delta) override;
};

