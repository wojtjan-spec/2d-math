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

		v2 p = v2(100.0f, 0);
		rotation r = sincos(t * 0.01f);
		for (int i = 0; i < 32; ++i) {
			draw_line(v2(0, 0), p, color_white());
			p = mul(r, p);
		}

		tigrUpdate(screen);
	}

	tigrFree(screen);;

	return 0;
}
