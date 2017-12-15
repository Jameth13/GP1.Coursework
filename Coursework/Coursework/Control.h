#ifndef _CONTROL_H
#define _CONTROL_H

#include <SDL.h>
#include <string>
#include <vector>
#include <chrono>
#include "GameConstants.h"

using namespace std::chrono;

class Control
{
private:
	static Control* pInstance;
	//List of all keys pressed and functions to add/remove (without duplicates).
	std::vector<std::string> keys;
	void add(std::string key);
	void remove(std::string key);
	//Camera
	float xCamera;
	float yCamera;
	//Mouse
	int xMouse;
	int yMouse;
	//Single-frame inputs.
	bool mLeftOnce = true;
	bool mRightOnce = true;
	bool escapeOnce = true;
	//Game loop
	bool looping;
	//Render scale for accurate mouse input in fullscreen.
	FPoint renderScale;
	FPoint renderExcess;
	//DeltaTime
	float deltatime;
	void calcDeltaTime();
	steady_clock::time_point now;
	steady_clock::time_point last;


public:
	static Control* getInstance();

	void initalize();
	//Get input from SDL
	void update();
	//Game loop
	bool getLooping();
	void setLooping(bool b);
	//Ask if keys are up or down.
	bool down(std::string key);
	bool up(std::string key);
	//Print list of all key presses (debugging).
	std::string print();
	//Camera
	SDL_Point getCameraPos();
	void setCameraPos(FPoint pos);
	void moveCameraPos(FPoint amount);
	//Mouse
	SDL_Point getMousePos();
	SDL_Point getMousePosFixedY();
	//Reset all key presses.
	void reset();
	//Render scale for accurate mouse input in fullscreen.
	void setRenderScale(FPoint rs);
	FPoint getRenderScale();
	void setRenderExcess(FPoint re1);
	FPoint getRenderExcess();
	//DeltaTime
	float getDeltaTime();
};

#endif
