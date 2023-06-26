#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BackGround : public GameEngineActor
{
public:
	
	BackGround();
	~BackGround();

	
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	void Init(const std::string& _FileName, const std::string& _DebugFileName);
	void SwitchRender();
	void BackGroundLoop();
protected:

private:

	bool SwitchRenderValue = true;

	class GameEngineRenderer* Renderer;
	class GameEngineRenderer* DebugRenderer;
	class GameEngineRenderer* LeftRenderer;
	class GameEngineRenderer* RightRenderer;

	float4 Scale;
	float4 OffSetX;
	float4 OffSetY;

	GameEngineCollision* LeftWall;
	GameEngineCollision* RightWall;

	void MoveRendererLeft();
	void MoveRendererRight();
	void MoveCollisionLeft();
	void MoveCollisionRight();
	
	void Start() override;
	
};

