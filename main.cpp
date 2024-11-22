#include "unistd.h"
#include "math.h"
#include "draw.h"

int main()
{
	screen = tigrWindow(640, 480, "Math 101", 0);

	float t = 0;
	while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
		float dt = tigrTime();
		t += dt;
		tigrClear(screen, color_black());

		v2 a = v2(-100, 0);
		v2 b = v2(-100, 100);
		v2 c = v2(100, 50);

		float t0 = 0;
		for (int i = 0; i <= 30; ++i) {
			float t1 = (float)i / 30.0f;
			v2 p0 = bezier(a, b, c, t0);
			v2 p1 = bezier(a, b, c, t1);
			draw_line(p0, p1, color_white());
			t0 = t1;
		}

		float pt = (cosf(t) + 1.0f) * 0.5f;
		v2 box_center = bezier(a, b, c, pt);
		draw_box(aabb(box_center - v2(10, 10), box_center + v2(10, 10)), color_white());

		tigrUpdate(screen);
	}

	tigrFree(screen);

	return 0;
}
