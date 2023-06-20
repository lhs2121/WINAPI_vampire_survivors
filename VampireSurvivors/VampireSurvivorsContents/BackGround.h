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
	void BackGroundLoop(class Player* player);
protected:

private:

	bool SwitchRenderValue = true;
	class GameEngineRenderer* Renderer;
	class GameEngineRenderer* DebugRenderer;
	class GameEngineRenderer* OtherRendererGroup[2];

	std::string FileName;
	float4 Scale;
	float4 OffSetX;
	float4 OffSetY;

	GameEngineCollision* LeftWall;
	GameEngineCollision* RightWall;

	bool RightWallCheck;
	bool LeftWallCheck;
	bool OnCollision = false;

	void MoveLeft();
	void MoveRight();
	void MoveOtherRenderer();
	void Start() override;
	void Update(float _Delta) override;
	
};

