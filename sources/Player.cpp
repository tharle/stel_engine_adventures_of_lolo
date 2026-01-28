#include "Player.h"
#include "StelAnimation.h"
#include "LevelManager.h"
#include "Chest.h"
#include "Projectil.h"


Player::~Player()
{
	Physic().Remove(m_EntityParent);
}

void Player::Start(LevelManager* currentLevel, std::string currentSceneName)
{
	StelComponent::Start();
	m_CurrentLevel = currentLevel;
	m_Foward = StelPointI::Down();
	m_IsAlive = true;
	m_CurrentScene = currentSceneName;

	// Load sounds and audios
	m_DieSfx = Audio().LoadSound("Assets/Audios/Die.wav");
	if (m_DieSfx == 0)   Log().Print(LOG_WARNING, "ERROR LOAD AUDIO");

	m_WalkSfx = Audio().LoadSound("Assets/Audios/sound_walk.wav");
	if (m_WalkSfx == 0)   Log().Print(LOG_WARNING, "ERROR LOAD AUDIO");

	m_ShootSfx = Audio().LoadSound("Assets/Audios/shoot.wav");
	if (m_ShootSfx == 0)   Log().Print(LOG_WARNING, "ERROR LOAD AUDIO");

	// Load Fonts
	m_TitleFontId = Gfx().LoadFont("Assets/Fonts/Merlovaz.ttf", 30);
	m_DecrpFontId = Gfx().LoadFont("Assets/Fonts/Merlovaz.ttf", 14);
	
	// Animation
	m_Model = m_EntityParent->AddComponent<StelAnimation>();
	m_Model->Init("Assets/adv_lolo_char.png");
	m_Model->Start();
	m_Model->AddAnimationFrames(5, { 0, 0 }, { 16, 16 });
	m_Model->AddAnimationFrames(5, { 0, 1 }, { 16, 16 });
	m_Model->AddAnimationFrames(5, { 0, 2 }, { 16, 16 });
	m_Model->AddAnimationFrames(5, { 0, 3 }, { 16, 16 });
	m_Model->AddAnimationFrames(4, { 0, 4 }, { 16, 16 });
	m_Model->AddAnimationFrames(4, { 0, 5 }, { 16, 16 });

	m_Model->AddClip(ANIMATION_PLAYER_DOWN, 0, 5, 0.02f);
	m_Model->AddClip(ANIMATION_PLAYER_LEFT, 5, 5, 0.02f);
	m_Model->AddClip(ANIMATION_PLAYER_UP, 10, 5, 0.02f);
	m_Model->AddClip(ANIMATION_PLAYER_RIGHT, 15, 5, 0.02f);

	m_Model->AddClip(ANIMATION_PLAYER_DIE, 20, 4, 0.2f);
	m_Model->AddClip(ANIMATION_PLAYER_VICTORY, 24, 4, 0.2f);
	

	// COLLIDER
	float offset = 4.0f;
	m_Collider = { -offset,-offset, - offset , - offset };
	Physic().AddToLayer(LAYER_NAME_PLAYER, m_EntityParent);
}


void Player::Update(float dt) 
{
	if (!m_IsAlive) 
	{
		m_ElapseTimeDie += dt;

		if(m_ElapseTimeDie >= DELAY_TO_DIE) World().LoadScene(m_CurrentScene);

		return;
	}

	Move(dt);
	InputEvents(dt);
}

void Player::Draw()
{
	Gfx().DrawString("Move = WASD        - Try Again = Shift      -      J = Shoot", m_DecrpFontId, { 120.0f, 490.0f }, StelColor::AQUA);
}

void Player::Die()
{
	m_IsAlive = false;
	m_ElapseTimeDie = 0;
	m_Model->Play(ANIMATION_PLAYER_DIE, false);
}

void Player::Move(float dt)
{
	// In the original game, if you press up/down, will ignore left or right
	float axiosV = Input().GetAxiosVertical();
	float axiosH = axiosV == 0? Input().GetAxiosHorizontal() : 0; 

	if (axiosH == 0 && axiosV == 0)
	{
		m_Model->Stop();
		return;
	}


	StelTransform transform = GetTransform();
	StelPointF position = transform.Position;
	position.x += axiosH * dt * m_Speed * GetTransform().GetTrueRect().h;
	position.y += axiosV * dt * m_Speed * GetTransform().GetTrueRect().h;

	StelRectF collider = {
		position.x - m_Collider.x,
		position.y - m_Collider.y,
		GetTransform().Size.x + m_Collider.x,
		GetTransform().Size.y + m_Collider.y
	};

	// Colling with tile
	if (!m_CurrentLevel->IsColliding(collider.Resize(GetTransform().Scale)))
	{
		transform.Position = position;
		SetTransform(transform);
	}
	

	// Animation	
	if (m_CooldownWalkSound <= 0)
	{
		m_CooldownWalkSound = COOLDOWN_WALK_SOUND;
		Audio().PlaySFX(m_WalkSfx);
	}
	else m_CooldownWalkSound -= dt;
		
	if (axiosV > 0) 
	{
		m_Model->Play(ANIMATION_PLAYER_DOWN, true);
		m_Foward = StelPointI::Down();
	}
	else if (axiosV < 0) 
	{
		m_Model->Play(ANIMATION_PLAYER_UP, true);
		m_Foward = StelPointI::Up();
	}
	else if (axiosH < 0)
	{
		m_Model->Play(ANIMATION_PLAYER_LEFT, true);
		m_Foward = StelPointI::Left();
		
	}
	else if (axiosH > 0) 
	{
		m_Model->Play(ANIMATION_PLAYER_RIGHT, true);
		m_Foward = StelPointI::Right();
	} 
	
}

void Player::InputEvents(float dt)
{
	// QUIT
	IEvents::StelEvent stelEvent;
	if(Events().Contanis(IEvents::Quit, stelEvent))
	{
		World().ExitGame();
	}

	// DIE
	if (Input().IsKeyDown(IInput::LShift) || Input().IsKeyDown(IInput::RShift)) 
	{
		Die();
		Audio().PlaySFX(m_DieSfx);
	}


	// HIT
	if (m_CooldownFire > 0) m_CooldownFire -= dt;
	if (m_CooldownFire <= 0 && Input().IsKeyDown(IInput::J))
	{
		m_CooldownFire = BULLET_PER_SECOND;

		StelRectF collider = GetTransform().GetTrueRect();
		StelEntity* projectilEntity = World().CreateLater("Projectil");
		projectilEntity->SetTransform(GetTransform());
		Projectil* projectil = projectilEntity->AddComponent<Projectil>();
	
		projectil->Start(m_Foward);
		Audio().PlaySFX(m_ShootSfx);
	}
}
