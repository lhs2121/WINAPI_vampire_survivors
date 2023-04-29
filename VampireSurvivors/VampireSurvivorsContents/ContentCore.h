#pragma once
#include <GameEngineCore/GameEngineCore.h>

// ���� :
class ContentCore : public CoreProcess
{
public:
	// constrcuter destructer
	ContentCore();
	~ContentCore();

	// delete Function
	ContentCore(const ContentCore& _Other) = delete;
	ContentCore(ContentCore&& _Other) noexcept = delete;
	ContentCore& operator=(const ContentCore& _Other) = delete;
	ContentCore& operator=(ContentCore&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

	// �ൿ�Ѱ�.
	void Update() override;

	// �׷�����.
	void Render() override;

	// �����ȴ�.
	void Release() override;
};

