class Bottle
{
private:
    sf::Sprite create_sprite(sf::Texture &tx, sf::Vector2f pos, sf::Vector2f sc)
    {
        sf::Sprite sprite;
        sprite.setTexture(tx);
        sprite.setPosition(pos);
        sprite.setScale(sc);

        return sprite;
    }

public:
    std::vector<sf::Image> btlImg{6};
    std::vector<sf::Sprite> sprites{6};
    Bottle()
    {
        if (!btlImg[0].loadFromFile("./res/emptybtl.png") || !btlImg[1].loadFromFile("./res/bit.png") ||
            !btlImg[2].loadFromFile("./res/half.png") || !btlImg[3].loadFromFile("./res/morehalf.png") ||
            !btlImg[4].loadFromFile("./res/prelast.png"))
        {
            std::cerr << "err" << std::endl;
        }
    }

    void add_sprite(sf::Texture &tx, sf::Vector2f pos, sf::Vector2f sc, short i)
    {
        sprites[i] = create_sprite(tx, pos, sc);
    }
};