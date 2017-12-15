#include <iostream>
#include "Control.h"
#include "Tools.h"

Control* Control::pInstance = NULL;
static Tools* tools = Tools::getInstance();

Control* Control::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new Control();
	}
	return Control::pInstance;
}

void Control::initalize()
{
	looping = true;
	xCamera = 0;
	yCamera = 0;
}

//Update deltatime.
//Get input from SDL.
//add(): Add key press to vector<string> keys.
//remove(): remove key press from vector<string> keys.
//Note: Mouse clicks are handled the same as keys.
void Control::update()
{

	calcDeltaTime();

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			looping = false;
		}

		switch (event.type)
		{
		case SDL_MOUSEMOTION:
			//xMouse and yMouse keep track of the mouse position (adjusted for render scale and excess).
			xMouse = tools->round((float)event.motion.x / getRenderScale().x - renderExcess.x);
			yMouse = tools->round((float)event.motion.y / getRenderScale().y - renderExcess.y);
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				add("mLeft");
				break;
			case SDL_BUTTON_RIGHT:
				add("mRight");
				break;
			default:
				break;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				remove("mLeft");
				break;
			case SDL_BUTTON_RIGHT:
				remove("mLeft");
				break;
			default:
				break;
			}
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				add("escape");
				break;
			case SDLK_w:
				add("w");
				break;
			case SDLK_a:
				add("a");
				break;
			case SDLK_s:
				add("s");
				break;
			case SDLK_d:
				add("d");
				break;
			case SDLK_LSHIFT:
				add("shift");
				break;
			default:
				break;
			}
			break;

		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				remove("escape");
				break;
			case SDLK_w:
				remove("w");
				break;
			case SDLK_a:
				remove("a");
				break;
			case SDLK_s:
				remove("s");
				break;
			case SDLK_d:
				remove("d");
				break;
			case SDLK_LSHIFT:
				remove("shift");
				break;
			default:
				break;
			}

			default:
			break;
		}

	}

	//Single-frame key presses return true only on the initial frame the key press was detected.
	//Single-frame mouse clicks
	if (down("mLeft")) {
		if (mLeftOnce) {
			mLeftOnce = false;
			add("mLeftOnce");
		}
		else {
			remove("mLeftOnce");
		}
	}
	else {
		mLeftOnce = true;
	}
	if (down("mRight")) {
		if (mRightOnce) {
			mRightOnce = false;
			add("mRightOnce");
		}
		else {
			remove("mRightOnce");
		}
	}
	else {
		mRightOnce = true;
	}
	//Single-frame escape
	if (down("escape")) {
		if (escapeOnce) {
			escapeOnce = false;
			add("escapeOnce");
		}
		else {
			remove("escapeOnce");
		}
	}
	else {
		escapeOnce = true;
	}
}

void Control::calcDeltaTime()
{
	now = high_resolution_clock::now();

	nanoseconds nano = duration_cast<nanoseconds>(now - last);

	//Get nanoseconds as long
	long nanoseconds = nano.count();
	//Convert nanoseconds to float of milliseconds.
	deltatime = nanoseconds / 1000000.0f;

	last = now;
}

float Control::getDeltaTime()
{
	return deltatime;
}

//Return camera position as SDL_Point.
SDL_Point Control::getCameraPos()
{
	return SDL_Point({ (int)xCamera, (int)yCamera });
}

//Return true mouse position as SDL_Point.
SDL_Point Control::getMousePos()
{
	return { xMouse, yMouse };
}

//Return fixed mouse position as SDL_Point.
//Clarification: Because graphics coordinates use an inverted Y-axis sometimes the yMouse position needs to be flipped.
SDL_Point Control::getMousePosFixedY()
{
	return { xMouse, WINDOW_HEIGHT - yMouse };
}

//Set camera position.
void Control::setCameraPos(FPoint pos)
{
	xCamera = pos.x;
	yCamera = pos.y;
}

//Move camera position.
void Control::moveCameraPos(FPoint amount)
{
	xCamera += amount.x;
	yCamera += amount.y;
}

//Get or Set the game loop bool.
bool Control::getLooping()
{
	return Control::looping;
}
void Control::setLooping(bool b)
{
	looping = b;
}


//Add or Remove keys to vextor<string> keys (without duplicates).
void Control::add(std::string key)
{
	bool found = false;

	for (unsigned int i = 0; i < keys.size(); i++) {
		if (keys[i] == key) {
			found = true;
		}
	}

	if (!found) keys.push_back(key);
}
void Control::remove(std::string key)
{
	for (unsigned int i = 0; i < keys.size(); i++) {
		if (keys[i] == key) {
			keys.erase(keys.begin() + i);
		}
	}
}

//Ask if keys are up or down.
bool Control::down(std::string key)
{
	for (unsigned int i = 0; i < keys.size(); i++) {
		if (keys[i] == key) return true;
	}
	return false;
}
bool Control::up(std::string key)
{
	for (unsigned int i = 0; i < keys.size(); i++) {
		if (keys[i] == key) return false;
	}
	return true;
}

//Set or Get render scale and excess
void Control::setRenderScale(FPoint rs)
{
	renderScale = rs;
}
FPoint Control::getRenderScale()
{
	return renderScale;
}
void Control::setRenderExcess(FPoint re)
{
	renderExcess = re;
}
FPoint Control::getRenderExcess()
{
	return renderExcess;
}

//Print list of all key presses (debugging).
std::string Control::print()
{
	std::string str;
	for (unsigned int i = 0; i < keys.size(); i++) {
		str += keys[i] + ", ";
	}
	str += "\n";
	return str;
}

//Reset control.
void Control::reset()
{
	keys.clear();
	looping = true;
	xCamera = 0;
	yCamera = 0;
}
