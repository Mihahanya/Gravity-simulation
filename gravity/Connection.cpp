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
	//static const double v_max=300, x_max=3;

    if (vs::dist(p1.pos, p2.pos) < p1.rad + p2.rad) {
		p1.collised = p2.collised = true;

		vec v1 = p1.vel, v2 = p2.vel;
		double m1 = p1.mass, m2 = p2.mass, ang = vs::angle(p2.pos-p1.pos);

		// Move the particle 
		vec dir = vs::norm(p1.pos-p2.pos) * (p1.rad+p2.rad);
		if (m1 <= m2) p1.pos = p2.pos + dir;
		else		  p2.pos = p1.pos - dir;
		
		// Reflexing the velocity
		v1 = vs::rotate(v1, ang, true);
		v2 = vs::rotate(v2, ang, true);
		vec pre_v1 = v1;

		v1.x -= (1+p1.bounciness) * m2 / (m1+m2) * (v1.x-v2.x);
		v2.x -= (1+p2.bounciness) * m1 / (m1+m2) * (v2.x-pre_v1.x);
		
		p1.vel = vs::rotate(v1, ang, false);
		p2.vel = vs::rotate(v2, ang, false);


		//vec dir = vs::norm(p1.pos - p2.pos);
		//double intersection = p1.rad + p2.rad - vs::dist(p1.pos, p2.pos);

		// k ~ m * (v_max / x_max)^2
		// m - mass of these most energetic particles
		// E = (m * v^2) / 2
		/*double e1 = p1.mass * pow(vs::length(p1.vel), 2),
			   e2 = p2.mass * pow(vs::length(p2.vel), 2);
		double m = (e1 > e2) ? p1.mass : p2.mass;
		double k = m * pow(v_max/x_max, 2) * 0.5;*/
		//double k = min(p1.mass, p2.mass) * pow(v_max/x_max, 2) * 0.05;

		// Fn = k*x
		//vec restoring_force = dir * intersection * 10.;

		/*p1.accel += restoring_force / p1.mass;
		p2.accel -= restoring_force / p2.mass;*/

		/*double v1 = vs::length(p1.vel), v2 = vs::length(p2.vel),
			   m1 = p1.mass, m2 = p2.mass, 
			   k1 = p1.bounciness, k2 = p2.bounciness;

		vec normal {-dir.y, dir.x};

		p1.accel = 2.*(normal * vs::dot(normal, p1.vel) - p1.vel) * (double)FPS * intersection / 5.;
		p2.accel = 2.*(normal * vs::dot(normal, p2.vel) - p2.vel) * (double)FPS * intersection / 5.;*/
	}
}
