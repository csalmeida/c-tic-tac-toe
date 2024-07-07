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

enum Cell {
    EMPTY_CELL = 0,
    PLAYER_X_CELL = 1,
    PLAYER_O_CELL = 2
};

// Similar to Cell except it cannot be empty.
enum Player {
  PLAYER_X = PLAYER_X_CELL,
  PLAYER_O = PLAYER_O_CELL,
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
  enum Player player;
  enum GameState state;
} game_t;

#endif // GAME_H_