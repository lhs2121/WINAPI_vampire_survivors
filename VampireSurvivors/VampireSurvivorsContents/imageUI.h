#pragma once
#include <GameEngineCore/GameEngineActor.h>


class imageUI : public GameEngineActor
{
public:

	imageUI();
	~imageUI();


	imageUI(const imageUI& _Other) = delete;
	imageUI(imageUI&& _Other) noexcept = delete;
	imageUI& operator=(const imageUI& _Other) = delete;
	imageUI& operator=(imageUI&& _Other) noexcept = delete;


	void Init(const std::string& path, const float4 RenderPos = float4::ZERO, float Ratio = 1.0f);

protected:

private:


	class GameEngineRenderer* Renderer;


	void Start() override;
};

