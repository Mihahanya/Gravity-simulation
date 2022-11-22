#include "Connection.h"


Connection::Connection(Body &p1, Body &p2) : p1{p1}, p2{p2} {}

void Connection::calc_force() {
    if (vs::dist(p1.pos, p2.pos) < p1.rad + p2.rad) return;

	vec dir = vs::norm(p1.pos - p2.pos);
	double r = vs::dist(p1.pos, p2.pos);

	// F = (m1 * m2) / r^2; F = m * a
	// a1 = m2 / r^2; a2 = m1 / r^2
	p1.accel -= dir * p2.mass / pow(r, 2);
	p2.accel += dir * p1.mass / pow(r, 2);
}

void Connection::do_collision() {
	static const double v_max=300, x_max=3;

	p1.collised = p2.collised = false;

    if (vs::dist(p1.pos, p2.pos) < p1.rad + p2.rad) {
		p1.collised = p2.collised = true;

		/*if (p1.mass <= p2.mass) p1.pos = p2.pos + vs::norm(p1.pos-p2.pos) * (p1.rad+p2.rad);
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
		p2.vel = vs::rotate(v2, ang, false) * p2.bounciness;*/


		vec dir = vs::norm(p1.pos - p2.pos);
		double intersection = p1.rad + p2.rad - vs::dist(p1.pos, p2.pos);

		// k ~ m * (v_max / x_max)^2
		// m - mass of these most energetic particles
		// E = (m * v^2) / 2
		/*double e1 = p1.mass * pow(vs::length(p1.vel), 2),
			   e2 = p2.mass * pow(vs::length(p2.vel), 2);
		double m = (e1 > e2) ? p1.mass : p2.mass;*/
		double k = min(p1.mass, p2.mass) * pow(v_max/x_max, 2) * 0.5;

		// Fn = k*x
		vec restoring_force = dir * intersection * k;

		p1.accel += restoring_force / p1.mass;
		p2.accel -= restoring_force / p2.mass;
	}
}
