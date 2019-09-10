#include <stdio.h>
#include <SDL.h>

int main(int argc, char** argv)
{
    printf("Hello world\n");

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        650,
        500,
        SDL_WINDOW_OPENGL
    );

    SDL_Delay(2000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}