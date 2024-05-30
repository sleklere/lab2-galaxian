#pragma once
#include "Enemy.h"

class Galaxian : public Enemy
{
public:
	void update() const override;
	// destructor para "matar" al enemigo
};

