#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include<vector>

class WeaponStats
{

private:

	int level = 0;
	int Count = 0;
	float speed = 100;
	float damage = 50;
	float deathTime = 5;
	float coolTime = 5;
	float interval = 0.15f;
	float4 scale = { 0,0 };


public:

	static std::vector<WeaponStats> ALLSTATES;

	int getLevel() const { return level; }
	void setLevel(float value) { level = value; }

	int getCount() const { return Count; }
	void setCount(float value) { Count = value; }

	float getDamage() const { return damage; }
	void setDamage(float value) { damage = value; }

	float getSpeed() const { return speed; }
	void setSpeed(float value) { speed = value; }

	float getDeathTime() const { return deathTime; }
	void setDeathTime(float value) { deathTime = value; }

	float getCoolTime() const { return coolTime; }
	void setCoolTime(float value) { coolTime = value; }

	float getInterval() const { return interval; }
	void setInterval(float value) { interval = value; }

	float4 getScale() const { return scale; }
	void setScale(float4 value) { scale = value; }

	void addLevel(int value) { level += value; }
	void addCount(int value) { Count += value; }
	void addSpeed(float value) { speed += value; }
	void addDamage(float value) { damage += value; }
	void addDeathTime(float value) { deathTime += value; }
	void addCoolTime(float value) { coolTime += value; }
	void addInterval(float value) { interval += value; }
	void addScale(float4 value) { scale += value; }


};