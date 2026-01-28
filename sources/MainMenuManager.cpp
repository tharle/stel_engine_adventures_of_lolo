#include "MainMenuManager.h"

void MainMenuManager::Start()
{
	Audio().StopMusic();
	m_TitleFontId = Gfx().LoadFont("Assets/Fonts/Merlovaz.ttf", 26);
	m_DecrpFontId = Gfx().LoadFont("Assets/Fonts/Merlovaz.ttf", 14);

	size_t ambianceMusicId = Audio().LoadMusic("Assets/Audios/mainmenu.wav");
	if (ambianceMusicId == 0)  Log().Print(LOG_WARNING, "ERROR LOAD MUSIC");
	Audio().PlayMusic(ambianceMusicId);
}

void MainMenuManager::Update(float dt)
{
	if (m_ElapseTimeTouched > 0) m_ElapseTimeTouched -= dt;
	if (Input().IsKeyDown(IInput::Space) && m_ElapseTimeTouched <= 0)
	{
		Stel::Engine::Get().GetWorld().LoadScene("Game1");
		m_ElapseTimeTouched = 1.0f;
	}
}

void MainMenuManager::Draw()
{
	Gfx().FillRect({ 0.0f, 0.0f, 512.0f, 512.0f }, StelColor::BLUE);
	Gfx().FillRect({ 100.0f, 80.0f, 312.0f, 240.0f }, StelColor::BLACK);
	Gfx().DrawString("AVENTURE OF LOLO", m_TitleFontId, { 120.0f, 140.0f }, StelColor::AQUA);
	if (m_ElapseTimeTouched <= 0) Gfx().DrawString("- Press space to START - ", m_DecrpFontId, { 180.0f, 250.0f }, StelColor::AZURE);
}