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
    scene.color = Color(20, 25, 30);
    scene.set_window(&window);

    vector<Body> bs;
    for (int i=0; i<500; i++) {
        Body p(rand()%100 + 2e3, 0.02);
        p.vel = vec(rand() % 1000 - 500, rand() % 1000 - 500)*0.1;
        p.pos = vec(rand()%W, rand()%H);
        p.color = Color(rand()%256, rand()%256, rand()%256, 200); p.rad = 2.5;

        bs.push_back(p);
    }
    for (Body &b : bs) scene.join_body(b);

    Body p1(1e4, 0.4);
    p1.rad = 10;
    //p1.vel = vec(100, 0);
    p1.vel = vec(50, -80);
    p1.pos = vec(450-200, 460);
    p1.color = Color::Cyan; 

    Body p2(2e6, 0.01);
    p2.rad = 15;
    //p2.vel = vec(-50, 0);
    p2.vel = vec(40, -50);
    p2.pos = vec(W/2-500, H/2);
    p2.color = Color::Green; 

    Body star(2e6, 0.01); 
    star.rad = 15;
    star.vel = vec(-30, 40);
    star.pos = vec(W/2, H/2);
    star.color = Color::Yellow;

    //scene.join_body(p1);
    scene.join_body(p2);
    scene.join_body(star);

    //

    RenderTexture rt;
    rt.create(W, H);

    main_loop([&]
    {
        float system_energy = 0;
        for (auto& b : scene.planets) {
            system_energy += b->mass * pow(vs::length(b->vel), 2.) / 2.; // kinetic energy

            // Bouncing form the borders of window
            if (b->pos.x < 0 or b->pos.x > W) { 
                b->vel.x *= -1.; 
                b->pos.x = max(min(b->pos.x, (double)W), 0.); 
            }
            if (b->pos.y < 0 or b->pos.y > H) { 
                b->vel.y *= -1.; 
                b->pos.y = max(min(b->pos.y, (double)H), 0.);
            }
            
            /*if (b->pos.x < 0) b->pos.x = W; 
            if (b->pos.y < 0) b->pos.y = H; 
            if (b->pos.x > W) b->pos.x = 0; 
            if (b->pos.y > H) b->pos.y = 0;*/ 

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
        if (Keyboard::isKeyPressed(Keyboard::W)) window.draw(Sprite(rt.getTexture()));
        if (Keyboard::isKeyPressed(Keyboard::Q)) scene.draw_accels();
        
        printf("FPS: %.1f, \tkinetic energy: %.3f \r", 1./scene.delta_time, system_energy);

    }, scene);

    return 0;
}
