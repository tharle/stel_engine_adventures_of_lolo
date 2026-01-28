#include "GameSceneLevel1.h"
#include "StelEngine.h"
#include "Player.h"
#include "StelAnimation.h"
#include "LevelManager.h"
#include "Collectable.h"
#include "Chest.h"
#include "Door.h"
#include "Box.h"
#include "Enemy.h"

void GameSceneLevel1::Load()
{
	float scaleFactor = 2.0f;
	StelPointF size = { 16.0f , 16.0f };
	float mult = scaleFactor * size.x;
	char* spriteSheet = "Assets/adv_lolo_map.png";
	char* spriteSheetMisc = "Assets/adv_lolo_misc.png";

	StelEntity* level  = Instantiate("Level");
	level->SetTransform(StelPointF::Zero(), size, scaleFactor, 0.0f);
	LevelManager* levelManager = level->AddComponent<LevelManager>();
	StelTileMap* map = level->AddComponent<StelTileMap>();
	map->Load("Assets/adv_lolo_map.png", { 16, 16 });
	TLayer nLayer = {
		{ -1,4,6,6,6,5,5,6,6,5,5,6,6,7,-1,-1},
		{-1,40,41,42,42,42,42,42,148,42,42,42, 42,43,-1,-1},
		{-1,40,36,37,37,37,37,37,1,37,37,73,73,79,-1,-1},
		{-1,40,36,73,73,37,1,1,1,37,37,73,73,79,-1,-1},
		{-1,40,0,73,73,37,37,37,1,37,37,37,73,79,-1,-1},
		{-1,40,0,1,73,73,37,37,1,37,37,37,73,79,-1,-1},
		{-1,40,0,1,1,1,37,37,1,37,37,73,1,79,-1,-1},
		{-1,40,0,1,1,1,1,1,1,1,37,1,1,79,-1,-1},
		{-1,40,0,1,1,1,1,1,1,1,1,1,1,79,-1,-1},
		{-1,40,0,73,73,1,1,1,1,73,73,1,1,79,-1,-1},
		{-1,40,72,73,73,73,1,1,1,73,73,73,1,79,-1,-1},
		{-1,40,72,73,73,73,1,1,1,1,73,73,1,79,-1,-1},
		{-1,76,36,73,73,37,110,1,1,1,1,1,1,79,-1,-1},
		{-1,76,36,37,37,37,37,37,1,1,1,1,1,79,-1,-1},
		{-1,112,113,114,114,113,114,113,113,113,113,113,113,115,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
	};
	map->AddLayer("level_1_map", nLayer, false);

	TLayer colliderLayer = {
		{-1,-1,-1,-1,-1,-1,-1,-1,200,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,200,-1,200,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,200,200,200,-1,200,-1,-1,-1,-1,-1,-1},
		{-1,200,200,200,-1,200,-1,-1,-1,200,-1,-1,-1,200,-1,-1},
		{-1,200,-1,200,200,200,200,200,-1,200,-1,-1,-1,200,-1,-1},
		{-1,200,-1,-1,200,200,200,200,-1,200,-1,200,200,200,-1,-1},
		{-1,200,-1,-1,-1,-1,200,200,-1,200,200,200,-1,200,-1,-1},
		{-1,200,-1,-1,-1,-1,-1,-1,-1,-1,200,-1,-1,200,-1,-1},
		{-1,200,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,200,-1,-1},
		{-1,200,-1,200,200,-1,-1,-1,-1,200,200,-1,-1,200,-1,-1},
		{-1,200,200,200,200,200,-1,-1,-1,200,200,200,-1,200,-1,-1},
		{-1,-1,-1,-1,-1,200,-1,-1,-1,-1,200,200,-1,200,-1,-1},
		{-1,-1,-1,-1,-1,200,-1,-1,-1,-1,-1,-1,-1,200,-1,-1},
		{-1,-1,-1,-1,-1,200,200,200,-1,-1,-1,-1,-1,200,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,200,200,200,200,200,200,200,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
	};
	map->AddLayer("level_1_collider", colliderLayer, true);
	map->DrawColliders = true;
	levelManager->Start(map);

	StelEntity* heart1 = Instantiate("Item1");
	heart1->SetTransform({ 6.0f * mult, 3.0f * mult }, size, scaleFactor, 0.0f);
	Collectable* c1 = heart1->AddComponent<Collectable>();
	c1->Start(spriteSheet, {1, 3});

	StelEntity* heart2 = Instantiate("Item2");
	heart2->SetTransform({ 12.0f * mult, 6.0f * mult }, size, scaleFactor, 0.0f);
	Collectable* c2 = heart2->AddComponent<Collectable>();
	c2->Start(spriteSheet, { 1, 3 });

	StelEntity* chestEnitty = Instantiate("Chest");
	chestEnitty->SetTransform({ 6.0f * mult, 12.0f * mult }, size, scaleFactor, 0.0f);
	Chest* chest = chestEnitty->AddComponent<Chest>();
	Collectable::OnItem.AddListener(chest);
	chest->Start(spriteSheet, 2);

	StelEntity* doorEntity = Instantiate("Door");
	doorEntity->SetTransform({ 8.0f * mult, 1.0f * mult }, size, scaleFactor, 0.0f);
	Door* door = doorEntity->AddComponent<Door>();
	door->Start(spriteSheet, "MainMenu");

	StelEntity* player = Instantiate("Player");
	player->SetTransform({ 6.0f * mult, 9.0f * mult }, size, scaleFactor, 0.0f);
	Player* playerControls = player->AddComponent<Player>();
	playerControls->Start(levelManager, m_Name);

	StelEntity* dragBox = Instantiate("Box");
	dragBox->SetTransform({ 6.0f * mult, 11.0f * mult }, size, scaleFactor, 0.0f);
	dragBox->AddComponent<Box>()->Start(levelManager);
	StelAtlas* boxModel = dragBox->AddComponent<StelAtlas>();
	boxModel->Init(spriteSheet);
	StelPointI sizeInt = StelPointI::FromFloat(size.x, size.y);
	boxModel->AddFrame({ 0, 3 * sizeInt.y,sizeInt.x, sizeInt.y });
	boxModel->SetFrame(0);
	boxModel->Start();

	StelEntity* greenWormEntity = Instantiate("Green Worm");
	greenWormEntity->SetTransform({ 12.0f * mult, 7.0f * mult }, size, scaleFactor, 0.0f);
	Enemy* greenWorm = greenWormEntity->AddComponent<Enemy>();
	greenWorm->Start(spriteSheetMisc, player);
	Box* greenWormBox = greenWormEntity->AddComponent<Box>();
	greenWormBox->SetDraggable(false);
	greenWormBox->Start(levelManager);

	
}

void GameSceneLevel1::OnClose()
{
	Chest::OnGetPearl.Clear();
	Chest::OnOpenChest.Clear();
	Collectable::OnItem.Clear();
	Stel::Engine::Get().GetPhysic().RemoveLayer(LAYER_NAME_PLAYER);
	Stel::Engine::Get().GetPhysic().RemoveLayer(LAYER_NAME_COLLIDABLE);
	Stel::Engine::Get().GetPhysic().RemoveLayer(LAYER_NAME_ENEMY);

}
