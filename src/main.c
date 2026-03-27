#include <stdio.h>
#include <time.h>

#define YSTAR_IMPLEMENTATION
#include "ystar.h"
#include <raylib.h>

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
	uint64_t seed = time (NULL);

	InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT, "Ant -- vs-123");
	SetTargetFPS (30);

	bool board[BOARD_COLS * BOARD_ROWS] = { 0 };
	struct ant_t ants[ANTS_COUNT]              = { 0 };

	for (int i = 0; i < ANTS_COUNT; i++)
		{
			ants[i].x   = ystar_between (&seed, 0, BOARD_COLS);
			ants[i].y   = ystar_between (&seed, 0, BOARD_ROWS);
			ants[i].direction = (enum direction_t) (ystar_between (&seed, 0, 4));
		}

	while (!WindowShouldClose ())
		{
			BeginDrawing ();
			ClearBackground (RAYWHITE);
			DrawText ("Press ESC to quit", 10, WINDOW_HEIGHT - 20, 10, DARKGRAY);
			EndDrawing ();
		}

	return 0;
}
