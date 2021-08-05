#include <SFML/Graphics.hpp>

const float GRAVITY = 0.07f;

float player_velocityX = 0.0f, player_velocityY = 0.0f;
float player_pos_X = 640.0f, player_pos_Y = 600.0f;

bool is_on_ground = false;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Jumping");
    window.setVerticalSyncEnabled(true);

    sf::CircleShape player(40.0f);
    player.setFillColor(sf::Color::Blue);

    sf::Clock game_clock;

    while (window.isOpen())
    {
        float deltaTime = game_clock.restart().asMilliseconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player_velocityX = -0.5f;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player_velocityX = 0.5f;        
        else 
            player_velocityX = 0.0f; 

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && is_on_ground)
            player_velocityY = -2.5f;

        if (player.getPosition().y < 600.0f)
        {
            is_on_ground = false;
            player_velocityY += GRAVITY;
        }
        else if (player.getPosition().y > 600.0f)
        {
            is_on_ground = true;
            player.setPosition(player.getPosition().x, 600.0f);
            player_velocityY = 0.0f;
        }            

        player.move(player_velocityX * deltaTime, player_velocityY * deltaTime);
       
        window.clear();
        window.draw(player);
        window.display();
    }

    return 0;
}