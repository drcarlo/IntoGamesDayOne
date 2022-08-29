#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;


void Initialise() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    else {
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            return;
        }


        window = SDL_CreateWindow("IntoGames", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 768, 768, SDL_WINDOW_SHOWN);

        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
            printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());

        }
    }

}


bool Update() {
    SDL_Event e;


    /* Poll for events. SDL_PollEvent() returns 0 when there are no  */
    /* more events on the event queue, our while loop will exit when */
    /* that occurs.                                                  */
    while (SDL_PollEvent(&e) != 0) {

        if (e.type == SDL_QUIT) {
            return false;
        }
    }

    return true;
}

void InitialiseContent() {
    SDL_Surface* image = IMG_Load("assets/character.png");

    texture = SDL_CreateTextureFromSurface(renderer, image);


    SDL_FreeSurface(image);
}


void Draw() {
    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 0);
    SDL_RenderClear(renderer);

    int windowHeight, windowWidth;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);

    SDL_Rect destinationRectangle{ windowWidth / 2, windowHeight / 2, 50, 50 };

    SDL_RenderCopy(renderer, texture, NULL, &destinationRectangle);

    SDL_RenderPresent(renderer);
}



void Exit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    window = NULL;
    SDL_Quit();
}

int main() {
	Initialise();
	InitialiseContent();

	bool gameLoop = true;
	while (gameLoop) {
		Update();
		Draw();
		SDL_Delay(17); // 60 fps
	}

	Exit();

	return 0;
}