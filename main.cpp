#include "tigr.h"
#include <unistd.h>
#include <math.h>

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
v2 operator*(v2 a, float b) {return v2(a.x * b, a.y * b);}

struct aabb
{
	aabb() { }
	aabb(v2 min, v2 max) { this->min = min; this->max = max; }
	v2 min;
	v2 max;
};

float width(aabb box) {return box.max.x - box.min.x; };
float height(aabb box) {return box.max.y - box.min.y; };
v2 center(aabb box) {return (box.min + box.max) * 0.5f; };
float len(v2 v) { return sqrtf(v.x * v.x + v.y * v.y); }

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

void draw_line(v2 a, v2 b, TPixel color)
{
	tigrLine(screen, (int)a.x, (int)a.y, (int)b.x, (int)b.y, color);
}

void draw_box(aabb box, TPixel color)
{
	float w = width(box) + 1;
	float h = height(box) + 1;
	draw_line(box.min, box.min + v2(w, 0), color);
	draw_line(box.min + v2(0,1), box.min + v2(0, h-1), color);
	draw_line(box.max, box.max - v2(w, 0), color);
	draw_line(box.max - v2(0,1), box.max - v2(0, h-1), color);
}

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
