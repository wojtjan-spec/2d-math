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

v2 operator+(v2 a, v2 b) { return v2(a.x + b.x, a.y + b.y); }
v2 operator+=(v2& a, v2 b) { a = v2(a.x + b.x, a.y + b.y); return a; }
v2 operator-(v2 a, v2 b) { return v2(a.x - b.x, a.y - b.y); }
v2 operator-=(v2& a, v2 b) { a = v2(a.x - b.x, a.y - b.y); return a; }
v2 operator*(v2 a, float b) {return v2(a.x * b, a.y * b);}
v2 operator*=(v2& a, float b) { a = v2(a.x * b, a.y * b); return a; }
v2 operator/(v2 a, float b) { return v2(a.x / b, a.y / b); }
v2 operator/=(v2& a, float b) { a = v2(a.x / b, a.y / b); return a; }
float len(v2 v) { return sqrtf(v.x * v.x + v.y * v.y); }

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
