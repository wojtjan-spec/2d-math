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

v2 norm(v2 v) { float l = len(v); return v * (1.0f / l); }

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

struct rotation 
{
	rotation() { }
	rotation(float angle) { s = sinf(angle); c = sinf(angle); }
	rotation(float s, float c) { this->s = s; this->c = c; }
	float s;
	float c;
};

rotation sincos(float a) { rotation r; r.c = cosf(a); r.s = sinf(a); return r; };
v2 mul(rotation a, v2 b) {return v2(a.c * b.x - a.s * b.y, a.s * b.x + a.c * b.y); }; 

v2 rotate(v2 v, float radians)
{
	float s = sinf(radians);
	float c = cosf(radians);
	return v2(c * v.x - s * v.y, s* v.x + c * v.y);
}

v2 vector_of_unit_circle_from_angle(float radians)
{
	return v2(cosf(radians), sinf(radians));
}

v2 skew(v2 a) { return v2(-a.y, a.x); };

v2 rotate_point_a_around_point_b(v2 a, v2 b, float radians)
{
	float s = sinf(radians);
	float c = cosf(radians);

	a = a - b; 

	a = v2(c * a.x - s * a.y, s * a.x + c * a.y);

	return a + b;
}

float atan2_360(float y, float x) { return atan2f(-y, x) + 3.14159265f; };
float atan2_360(rotation r) { return atan2_360(r.s, r.c); };
float atan2_360(v2 v) {return atan2f(-v.y, -v.x) + 3.14159265f;};