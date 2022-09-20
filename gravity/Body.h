#pragma once

#include <set>
#include "config.h"
#include "fs.h"
#include "Drawable.h"


class Body : public Drawable
{
	friend class Connection;

public:
	double mass, bounciness, rad=5;
	vec pos=vs::zero, prev_pos=vs::zero;
	bool collised = false;

	Body(double mass, double bounciness, Color color);
	
	void update(double dt);

	void add_accel(vec);
	void set_vel(vec);

	void draw() override;
	void show_accels();

private:
	vec vel, accel;
};


Body::Body(double mass, double bounciness=0.2, Color color=Color::White) : 
	mass{mass}, bounciness{bounciness}, Drawable{color} {}

void Body::set_vel(vec vel) { this->vel = vel; }
void Body::add_accel(vec f) { accel += f; }

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
