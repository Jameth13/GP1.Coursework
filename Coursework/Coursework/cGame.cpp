/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"
#include "Player.h"
#include "SceneManager.h"
#include "Control.h"
//DeltaTime
#include <chrono>

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTxtMgr = cTextureMgr::getInstance();
static cFontMgr* fontMgr = cFontMgr::getInstance();
static cSoundMgr* soundMgr = cSoundMgr::getInstance();
static SceneManager* sceneMgr = SceneManager::getInstance();
static Control* control = Control::getInstance();

cGame* cGame::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}

void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	//Get width and height of render context
	SDL_GetRendererOutputSize(theRenderer, &renderWidth, &renderHeight);
	//Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);

	theTxtMgr->setRenderer(theRenderer);
	soundMgr->initMixer();

	//SLoad textures
	textureName = {
		"transparent", "grass01", "wall", "water01", "test",
		"playerUp", "playerDown" , "playerLeft", "playerRight", "playerProj", "playerHealth5", "playerHealth4", "playerHealth3", "playerHealth2", "playerHealth1", "playerHealth0",
		"grass02", "grass03" , "water02", "water03",
		"mainMenu", "controls", "credits", "win", "gameOver",
		"button01", "button02", "buttonStart", "buttonContinue", "buttonControls", "buttonCredits", "buttonQuit", "buttonBack",
		"boss", "bossProj", "bossHealth00", "bossHealth05", "bossHealth10", "bossHealth15", "bossHealth20", "bossHealth25", "bossHealth30", "bossHealth35", "bossHealth40", "bossHealth45", "bossHealth50", "bossHealth55", "bossHealth60", "bossHealth65", "bossHealth70", "bossHealth75", "bossHealth80", "bossHealth85", "bossHealth90", "bossHealth95", "bossHealth100"
	};
	texturesToUse = {
		"Resources\\Sprites\\transparent.png", "Resources\\Sprites\\Tiles\\grass01.png", "Resources\\Sprites\\Tiles\\wall.png" , "Resources\\Sprites\\Tiles\\water01.png", "Resources\\Sprites\\Tiles\\test.png",
		"Resources\\Sprites\\Player\\playerUp.png", "Resources\\Sprites\\Player\\playerDown.png",  "Resources\\Sprites\\Player\\playerLeft.png", "Resources\\Sprites\\Player\\playerRight.png", "Resources\\Sprites\\Player\\projectile.png", "Resources\\Sprites\\Player\\health5.png", "Resources\\Sprites\\Player\\health4.png", "Resources\\Sprites\\Player\\health3.png", "Resources\\Sprites\\Player\\health2.png", "Resources\\Sprites\\Player\\health1.png", "Resources\\Sprites\\Player\\health0.png",
		"Resources\\Sprites\\Tiles\\grass02.png" , "Resources\\Sprites\\Tiles\\grass03.png","Resources\\Sprites\\Tiles\\water02.png" , "Resources\\Sprites\\Tiles\\water03.png",
		"Resources\\Sprites\\Titles\\mainMenu.png", "Resources\\Sprites\\Titles\\controls.png", "Resources\\Sprites\\Titles\\credits.png", "Resources\\Sprites\\Titles\\win.png", "Resources\\Sprites\\Titles\\GameOver.png",
		"Resources\\Sprites\\Buttons\\button01.png", "Resources\\Sprites\\Buttons\\button02.png", "Resources\\Sprites\\Buttons\\buttonStart.png", "Resources\\Sprites\\Buttons\\buttonContinue.png", "Resources\\Sprites\\Buttons\\buttonControls.png", "Resources\\Sprites\\Buttons\\buttonCredits.png", "Resources\\Sprites\\Buttons\\buttonQuit.png", "Resources\\Sprites\\Buttons\\buttonBack.png",
		"Resources\\Sprites\\Boss\\boss.png", "Resources\\Sprites\\Boss\\projectile.png", "Resources\\Sprites\\Boss\\health00.png", "Resources\\Sprites\\Boss\\health05.png", "Resources\\Sprites\\Boss\\health10.png", "Resources\\Sprites\\Boss\\health15.png", "Resources\\Sprites\\Boss\\health20.png", "Resources\\Sprites\\Boss\\health25.png", "Resources\\Sprites\\Boss\\health30.png", "Resources\\Sprites\\Boss\\health35.png", "Resources\\Sprites\\Boss\\health40.png", "Resources\\Sprites\\Boss\\health45.png", "Resources\\Sprites\\Boss\\health50.png", "Resources\\Sprites\\Boss\\health55.png", "Resources\\Sprites\\Boss\\health60.png", "Resources\\Sprites\\Boss\\health65.png", "Resources\\Sprites\\Boss\\health70.png", "Resources\\Sprites\\Boss\\health75.png", "Resources\\Sprites\\Boss\\health80.png", "Resources\\Sprites\\Boss\\health85.png", "Resources\\Sprites\\Boss\\health90.png", "Resources\\Sprites\\Boss\\health95.png", "Resources\\Sprites\\Boss\\health100.png"
	};

	for (unsigned int tCount = 0; tCount < textureName.size(); tCount++)
	{	
		theTxtMgr->addTexture(textureName[tCount], texturesToUse[tCount]);
	}



	//Load game sounds
	soundList = { "mainMenu", "button", "bossShoot", "bossHit", "bossDeath" , "playerShoot", "playerHit", "playerDeath" };
	soundTypes = { MUSIC, SFX, SFX, SFX, SFX, SFX, SFX, SFX };
	soundsToUse = { "Resources/Audio/mainMenu.mp3", "Resources/Audio/buttonPress.wav", "Resources/Audio/bossShoot.wav", "Resources/Audio/bossHit.wav", "Resources/Audio/bossDeath.wav", "Resources/Audio/playerShoot.wav", "Resources/Audio/playerHit.wav", "Resources/Audio/playerDeath.wav" };
	for (unsigned int sounds = 0; sounds < soundList.size(); sounds++)
	{
		soundMgr->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	}

	//Load fonts
	fontMgr->initFontLib();
	fontList = { "digital", "spaceAge", "gameOver" };
	fontsToUse = { "Resources/Fonts/digital-7.ttf", "Resources/Fonts/space age.ttf", "Resources/Fonts/game_over.ttf" };
	for (unsigned int fonts = 0; fonts < fontList.size(); fonts++)
	{
		fontMgr->addFont(fontList[fonts], fontsToUse[fonts], 48);
	}
	fontMgr->addFont("gameOverLarge", "Resources/Fonts/game_over.ttf", 60);

	control->initalize();
	sceneMgr->initalize(theRenderer, textureName);
}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	//Main game loop
	while (control->getLooping())
	{
		this->update();
		this->render(theSDLWND, theRenderer);
	}
}

//Update
void cGame::update()
{
	control->update();
	sceneMgr->update();
	sceneMgr->resetOneLoad();
}

//Render
void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);	//First

	sceneMgr->render(theSDLWND, theRenderer, textureName);

	SDL_RenderPresent(theRenderer);	//Last
}

void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}

