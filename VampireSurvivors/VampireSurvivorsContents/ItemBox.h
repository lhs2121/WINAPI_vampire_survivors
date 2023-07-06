#pragma once
#include <GameEngineCore/GameEngineActor.h>

class ItemBox : public GameEngineActor
{
public:

	ItemBox() {}
	~ItemBox() {}

	ItemBox(const ItemBox& _Other) = delete;
	ItemBox(ItemBox&& _Other) noexcept = delete;
	ItemBox& operator=(const ItemBox& _Other) = delete;
	ItemBox& operator=(ItemBox&& _Other) noexcept = delete;


	

private:

	class GameEngineRenderer* Renderer;
	class GameEngineRenderer* Cursor;
	class GameEngineCollision* Collision;

	void Start() override;
	void Update(float _Delta) override;
};

