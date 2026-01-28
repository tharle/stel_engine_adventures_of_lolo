#pragma once
#include "StelComponent.h"
#include "StelObserver.h"
#include "StelSubject.h"

#define EVENT_OPEN_CHEST_ID 0
#define EVENT_GET_PEARL_ID 1

class StelAtlas;


// Trigger to open the door, it will be open after get all collectables in level
class Chest : public StelComponent, public IUpdatable, public StelObserver<bool>
{
private:
	StelAtlas* m_Model = nullptr;
	int m_CountHeartsTakes = 0;
	int m_ChestAmount = 0;

public:
	Chest(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~Chest() = default;

	virtual void Start(char* spriteSheet, int chestAmount);
	virtual void Update(float dt) override;
	virtual void OnNotify(const bool& value) override;

	bool IsOpen();

	static StelSubject<int> OnOpenChest;
	static StelSubject<int> OnGetPearl;
};