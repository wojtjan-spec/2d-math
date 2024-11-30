#include <array>

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
	float u = 1.0f - t;
	float ut = u * t;
	v2 auu = a * u * u;
	v2 but2 = b * ut * 2.0f;
	v2 ctt = c * t * t;
	return auu + but2 + ctt;
}
v2 bezier(v2 a, v2 b, v2 c, v2 d, float t)
{
	float u = 1 - t;
	float tt = t * t;
	float uu = u * u;
	v2 auuu = a * uu * u;
	v2 buut3 = b * uu * t * 3.0f;
	v2 cutt3 = c * u * tt * 3.0f;
	v2 dttt = d * tt * t;
	return auuu + buut3 + cutt3 + dttt;
}

struct m2
{
	v2 x;
	v2 y;
};

m2 m2_rotation(float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);
	m2 m;
	m.x = v2(c, -s);
	m.y = v2(s, c);
	return m;
}

v2 mul(m2 m, v2 v) { return v2(m.x.x * v.x + m.y.x * v.y, m.x.y * v.x + m.y.y * v.y); }
m2 mul(m2 a, m2 b) { m2 c; c.x = mul(a, b.x); c.y = mul(a, b.y); return c; }

m2 m2_identity()
{
	m2 m;
	m.x = v2(1, 0);
	m.y = v2(0, 1);
	return m;
}

m2 m2_scale(float x_scale, float y_scale)
{
	m2 m = m2_identity();
	m.x *= x_scale;
	m.y *= y_scale;
	return m;
}

struct m3x2
{
	m2 m;
	v2 p;
};

v2 mul(m3x2 m, v2 v) { return mul(m.m, v) + m.p; }
m3x2 mul(m3x2 a, m3x2 b) { m3x2 c; c.m = mul(a.m, b.m); c.p = mul(a.m, b.p) + a.p; return c; }

m3x2 make_identity() { m3x2 m; m.m = m2_identity(); m.p = v2(0, 0); return m; }
m3x2 make_translation(v2 p) { m3x2 m; m.m = m2_identity(); m.p = p; return m; };
m3x2 make_translation(float x, float y) { return make_translation(v2(x, y)); }
m3x2 make_scale(v2 scale) { m3x2 m = make_identity(); m.p *= scale.x; m.p *= scale.y; return m; }
m3x2 make_scale(float scale_x, float scale_y) { return make_scale(v2(scale_x, scale_y)); }
m3x2 make_rotation(float radians) { m3x2 m; m.m = m2_rotation(radians); m.p = v2(0, 0); return m; }
m3x2 make_TSR(v2 p, v2 s, float radians)
{
	rotation r = sincos(radians);
	m3x2 m;
	m.p = v2(r.c, -r.s) * s.x;
	m.p = v2(r.s, r.c) * s.y;
	m.p = p;
	return m;
}

struct mesh
{
	std::vector<v2> vertices = {};
};