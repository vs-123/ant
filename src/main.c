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

struct game_t
{
	bool board[BOARD_COLS * BOARD_ROWS];
	struct ant_t ants[ANTS_COUNT];
	uint64_t seed;
};

void
game_init (struct game_t *game)
{
	game->seed = time (NULL);
	for (int i = 0; i < ANTS_COUNT; i++)
		{
			game->ants[i].x = ystar_between (&game->seed, 0, BOARD_COLS);
			game->ants[i].y = ystar_between (&game->seed, 0, BOARD_ROWS);
			game->ants[i].direction
			    = (enum direction_t) (ystar_between (&game->seed, 0, 4));
		}
}

void
game_render (struct game_t *game)
{
	ClearBackground (RAYWHITE);

	for (int y = 0; y < BOARD_ROWS; y++)
		{
			for (int x = 0; x < BOARD_COLS; x++)
				{
					if (game->board[y * BOARD_COLS + x])
						{
							DrawRectangle (x * CELL_SIZE,
							               y * CELL_SIZE,
							               CELL_SIZE,
							               CELL_SIZE,
							               BLACK);
						}
				}
		}

	for (int i = 0; i < ANTS_COUNT; i++)
		{
			DrawRectangle (game->ants[i].x * CELL_SIZE,
			               game->ants[i].y * CELL_SIZE,
			               CELL_SIZE,
			               CELL_SIZE,
			               RED);
		}

	DrawText ("Press ESC to quit", 10, WINDOW_HEIGHT - 20, 10, DARKGRAY);
}

int
main (void)
{

	InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT, "Ant -- vs-123");
	SetTargetFPS (30);

	struct game_t game = { 0 };
	game_init (&game);

	while (!WindowShouldClose ())
		{
			BeginDrawing ();
			game_render (&game);
			EndDrawing ();
		}

	return 0;
}
