#include "GameConstants.h"
#include "Tools.h"
#include "Math.h"
#include <iostream>
#include <stddef.h>	//NULL
#include <random>

Tools* Tools::pInstance = NULL;

Tools * Tools::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new Tools();
	}
	return Tools::pInstance;
}

//Round float or double to int.
int Tools::round(float f)
{
	return (int)floor(f + 0.5f);
}
int Tools::round(double d)
{
	return (int)floor(d + 0.5);
}

//Generate random int double or float between the two given values (inclusive).
int Tools::random(int a, int b)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(a, b);

	return round(dist(mt));
}
float Tools::random(float a, float b)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(a, b);

	return dist(mt);
}
double Tools::random(double a, double b)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(a, b);

	return dist(mt);
}

//Calculate the unit vector between two points.
FPoint Tools::calcUnitVec(SDL_Point a, SDL_Point b)
{
	float sqRoot = sqrt(pow((float)(b.x - a.x), 2.0f) + pow((float)(b.y - a.y), 2.0f));

	return { (b.x - a.x) / sqRoot, (b.y - a.y) / sqRoot };
}