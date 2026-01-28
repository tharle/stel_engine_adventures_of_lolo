#pragma once
#include "StelComponent.h"
#include "StelObserver.h"
#include "AEnemyState.h"
#include "StelAnimation.h"
#include "Chest.h"

#define LAYER_NAME_ENEMY "ENEMY"

#define ENEMY_ANIMATION_FRAME_DEAD 0
#define ENEMY_ANIMATION_FRAME_FROZEN_0 1
#define ENEMY_ANIMATION_FRAME_FROZEN_1 2

#define DELAY_STUNNED 2.0f


class AEnemyState;
class StelAnimation;

// Classe base for enemys
class Enemy : public StelComponent, public IUpdatable {
private:
	StelEntity* m_Player = nullptr;
	AEnemyState* m_CurrentState = nullptr;
	std::map<std::string, AEnemyState*> m_States;
	StelAnimation* m_Model = nullptr;
	bool m_IsChestOpen = false;
	bool m_IsAlive = true;
	int m_Damage = 0;

public:
	Enemy(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~Enemy();

	virtual void Update(float dt) override;
	virtual void Destroy() override;
	virtual void Start(std::string spriteSheet, StelEntity* player);
	virtual void ChangeState(const std::string& state);

	inline bool IsActive() { return m_IsAlive; }
	inline void SetAlive(bool value) { m_IsAlive = value; }
	inline StelAnimation& GetAnimation() { return *m_Model; }

	StelPointF GetDiffPlayer();
	bool IsCurrentState(AEnemyState* state);
	void TakeHit();
	void GotHeal();
	void SetBoxDrag(bool value);
};

// First State of ennemy
class EnemyStateIdle : public AEnemyState, public StelObserver<int>
{
private:
	bool m_StayIdle = true;
public:
	EnemyStateIdle(Enemy* parent) : AEnemyState(parent) {};
	virtual ~EnemyStateIdle() 
	{
		Chest::OnOpenChest.RemoveListener(this);
	};

	virtual void OnEnter() override
	{
		if (m_StayIdle) 
		{
			Chest::OnOpenChest.AddListener(this);
			m_Enemy->GetAnimation().SetFrame(3);
		}
		else {
			m_Enemy->ChangeState(ENEMY_STATE_ATTACK);
		}
		
	};
	
	virtual void Execute(float dt) 
	{
		StelPointF diff = m_Enemy->GetDiffPlayer();
		StelRectF collider = m_Enemy->GetTransform().GetTrueRect();

		if (diff.x < 0 && abs(diff.x) > collider.w) m_Enemy->GetAnimation().SetFrame(3);
		else if (diff.x <= 0 && abs(diff.x) <= collider.w) m_Enemy->GetAnimation().SetFrame(4);
		else if (diff.x >= 0 && abs(diff.x) <= collider.w) m_Enemy->GetAnimation().SetFrame(5);
		else if (diff.x > 0 && abs(diff.x) > collider.w) m_Enemy->GetAnimation().SetFrame(6);
	};

	virtual void OnExit() 
	{
	};

	virtual void OnNotify(const int& eventId)
	{
		if (eventId == EVENT_OPEN_CHEST_ID)
		{
			m_Enemy->ChangeState(ENEMY_STATE_ATTACK);
			m_StayIdle = false;
		}
	};

	virtual bool IsActive() { return m_Enemy->IsCurrentState(this); }
};


// STATE after get all collectable but before get the pearl
class EnemyStateAttack : public AEnemyState, public StelObserver<int>
{
public:
	EnemyStateAttack(Enemy* parent) : AEnemyState(parent) {};
	virtual ~EnemyStateAttack() 
	{
		Chest::OnGetPearl.RemoveListener(this);
	};

	virtual void OnEnter() override
	{
		Chest::OnGetPearl.AddListener(this);
		m_Enemy->GetAnimation().Play(ENEMY_STATE_ATTACK, true);
	};

	virtual void Execute(float dt)
	{
	};

	virtual void OnExit()
	{
	};

	virtual void OnNotify(const int& eventId)
	{
		if (eventId == EVENT_GET_PEARL_ID)
		{
			m_Enemy->ChangeState(ENEMY_STATE_DEAD);
		}
	};

	virtual bool IsActive() { return m_Enemy->IsCurrentState(this); }
};


// STATE "EGG"
class EnemyStateFrozen: public AEnemyState
{
private:
	float m_ElapsedTime = 0.0f;
	bool m_IsStartBroken = false;
public:
	EnemyStateFrozen(Enemy* parent) : AEnemyState(parent) {};
	virtual ~EnemyStateFrozen() = default;

	virtual void OnEnter() override
	{
		m_ElapsedTime = 0.0f;
		m_IsStartBroken = false;
		m_Enemy->GetAnimation().Stop();
		m_Enemy->GetAnimation().SetFrame(ENEMY_ANIMATION_FRAME_FROZEN_0);
		m_Enemy->SetBoxDrag(true);
	};

	virtual void Execute(float dt)
	{
		m_ElapsedTime += dt;

		if (m_ElapsedTime >= DELAY_STUNNED && !m_IsStartBroken)
		{
			m_IsStartBroken = true;
			m_Enemy->GetAnimation().SetFrame(ENEMY_ANIMATION_FRAME_FROZEN_1);
			m_ElapsedTime = 0;
		}else if (m_ElapsedTime >= DELAY_STUNNED) 
		{
			m_Enemy->ChangeState(ENEMY_STATE_IDLE);
		}
	};

	virtual void OnExit()
	{
		m_Enemy->GotHeal();
		m_Enemy->SetBoxDrag(false);
	};
};

// State of before true delete enemy
class EnemyStateDead: public AEnemyState
{
private:
	float m_ElapsedTime = 0.0f;
public:
	EnemyStateDead(Enemy* parent) : AEnemyState(parent) {};
	virtual ~EnemyStateDead() = default;

	virtual void OnEnter() override
	{
		m_ElapsedTime = 0;
		m_Enemy->GetAnimation().Stop();
		m_Enemy->GetAnimation().SetFrame(ENEMY_ANIMATION_FRAME_DEAD);
		m_Enemy->SetAlive(false);
		m_Enemy->Destroy();
	};

	virtual void Execute(float dt)
	{
		
	};

	virtual void OnExit()
	{
	};
};