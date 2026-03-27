#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define YSTAR_IMPLEMENTATION
#include "ystar.h"
#include <raylib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define CELL_SIZE 20
#define BOARD_COLS (WINDOW_WIDTH / CELL_SIZE)
#define BOARD_ROWS (WINDOW_HEIGHT / CELL_SIZE)
#define MAX_ANTS (BOARD_COLS * BOARD_ROWS - 1)

enum direction_t
{
	DIRECTION_NORTH,
	DIRECTION_EAST,
	DIRECTION_SOUTH,
	DIRECTION_WEST,
};

struct ant_t
{
	unsigned int x;
	unsigned int y;
	enum direction_t direction;
};

struct game_t
{
	bool *board;
	struct ant_t ants[MAX_ANTS];
	unsigned int ants_active_count;
	uint64_t seed;
	bool is_paused;
};

void
game_init (struct game_t *game)
{
	game->seed              = (uint64_t)time (NULL);
	game->is_paused         = true;
	game->ants_active_count = 0;

	game->board = calloc (BOARD_COLS * BOARD_ROWS, sizeof (bool));
}

void
game_update (struct game_t *game)
{
	for (unsigned int i = 0; i < game->ants_active_count; i++)
		{
			unsigned int index = game->ants[i].y * BOARD_COLS + game->ants[i].x;

			if (game->board[index])
				{
					game->ants[i].direction = (game->ants[i].direction + 1) % 4;
					game->board[index]      = false;
				}
			else
				{
					game->ants[i].direction = (game->ants[i].direction + 3) % 4;
					game->board[index]      = true;
				}

			switch (game->ants[i].direction)
				{
				case DIRECTION_NORTH:
					game->ants[i].y--;
					break;
				case DIRECTION_EAST:
					game->ants[i].x++;
					break;
				case DIRECTION_SOUTH:
					game->ants[i].y++;
					break;
				case DIRECTION_WEST:
					game->ants[i].x--;
					break;
				}

			game->ants[i].x = (game->ants[i].x + BOARD_COLS) % BOARD_COLS;
			game->ants[i].y = (game->ants[i].y + BOARD_ROWS) % BOARD_ROWS;
		}
}

void
game_handle_input (struct game_t *game)
{
	if (IsKeyPressed (KEY_SPACE))
		{
			game->is_paused = !game->is_paused;
		}

	if (IsKeyPressed (KEY_N) || IsKeyPressedRepeat (KEY_N))
		{
			game->is_paused = true;
			game_update (game);
		}

	if (IsMouseButtonPressed (MOUSE_LEFT_BUTTON))
		{
			Vector2 mouse_pos   = GetMousePosition ();
			unsigned int cell_x = (unsigned int)(mouse_pos.x / CELL_SIZE);
			unsigned int cell_y = (unsigned int)(mouse_pos.y / CELL_SIZE);

			if (cell_x >= BOARD_COLS || cell_y >= BOARD_ROWS)
				{
					return;
				}

			int found_idx = -1;
			for (unsigned int i = 0; i < game->ants_active_count; i++)
				{
					if (game->ants[i].x == cell_x && game->ants[i].y == cell_y)
						{
							found_idx = i;
							break;
						}
				}

			if (found_idx != -1)
				{
					game->ants[found_idx] = game->ants[game->ants_active_count - 1];
					game->ants_active_count--;
				}
			else if (game->ants_active_count < MAX_ANTS)
				{
					unsigned int new_idx  = game->ants_active_count++;
					game->ants[new_idx].x = cell_x;
					game->ants[new_idx].y = cell_y;
					game->ants[new_idx].direction
					    = (enum direction_t)ystar_between (&game->seed, 0, 4);
				}
		}
}

void
game_render (struct game_t *game)
{
	ClearBackground (RAYWHITE);

	for (unsigned int i = 0; i < BOARD_COLS * BOARD_ROWS; i++)
		{
			if (game->board[i])
				{
					DrawRectangle ((i % BOARD_COLS) * CELL_SIZE,
					               (i / BOARD_COLS) * CELL_SIZE,
					               CELL_SIZE,
					               CELL_SIZE,
					               BLACK);
				}
		}

	for (unsigned int i = 0; i < game->ants_active_count; i++)
		{
			DrawRectangle (game->ants[i].x * CELL_SIZE,
			               game->ants[i].y * CELL_SIZE,
			               CELL_SIZE,
			               CELL_SIZE,
			               RED);
		}

	DrawText (TextFormat ("[ANTS] %d | %s",
	                      game->ants_active_count,
	                      game->is_paused ? "PAUSED" : "RUNNING"),
	          10,
	          10,
	          20,
	          (game->is_paused ? RED : DARKGREEN));
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
			game_handle_input (&game);

			if (!game.is_paused)
				{
					game_update (&game);
				}

			BeginDrawing ();
			game_render (&game);
			EndDrawing ();
		}

	free (game.board);
	CloseWindow ();
	return 0;
}
