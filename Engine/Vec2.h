#pragma once

#include <iostream>

struct Vec2 {
	float m_x, m_y;
	Vec2(float x, float y) : m_x(x), m_y(y) { }
	Vec2() { m_x = 0; m_y = 0; }
	Vec2(const Vec2& vec2) : m_x(vec2.m_x), m_y(vec2.m_y) { }
    Vec2 operator+(const Vec2& other) const {
        return Vec2(m_x + other.m_x, m_y + other.m_y);
    }
    Vec2 operator*(float scalar) const {
        return Vec2(m_x * scalar, m_y * scalar);
    }
    Vec2 operator/(float scalar) const {
        return Vec2(m_x / scalar, m_y / scalar);
    }
    float GetMagnitude() const {
        return std::sqrt(m_x * m_x + m_y * m_y);
    }
    void Normalize() {
        float magnitude = std::sqrt(m_x * m_x + m_y * m_y);
        if (magnitude > 0.0f) {
            m_x /= magnitude;
            m_y /= magnitude;
        }
    }
};