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

float dot(v2 a, v2 b) { return a.x * b.x + a.y * b.y; };
float len(v2 v) { return sqrtf(dot(v, v)); }
float len_squared(v2 v) { return dot(v, v); }
float sign(float x) { return x > 0 ? 1.0f : -1.0f; }

v2 norm(v2 v) { float l = len(v); return v * (1.0f / l); }

struct aabb
{
	aabb() { }
	aabb(v2 min, v2 max) { this->min = min; this->max = max; }
	v2 min;
	v2 max;
};

float width(aabb box) { return box.max.x - box.min.x; };
float height(aabb box) { return box.max.y - box.min.y; };
v2 center(aabb box) { return (box.min + box.max) * 0.5f; };

struct rotation 
{
	rotation() { }
	rotation(float angle) { s = sinf(angle); c = sinf(angle); }
	rotation(float s, float c) { this->s = s; this->c = c; }
	float s;
	float c;
};

rotation sincos(float a) { rotation r; r.c = cosf(a); r.s = sinf(a); return r; };
v2 mul(rotation a, v2 b) { return v2(a.c * b.x - a.s * b.y, a.s * b.x + a.c * b.y); }; 

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
float atan2_360(v2 v) { return atan2f(-v.y, -v.x) + 3.14159265f;};

float det2(v2 a, v2 b) { return a.x * b.y - a.y * b.x; }

float shortest_arc(v2 a, v2 b)
{
	a = norm(a);
	b = norm(b);
	float c = dot(a, b);
	float s = det2(a, b);
	float theta = acosf(c);
	if (s > 0) {
		return theta;
	} else {
		return -theta;
	}
}

struct halfspace
{
	halfspace() { }
	halfspace(v2 n, v2 p) { this->n = n; c = dot(n, p); }
	halfspace(v2 n, float c) { this->n = n; this->c = c; }
	v2 n;
	float c;
};

float distance(halfspace h, v2 p) { return dot(h.n, p) - h.c; }
v2 project(halfspace h, v2 p) { return p - h.n * distance(h, p); }
v2 intersect(halfspace h, v2 q, v2 p)
{
	float dq = distance(h, q);
	float dp = distance(h, p);
	return q + (p - q) * (dq / (dq - dp));
}

float lerp(float a, float b, float t) { return a + (b - a) * t; }
v2 lerp(v2 a, v2 b, float t) { return a + (b - a) * t; }
v2 bezier(v2 a, v2 b, v2 c, float t)
{
	v2 d = lerp(a, b, t);
	v2 e = lerp(b, c, t);
	return lerp(d, e, t);
}
v2 bezier(v2 a, v2 b, v2 c, v2 d, float t)
{
	v2 e = bezier(a, b, c, t);
	v2 f = bezier(b, c, d, t);
	return lerp(e, f, t);
}