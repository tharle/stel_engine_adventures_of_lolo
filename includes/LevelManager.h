#pragma once
#include "StelComponent.h"
#include "StelTileMap.h"

#define COOLDOWN_CHANGE_SCENE 1.0f
#define COOLDOWN_WALK_SOUND 0.2f


// Class for manager of all levels in game
class LevelManager : public StelComponent, public IUpdatable, public IDrawable{
private:
	StelTileMap* m_Background = nullptr;

	// Delay for keydown
	float m_CooldownChangeScene = COOLDOWN_CHANGE_SCENE;

	// Audio
	size_t m_AmbianceMusic = 0;
public:
	LevelManager(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~LevelManager() = default;
	virtual void Start(StelTileMap* tileMap);
	virtual void Update(float dt) override;
	virtual void Draw() override;

	bool IsColliding(StelRectF boxCollider);
	void ChangeScene(float dt);
};