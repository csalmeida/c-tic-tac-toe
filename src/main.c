#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "game.h"
#include "logic.h"
#include "rendering.h"

int main(int argc, char *argv[]) 
{
  // Initializes SDL with selected subsystems:
  int sdl = SDL_Init(SDL_INIT_VIDEO);

  // Exits if SDL was not initialized correctly:
  bool sdl_is_init = sdl == 0;
  if (!sdl_is_init) {
    fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  // Setting up a window:
  // https://wiki.libsdl.org/SDL2/SDL_CreateWindow
  SDL_Window *window = SDL_CreateWindow(
    "⭕️❌ Tic Tac Toe ❌⭕️", 
    SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, 
    SCREEN_WIDTH, 
    SCREEN_HEIGHT,
    SDL_WINDOW_SHOWN
  );

  if (window == NULL) {
    fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  // Create a 2D rendering context for a window.
  // https://wiki.libsdl.org/SDL2/SDL_CreateRenderer
  // https://wiki.libsdl.org/SDL2/SDL_RendererFlags
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  // Destroys window if renderer fails to instantiate:
  if (renderer == NULL) {
    SDL_DestroyWindow(window);
    fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  game_t game ={
    .board = {
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
      EMPTY_CELL, EMPTY_CELL, EMPTY_CELL
    },
    .player = PLAYER_X,
    .state = TIE_STATE,
  };

  // https://wiki.libsdl.org/SDL2/SDL_Event
  SDL_Event event;

  // Mutates state based on events:
  while (game.state != QUIT_STATE) {
    while(SDL_PollEvent(&event)) {
      switch (event.type)
      {
      case SDL_QUIT:
        game.state = QUIT_STATE;
        break;
      case SDL_MOUSEBUTTONDOWN:
        click_on_cell(&game, event.button.y / CELL_HEIGHT, event.button.x / CELL_WIDTH);
        break;
      
      default:
        break;
      }
    }

    // Draw a black frame to the screen:
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    render_game(renderer, &game);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}