#pragma once

#define ENEMY_STATE_IDLE "IDLE" 
#define ENEMY_STATE_ATTACK "ATTACK"
#define ENEMY_STATE_SLEEP "SLEEP" 
#define ENEMY_STATE_FROZEN "FROZEN"
#define ENEMY_STATE_DEAD "DEAD"

class Enemy;


// Classe abastract base for all enemys states
class AEnemyState {
protected:
	Enemy* m_Enemy;
public:
	AEnemyState(Enemy* parent) : m_Enemy(parent){}
	virtual ~AEnemyState() = default;

	virtual void OnEnter() = 0;
	virtual void Execute(float dt) = 0;
	virtual void OnExit() = 0;
};