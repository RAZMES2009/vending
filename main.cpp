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

    Bottle btl5 = Bottle();
    Bottle btl10 = Bottle();
    std::vector<sf::Texture> tx5{5};
    std::vector<sf::Texture> tx10{5};
    for (size_t i = 0; i < 5; i++)
    {
        tx5[i].loadFromImage(btl5.btlImg[i]);
        btl5.add_sprite(tx5[i], sf::Vector2f(322, 140), sf::Vector2f(0.2, 0.2), i);
        tx10[i].loadFromImage(btl10.btlImg[i]);
        btl10.add_sprite(tx10[i], sf::Vector2f(305, 135), sf::Vector2f(0.25, 0.25), i);
    }

    std::vector<sf::CircleShape> btns{2};
    for (size_t i = 0; i < 2; i++)
    {
        std::cerr << i;
        btns[i].setRadius(5);
        btns[i].setFillColor(sf::Color::White);
        btns[i].setPosition(i ? sf::Vector2f(530, 185) : sf::Vector2f(530, 210));
    }

    sf::Font font;
    if (!font.loadFromFile("./res/font/OrelegaOne-Regular.ttf"))
        std::cerr << "err" << std::endl;

    sf::Text txtMain;
    txtMain.setFont(font);
    txtMain.setString(L"Выберите литраж");
    txtMain.setCharacterSize(12);
    txtMain.setFillColor(sf::Color::White);
    txtMain.setPosition(530, 165);

    sf::Text txtExit;
    txtExit.setFont(font);
    txtExit.setString(L"Заберите воду");
    txtExit.setCharacterSize(10);
    txtExit.setFillColor(sf::Color::White);
    txtExit.setPosition(573, 255);

    std::vector<sf::Text> txtV{2};
    for (size_t i = 0; i < txtV.size(); i++)
    {
        txtV[i].setFont(font);
        txtV[i].setString(i ? L"5 литров" : L"10 литров");
        txtV[i].setCharacterSize(12);
        txtV[i].setFillColor(sf::Color::White);
        txtV[i].setPosition(i ? sf::Vector2f(545, 182) : sf::Vector2f(545, 207));
    }

    std::vector<sf::Text> txtCard{2};
    for (size_t i = 0; i < txtCard.size(); i++)
    {
        txtCard[i].setFont(font);
        txtCard[i].setString(i ? L"Приложите карту" : L"Успешно");
        txtCard[i].setCharacterSize(10);
        txtCard[i].setFillColor(i ? sf::Color::White : sf::Color::Green);
        txtCard[i].setPosition(i ? sf::Vector2f(567, 255) : sf::Vector2f(585, 255));
    }

    sf::Clock clock;
    float time_interval;

    bool flgPressedFillBtn = false, flgPressedBtl = false, flgPressedCard = false;
    std::vector<sf::Sprite> currentBtl;
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

        if ((sf::Mouse::getPosition(window).x >= 355 && sf::Mouse::getPosition(window).x <= 446) &&
            (sf::Mouse::getPosition(window).y >= 170 && sf::Mouse::getPosition(window).y <= 340) &&
            event.type == sf::Event::MouseButtonPressed && !flgPressedBtl)
        {
            flgPressedFillBtn = false;
            flgPressedBtl = true;
            flgPressedCard = false;
            for (size_t i = 0; i < 2; i++)
                txtV[i].setFillColor(sf::Color::White);
        }
        if ((sf::Mouse::getPosition(window).x >= 529 && sf::Mouse::getPosition(window).x <= 541) &&
            (sf::Mouse::getPosition(window).y >= 184 && sf::Mouse::getPosition(window).y <= 195) &&
            event.type == sf::Event::MouseButtonPressed && !flgPressedFillBtn)
        {
            currentBtl = btl5.sprites;
            flgPressedFillBtn = true;
            flgPressedBtl = false;
            txtV[1].setFillColor(sf::Color::Green);
        }
        if ((sf::Mouse::getPosition(window).x >= 528 && sf::Mouse::getPosition(window).x <= 541) &&
            (sf::Mouse::getPosition(window).y >= 208 && sf::Mouse::getPosition(window).y <= 221) &&
            event.type == sf::Event::MouseButtonPressed && !flgPressedFillBtn)
        {
            currentBtl = btl10.sprites;
            flgPressedFillBtn = true;
            flgPressedBtl = false;
            txtV[0].setFillColor(sf::Color::Green);
        }

        if ((sf::Mouse::getPosition(window).x >= 560 && sf::Mouse::getPosition(window).x <= 650) &&
            (sf::Mouse::getPosition(window).y >= 255 && sf::Mouse::getPosition(window).y <= 295) &&
            event.type == sf::Event::MouseButtonPressed && !flgPressedCard && flgPressedFillBtn)
        {
            flgPressedCard = true;
        }

        if (flgPressedBtl)
            clock.restart();

        if (flgPressedCard)
        {
            time_interval = clock.getElapsedTime().asSeconds();
            if (time_interval > 0)
                window.draw(currentBtl[0]);
            if (time_interval > 3)
                window.draw(currentBtl[1]);
            if (time_interval > 5)
                window.draw(currentBtl[2]);
            if (time_interval > 7)
                window.draw(currentBtl[3]);
            if (time_interval > 9)
                window.draw(currentBtl[4]);
            if (time_interval > 11)
            {
                window.draw(currentBtl[5]);
                flgPressedFillBtn = false;
                window.draw(txtExit);
            }
        }

        window.draw(btns[0]);
        window.draw(btns[1]);
        window.draw(txtMain);
        window.draw(txtV[0]);
        window.draw(txtV[1]);
        if (flgPressedFillBtn)
            window.draw(txtCard[flgPressedCard ? 0 : 1]);
        window.display();
    }

    return 0;
}