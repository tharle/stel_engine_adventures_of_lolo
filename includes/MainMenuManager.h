#pragma once
#include "StelComponent.h"
#include "StelEngine.h"

// Manager for print main menu
class MainMenuManager : public StelComponent, public IDrawable, public IUpdatable 
{
public:
	MainMenuManager(StelEntity* parent) : StelComponent(parent) { };
	virtual ~MainMenuManager() = default;
	virtual void Start() override;
	virtual void Update(float dt) override;
	virtual void Draw() override;
private:

	//Fonts Loadeds
	size_t m_TitleFontId = 0;
	size_t m_DecrpFontId = 0;
	float m_ElapseTimeTouched = 1.0f;
};