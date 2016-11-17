#include "Mouse.h"

Mouse::Mouse()
{

}

Mouse::Mouse(float _x, float _y)
{
	SetCursorPos((int)_x, (int)_y);
	this->m_x = _x;
	this->m_y = _y;
	this->m_movementX = 0;
	this->m_movementY = 0;
	this->m_prevX = _x;
	this->m_prevY = _y;
}

Mouse::~Mouse()
{

}

float Mouse::getMovementX()const
{
	return this->m_movementX;
}

float Mouse::getMovementY()const
{
	return this->m_movementY;
}

void Mouse::setCursorVisibility(bool _visibility)
{
	if(_visibility)
		ShowCursor(TRUE);
	else
		ShowCursor(FALSE);
}

void Mouse::update(HWND _hwnd)
{
	this->m_prevX = this->m_x;
	this->m_prevY = this->m_y;

	// Get the current mouse position.
	POINT currentMousePos;
	GetCursorPos(&currentMousePos);
	ScreenToClient(_hwnd, &currentMousePos);

	this->m_movementX = currentMousePos.x-this->m_prevX;
	this->m_movementY = currentMousePos.y-this->m_prevY;

	this->m_x = (float)currentMousePos.x;
	this->m_y = (float)currentMousePos.y;
}