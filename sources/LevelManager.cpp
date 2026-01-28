#include "LevelManager.h"

void LevelManager::Start(StelTileMap* tileMap)
{
    m_Background = tileMap;

    // Load sounds and audios
    m_AmbianceMusic = Audio().LoadMusic("Assets/Audios/bgm.wav");
    if (m_AmbianceMusic == 0)  Log().Print(LOG_WARNING, "ERROR LOAD MUSIC");
    Audio().PlayMusic(m_AmbianceMusic);
}

void LevelManager::Update(float dt)
{
    ChangeScene(dt);
}

void LevelManager::ChangeScene(float dt)
{
    if (m_CooldownChangeScene > 0) m_CooldownChangeScene -= dt;
    if (Input().IsKeyDown(IInput::Space) && m_CooldownChangeScene <= 0)
    {
        World().LoadScene("MainMenu");

        Log().Print(LOG_INFO, "SPACE WAS PRESSED");
        m_CooldownChangeScene = COOLDOWN_CHANGE_SCENE;
    }
}

void LevelManager::Draw()
{
	//m_Background.Draw();
}

bool LevelManager::IsColliding(StelRectF boxCollider)
{
    int tileIndex;
    return m_Background->IsColliding(boxCollider, &tileIndex);
}
