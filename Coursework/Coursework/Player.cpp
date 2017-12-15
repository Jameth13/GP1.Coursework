#include "Player.h"
#include "Control.h"
#include "Tools.h"
#include "cFontMgr.h"
#include "cSoundMgr.h"

Player* Player::pInstance = NULL;
static Control* control = Control::getInstance();
static cTextureMgr* theTxtMgr = cTextureMgr::getInstance();
static cSoundMgr* soundMgr = cSoundMgr::getInstance();
static Tools* tools = Tools::getInstance();

Player * Player::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new Player();
	}
	return Player::pInstance;
}

void Player::initalize()
{
	health = 5;
	timer = 100.0f;	//Delay first bullet fire.

	//Character sprite
	spChar.setTexture(theTxtMgr->getTexture("playerUp"));
	spChar.setSpritePos({ WINDOW_WIDTH / 2 - theTxtMgr->getTexture("playerUp")->getTWidth() / 2, WINDOW_HEIGHT / 2 - theTxtMgr->getTexture("playerUp")->getTHeight() / 2 });
	spChar.setSpriteDimensions(theTxtMgr->getTexture("playerUp")->getTWidth(), theTxtMgr->getTexture("playerUp")->getTHeight());
	posCentre = { spChar.getSpritePos().x + spChar.getSpritePos().w / 2, spChar.getSpritePos().y + spChar.getSpritePos().h / 2 };

	//Health Bar sprite
	spHealth.setTexture(theTxtMgr->getTexture("playerHealth5"));
	spHealth.setSpritePos({ 10, 40 });
	spHealth.setSpriteDimensions(theTxtMgr->getTexture("playerHealth5")->getTWidth(), theTxtMgr->getTexture("playerHealth5")->getTHeight());
}

void Player::update()
{
	
	movement();

	//Shooting
	if (timer > firerate) timer = firerate;	//Timer can be greater than firerate after pressing shift for faster shooting.
	timer -= 0.08f * control->getDeltaTime();;
	if(control->down("mLeft") && timer < 0)
	{
		soundMgr->getSnd("playerShoot")->play(0);

		timer = firerate;
		Projectile proj;
		proj.initalize(posCentre, tools->calcUnitVec(posCentre, control->getMousePosFixedY()), "playerProj");
		projectiles.push_back(proj);
	}

	//Update health bar
	switch (health) {
	case 5:
		spHealth.setTexture(theTxtMgr->getTexture("playerHealth5"));
		break;
	case 4:
		spHealth.setTexture(theTxtMgr->getTexture("playerHealth4"));
		break;
	case 3:
		spHealth.setTexture(theTxtMgr->getTexture("playerHealth3"));
		break;
	case 2:
		spHealth.setTexture(theTxtMgr->getTexture("playerHealth2"));
		break;
	case 1:
		spHealth.setTexture(theTxtMgr->getTexture("playerHealth1"));
		break;
	case 0:
		spHealth.setTexture(theTxtMgr->getTexture("playerHealth0"));
		break;
	default:
		break;
	}
	
	//Update projectiles
	for (unsigned int i = 0; i < projectiles.size(); i++) {
		projectiles[i].update();
	}
}

//Render player, health bar, and projectiles.
void Player::render(SDL_Renderer* theRenderer)
{
	spChar.render(theRenderer, &spChar.getSpriteDimensions(), &spChar.getSpritePos(), spChar.getSpriteRotAngle(), &spChar.getSpriteCentre(), spChar.getSpriteScale());
	spHealth.render(theRenderer, &spHealth.getSpriteDimensions(), &spHealth.getSpritePos(), spHealth.getSpriteRotAngle(), &spHealth.getSpriteCentre(), spHealth.getSpriteScale());

	for (unsigned int i = 0; i < projectiles.size(); i++) {
		projectiles[i].render(theRenderer);
	}

}

//Movement
void Player::movement()
{
	//Adjust speed and firerate
	speed = 0.16f * control->getDeltaTime();
	firerate = 36;
	if (slow) speed *= 0.3f;
	if (control->down("shift") && !slow) {
		speed *= 0.6f;
		firerate *= 0.6f;
	}

	//Update directions
	//We use a list of direction because if both W & S or A & D are pressed, we wont the most recent (last in the list) to dominate.
	if (control->down("w")) addDir("up");
	else removeDir("up");

	if (control->down("s")) addDir("down");
	else removeDir("down");

	if (control->down("a")) addDir("left");
	else removeDir("left");

	if (control->down("d")) addDir("right");
	else removeDir("right");

	//Determine which direction to move based on list.
	string move[2];
	for (unsigned int i = 0; i < directions.size(); i++) {
		if (directions[i] == "up") move[0] = "up";
		if (directions[i] == "down") move[0] = "down";
		if (directions[i] == "left") move[1] = "left";
		if (directions[i] == "right") move[1] = "right";
	}

	//Update position
	//We use diagonalSpeedFix to stop the player from moving faster while traveling diagonally.
	float diagonalSpeedFix = 1.0f;
	if (!(move[0] == "" || move[1] == "")) diagonalSpeedFix = 0.707f;
	if (move[0] == "up") control->moveCameraPos({ 0, speed * diagonalSpeedFix });
	if (move[0] == "down") control->moveCameraPos({ 0, -speed * diagonalSpeedFix });
	if (move[1] == "left") control->moveCameraPos({ speed * diagonalSpeedFix, 0 });
	if (move[1] == "right") control->moveCameraPos({ -speed * diagonalSpeedFix, 0 });

	//Update sprites
	if (directions.size() > 0) {
		if (directions.back() == "up") spChar.setTexture(theTxtMgr->getTexture("playerUp"));
		if (directions.back() == "down") spChar.setTexture(theTxtMgr->getTexture("playerDown"));
		if (directions.back() == "left") spChar.setTexture(theTxtMgr->getTexture("playerLeft"));
		if (directions.back() == "right") spChar.setTexture(theTxtMgr->getTexture("playerRight"));
	}
	//Return to normal speed
	slow = false;
}

void Player::addDir(std::string dir)
{
	bool found = false;
	for (unsigned int i = 0; i < directions.size(); i++) {
		if (directions[i] == dir) {
			found = true;
		}
	}
	if (!found) directions.push_back(dir);
}
void Player::removeDir(std::string dir)
{
	for (unsigned int i = 0; i < directions.size(); i++) {
		if (directions[i] == dir) {
			directions.erase(directions.begin() + i);
		}
	}
}

SDL_Rect Player::getPos()
{
	return spChar.getSpritePos();
}
SDL_Point Player::getPosCentre()
{
	return posCentre;
}
void Player::setSlow(bool b)
{
	slow = b;
}

//Health
int Player::getHealth()
{
	return health;
}
void Player::setHealth(int h)
{
	health = h;
}
void Player::hit(int amount)
{
	soundMgr->getSnd("playerHit")->play(0);
	health -= abs(amount);
}


//Score
void Player::setScore(int s)
{
	score = s;
}
void Player::modScore(int i)
{
	score += i;
}
int Player::getScore()
{
	return score;
}

//Revive
void Player::revive()
{
	health = 5;
	timer = firerate;
	score = 0;
	removeAllProjectiles();
}

//Shooting
std::vector<Projectile> Player::getProjectiles()
{
	return projectiles;
}
void Player::removeProjectile(int index)
{
	projectiles.erase(projectiles.begin() + index);
}
void Player::removeAllProjectiles()
{
	projectiles.clear();
}
