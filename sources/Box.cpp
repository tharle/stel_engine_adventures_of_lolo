#include "Box.h"
#include "StelAtlas.h"
#include "Player.h"
#include "LevelManager.h"


void Box::Start(LevelManager* currentLevel)
{
	StelComponent::Start();

	m_CurrentLevel = currentLevel;

	float offset = OFFSET_COLLIDER;
	m_Collider = { -offset,-offset, -offset , -offset };

	Physic().AddToLayer(LAYER_NAME_COLLIDABLE, m_EntityParent);
}

void Box::Update(float dt)
{
	MoveAndDrag(dt);
}


void Box::MoveAndDrag(float dt)
{
	// Nullpointer after change scene(player was destroyed but box try to find him
	// This why I try need to use "reference" of player and not other from colision
	StelEntity* other = Physic().CollideWithLayer(m_EntityParent, LAYER_NAME_PLAYER);
	if (other) 
	{	
		int axiosV = static_cast<int>(Input().GetAxiosVertical());
		int axiosH = axiosV == 0 ? static_cast<int>(Input().GetAxiosHorizontal()) : 0;
		StelPointI direction = { axiosH, axiosV };

		StelPointF diff = GetTransform().Position.Diff(other->GetTransform().Position);

		// Check if player is moving the box in the good direction 
		if ((diff.x > 0 && direction.x > 0)
			|| (diff.x < 0 && direction.x < 0)
			|| (diff.y > 0 && direction.y > 0)
			|| (diff.y < 0 && direction.y < 0))
		{
			// DRAG
			StelTransform transform = GetTransform();
			StelPointF position = transform.Position;
			position.x += direction.x * dt * m_Speed * GetTransform().GetTrueRect().w + (OFFSET_SHIFT * direction.x);
			position.y += direction.y * dt * m_Speed * GetTransform().GetTrueRect().h + (OFFSET_SHIFT * direction.y);

			// Check colling with tile 
			if (CanDragBox(position, direction))
			{
				// Confirm translade
				transform.Position = position;
				SetTransform(transform);
			}
			else
			{
				// Make the player be in before position
				StelPointF knockBack = transform.Position.Diff(position);
				knockBack.x += (OFFSET_SHIFT * axiosH);
				knockBack.y += (OFFSET_SHIFT * axiosV);
				other->SetTransform(other->GetTransform().Translate(knockBack));

			}
		}
	}
}

bool Box::CanDragBox(StelPointF position, StelPointI direction) {

	if (!m_IsDraggable) return false;

	StelEntity* other = Physic().CollideWithLayer(m_EntityParent, LAYER_NAME_COLLIDABLE);
	

	// In my version of game, if the box touch other "Collidable" (ennemy or other box) will be stuck
	if (other) {
		return false;
	}

	StelRectF collider = {
				position.x - m_Collider.x,
				position.y - m_Collider.y,
				GetTransform().Size.x + m_Collider.x,
				GetTransform().Size.y + m_Collider.y
	};
	return !m_CurrentLevel->IsColliding(collider.Resize(GetTransform().Scale));
}
