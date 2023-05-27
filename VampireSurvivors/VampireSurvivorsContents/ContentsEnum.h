#pragma once

enum class UpdateOrder
{
	Player,
	Monster,
};

enum class RenderOrder
{
	BackGround,
	Play,
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