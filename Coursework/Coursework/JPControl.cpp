#include "Control.h"
float Control::xPos = 0;
float Control::yPos = 0;
bool Control::looping = true;

Control::Control()
{
}

void Control::initalize()
{
	Control::xPos = 0;
	Control::yPos = 0;
	Control::looping = true;
}

void Control::update(float deltaTime)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			looping = false;
		}

		switch (event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				break;
			case SDL_BUTTON_RIGHT:
				break;
			default:
				break;
			}
			break;

			case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				looping = false;
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
			default:
				break;
			}
			break;

			case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				looping = false;
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
			default:
				break;
			}

			default:
			break;
		}

	}


	if (down("w")) yPos += 10000.0 * deltaTime;
	if (down("a")) xPos += 10000.0 * deltaTime;
	if (down("s")) yPos -= 10000.0 * deltaTime;
	if (down("d")) xPos -= 10000.0 * deltaTime;
}

SDL_Point Control::getPos()
{
	return SDL_Point({ (int)xPos, (int)yPos });
}

bool Control::getLooping()
{
	return Control::looping;
}

void Control::add(std::string key)
{
	bool found = false;

	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] == key) {
			found = true;;
		}
	}

	if (!found) keys.push_back(key);
}

void Control::remove(std::string key)
{
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] == key) {
			keys.erase(keys.begin() + i);
		}
	}
}

bool Control::down(std::string key)
{
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] == key) return true;
	}
	return false;
}

bool Control::up(std::string key)
{
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] == key) return false;
	}
	return true;
}

std::string Control::print()
{
	std::string str;
	for (int i = 0; i < keys.size(); i++) {
		str += keys[i] + ", ";
	}
	str += "\n";
	return str;
}
