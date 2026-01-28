#include "Enemy.h"
#include "StelAnimation.h"
#include "Chest.h"
#include "Box.h"


void Enemy::Start(std::string spriteSheet, StelEntity* player)
{
	StelComponent::Start();
	m_Player = player;

	StelPointI size = StelPointI::FromFloat(GetTransform().Size.x, GetTransform().Size.y);
	
	// Animation
	m_Model = m_EntityParent->AddComponent<StelAnimation>();
	m_Model->Init(spriteSheet);
	m_Model->Start();
	//Die
	m_Model->AddAnimationFrames(1, { 0, 8 }, { size.x, size.y });
	m_Model->AddAnimationFrames(1, { 0, 4 }, { size.x, size.y });
	m_Model->AddAnimationFrames(1, { 1, 4 }, { size.x, size.y });
	m_Model->AddAnimationFrames(4, { 0, 6 }, { size.x, size .y});
	m_Model->AddAnimationFrames(1, { 3, 6 }, { size.x, size.y });
	m_Model->AddAnimationFrames(1, { 2, 6 }, { size.x, size.y });
	m_Model->AddAnimationFrames(1, { 1, 6 }, { size.x, size.y });

	m_Model->AddClip(ENEMY_STATE_IDLE, 3, 1, 0.0f);
	m_Model->AddClip(ENEMY_STATE_ATTACK, 3, 7, 0.1f);

	m_Model->Play(ENEMY_STATE_IDLE, false);

	// States
	m_States.emplace(ENEMY_STATE_IDLE, new EnemyStateIdle(this));
	m_States.emplace(ENEMY_STATE_ATTACK, new EnemyStateAttack(this));
	m_States.emplace(ENEMY_STATE_DEAD, new EnemyStateDead(this));
	m_States.emplace(ENEMY_STATE_FROZEN, new EnemyStateFrozen(this));

	ChangeState(ENEMY_STATE_IDLE);

	Physic().AddToLayer(LAYER_NAME_ENEMY, m_EntityParent);

}

void Enemy::ChangeState(const std::string& state)
{
	if (m_States.count(state) <= 0) return;

	if (m_CurrentState) m_CurrentState->OnExit();

	m_CurrentState = m_States[state];
	m_CurrentState->OnEnter();
}

Enemy::~Enemy()
{
	for (auto state : m_States) { 
		delete state.second; 
	}
	m_States.clear();
}

void Enemy::Update(float dt)
{
	if(m_CurrentState != nullptr) m_CurrentState->Execute(dt);
}

void Enemy::Destroy()
{
	m_EntityParent->Destroy();
}

StelPointF Enemy::GetDiffPlayer()
{
	StelPointF playerPos = m_Player->GetTransform().Position;
	StelPointF diff = playerPos.Diff(GetTransform().Position);

	return diff;
}

bool Enemy::IsCurrentState(AEnemyState* state)
{
	return m_CurrentState == state;
}

void Enemy::TakeHit()
{
	if (!this) return;

	m_Damage++;

	if (m_Damage <= 1) ChangeState(ENEMY_STATE_FROZEN);
	else ChangeState(ENEMY_STATE_DEAD);
}

void Enemy::GotHeal()
{
	m_Damage = 0;
}

void Enemy::SetBoxDrag(bool value)
{
	m_EntityParent->GetComponent<Box>()->SetDraggable(value);
}
