#include "Tile.h"
#include "cTextureMgr.h"

void Tile::animate()
{
	timing += 1;

	if (id == 1) {
		if (timing == 0) {
			static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
			setTexture(theTextureMgr->getTexture("grass01"));
		}
		if (timing == interval * 2) {
			static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
			setTexture(theTextureMgr->getTexture("grass02"));
		}
		if (timing == interval * 4) {
			static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
			setTexture(theTextureMgr->getTexture("grass01"));
		}
		if (timing == interval * 6) {
			static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
			setTexture(theTextureMgr->getTexture("grass03"));
			timing = -interval;
		}
	}

	if (id == 3) {
		if (timing == 0) {
			static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
			setTexture(theTextureMgr->getTexture("water01"));
		}
		if (timing == interval) {
			static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
			setTexture(theTextureMgr->getTexture("water02"));
		}
		if (timing == interval * 2) {
			static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
			setTexture(theTextureMgr->getTexture("water01"));
		}
		if (timing == interval * 3) {
			static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
			setTexture(theTextureMgr->getTexture("water03"));
			timing = -interval;
		}
	}
}
