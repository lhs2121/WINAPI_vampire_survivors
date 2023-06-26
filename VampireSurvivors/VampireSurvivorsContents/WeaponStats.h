#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <vector>
#include <map>

enum class WeaponType;
class WeaponStats
{

private:

	int level;
	int count;
	float speed;
	float damage;
	float deathTime;
	float coolTime;
	float interval;
	float4 scale;
	bool isSelecting = false;


public:
	static std::map<WeaponType,WeaponStats> AllStats;

	static void AllStatsSetting();

	void setStats(int _level, int _Count, float _speed, float _damage, float _deathTime, 
	float _cooltime, float _interval, float4 _scale)
	{
		level = _level;
		count = _Count;
		speed = _speed;
		damage = _damage;
		deathTime = _deathTime;
		coolTime = _cooltime;
		interval = _interval;
		scale = _scale;
	}
	
	int getLevel() const { return level; }
	void setLevel(float value) { level = value; }

	int getCount() const { return count; }
	void setCount(float value) { count = value; }

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

	bool getIsSelecting() const { return isSelecting; }
	void setIsSelecting(bool _value) { isSelecting = _value; }

	void addLevel(int value) { level += value; }
	void addCount(int value) { count += value; }
	void addSpeed(float value) { speed += value; }
	void addDamage(float value) { damage += value; }
	void addDeathTime(float value) { deathTime += value; }
	void addCoolTime(float value) { coolTime += value; }
	void addInterval(float value) { interval += value; }
	void addScale(float4 value) { scale += value; }


};