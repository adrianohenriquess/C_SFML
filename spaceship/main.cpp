#include <SFML/Graphics.hpp>
#include <memory>

int main()
{
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 720), "Spaceship 1.0", sf::Style::Titlebar | sf::Style::Close);
    auto spaceShipTexture = std::make_shared<sf::Texture>();
    spaceShipTexture->loadFromFile("./spaceship-min.png");

    std::shared_ptr<sf::Sprite> spaceShip = std::make_shared<sf::Sprite>();
    spaceShip->setTexture(*spaceShipTexture);
    spaceShip->setPosition(0, 0);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        window->draw(*spaceShip);
        window->display();
    }

    return 0;
}

