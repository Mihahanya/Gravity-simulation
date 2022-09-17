#pragma once

#include <set>
#include "config.h"
#include "fs.h"
#include "Drawable.h"

class HeavenlyBody;

using HBody = HeavenlyBody;

class HeavenlyBody : public Drawable
{
public:
	double mass, bounciness, rad=5;
	vec pos=vs::zero, prev_pos=vs::zero;

	HeavenlyBody(double mass, double bounciness, Color color);

	void join_body(HeavenlyBody&);
	
	void calc_force();
	void update(double dt);
	void do_collision();

	void add_accel(vec);
	void set_vel(vec);

	void draw() override;
	void show_accels();

private:
	vec vel, accel;
	
	vector<HeavenlyBody*> planets{};
};


HeavenlyBody::HeavenlyBody(double mass, double bounciness=0.5, Color color=Color::White) : 
	mass{mass}, bounciness{bounciness}, Drawable{color} {}

void HeavenlyBody::set_vel(vec vel) { this->vel = vel; }
void HeavenlyBody::add_accel(vec f) { accel += f; }

void HeavenlyBody::join_body(HeavenlyBody& b) { planets.push_back(&b); }

void HeavenlyBody::calc_force() {
	accel = vs::zero;

	for (auto& p : planets) {
		//if (p->forced_pl.count(this)) {
		//	//p->forced_pl.erase(p->forced_pl.find(this));
		//	cout << '1';
		//	continue;
		//}

		vec dir = vs::norm(p->pos - pos);
		double r = vs::dist(p->pos, pos);
		
		accel += dir * p->mass / pow(r, 2);
		//p->accel -= dir * mass / pow(r, 2);

		//forced_pl.insert(p);
	}
}

void HeavenlyBody::update(double dt) {
	prev_pos = pos;
	
	vel += accel * dt;
	pos += vel * dt;
}

inline void HeavenlyBody::do_collision() {
    for (auto& p : planets) {
        if (vs::dist(pos, p->pos) < rad + p->rad) {
			vel -= (vel - p->vel) * (1.+bounciness) * p->mass/(p->mass+mass);
			if (mass <= p->mass) pos = p->pos + vs::norm(pos-p->pos) * (rad+p->rad);
            
            //return;
        }
    }
}

void HeavenlyBody::draw() {
	ff::easy_circle(pos, rad, *window, color);
}

void HeavenlyBody::show_accels() {
	ff::easy_line(pos, prev_pos, *window, Color::Cyan);
	ff::easy_line(pos, pos + vel, *window, Color(0, 0, 255, 127));
	ff::easy_line(pos, pos + accel, *window, Color(255, 0, 0, 127));
}
