#pragma once
#include "Enemy.h"

class GalaxianRed: public Enemy
{
public:
	GalaxianRed();
	//void updateDrawing();
	void updateDrawing() override;
};
