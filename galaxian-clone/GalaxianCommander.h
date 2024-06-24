#pragma once
#include "Galaxian.h"
#include "Enemy.h"

class GalaxianCommander : public Enemy
{
public:
	GalaxianCommander();
	void updateDrawing() override;
};

