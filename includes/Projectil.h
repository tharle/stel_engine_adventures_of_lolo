#pragma once
#include "StelComponent.h"
#define PROJECTIL_SPEED 10.0f

#define PROJECTIL_SPRITE_SOUTH 0
#define PROJECTIL_SPRITE_WEST 1
#define PROJECTIL_SPRITE_NORTH 2
#define PROJECTIL_SPRITE_EAST 3

class StelAtlas;

// Projectil for kill enemies
class Projectil : public StelComponent, public IUpdatable {
private:
	StelAtlas* m_Model = nullptr;
	float m_Speed = PROJECTIL_SPEED;
	bool m_IsPlayerOwner = true;
	StelPointI m_Direction = StelPointI::Zero();
	StelRectF m_Limits = StelRectF::Zero();
public:
	Projectil(StelEntity* parent) : StelComponent(parent) {};
	virtual ~Projectil() = default;
	virtual void Start(StelPointI direction, bool isPlayerOwner = true, float speed = PROJECTIL_SPEED);
	virtual void Update(float dt);
	Projectil* Clone();
};