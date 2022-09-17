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

    /*vector<HBody> bs;
    for (int i=0; i<200; i++) {
        HBody p(1e3);
        p.set_vel(vec(rand() % 400 - 200, rand() % 400 - 200));
        p.pos = vec(rand()%500+200, rand()%500+200);
        p.color = Color(rand()%256, rand()%256, rand()%256); p.rad = 2;

        bs.push_back(p);
    }
    for (HBody &b : bs) scene.join_body(b);*/

    HBody p1(1);
    //p1.set_vel(vec(0, 100));
    p1.pos = vec(450-100, 450);
    p1.color = Color::Cyan; 

    HBody p2(1);
    p2.set_vel(vec(100, -100));
    p2.pos = vec(450+100, 450);
    p2.color = Color::Green; 

    HBody star(3e6); 
    star.rad = 10;
    //star.set_vel(vec(10, -10));
    star.pos = vec(450, 450);
    star.color = Color::Yellow;

    scene.join_body(star);
    scene.join_body(p1);
    scene.join_body(p2);

    //

    RenderTexture rt;
    rt.create(W, H);

    main_loop([&]
    {
        //for (auto b : scene.planets) {
        //    if (b->prev_pos == vs::zero) continue;

        //    vec pos = vec(b->pos.x, H - b->pos.y);
        //    vec p_pos = vec(b->prev_pos.x, H - b->prev_pos.y);

        //    float k = 0.2;
        //    Color col = Color(b->color.r * k, b->color.g * k, b->color.b * k);

        //    //ff::easy_circle(pos, b->rad * 0 + 2, rt, col);
        //    ff::easy_line(pos, p_pos, rt, col);
        //}
        //window.draw(Sprite(rt.getTexture()));

        if (Keyboard::isKeyPressed(Keyboard::Q)) scene.draw_accels();
        
        cout << "FPS: " << round(1 / scene.delta_time * 10) / 10 << " \r";
    }, scene);

    return 0;
}
