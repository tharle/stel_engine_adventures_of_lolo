#pragma once
#include "StelComponent.h"
#include "Player.h"

#define OFFSET_SHIFT 10.0f
#define OFFSET_COLLIDER 4.0f

class StelAtlas;
class LevelManager;


// Box draggable, can be "egg" from enemy
class Box : public StelComponent, public IUpdatable {
private:
	StelAtlas* m_Model = nullptr;
	LevelManager* m_CurrentLevel = nullptr;
	StelRectF m_Collider = StelRectF::Zero(); // only for Tilemaps
	bool m_IsDraggable = true;
	float m_Speed = PLAYER_SPEED;

	void MoveAndDrag(float dt);
	bool CanDragBox(StelPointF position, StelPointI direction);
public:
	Box(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~Box() = default;

	virtual void Start(LevelManager* currentLevel);
	virtual void Update(float dt) override;

	void SetDraggable(bool value) { m_IsDraggable = value; }
};