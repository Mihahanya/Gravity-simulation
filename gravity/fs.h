#pragma once

#include "config.h"

namespace vs
{
    const vec zero{ 0, 0 };

    inline double dist(const vec& v1, const vec& v2) {
        return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
    }

    inline double length(const vec& v) {
        return sqrt(v.x*v.x + v.y*v.y);
    }

    inline double dot(const vec& a, const vec& b) {
        return a.x * b.x + a.y * b.y;
    }

    inline vec norm(const vec& v) {
        return v / length(v);
    }

    inline vec reflect(const vec& rd, const vec& n) {
        return rd - n * 2. * dot(n, rd);
    }

    inline vec rotate(const vec& v, double a, bool reverse=false) {
        //return { v.x * cos(a) - v.y * sin(a), v.x * sin(a) + v.y * cos(a) };
        return {
            reverse ? (v.x * cos(a) + v.y * sin(a)) : (v.x * cos(a) - v.y * sin(a)),
            reverse ? (v.y * cos(a) - v.x * sin(a)) : (v.y * cos(a) + v.x * sin(a))
        };
    }

    inline double angle(const vec& v) {
        if (v == vs::zero) return 0;
        return atan(v.y / v.x);
    }
}


namespace ff 
{
	template <typename T>
	inline void easy_line(const vec& v1, const vec& v2, T& window, Color color = Color::Black) {
		Vertex vtx[] = { Vertex((Vector2f)v1), Vertex((Vector2f)v2) };
		vtx[0].color = vtx[1].color = color;
		window.draw(vtx, 2, LinesStrip);
	}

	template <typename T>
	inline void easy_circle(const vec& pos, double r, T& window, Color color = Color::Black) {
		sf::CircleShape c(r);
		c.setFillColor(color);
		c.setPosition(Vector2f(pos - vec(r, r)));

		window.draw(c);
	}
}
