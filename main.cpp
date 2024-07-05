#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "./bottle/bottle.h"

#define WIDTH 1024
#define HEIGHT 800

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Vending");

    sf::Image ImageMain;
    if (!ImageMain.loadFromFile("./res/main.png"))
        std::cerr << "err" << std::endl;

    sf::Texture texture;
    texture.loadFromImage(ImageMain);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(WIDTH / 4, 20);

    Bottle btl = Bottle();
    std::vector<sf::Texture> tx{5};
    for (size_t i = 0; i < 5; i++)
    {
        tx[i].loadFromImage(btl.btlImg[i]);
        btl.add_sprite(tx[i], sf::Vector2f(322, 140), sf::Vector2f(0.2, 0.2), i);
    }

    sf::CircleShape btn1(5);
    btn1.setFillColor(sf::Color::White);
    btn1.setPosition(530, 185);
    sf::CircleShape btn2(5);
    btn2.setFillColor(sf::Color::White);
    btn2.setPosition(530, 200);
    sf::CircleShape btn3(5);
    btn3.setFillColor(sf::Color::White);
    btn3.setPosition(530, 215);

    sf::Clock clock;
    float time_interval;

    bool flgPressedFillBtn = false;
    bool flgPressedBtl = false;

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        std::cout << "x: " << pixelPos.x << " y: " << pixelPos.y << std::endl;

        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(sprite);
        window.draw(btl.sprites[0]);

        if ((sf::Mouse::getPosition(window).x >= 529 && sf::Mouse::getPosition(window).x <= 541) &&
            (sf::Mouse::getPosition(window).y >= 184 && sf::Mouse::getPosition(window).y <= 195) &&
            event.type == sf::Event::MouseButtonPressed && !flgPressedFillBtn)
        {
            flgPressedFillBtn = true;
            flgPressedBtl = false;
        }
        if ((sf::Mouse::getPosition(window).x >= 355 && sf::Mouse::getPosition(window).x <= 446) &&
            (sf::Mouse::getPosition(window).y >= 170 && sf::Mouse::getPosition(window).y <= 340) &&
            event.type == sf::Event::MouseButtonPressed && !flgPressedBtl)
        {
            flgPressedFillBtn = false;
            flgPressedBtl = true;
        }

        if (flgPressedBtl)
            clock.restart();

        if (flgPressedFillBtn)
        {
            time_interval = clock.getElapsedTime().asSeconds();
            if (time_interval > 1)
                window.draw(btl.sprites[1]);
            if (time_interval > 3)
                window.draw(btl.sprites[2]);
            if (time_interval > 5)
                window.draw(btl.sprites[3]);
            if (time_interval > 7)
                window.draw(btl.sprites[4]);
        }

        window.draw(btn1);
        window.draw(btn2);
        window.draw(btn3);
        window.display();
    }

    return 0;
}