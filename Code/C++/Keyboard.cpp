#include "Keyboard.h"


Keyboard::Keyboard()
{
	this->m_accelerate	= VK_UP;
	this->m_brake		= VK_DOWN;
	this->m_turnLeft	= VK_LEFT;
	this->m_turnRight	= VK_RIGHT;
	this->m_shoot		= VK_SPACE;
	this->m_pause		= 'P';

	this->m_accelerateIsDown	= false;
	this->m_brakeIsDown			= false;
	this->m_turnLeftIsDown		= false;
	this->m_turnRightIsDown		= false;
	this->m_shootIsDown			= false;
	this->m_pauseIsDown			= false;
}

Keyboard::~Keyboard()
{

}

bool Keyboard::getAccelerateIsDown()const
{
	return this->m_accelerateIsDown;
}

bool Keyboard::getBrakeIsDown()const
{
	return this->m_brakeIsDown;
}

bool Keyboard::getTurnLeftIsDown()const
{
	return this->m_turnLeftIsDown;
}

bool Keyboard::getTurnRightIsDown()const
{
	return this->m_turnRightIsDown;
}

bool Keyboard::getShootIsDown()const
{
	return this->m_shootIsDown;
}

bool Keyboard::getPauseIsDown()const
{
	return this->m_pauseIsDown;
}

void Keyboard::keyDown(WPARAM _key)
{
	if(_key == this->m_accelerate)
		this->m_accelerateIsDown = true;
	if(_key == this->m_brake)
		this->m_brakeIsDown = true;
	else if(_key == this->m_turnLeft)
		this->m_turnLeftIsDown = true;
	else if(_key == this->m_turnRight)
		this->m_turnRightIsDown = true;
	else if(_key == this->m_shoot)
		this->m_shootIsDown = true;
	else if(_key == this->m_pause)
		this->m_pauseIsDown = true;

	// temporary, for development only
	else if(GetAsyncKeyState(VK_ESCAPE))
		PostQuitMessage(0);
}

void Keyboard::keyUp(WPARAM _key)
{
	if(_key == this->m_accelerate)
		this->m_accelerateIsDown = false;
	if(_key == this->m_brake)
		this->m_brakeIsDown = false;
	else if(_key == this->m_turnLeft)
		this->m_turnLeftIsDown = false;
	else if(_key == this->m_turnRight)
		this->m_turnRightIsDown = false;
	else if(_key == this->m_shoot)
		this->m_shootIsDown = false;
	else if(_key == this->m_pause)
		this->m_pauseIsDown = false;
}