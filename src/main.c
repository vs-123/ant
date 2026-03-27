#include <raylib.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define CELL_SIZE 10
#define BOARD_COLS (WINDOW_WIDTH / CELL_SIZE)
#define BOARD_ROWS (WINDOW_HEIGHT / CELL_SIZE)

#define ANTS_COUNT 10

enum direction_t
{
	DIRECTION_NORTH,
	DIRECTION_EAST,
	DIRECTION_WEST,
	DIRECTION_SOUTH,
};

struct ant_t
{
	int x;
	int y;
	enum direction_t direction;
};

int
main (void)
{
	InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT, "Ant -- vs-123");
	SetTargetFPS (30);

	bool board[BOARD_COLS * BOARD_ROWS] = { 0 };
	ant_t ants[ANTS_COUNT] = {0};


	while (!WindowShouldClose ())
		{
			BeginDrawing ();
			ClearBackground (DARKGREEN);
			EndDrawing ();
		}

	return 0;
}
