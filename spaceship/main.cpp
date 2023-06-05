#include <SFML/Graphics.hpp>
#include <memory>

/*void moveKeys(std::shared_ptr<sf::Sprite> spaceShip, std::shared_ptr<sf::RenderWindow> window) {
    
}*/

int main() {
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 720), "Spaceship 1.0", sf::Style::Titlebar | sf::Style::Close);
    window->setPosition(sf::Vector2i(0, 0));
    window->setFramerateLimit(30);

    //nave espacial
    auto spaceShipTexture = std::make_shared<sf::Texture>();
    spaceShipTexture->loadFromFile("./spaceship-min.png");
    std::shared_ptr<sf::Sprite> spaceShip = std::make_shared<sf::Sprite>();
    spaceShip->setTexture(*spaceShipTexture);
    spaceShip->setPosition(0, 0);

    //missel
    auto misselTexture = std::make_shared<sf::Texture>();
    misselTexture->loadFromFile("./bullet.png");
    auto missel = std::make_shared<sf::Sprite>(*misselTexture);
    //missel->setColor(sf::Color::Red);
    std::vector<sf::Sprite> missels;
    int shoot = 20;

    //backgroung
    auto bgTexture = std::make_shared<sf::Texture>();
    bgTexture->loadFromFile("./bg.jpg");
    auto bgSprite = std::make_shared<sf::Sprite>(*bgTexture);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        //movimenta a nave
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            spaceShip->move(10.f, 0.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            spaceShip->move(-10.f, 0.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            spaceShip->move(0.f, 10.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            spaceShip->move(0.f, -10.f);
        }

        //verifica se a nave ultrapassou os limites da janela
        if (spaceShip->getPosition().x < 0) {
            spaceShip->setPosition(0, spaceShip->getPosition().y);
        }

        if (spaceShip->getPosition().x > window->getSize().x - spaceShipTexture->getSize().x) {
            spaceShip->setPosition(window->getSize().x - spaceShipTexture->getSize().x, spaceShip->getPosition().y);
        }

        if (spaceShip->getPosition().y < 0) {
            spaceShip->setPosition(spaceShip->getPosition().x, 0);
        }

        if (spaceShip->getPosition().y > window->getSize().y - spaceShipTexture->getSize().y) {
            spaceShip->setPosition(spaceShip->getPosition().x, window->getSize().y - spaceShipTexture->getSize().y);
        }


        if (shoot < 20) {
            ++shoot;
        }

        //posiciona o missel e carrega no vetor de misseis 
        //carrega no pente pra atirar
        //Quando pressionar a tecla de espaço adiciona um missel
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shoot >= 20) {
            missel->setPosition(spaceShip->getPosition().x + 35.f, 
                spaceShip->getPosition().y + (spaceShipTexture->getSize().y / 2.f) + 5.f);
            missels.push_back(*missel);
            shoot = 0;
        }

        //mover e deletar caso ultrapasse a janela
        for (int i{}; i < missels.size(); ++i) {
            missels[i].move(40.f, 0);
            if (missels[i].getPosition().x >= window->getSize().x) {
                missels.erase(missels.begin());
            }
        }

        window->clear();
        window->draw(*bgSprite);
        window->draw(*spaceShip);
        for(auto &m : missels) {
            window->draw(m);
        }
        
        window->display();
    }

    return 0;
}

