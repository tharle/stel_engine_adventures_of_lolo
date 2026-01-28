#pragma once
#include "StelComponent.h"
#include "StelObserver.h"
#include <string>

class StelAtlas;


// The portal for go to another level
class Door : public StelComponent, public IUpdatable, public StelObserver<int>
{
private:
	StelAtlas* m_Model = nullptr;
	bool m_IsOpen = false;
	std::string m_NextScene = "";
public:
	Door(StelEntity* parent) : StelComponent(parent) {  }
	virtual ~Door();

	virtual void Start(std::string spriteSheet, std::string nextSceneName);
	virtual void Update(float dt) override;

	virtual void OnNotify(const int& idEvent) override;
};