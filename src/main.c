#include <raylib.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

int
main (void)
{
	InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT, "Ant -- vs-123");

	while (!WindowShouldClose ())
		{
			BeginDrawing ();
			ClearBackground (DARKGREEN);
			EndDrawing ();
		}

	return 0;
}
