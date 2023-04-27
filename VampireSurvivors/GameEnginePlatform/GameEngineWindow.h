#pragma once
#include <Windows.h>
#include <string>

// ���� :
class GameEngineWindow
{
public:
	static GameEngineWindow MainWindow;

	// constrcuter destructer
	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

	void Open(const std::string& _Title, HINSTANCE _hInstance); //��ü�� �����ؼ� �����츦 ��������� �Լ�

	static void MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)()); //�̺�Ʈ �ڵ鷯

protected:

private:
	static HINSTANCE Instance; // ���α׷� �ڵ�
	std::string Title = ""; // ������ ���� Ÿ��Ʋ
	HWND hWnd = nullptr; // ������â �ڵ�

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //�ݹ��Լ�
	void InitInstance();
	void MyRegisterClass();
};

