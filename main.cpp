#include "tigr.h"
#include <unistd.h>

struct v2 
{
	float x;
	float y;
	
	v2() {};
	v2(float x, float y) 
	{ 
		this -> x = x;
		this -> y = y;
	}
};

v2 operator+(v2 a, v2 b) {return v2(a.x + b.x, a.y + b.y); };
v2 operator-(v2 a, v2 b) {return v2(a.x - b.x, a.y - b.y); };

Tigr* screen;
TPixel color_white() { return tigrRGB(255, 255, 255); }
TPixel color_black() { return tigrRGB(0, 0, 0); }
TPixel color_red() { return tigrRGB(255, 0, 0); }
TPixel color_green() { return tigrRGB(0, 255, 0); }
TPixel color_blue() { return tigrRGB(0, 0, 255); }

void draw_point(v2 p, TPixel color)
{
	tigrPlot(screen, (int)p.x, (int)p.y, color);
}

int main()
{
	screen = tigrWindow(640, 480, "Math 101", 0);

	while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
		tigrClear(screen, color_black());
		
		v2 a = v2(200, 300);
	        v2 b = v2(100, 150);
	        v2 c = v2(600, 400);

		draw_point(a, color_white());
		draw_point(b, color_white());
		draw_point(c, color_white());
		
		v2 offset(20, 0);
		
		draw_point(a + offset, color_red());
		draw_point(b + offset, color_green());
		draw_point(c + offset, color_blue());

		tigrUpdate(screen);
	}

	tigrFree(screen);

	return 0;
}
