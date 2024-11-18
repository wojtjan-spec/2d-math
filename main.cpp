#include "unistd.h"
#include "math.h"
#include "draw.h"

int main()
{
	screen = tigrWindow(640, 480, "Math 101", 0);

	aabb red_box = aabb(world_to_screen(v2(-50, -50)), world_to_screen(v2(50, 50)));
	aabb blue_box = aabb(world_to_screen(v2(-50, -50)), world_to_screen(v2(50, 50)));
	while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
		float dt = tigrTime();
		tigrClear(screen, color_black());

		red_box.min += v2(30.0f, 0) * dt;
		red_box.max += v2(30.0f, 0) * dt;
		blue_box.min += v2(0, 30.0f) * dt;
		blue_box.max += v2(0, 30.0f) * dt;
		draw_box(red_box, color_red());
		draw_box(blue_box, color_blue());

		tigrUpdate(screen);
	}

	tigrFree(screen);

	return 0;
}
