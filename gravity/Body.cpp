#include "Body.h"


void Body::update(double dt) {
	prev_pos = pos;
	
	vel += accel * dt;
	pos += vel * dt;

	accel = vs::zero;
}

void Body::draw() {
	ff::easy_circle(pos, rad, *window, color);
}

void Body::show_accels() {
	ff::easy_line(pos, prev_pos, *window, Color::Cyan);
	ff::easy_line(pos, pos + vel, *window, Color(0, 0, 255, 127));
	ff::easy_line(pos, pos + accel, *window, Color(255, 0, 0, 127));
	if (collised) ff::easy_circle(pos, rad/2, *window, Color::Red);
}
