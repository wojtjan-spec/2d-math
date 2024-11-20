#include "unistd.h"
#include "math.h"
#include "draw.h"

int main()
{
	screen = tigrWindow(640, 480, "Math 101", 0);

	float t = 0;
	v2 aim = v2(50, 100);
	while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
		float dt = tigrTime();
		t += dt;
		tigrClear(screen, color_black());

		v2 m = mouse();
		draw_box(aabb(m - v2(10.0f, 10.0f), m + v2(10.0f, 10.0f)), color_white());
		float angle = shortest_arc(aim, m);
		aim = mul(sincos(angle * dt * 2.0f), aim);
		draw_vector(v2(0, 0), aim, color_white());

		tigrUpdate(screen);
	}

	tigrFree(screen);

	return 0;
}
