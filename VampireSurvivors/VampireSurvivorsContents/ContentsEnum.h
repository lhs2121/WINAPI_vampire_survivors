#pragma once

enum class UpdateOrder
{
	BackGround,
	Player,
	Weapon,
	Monster,
	
};

enum class RenderOrder
{
	BackGround,
	UnderMonster,
	Player,
	UpperMonster,
	Weapon,
	PlayUI,
};

// ������Ŀ 
enum class CollisionOrder
{
	BackGround,
	Player,
	Monster,
	Weapon,
};

enum class WeaponType
{
	Projectile,

};