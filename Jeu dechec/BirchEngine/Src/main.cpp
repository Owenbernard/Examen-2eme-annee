#include "SDL.h"
#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{

	//fps
	const int FPS = 60;
	//limite par seconde
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	//creation d'un jeu
	game = new Game();
	//mise en place de la fenetre de jeu,x,y,fullscreen
	game->init("GameWindow", 800, 640, false);

	while (game->running())
	{

		//limiteur
		frameStart = SDL_GetTicks();

		//event 
		game->handleEvents();
		//reaffichage
		game->update();
		//affichage
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;
}