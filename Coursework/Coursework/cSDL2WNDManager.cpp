/*
==================================================================================
cSDL2WNDManager.cpp
==================================================================================
*/
#include <string>
#include <fstream>
#include "cSDL2WNDManager.h"
#include "GameConstants.h"
#include "Control.h"
#include "Tools.h"

cSDL2WNDManager* cSDL2WNDManager::pInstance = NULL;
static Control* control = Control::getInstance();
static Tools* tools = Tools::getInstance();

/*
=================================================================================
Constructor
=================================================================================
*/
cSDL2WNDManager::cSDL2WNDManager()
{

}
/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cSDL2WNDManager* cSDL2WNDManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cSDL2WNDManager();
	}
	return cSDL2WNDManager::pInstance;
}

/*
=================================================================================
* Initialise the SDL Context with desired Window Title String, width and height
* @param strWNDTitle The Window Title String
* @param iWidth The width of the window to draw
* @param iHeight The height of the window to draw
=================================================================================
*/
bool cSDL2WNDManager::initWND(string strWNDTitle, int iWidth, int iHeight)
{
	// Initialize SDL's Video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Failed to initialize SDL\n";
		return false;
	}

	SDL_Init(SDL_INIT_GAMECONTROLLER);

	//Load fullscreen.ini
	bool bFullscreen = false;
	string sFullscreen;
	fstream fFullscreen;

	fFullscreen.open("Resources\\fullscreen.ini");
	if (fFullscreen.is_open())
	{
		getline(fFullscreen, sFullscreen);
		bFullscreen = stoi(sFullscreen);
		fFullscreen.close();
	} else {
		cout << "Unable to open file fullscreen.ini\n";
	}

	//Load either fullscreen or windowed tags.
	Uint32 flags;
	if (bFullscreen) flags = SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_MAXIMIZED;
	else flags = SDL_WINDOW_OPENGL;

	mainWindow = SDL_CreateWindow(strWNDTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, iWidth, iHeight, flags);

	//Check that everything worked out okay
	if (!mainWindow)
	{
		cout << "Unable to create window\n";
		CheckSDLError(__LINE__);
		return false;
	}
	else
	{
		//Get the renderer
			theRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_PRESENTVSYNC);

			if (theRenderer != 0)
			{
				std::cout << "Renderer creation succeeded" << std::endl;

				SDL_SetRenderDrawColor(theRenderer, 0, 0, 100, 255);
			}
			else
			{
				std::cout << "Renderer creation failed" << std::endl;
				return false;
			}
	}


	//Calculate render scale (how far to stretch the 1280x720 game to fit the screen, maintaining aspect ratio).
	//Calculate the render excess (how the any black bars should be).
	//Supports ultrawide!
	SDL_DisplayMode resolution;
	SDL_GetCurrentDisplayMode(0, &resolution);
	
	FPoint renderScale = { (float)resolution.w / (float)WINDOW_WIDTH, (float)resolution.h / (float)WINDOW_HEIGHT };
	FPoint renderExcess = { 0, 0 };
	if (renderScale.x > renderScale.y) {
		renderScale.x = renderScale.y;
		renderExcess.x = (resolution.w - WINDOW_WIDTH * renderScale.x) / 2;
	}
	if (renderScale.x < renderScale.y) {
		renderScale.y = renderScale.x;
		renderExcess.y = (resolution.h - WINDOW_HEIGHT * renderScale.y) / 2;
	}

	const SDL_Rect rect = { tools->round(renderExcess.x / renderScale.x), tools->round(renderExcess.y / renderScale.y), WINDOW_WIDTH, WINDOW_HEIGHT };
	const SDL_Rect *pRect = &rect;

	if (bFullscreen) {
		control->setRenderScale(renderScale);
		control->setRenderExcess({ renderExcess.x / renderScale.x, renderExcess.y / renderScale.y });
		SDL_RenderSetScale(theRenderer, renderScale.x, renderScale.y);
		SDL_RenderSetViewport(theRenderer, pRect);
	}
	else {
		control->setRenderExcess({ 0, 0 });
		control->setRenderScale({ 1, 1 });
	}

	return true;
}

void cSDL2WNDManager::CheckSDLError(int line = -1)
{
	string error = SDL_GetError();

	if (error != "")
	{
		cout << "SLD Error : " << error << std::endl;

		if (line != -1)
			cout << "\nLine : " << line << std::endl;

		SDL_ClearError();
	}
}


SDL_Window* cSDL2WNDManager::getSDLWindow()
{
	return mainWindow;
}

SDL_GLContext cSDL2WNDManager::getSDL_GLContext()
{
	return mainContext;
}

SDL_Renderer* cSDL2WNDManager::getSDLRenderer()
{
	return theRenderer;
}