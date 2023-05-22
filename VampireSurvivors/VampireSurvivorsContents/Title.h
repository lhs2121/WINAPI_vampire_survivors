#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class Title : public GameEngineLevel
{
public:
	// constrcuter destructer
	Title();
	~Title();

	// delete Function
	Title(const Title& _Other) = delete;
	Title(Title&& _Other) noexcept = delete;
	Title& operator=(const Title& _Other) = delete;
	Title& operator=(Title&& _Other) noexcept = delete;

protected:
	void Update(float _DeltaTime) override;

private:

};

