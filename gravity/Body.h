#pragma once

#include "config.h"
#include "fs.h"
#include "Drawable.h"


class Body : public Drawable
{
	friend class Connection;

public:
	Body(double mass, double bounciness=0.4, Color color=Color::White) : 
		mass{mass}, bounciness{bounciness}, Drawable{color} {}
	
	void update(double dt);

	void draw() override;
	void show_accels();

	double mass, bounciness=0.4, rad=5;
	bool collised = false;
	vec pos=vs::zero, prev_pos=vs::zero, vel, accel;
};

