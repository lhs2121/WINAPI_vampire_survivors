#pragma once
#include "Item.h"
class Exp : public Item
{
public:
	Exp() {}
	~Exp() {}

	Exp(const Exp& _Other) = delete;
	Exp(Exp&& _Other) noexcept = delete;
	Exp& operator=(const Exp& _Other) = delete;
	Exp& operator=(Exp&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update(float _Delta) override;
	void ItemEffect() override;
	void Eat() override;
};

