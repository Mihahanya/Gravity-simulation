#include "Scene.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    RenderWindow window(sf::VideoMode(W, H), "Physical Simulation", sf::Style::Close | sf::Style::Titlebar, settings);

#if FPS > 0
    window.setFramerateLimit(FPS);
#endif

    // Earth - 6e24, Moon - 7.3e22, Sun - 2e30

    Scene scene;
    scene.set_window(&window);

    vector<Body> bs;
    for (int i=0; i<200; i++) {
        Body p(5);
        p.vel = vec(rand() % 1000 - 500, rand() % 1000 - 500)*0.0;
        p.pos = vec(rand()%500+200, rand()%500+200);
        p.color = Color(rand()%256, rand()%256, rand()%256); p.rad = 5;

        bs.push_back(p);
    }
    for (Body &b : bs) scene.join_body(b);

    Body p1(2e3, 0.8);
    p1.rad = 15;
    p1.vel = vec(100, 0);
    //p1.vel = vec(50, -80);
    p1.pos = vec(450-200, 460);
    p1.color = Color::Cyan; 

    Body p2(2e3, 0.8);
    p2.rad = 10;
    //p2.vel = vec(-50, 0);
    //p2.vel = vec(-70, -80);
    p2.pos = vec(450+200, 460);
    p2.color = Color::Green; 

    Body star(3e6); 
    star.rad = 20;
    //star.vel = vec(10, -10);
    star.pos = vec(450, 450);
    star.color = Color::Yellow;

    scene.join_body(p1);
    scene.join_body(p2);
    //scene.join_body(star);

    //

    RenderTexture rt;
    rt.create(W, H);

    main_loop([&]
    {
        float kinetic_energy = 0;
        for (auto& b : scene.planets) {
            kinetic_energy += b->mass * pow(vs::length(b->vel), 2.) / 2.;

            // Bouncing form the borders of window
            if (b->pos.x < 0 or b->pos.x > W) { 
                b->vel.x *= -1.; 
                b->pos.x = max(min(b->pos.x, (double)W), 0.); 
            }
            if (b->pos.y < 0 or b->pos.y > H) { 
                b->vel.y *= -1.; 
                b->pos.y = max(min(b->pos.y, (double)H), 0.);
            }

            // Tail adding
            if (b->prev_pos != vs::zero) {
                vec pos = vec(b->pos.x, H - b->pos.y);
                vec p_pos = vec(b->prev_pos.x, H - b->prev_pos.y);

                float k = 0.2;
                Color col = Color(b->color.r * k, b->color.g * k, b->color.b * k);

                //ff::easy_circle(pos, b->rad * 0 + 2, rt, col);
                ff::easy_line(pos, p_pos, rt, b->color);
            }
        }
        window.draw(Sprite(rt.getTexture()));

        if (Keyboard::isKeyPressed(Keyboard::Q)) scene.draw_accels();
        
        printf("FPS: %.1f, \tkinetic energy: %.3f \r", scene.delta_time, kinetic_energy);

    }, scene);

    return 0;
}
