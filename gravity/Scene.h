#pragma once

#include "Body.h"
#include "Connection.h"

class Scene;

void main_loop(auto main_loop_activity, Scene&);


class Scene : public Drawable
{
public:
	vector<Body*> planets{};
	double delta_time = 0.01; // ~ 100 fps
	bool pause = false;

	void update();

	void draw() override;
	void draw_accels();

	void join_body(Body &body);
	void set_window(RenderWindow* w) override;

	friend void main_loop(auto, Scene&);

private:
    sf::Clock delta_clock;

	vector<Connection> conns{};
};


void main_loop(auto main_loop_activity, Scene& scene) {
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
		
		main_loop_activity();
		
		scene.update();

		scene.window->display();
	}
}

