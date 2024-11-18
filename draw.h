#include "tigr.h"
#include "math_101.h"

Tigr* screen;

v2 world_to_screen(v2 p)
{
	p.y = -p.y;
	float half_screen_width = 640.0f / 2.0f;
	float half_screen_height = 480.0f / 2.0f;
	p.x += half_screen_width;
	p.y += half_screen_height;
	return p;
}

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

TPixel color_white() { return tigrRGB(255, 255, 255); }
TPixel color_black() { return tigrRGB(0, 0, 0); }
TPixel color_red() { return tigrRGB(255, 0, 0); }
TPixel color_green() { return tigrRGB(0, 255, 0); }
TPixel color_blue() { return tigrRGB(0, 0, 255); }
