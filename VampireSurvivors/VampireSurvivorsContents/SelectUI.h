#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>
#include <map>

class GameEngineRenderer;
class SelectBox;
class GameEngineCollision;
enum class WeaponType;
enum class PassiveType;
class SelectUI : public GameEngineActor
{
public:
	static SelectUI* UI;

	void On() override;
	void Off() override;


	SelectUI(){UI = this;}
	~SelectUI(){}
	SelectUI(const SelectUI& _Other) = delete;
	SelectUI(SelectUI&& _Other) noexcept = delete;
	SelectUI& operator=(const SelectUI& _Other) = delete;
	SelectUI& operator=(SelectUI&& _Other) noexcept = delete;

private:

	std::map<WeaponType, PassiveType> RandomType;

	SelectBox* SelectBox1 = nullptr;
	SelectBox* SelectBox2 = nullptr;
	SelectBox* SelectBox3 = nullptr;
	SelectBox* SelectBox4 = nullptr;

	GameEngineRenderer* ItemSelectPanel = nullptr;
	GameEngineRenderer* Text_LevelUp = nullptr;

	GameEngineCollision* Collision1 = nullptr;
	GameEngineCollision* Collision2 = nullptr;
	GameEngineCollision* Collision3 = nullptr;
	GameEngineCollision* Mouse = nullptr;

	void ButtonSetting();
	void RandomTypeSetting();

	void Start() override;
	void Update(float _Delta) override;
};

