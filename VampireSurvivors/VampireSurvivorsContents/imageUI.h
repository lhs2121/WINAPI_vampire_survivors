#pragma once
#include <GameEngineCore/GameEngineActor.h>


class imageUI : public GameEngineActor
{
public:

	imageUI();
	virtual ~imageUI();
	


	imageUI(const imageUI& _Other) = delete;
	imageUI(imageUI&& _Other) noexcept = delete;
	imageUI& operator=(const imageUI& _Other) = delete;
	imageUI& operator=(imageUI&& _Other) noexcept = delete;


	void Init(const std::string& path, const float4 RenderPos = float4::ZERO, int _Order = 0);

protected:

private:


	class GameEngineRenderer* Renderer;


	void Start() override;
};

