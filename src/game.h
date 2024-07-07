#ifndef GAME_H_
#define GAME_H_

// Defines the initial size of the window:
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// The number of rows and columns (defines number of squares on the board).
#define BOARD_ROWS 3
#define BOARD_COLS 3

// The size of each cell (a square on the board).
#define CELL_WIDTH (SCREEN_WIDTH / BOARD_ROWS)
#define CELL_HEIGHT (SCREEN_HEIGHT / BOARD_COLS)

// This could be an enum.
enum Cell {
    EMPTY = 0,
    PLAYER_X = 1,
    PLAYER_O = 2
};

enum GameState {
    IN_PLAY_STATE = 0, // The game is still running (Player X and O have moves left).
    PLAYER_X_WON_STATE = 1,
    PLAYER_O_WON_STATE = 2,
    TIE_STATE = 3,
    QUIT_STATE = 4
};

typedef struct {
  enum Cell board[BOARD_ROWS * BOARD_COLS];
  int player;
  enum GameState state;
} game_t;

#endif // GAME_H_