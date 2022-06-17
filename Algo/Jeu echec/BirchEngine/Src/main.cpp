#include "librarie.h"
#include <iostream>


typedef struct coord coord;
struct coord {
	int x;
	int y;
};


void update(float  deltaTime) {

}


int main(int argc, char* argv[])
{
	bool quit = false;

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart = SDL_GetTicks();
	int frameTime = 0;
	float deltaTime;


	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	SDL_Window* window = NULL;
	window = SDL_CreateWindow("Jeu d'echecs", 100, 100, 1024, 720, SDL_WINDOW_SHOWN);


	if (window == NULL) {
		std::cout << "fenetre non creer" << std::endl;
		return 0;
	}

	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
	SDL_Event* mainEvent = new SDL_Event();

	/*
	//affichage des cases
	char* TabLettre[26] = { "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z" };
	const char* text = "ananas";
	TTF_Font* Sans = TTF_OpenFont("BEECH___.TTF", 24);
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(Sans, text, { 0,0,0 });
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect = { 30,30,surfaceMessage->w,surfaceMessage->h };
	SDL_FreeSurface(surfaceMessage);
	TTF_CloseFont(Sans);

	*/


	//sert a changer la taille du damier
	const int larg = 8;
	//taille des tableaux
	const int dimension = 8;
	//taille du damier
	int taille = (720 - 20) / dimension;
	bool toggle = false;
	//pos des images
	char* pieceTab[2][6] = { {"./images/blackPawn.png", "./images/blackKing.png" , "./images/blackQueen.png" , "./images/blackBishop.png" , "./images/blackKnight.png" , "./images/blackRook.png"},
							{"./images/whitePawn.png", "./images/whiteKing.png" , "./images/whiteQueen.png" , "./images/whiteBishop.png" , "./images/whiteKnight.png" , "./images/whiteRook.png"} };
	coord Echequier[dimension][dimension] = 
	{
		NULL
	};
	//posiotion des pieces
	int Piece[dimension][dimension] = 
	{	{5,4,3,2,1,3,4,5},
		{0,0,0,0,0,0,0,0},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{6,6,6,6,6,6,6,6},
		{11,10,9,8,7,9,10,11},
	};



	while (!quit && mainEvent->type!=SDL_QUIT)
	{

		//limiteur
		deltaTime = SDL_GetTicks() - frameStart;
		frameStart = SDL_GetTicks();
		update(float(deltaTime) / 1000.0);


		SDL_PollEvent(mainEvent);
		SDL_RenderClear(renderer);


		//affichage damier
		for (int i = 0; i < larg; ++i)	{
			for (int j = 0; j < larg; ++j)	{
				SDL_Texture* Sol = NULL;
				if (toggle) {
					Sol = IMG_LoadTexture(renderer, "./images/black.png");
					toggle = !toggle;
				}
				else {
					Sol = IMG_LoadTexture(renderer, "./images/white.png");
					toggle = !toggle;
				}

				SDL_Rect Sol_rect;
				Sol_rect.x = j * taille;
				Sol_rect.y = i * taille;
				Sol_rect.w = taille;
				Sol_rect.h = taille;

				SDL_RenderCopy(renderer, Sol, NULL, &Sol_rect);
				//SDL_RenderCopy(renderer, surfaceMessage, NULL, &Message_rect);

			}
			toggle = !toggle;
		}
		
		//affichage des pieces
		for (int i = 0; i < larg; ++i) {
			for (int j = 0; j < larg; ++j) {

				char* pieceActive = "./images/none.bmp";

				switch (Piece[i][j])
				{
				case 0 :
					pieceActive = pieceTab[0][0];
				break;
				case 1:
					pieceActive = pieceTab[0][1];
					break;
				case 2:
					pieceActive = pieceTab[0][2];
					break;
				case 3:
					pieceActive = pieceTab[0][3];
					break;
				case 4:
					pieceActive = pieceTab[0][4];
					break;
				case 5:
					pieceActive = pieceTab[0][5];
					break;
				case 6:
					pieceActive = pieceTab[1][0];
				break;
				case 7:
					pieceActive = pieceTab[1][1];
					break;
				case 8:
					pieceActive = pieceTab[1][2];
					break;
				case 9:
					pieceActive = pieceTab[1][3];
					break;
				case 10:
					pieceActive = pieceTab[1][4];
					break;
				case 11:
					pieceActive = pieceTab[1][5];
					break;
				default:
					break;
				}

				SDL_Texture* Sol = IMG_LoadTexture(renderer,pieceActive);
				
				SDL_Rect Sol_rect;
				Sol_rect.x = j * taille;
				Sol_rect.y = i * taille;
				Sol_rect.w = taille;
				Sol_rect.h = taille;

				SDL_RenderCopy(renderer, Sol, NULL, &Sol_rect);

			}
		}

	
		//affiche puis libère la memoire
		SDL_RenderPresent(renderer);
		SDL_DestroyRenderer(renderer);


		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	//ferme le jeu
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	delete mainEvent;

	return 0;
}