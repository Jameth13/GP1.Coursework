#include "Boss.h"
#include "Player.h"
#include "Control.h"
#include "Tools.h"
#include "cTextureMgr.h"
#include "cSoundMgr.h"

Boss* Boss::pInstance = NULL;
static cTextureMgr* theTxtMgr = cTextureMgr::getInstance();
static cSoundMgr* soundMgr = cSoundMgr::getInstance();
static Control* control = Control::getInstance();
static Tools* tools = Tools::getInstance();
static Player* player = Player::getInstance();

Boss * Boss::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new Boss();
	}
	return Boss::pInstance;
}

void Boss::initalize(SDL_Point p)
{
	health = 100;
	timer = 120.0f;		//Long initial timer to give the player time to react.
	fireRate = 16;
	//0.7854 is 45 degrees in radians
	angleSpacing = 0.7854f;

	//Character
	pos = { p.x - control->getCameraPos().x, p.y - control->getCameraPos().y};
	posCentre = { pos.x + theTxtMgr->getTexture("boss")->getTWidth() / 2, pos.y + theTxtMgr->getTexture("boss")->getTHeight() / 2 };

	spChar.setTexture(theTxtMgr->getTexture("boss"));
	spChar.setSpritePos(pos);
	spChar.setSpriteDimensions(theTxtMgr->getTexture("boss")->getTWidth(), theTxtMgr->getTexture("boss")->getTHeight());

	//Health Bar
	spHealth.setTexture(theTxtMgr->getTexture("bossHealth100"));
	spHealth.setSpritePos({ 100, 660 });
	spHealth.setSpriteDimensions(theTxtMgr->getTexture("bossHealth100")->getTWidth(), theTxtMgr->getTexture("bossHealth100")->getTHeight());
}

void Boss::update()
{
	//Update position
	move();
	spChar.setSpritePos({ pos.x + control->getCameraPos().x, pos.y + control->getCameraPos().y });
	posProj = { spChar.getSpritePos().x + 20, spChar.getSpritePos().y + 20 };

	//Shooting
	timer -= 0.06f * control->getDeltaTime();
	if (timer < 0) {
		//soundMgr->getSnd("bossShoot")->play(0);	//Doesn't work with fast firing.
		timer = fireRate;
		Projectile proj;
		angleOffset += 0.15f;

		if (fireTimes <= 0)
		{
			//Repeat each fire mode at least 5 times.
			fireTimes = 5;
			fireMode = tools->random(0, 1);
		}else{
			fireTimes--;
		}

		switch (fireMode) {
		case 0:
			//Tri-shot attack
			proj.initalize(posProj, tools->calcUnitVec({ posProj.x, WINDOW_HEIGHT - posProj.y }, { player->getPosCentre().x, player->getPosCentre().y - 50 }), "bossProj");
			projectiles.push_back(proj);
			proj.initalize(posProj, tools->calcUnitVec({ posProj.x, WINDOW_HEIGHT - posProj.y }, { player->getPosCentre().x, player->getPosCentre().y }), "bossProj");
			projectiles.push_back(proj);
			proj.initalize(posProj, tools->calcUnitVec({ posProj.x, WINDOW_HEIGHT - posProj.y }, { player->getPosCentre().x, player->getPosCentre().y + 50}), "bossProj");
			projectiles.push_back(proj);
			break;
		case 1:
			//AOE attack
			for (unsigned int i = 0; i < 8; i++) {
				FPoint vector = { cos(angleSpacing * i + angleOffset), sin(angleSpacing * i + angleOffset) };
				proj.initalize(posProj, vector, "bossProj");
				projectiles.push_back(proj);
			}
			break;
		default:
			break;
		}
	}

	//Update health bar
	switch (health) {
	case 100:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth100"));
		break;
	case 95:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth95"));
		break;
	case 90:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth90"));
		break;
	case 85:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth85"));
		break;
	case 80:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth80"));
		break;
	case 75:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth75"));
		break;
	case 70:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth70"));
		break;
	case 65:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth65"));
		break;
	case 60:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth60"));
		break;
	case 55:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth55"));
		break;
	case 50:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth50"));
		break;
	case 45:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth45"));
		break;
	case 40:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth40"));
		break;
	case 35:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth35"));
		break;
	case 30:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth30"));
		break;
	case 25:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth25"));
		break;
	case 20:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth20"));
		break;
	case 15:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth15"));
		break;
	case 10:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth10"));
		break;
	case 5:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth05"));
		break;
	case 0:
		spHealth.setTexture(theTxtMgr->getTexture("bossHealth00"));
		break;
	default:
		break;
	}

	//Update projectiles
	for (unsigned int i = 0; i < projectiles.size(); i++) {
		projectiles[i].update();
	}

}

//Render boss, health bar, and projectiles.
void Boss::render(SDL_Renderer* theRenderer)
{
	spChar.render(theRenderer, &spChar.getSpriteDimensions(), &spChar.getSpritePos(), spChar.getSpriteRotAngle(), &spChar.getSpriteCentre(), spChar.getSpriteScale());
	spHealth.render(theRenderer, &spHealth.getSpriteDimensions(), &spHealth.getSpritePos(), spHealth.getSpriteRotAngle(), &spHealth.getSpriteCentre(), spHealth.getSpriteScale());
	for (unsigned int i = 0; i < projectiles.size(); i++) {
		projectiles[i].render(theRenderer);
	}
}

//Movement
void Boss::move()
{
	if (pos.y > 775) direction = true;
	if (pos.y < 125) direction = false;
	
	if (direction) {
		pos = { pos.x, pos.y - tools->round(0.2f * control->getDeltaTime()) };
	}else{
		pos = { pos.x, pos.y + tools->round(0.2f * control->getDeltaTime()) };
	}
}
SDL_Rect Boss::getPos()
{
	return spChar.getSpritePos();
}
int Boss::getPosY()
{
	return pos.y;
}
void Boss::setPosY(int y)
{
	pos.y = y;
}

//Projectiles
std::vector<Projectile> Boss::getProjectiles()
{
	return projectiles;
}
void Boss::removeProjectile(int index)
{
	projectiles.erase(projectiles.begin() + index);
}
void Boss::removeAllProjectiles()
{
	projectiles.clear();
}

//Health
void Boss::hit(int amount)
{
	soundMgr->getSnd("bossHit")->play(0);
	health -= abs(amount);
}
int Boss::getHealth()
{
	return health;
}
void Boss::setHealth(int h)
{
	health = h;
}

//Reset everything
void Boss::reset()
{
	health = 100;
	timer = 100;
	removeAllProjectiles();
	pos = { 875 - control->getCameraPos().x, 750 - control->getCameraPos().y };
}