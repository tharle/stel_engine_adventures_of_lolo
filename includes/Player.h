#pragma once
#include "StelComponent.h"
#include "StelObserver.h"

#define LAYER_NAME_PLAYER "PLAYER"

#define ANIMATION_PLAYER_DOWN "walk_down"
#define ANIMATION_PLAYER_LEFT "walk_left"
#define ANIMATION_PLAYER_UP "walk_up"
#define ANIMATION_PLAYER_RIGHT "walk_right"
#define ANIMATION_PLAYER_DIE "die"
#define ANIMATION_PLAYER_VICTORY "victory"

#define PLAYER_SPEED 5.0f
#define BULLET_PER_SECOND 0.5f

#define DELAY_TO_DIE 1.5f

class StelAnimation;
class LevelManager;


// All controls and logic for player
class Player : public StelComponent, public IUpdatable, public IDrawable
{
public:
	Player(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~Player();
	virtual void Start(LevelManager* currentLevel, std::string currentSceneName);
	virtual void Update(float dt) override;
	virtual void Draw() override;
	
	inline float GetSpeed() { return m_Speed; }
	void Die();
private:
	// Physics
	StelRectF m_Collider = StelRectF::Zero(); // only for Tilemaps
	float m_Speed = PLAYER_SPEED;
	float m_CooldownFire = 0;
	StelPointI m_Foward = StelPointI::Down();
	bool m_IsAlive = true;
	float m_ElapseTimeDie = 0;

	// Animation
	StelAnimation* m_Model = nullptr;
	int m_CurrentFrame = 0;
	int m_MaxFrame = 0;

	// Audio
	size_t m_DieSfx = 0;
	size_t m_ShootSfx = 0;
	size_t m_WalkSfx = 0;
	float m_CooldownWalkSound = 0.0f;

	//Fonts Loadeds
	size_t m_TitleFontId = 0;
	size_t m_DecrpFontId = 0;

	// Level
	LevelManager* m_CurrentLevel = nullptr;

	// Scene
	std::string m_CurrentScene = "";


	void Move(float dt);
	void InputEvents(float dt);
};