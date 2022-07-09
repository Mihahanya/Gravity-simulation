#pragma once

#include "config.h"

namespace vs 
{
	inline double dist(vec a, vec b) {
		return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	}

	inline vec norm(vec v) {
		return v / dist(v, vec(0, 0));
	}
}

namespace ff 
{
	template <typename T>
	inline void easy_line(vec v1, vec v2, T& window, Color color = Color::Black) {
		Vertex vtx[] = { Vertex((Vector2f)v1), Vertex((Vector2f)v2) };
		vtx[0].color = vtx[1].color = color;
		window.draw(vtx, 2, LinesStrip);
	}

	template <typename T>
	inline void easy_circle(vec pos, double r, T& window, Color color = Color::Black) {
		sf::CircleShape c(r);
		c.setFillColor(color);
		c.setPosition(Vector2f(pos - vec(r, r)));

		window.draw(c);
	}
}
