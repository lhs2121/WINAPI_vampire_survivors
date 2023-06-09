#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Button : public GameEngineActor
{


public:

	Button();
	~Button();

	Button(const Button& _Other) = delete;
	Button(Button&& _Other) noexcept = delete;
	Button& operator=(const Button& _Other) = delete;
	Button& operator=(Button&& _Other) noexcept = delete;


	void Init(const std::string& path, const float4 RenderPos, int _Order = 0);

	void SetPanel(GameEngineActor* _Panel)
	{
		Panel = _Panel;
	}

protected:

	
	virtual void OnClick();
	

private:
	void Start() override;
	void Update(float _Delta) override;
	bool CheckCollision(float left, float right, float top, float bottom, int mouseX, int mouseY);
	class GameEngineRenderer* Renderer;
	GameEngineActor* Panel;
	float4 Scale;




};

