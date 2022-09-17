#pragma once

#include "HeavenlyBody.h"

class Scene;

void main_loop(auto, Scene&);

class Scene : public Drawable
{
public:
	vector<HBody*> planets{};
	double delta_time = 0.01; // ~ 100 fps
	bool pause = false;

	void update();

	void draw() override;
	void draw_accels();

	void join_body(HBody &body);
	void set_window(RenderWindow* w) override;

	friend void main_loop(auto, Scene&);

private:
    sf::Clock delta_clock;
};


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
	for (auto& b : planets) b->calc_force();
	for (auto& b : planets) b->do_collision();
}

void Scene::join_body(HBody& body) {
	body.set_window(window);
	for (auto& b : planets) {
		body.join_body(*b);
		b->join_body(body);
	}

	planets.push_back(&body);
}


void main_loop(auto main, Scene& scene) {
	bool is_focuse = true;
	while (scene.window->isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::P)) scene.pause = true;
		else scene.pause = false;

		Event e;
		while (scene.window->pollEvent(e)) {
			if (e.type == Event::Closed) scene.window->close();

			if (e.type == Event::LostFocus) is_focuse = false;
			if (e.type == Event::GainedFocus) is_focuse = true;
		}
		if (!is_focuse) continue;

		scene.window->clear(scene.color);

		scene.draw();
		scene.update();

		main();

		scene.window->display();
	}
}
