#pragma once
#include <vector>

class Input
{
public:
	enum class MouseState { UP, DOWN, PRESSED };
private:
	struct Mouse
	{
		int x, y;
		MouseState left, right;
	};


public:
	Input();
	bool GetSFKey(int key);
	void setKeyDown(int key);
	void setKeyUp(int key);
	bool isKeyDown(int key);
	bool isPressed(int key);
	void update();

	void setMouseX(int lx);
	void setMouseY(int ly);
	void setMousePosition(int lx, int ly);
	int getMouseX();
	int getMouseY();
	void setLeftMouse(MouseState state);
	bool isLeftMouseDown();
	bool isLeftMousePressed();
	void setRightMouse(MouseState state);
	bool isRightMouseDown();
	bool isRightMousePressed();

private:
	bool keys[256]{ false };
	std::vector<int> pressed;
	Mouse mouse;
};