#include "core/engine.h"
#include "scenes/scene01.h"
#include "scenes/scene02.h"
#include "scenes/scene03.h"
#include "scenes/scene04.h"
#include "Scenes/scene05.h"
#include "Scenes/scene06.h"
#include "Scenes/scene07.h"

int main(int argc, char** argv)
{
	int result = SDL_Init(SDL_INIT_VIDEO);
	if (result != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
	}
	
	Engine engine;
	engine.Initialize();
	engine.Get<FileSystem>()->SetPathname("resources\\");

	Scene* scene = new Scene07(&engine);
	scene->Initialize();

	while (!engine.ForceQuit())
	{
		engine.Update();
		scene->Update();

		scene->Render();
	}
	scene->Shutdown();
	engine.Shutdown();

	return 0;
}
