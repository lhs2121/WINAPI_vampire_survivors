#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Item : public GameEngineActor
{
public:

	Item() {}
	~Item() {}

	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;


protected:
	virtual void ItemEffect();
	void Move(float _Delta);
	void Eat();
	void Update(float _Delta) override;
	class GameEngineRenderer* Renderer;
	class GameEngineCollision* Collision;
	float4 dir;
   
private:
	bool isItemTaken = false;
	float sumdelta = 0;

	float OutWardSpeed = 250;
	float InWardSpeed = 0;
};

