#include "Projectil.h"
#include "StelAtlas.h"
#include "Enemy.h"
#include "Player.h"

void Projectil::Start(StelPointI direction, bool isPlayerOwner, float speed)
{
	StelComponent::Start();

	m_Direction = direction;
	m_Speed = speed;
	m_IsPlayerOwner = isPlayerOwner;
	
	/*StelTransform transform = GetTransform();
	transform.Position = startPos;
	SetTransform(transform);*/

	m_Model = m_EntityParent->AddComponent<StelAtlas>();
	m_Model->Init("Assets/adv_lolo_misc.png");
	StelPointI size = StelPointI::FromFloat(GetTransform().Size.x, GetTransform().Size.y);
	m_Model->AddFrame({ 0 * size.x, 3 * size.y, size.x, size.y }); // PROJECTIL_SPRITE_EAST
	m_Model->AddFrame({ 1 * size.x, 3 * size.y, size.x, size.y }); // PROJECTIL_SPRITE_WEST
	m_Model->AddFrame({ 2 * size.x, 3 * size.y, size.x, size.y }); // PROJECTIL_SPRITE_SOUTH
	m_Model->AddFrame({ 3 * size.x, 3 * size.y, size.x, size.y }); // PROJECTIL_SPRITE_NORTH

	m_Limits = GetTransform().GetTrueRect();
	m_Limits.x = 1.0f * m_Limits.w;
	m_Limits.y = 1.0f * m_Limits.h;
	m_Limits.w *= 13.0f;
	m_Limits.h *= 13.0f;


	if(direction.x > 0) m_Model->SetFrame(PROJECTIL_SPRITE_EAST);
	else if(direction.x < 0) m_Model->SetFrame(PROJECTIL_SPRITE_WEST);
	else if(direction.y > 0) m_Model->SetFrame(PROJECTIL_SPRITE_SOUTH);
	else m_Model->SetFrame(PROJECTIL_SPRITE_NORTH);

	m_Model->Start();
}

void Projectil::Update(float dt)
{
	StelPointF position = GetTransform().Position;

	position.x += m_Direction.x * m_Speed * dt * GetTransform().GetTrueRect().w;
	position.y += m_Direction.y * m_Speed * dt * GetTransform().GetTrueRect().h;

	SetPosition(position);

	if (m_IsPlayerOwner) 
	{
		StelEntity* other = Physic().CollideWithLayer(m_EntityParent, LAYER_NAME_ENEMY);
		if (other)
		{
			Enemy* enemy = other->GetComponent<Enemy>();
			enemy->TakeHit();
			m_EntityParent->Destroy();
			return;
		}
	}
	else 
	{
		StelEntity* other = Physic().CollideWithLayer(m_EntityParent, LAYER_NAME_PLAYER);
		if (other)
		{
			Player* player = other->GetComponent<Player>();
			player->Die();
			m_EntityParent->Destroy();
			return;
		}
	}

	if (position.x < m_Limits.x || position.x > m_Limits.w || position.y < m_Limits.y || position.y > m_Limits.h) m_EntityParent->Destroy();
	
}

Projectil* Projectil::Clone()
{
	return nullptr;
}
