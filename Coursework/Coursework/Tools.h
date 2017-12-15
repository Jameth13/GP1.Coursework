#ifndef _TOOLS_H
#define _TOOLS_H

class Tools
{
private:
	static Tools* pInstance;

public:
	static Tools* getInstance();
	//Round float or double to int.
	int round(float f);
	int round(double d);
	//Generate random int double or float between the two given values (inclusive).
	int random(int a, int b);
	float random(float a, float b);
	double random(double a, double b);
	//Calculate the unit vector between two points.
	FPoint calcUnitVec(SDL_Point a, SDL_Point b);
};
#endif
