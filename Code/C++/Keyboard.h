#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "stdafx.h"

class Keyboard
{
private:
	// Key codes
	int m_accelerate;
	int m_brake;
	int m_turnLeft;
	int m_turnRight;
	int m_shoot;
	int m_pause;
	
	// Key press checks
	bool m_accelerateIsDown;
	bool m_brakeIsDown;
	bool m_turnLeftIsDown;
	bool m_turnRightIsDown;
	bool m_shootIsDown;
	bool m_pauseIsDown;
public:
	Keyboard();
	virtual ~Keyboard();
	
	bool getAccelerateIsDown()const;
	bool getBrakeIsDown() const;
	bool getTurnLeftIsDown()const;
	bool getTurnRightIsDown()const;
	bool getShootIsDown() const;

	bool getPauseIsDown()const;

	void keyDown(WPARAM _key);
	void keyUp(WPARAM _key);
};

#endif