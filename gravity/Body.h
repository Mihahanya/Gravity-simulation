#include "h.h"

class Body
{
public:
	Color color;
	double rad;
	
	Body(double mass, vec accel=vec(0, 0)) {
		this->mass = mass; 
		vel = accel;
		pos = vec(0, 0);
		
		color = Color::Yellow;
		rad = 5;
	}

	void set_pos(vec pos) { this->pos = pos; }
	vec get_pos() { return pos; }
	void join_body(Body &b) { bds.push_back(&b); }
	void set_window(RenderWindow &w) { window = &w; }

	void calc_force() {
		accel = vec(0, 0);

		for (auto b : bds) {
			vec dir = norm(b->pos-pos);

			double r = dist(b->pos, pos);
			accel += dir*b->mass / pow(r, 2);
		}
	}

	void update(double dt) {
		vel += accel * dt;
		pos += vel * dt;
	}
	
	void draw() {
		easy_circle(pos, rad, *window, color);
	}

	void show_accels() {
		easy_line(pos, pos+vel, *window, Color(0, 0, 255, 127));
		easy_line(pos, pos+accel, *window, Color(255, 0, 0, 127));
	}

private:
	double mass;
	vec vel, pos, accel;
	
	vector<Body*> bds;
	RenderWindow *window;
};
