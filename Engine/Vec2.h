#pragma once

struct Vec2 {
	float m_x, m_y;
	Vec2(float x, float y) : m_x(x), m_y(y) { }
	Vec2() { m_x = 0; m_y = 0; }
	Vec2(const Vec2& vec2) : m_x(vec2.m_x), m_y(vec2.m_y) { }
	Vec2 operator+(const Vec2 vec2) {
		return Vec2(vec2.m_x + m_x, vec2.m_y + m_y);
	}
};