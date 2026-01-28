#include "Chest.h"
#include "StelAtlas.h"
#include "Player.h"

// Subjects
StelSubject<int> Chest::OnOpenChest;
StelSubject<int> Chest::OnGetPearl;

void Chest::Start(char* spriteSheet, int chestAmount)
{
	StelComponent::Start();

	m_Model = m_EntityParent->AddComponent<StelAtlas>();
	m_ChestAmount = chestAmount;
	m_Model->Init(spriteSheet);
	StelPointI size = StelPointI::FromFloat(m_EntityParent->GetTransform().Size.x, m_EntityParent->GetTransform().Size.y);
	m_Model->AddFrame({ 2 * size.x, 3 * size.y, size.x, size.y });
	m_Model->AddFrame({ 3 * size.x, 2 * size.y, size.x, size.y });
	m_Model->AddFrame({ 3 * size.x, 3 * size.y, size.x, size.y });
	m_Model->SetFrame(0);
	m_Model->Start();
}

void Chest::Update(float dt)
{
	if (!IsOpen()) return;

	if (Physic().CollideWithLayer(m_EntityParent, LAYER_NAME_PLAYER) != nullptr)
	{
		m_Model->SetFrame(2);
		Chest::OnGetPearl.Invoke(EVENT_GET_PEARL_ID);
	}
	
}

bool Chest::IsOpen() {
	return m_CountHeartsTakes >= m_ChestAmount;
}

void Chest::OnNotify(const bool& value)
{
	if(value) m_CountHeartsTakes++;

	if (IsOpen()) 
	{
		m_Model->SetFrame(1);
		Chest::OnOpenChest.Invoke(EVENT_OPEN_CHEST_ID);
	} 
}
