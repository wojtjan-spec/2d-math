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

		aabb box = aabb(v2(120, 120), v2(540, 360));
		
		v2 offset = v2(cosf(t), sinf(t)) * 100.0f;
		box.min = box.min - offset;
		box.max = box.max + offset;

		draw_box(box, color_white());

		tigrUpdate(screen);
	}

	tigrFree(screen);

	return 0;
}
