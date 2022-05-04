#include "Scene.h"

const int W = 700, H = 700;

int main()
{
    RenderWindow window(VideoMode(700, 700), "Simulation", Style::Close | Style::Titlebar);
    
    // Earth - 6e24, Moon - 7.3e22, Sun - 2e30

    Body p1(1e5, vec(0, 100)); 
    p1.set_pos(vec(250, 350));
    p1.color = Color::Cyan; p1.rad = 5;

    Body p2(1e5, vec(100, 10)); 
    p2.set_pos(vec(370, 250));
    p2.color = Color::Green; p2.rad = 4;

    Body star(1e6, vec(0, 0)); 
    star.set_pos(vec(350, 350));
    star.color = Color::Yellow; star.rad = 10;

    Scene scene;
    scene.set_window(window);
    scene.join_body(star);
    scene.join_body(p1);
    scene.join_body(p2);

    //

    RenderTexture rt;
    rt.create(W, H);

    while (window.isOpen())
    {       
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();

        for (auto b : scene.bds) {
            vec pos = vec((*b).get_pos().x, H-(*b).get_pos().y);

            float k = 0.2;
            Color col = Color((*b).color.r*k, (*b).color.g*k, (*b).color.b*k);

		    easy_circle(pos, (*b).rad, rt, col);
        }
        window.draw(Sprite(rt.getTexture()));

        scene.update();
        scene.draw();
        scene.draw_accels();

        window.display();
    }

    return 0;
}
