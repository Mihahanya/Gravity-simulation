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

		//vel -= (vel - p->vel) * (1.+bounciness) * p->mass/(p->mass+mass);
		/*double v1 = vs::length(p1.vel) - (vs::length(p1.vel)-vs::length(p2.vel)) * (1.+p1.bounciness) * p2.mass / (p2.mass+p1.mass);
		double v2 = vs::length(p2.vel) - (vs::length(p2.vel)-vs::length(p1.vel)) * (1.+p2.bounciness) * p1.mass / (p2.mass+p1.mass);
		
		p1.vel = vs::norm(vs::reflect(p1.vel, vs::norm(p1.pos - p2.pos)))*v1;
		p2.vel = vs::norm(vs::reflect(p2.vel, vs::norm(p2.pos - p1.pos)))*v2;*/
		
		if (p1.mass <= p2.mass) p1.pos = p2.pos + vs::norm(p1.pos-p2.pos) * (p1.rad+p2.rad);
		if (p2.mass <= p1.mass) p2.pos = p1.pos + vs::norm(p2.pos-p1.pos) * (p2.rad+p1.rad);
		
		vec v1 = p1.vel, v2 = p2.vel;
		double	o1 = vs::angle(p1.vel), o2 = vs::angle(p2.vel),
				m1 = p1.mass, m2 = p2.mass, 
				fi = vs::angle(p2.pos-p1.pos) - PI/2;

		p1.vel.x = (v1.x*cos(o1-fi)*(m1-m2) + 2*m2*v2.x*cos(o2-fi)) / (m1+m2) * cos(fi) + v1.x*sin(o1-fi)*cos(fi+PI/2);
		p1.vel.y = (v1.y*cos(o1-fi)*(m1-m2) + 2*m2*v2.y*cos(o2-fi)) / (m1+m2) * sin(fi) + v1.y*sin(o1-fi)*sin(fi+PI/2);
		//p1.vel *= p1.bounciness;

		p2.vel.x = (v2.x*cos(o2-fi)*(m1-m2) + 2*m1*v1.x*cos(o1-fi)) / (m1+m2) * cos(fi) + v2.x*sin(o2-fi)*cos(fi+PI/2);
		p2.vel.y = (v2.y*cos(o2-fi)*(m1-m2) + 2*m1*v1.y*cos(o1-fi)) / (m1+m2) * sin(fi) + v2.y*sin(o2-fi)*sin(fi+PI/2);
		//p2.vel *= p2.bounciness;
	}
}
