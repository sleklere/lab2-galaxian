#pragma once
#include "Galaxian.h"
#include "Enemy.h"

class GalaxianCommander : public Enemy
{
public:
	void update() const override;
};

