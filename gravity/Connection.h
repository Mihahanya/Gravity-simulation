#pragma once

#include "Body.h"

class Connection {
public:
	Connection(Body& p1, Body& p2); 

	void calc_force();
	void do_collision();

private:
	Body &p1, &p2;
};


Connection::Connection(Body &p1, Body &p2) : p1{p1}, p2{p2} {}

void Connection::calc_force() {
	vec dir = vs::norm(p1.pos - p2.pos);
	double r = vs::dist(p1.pos, p2.pos);

	p1.add_accel(-dir * p2.mass / pow(r, 2));
	p2.add_accel(dir * p1.mass / pow(r, 2));
}

void Connection::do_collision() {
	p1.collised = p2.collised = false;

    if (vs::dist(p1.pos, p2.pos) < p1.rad + p2.rad) {
		p1.collised = p2.collised = true;

		if (p1.mass <= p2.mass) p1.pos = p2.pos + vs::norm(p1.pos-p2.pos) * (p1.rad+p2.rad);
		if (p2.mass <= p1.mass) p2.pos = p1.pos + vs::norm(p2.pos-p1.pos) * (p2.rad+p1.rad);
		
		vec v1 = p1.vel, v2 = p2.vel;
		double m1 = p1.mass, m2 = p2.mass, 
			   ang = vs::angle(p2.pos-p1.pos);

		v1 = vs::rotate(v1, ang, true);
		v2 = vs::rotate(v2, ang, true);

		vec v_total = v1 - v2;
		v1.x = (v1.x*(m1-m2) + 2*m2*v2.x) / (m1+m2);
		v2.x = v_total.x + v1.x;
		
		p1.vel = vs::rotate(v1, ang, false) * p1.bounciness;
		p2.vel = vs::rotate(v2, ang, false) * p2.bounciness;
	}
}
