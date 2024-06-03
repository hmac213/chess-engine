#ifndef UNIQUE_LOOP
#define UNIQUE_LOOP

#define SCREEN_WIDTH 1100
#define SCREEN_HEIGHT 800

#include <iostream>
#include <SDL2/SDL.h>

int runVisualGame() {
    SDL_Window* window;
    SDL_Renderer* render;
    SDL_Surface* surface;

    if (SDL_Init(SDL_INIT_EVERYTHING != 0)) {
        std::cout << "There has been an error: " << SDL_GetError() << std::endl;
        return -1;
    } else {
        window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        surface = SDL_GetWindowSurface(window);

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                Uint32 squareColor;
                int squareX;
                int squareY;
                if ((i + j) % 2 == 0) {
                    squareColor = SDL_MapRGB(surface->format, 240, 217, 181);
                } else {
                    squareColor = SDL_MapRGB(surface->format, 181, 136, 99);
                }

                squareX = 150 + 100 * j;
                squareY = SCREEN_HEIGHT - 100 * (i + 1);

                SDL_Rect squareRect = { squareX, squareY, 100, 100};

                SDL_FillRect(surface, &squareRect, squareColor);
            }
        }

        SDL_UpdateWindowSurface(window);

        SDL_Delay(4000);
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}

#endif // UNIQUE_LOOP