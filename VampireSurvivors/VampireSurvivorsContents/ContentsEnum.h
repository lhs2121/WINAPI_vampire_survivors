#pragma once

enum class UpdateOrder
{
	BackGround,
	Player,
	Monster,
	Weapon,
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

// ÇïÅ×ÀÌÄ¿ 
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