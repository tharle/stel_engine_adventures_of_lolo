#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#include "StelEngine.h"
#include "MainMenuScene.h"
#include "GameSceneLevel1.h"

#ifdef  _DEBUG
#include "vld.h"
#endif //  _DEBUG

MainMenuScene mainMenuScene = MainMenuScene();
GameSceneLevel1 gameSceneLevel1 = GameSceneLevel1("Game1");

void InitGameplay()
{

	Stel::Engine::Get().GetWorld().Register("MainMenu", &mainMenuScene);
	Stel::Engine::Get().GetWorld().Register("Game1", &gameSceneLevel1);
	Stel::Engine::Get().GetWorld().LoadScene("MainMenu");

}

INT WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ PSTR, _In_ INT)
{
	if (Stel::Engine::Get().Init("Legends of Stel", { 512, 512 }))
	{
		InitGameplay();
		Stel::Engine::Get().Start();
	}
	return 0;
}