#pragma once

#include "Body.h"

class Scene
{
public:
	double dt;

	vector<Body*> bds;

	void update() {
        //dt = dtc.restart().asSeconds();	
        dt = 1./75.;	
		for (auto b : bds) (*b).update(dt);
		for (auto b : bds) (*b).calc_force();
	}

	void draw() {
		for (auto b : bds) 
			(*b).draw();
	}

	void draw_accels() {
		for (auto b : bds) 
			(*b).show_accels();
	}

	void set_window(RenderWindow &w) { window = &w; }


	void join_body(Body &body) {
		Body *bdy = &body;
		(*bdy).set_window(*window);
		for (auto b : bds) {
			(*bdy).join_body(*b);
			(*b).join_body(*bdy);
		}

		bds.push_back(&body);
	}

private:
	RenderWindow *window;
    Clock dtc;
};
