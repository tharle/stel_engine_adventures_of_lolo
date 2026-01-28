#pragma once
#include "Enemy.h"

class GreenWorm : public Enemy {
	void Start(std::string spriteSheet, std::map<std::string, AEnemyState*> states);
};