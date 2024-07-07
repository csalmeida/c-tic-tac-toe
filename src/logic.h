#ifndef LOGIC_H
#define LOGIC_H

#include <SDL2/SDL.h>
#include "game.h"
#include "logic.h"
#include "rendering.h"

// Switches player's turns:
void switch_player(game_t *game) {
  switch (game->player)
  {
  case PLAYER_X:
    game->player = PLAYER_O;
    break;
  case PLAYER_O:
    game->player = PLAYER_X;
  break;
  default:
    break;
  }
}

/**
 * Determines if a player has won the game.
 * Checks every row, column and diagonal to find a winner.
 */
int check_player_won(game_t *game, enum Player player) {
  // Used to find rows or columns completed by a player:
  int row_count = 0;
  int column_count = 0;

  // Used to find diagonals completed by a played: 
  int diagonal_a_count = 0;
  int diagonal_b_count = 0;

  for (size_t row = 0; row < BOARD_ROWS; row++)
  {
      for (size_t column = 0; column < BOARD_COLS; column++)
      {
        if (game->board[row * BOARD_ROWS + column] == (enum Cell) player) {
          row_count++;
        }

        if (game->board[column * BOARD_COLS + row] == (enum Cell) player) {
          column_count++;
        }
      }

      // A player has a full row or column which means they won the game.
      if (row_count >= BOARD_ROWS || column_count >= BOARD_COLS) {
        return 1;
      }

      // Reset the count and start again:
      row_count = 0;
      column_count = 0;

      // Count completed diagonals:
      if (game->board[row * BOARD_ROWS + row] == (enum Cell) player) {
        diagonal_a_count++;
      }

      if (game->board[row * BOARD_ROWS + BOARD_COLS - row - 1] == (enum Cell) player) {
        diagonal_b_count++;
      }
  }

  return diagonal_a_count >= BOARD_ROWS || diagonal_b_count >= BOARD_ROWS;
}

/**
 * Counts cells in a particular state.
 * Useful to find if there are any cells to play.
 */
int count_cells(const enum Cell *board, enum Cell cell_state) {
  int count = 0;
  size_t total_cells = BOARD_ROWS * BOARD_COLS;

  // Iterates through the board and adds cells that match the state to the count.
  for (size_t cell_num = 0; cell_num < total_cells; cell_num++)
  {
    if(board[cell_num] == cell_state) {
      count++;
    }
  }

  return count;
}

/**
 * Changes state of the game in case:
 * - Either player wins.
 * - There's a tie.
 */
void game_over_condition(game_t *game) {
  // Checks if there's a winner.
  int player_x_won = check_player_won(game, PLAYER_X);
  int player_o_won = check_player_won(game, PLAYER_O);

  if (player_x_won) {
    game->state = PLAYER_X_WON_STATE;
    return;
  }

  if (player_o_won) {
    game->state = PLAYER_O_WON_STATE;
    return;
  }
  
  // If there are no empty cells, set game state as tied:
  int empty_cell_count = count_cells(game->board, EMPTY_CELL);
  if (empty_cell_count == 0) {
    game->state = TIE_STATE;
  }
}

// Records a player move:
void commit_player_turn(game_t *game, int row, int column) {
  // Finds the current cell position and the cell the user clicked on:
  int cell_position = row * BOARD_ROWS + column;
  enum Cell *grid_cell = &game->board[cell_position];

  // Only allow a player to play on empty squares:
  if (*grid_cell == EMPTY_CELL) {
    *grid_cell = (enum Cell) game->player;
    switch_player(game);
    game_over_condition(game);
  }
}

// Resets the game to a clean state so that it can be played again.
void reset_game(game_t *game) {
  // Sets player X to take first turn.
  // Sets game in motion.
  game->player = PLAYER_X;
  game->state = IN_PLAY_STATE;

  // Goes through each square and resets it:
  for (size_t square = 0; square < BOARD_COLS * BOARD_ROWS; square++)
  {
    game->board[square] = EMPTY_CELL;
  }
}

// Modifies the state of the game as it 
void click_on_cell(game_t *game, int row, int column){
  if (game->state == IN_PLAY_STATE) {
    commit_player_turn(game, row, column);
    return;
  }

  reset_game(game);
}

#endif