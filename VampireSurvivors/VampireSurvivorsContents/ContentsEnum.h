#pragma once

enum class UpdateOrder
{
	Player,
	Monster,
};

enum class RenderOrder
{
	BackGround,
	UnderMonster,
	Player,
	Weapon,
	UpperMonster,
	PlayUI,
};

// ������Ŀ 
enum class CollisionOrder
{
	Map,
	Potal,
	PlayerBody,
	MonsterBody,
};