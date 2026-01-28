#include "MainMenuScene.h"
#include "StelEngine.h"
#include "MainMenuManager.h"

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::Load() 
{
	m_MainMenuEntity = Instantiate("MainMenu");
	m_MainMenuEntity->AddComponent<MainMenuManager>()->Start();
}