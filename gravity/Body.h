#pragma once

#include "config.h"
#include "fs.h"
#include "Drawable.h"


class Body : public Drawable
{
	friend class Connection;

public:
	double mass, bounciness=0.4, rad=5;
	vec pos=vs::zero, prev_pos=vs::zero;
	bool collised = false;

	Body(double mass, double bounciness=0.4, Color color=Color::White) : 
		mass{mass}, bounciness{bounciness}, Drawable{color} {}
	
	void update(double dt);

	void add_accel(vec);
	void set_vel(vec);

	void draw() override;
	void show_accels();

private:
	vec vel, accel;
};

