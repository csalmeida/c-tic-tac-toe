#ifndef RENDERING_H
#define RENDERING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h> // https://github.com/ferzkopp/SDL2_gfx
#include "game.h"

  const SDL_Color GRID_COLOR = {
      .r = 255,
      .g = 255,
      .b = 255
  };

  const SDL_Color PLAYER_X_COLOR = {
      .r = 255,
      .g = 50,
      .b = 50
  };

    const SDL_Color PLAYER_O_COLOR = {
      .r = 50,
      .g = 100,
      .b = 255
  };

    const SDL_Color TIE_COLOR = {
      .r = 100,
      .g = 100,
      .b = 100
  };

// Draws the board rows and columns with the chosen color:
void render_grid(SDL_Renderer *renderer, const SDL_Color *color) {
  // Switches rendering colour to use:
  SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);

  // The two following loops draw the board grid to the screen:
  // Draws all columns:
  for (size_t index = 1; index < BOARD_COLS; index++)
  {
    // Draws board column with a line:
    SDL_RenderDrawLine(renderer,
      index * CELL_WIDTH, 0, // Point A
      index * CELL_WIDTH, SCREEN_HEIGHT // Point B
    );
  }

  // Draws all rows:
  for (size_t index = 1; index < BOARD_ROWS; index++)
  {
    // Draws a line:
    SDL_RenderDrawLine(renderer,
      0, index * CELL_HEIGHT, // Point A
      SCREEN_WIDTH, index * CELL_HEIGHT // Point B
    );
  }
}

// Draws a cross inside a rectangle.
// To do that it calculates a smaller rectangle inside the original rectange,
// finds the middle of the rectangles,
// reaching the corners of the rectangle and drawing lines from them.
void render_x(SDL_Renderer *renderer, int row, int column, const SDL_Color *color) {
  // Find half of the square size.
  // min() picks the lower value between the two since the cells are tecnically rectangles.
  const float half_box_size = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25; // Same as dividing by 4.

  // Calculates the center of the box from which the corners can be found:
  const float center_x = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
  const float center_y = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

  // Draws a line:
  thickLineRGBA(renderer, 
    center_x - half_box_size, center_y - half_box_size, 
    center_x + half_box_size, center_y + half_box_size,
    10,
    color->r,
    color->g,
    color->b,
    255
  );

    thickLineRGBA(renderer, 
    center_x + half_box_size, center_y - half_box_size,
    center_x - half_box_size, center_y + half_box_size, 
    10,
    color->r,
    color->g,
    color->b,
    255
  );
}

void render_o(SDL_Renderer *renderer, int row, int column, const SDL_Color *color) {
  // Find half of the square size.
  // min() picks the lower value between the two since the cells are tecnically rectangles.
  const float half_box_size = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25; // Same as dividing by 4.

  // Calculates the center of the box from which the corners can be found:
  const float center_x = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
  const float center_y = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

  filledCircleRGBA(
    renderer, 
    center_x, center_y, half_box_size + 5,
    color->r,
    color->g,
    color->b,
    255 
  );

  filledCircleRGBA(
    renderer, 
    center_x, center_y, half_box_size - 10,
    0,
    0,
    0,
    255 
  );
}

// Renders player moves into the board by reading the current state:
void render_board(SDL_Renderer *renderer, const enum Cell *board, const SDL_Color *player_x_color, const SDL_Color *player_o_color) {
  // Iterates over each square on the board:
  for (size_t row_num = 0; row_num < BOARD_ROWS; row_num++)
  {
    for (size_t column_num = 0; column_num < BOARD_COLS; column_num++)
    {
      int current_square = board[row_num * BOARD_ROWS + column_num];
      switch (current_square)
      {
      case PLAYER_X_CELL:
        render_x(renderer, row_num, column_num, player_x_color);
        break;
      case PLAYER_O_CELL:
        render_o(renderer, row_num, column_num, player_o_color);
        break;
      default:
        break;
      }
    }
  }
  
}

void render_in_play_state(SDL_Renderer *renderer, const game_t *game) {
  render_grid(renderer, &GRID_COLOR);
  render_board(
    renderer, 
    game->board,
    &PLAYER_X_COLOR,
    &PLAYER_O_COLOR
  );
}

void render_game_over_state(SDL_Renderer *renderer, const game_t *game, const SDL_Color *color) {
  render_grid(renderer, color);
  render_board(
    renderer, 
    game->board,
    color,
    color
  );
}

// Only renders the state of the game and
// is not allowed to modify it.
// This is executed through reading the current stage and modifying
// the visual aspects via functions.
void render_game(SDL_Renderer *renderer, const game_t *game){
  switch (game->state)
  {
  case IN_PLAY_STATE:
    render_in_play_state(renderer, game);
    break;
  case PLAYER_X_WON_STATE:
    render_game_over_state(renderer, game, &PLAYER_X_COLOR);
    break;
  case PLAYER_O_WON_STATE:
    render_game_over_state(renderer, game, &PLAYER_O_COLOR);
    break;
  case TIE_STATE:
    render_game_over_state(renderer, game, &TIE_COLOR);
    break;
  default:
    break;
  }
}

#endif