#include "tigr.h"

int main()
{
	Tigr* screen = tigrWindow(640, 480, "Math 101", 0);

	while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
		tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));
		tigrUpdate(screen);
	}

	tigrFree(screen);

	return 0;
}
