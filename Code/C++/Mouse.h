#ifndef MOUSE_H
#define MOUSE_H

#include "stdafx.h"

class Mouse
{
private:
	float m_prevX;
	float m_prevY;
	float m_x;
	float m_y;
	float m_movementX;
	float m_movementY;
public:
	Mouse();
	Mouse(float _x, float _y);
	virtual ~Mouse();
	
	float getMovementX()const;
	float getMovementY()const;
	void setCursorVisibility(bool _visibility);
	void update(HWND _hwnd);
};

#endif