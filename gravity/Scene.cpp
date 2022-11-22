#include "Scene.h"


void Scene::draw() {
	for (auto& b : planets) b->draw();
}

void Scene::draw_accels() {
	for (auto& b : planets) b->show_accels();
}

void Scene::set_window(RenderWindow* w) { 
	window = w; 
	for (auto& b : planets) b->set_window(w);
}

void Scene::update() {
	delta_time = delta_clock.restart().asSeconds();

#if FPS > 0
	double dt = 1. / FPS;
#else
	double dt = delta_time;
#endif

	for (auto& b : planets) b->update(dt);
	for (auto& c : conns) c.calc_force();
	for (auto& c : conns) c.do_collision();
}

void Scene::join_body(Body& body) {
	body.set_window(window);
	for (auto& b : planets) {
		Connection c(*b, body);
		conns.push_back(c);
	}
	planets.push_back(&body);
}
