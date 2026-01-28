#pragma once
#include "StelScene.h"

class StelEntity;


// Scene for main menu screen
class MainMenuScene : public StelScene
{
private:
	StelEntity* m_MainMenuEntity;
public:
	~MainMenuScene();
	virtual void Load() override;
};