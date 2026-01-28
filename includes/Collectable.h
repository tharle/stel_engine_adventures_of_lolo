#pragma once
#include "StelComponent.h"
#include "StelSubject.h"
//#include <string>

class StelAtlas;


// All collectables from level
class Collectable : public StelComponent, public IUpdatable {
private:
	StelAtlas* m_Model = nullptr;
public:
	Collectable(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~Collectable() = default;

	virtual void Start(char* spriteSheet, StelPointI frame);
	virtual void Update(float dt) override;

	static StelSubject<bool> OnItem;
};

