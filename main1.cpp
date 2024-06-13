#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

const int screenWidth = 800;
const int screenHeight = 600;
const int mapWidth = 24;
const int mapHeight = 24;
const float playerSpeed = 0.005f;
const float rotationSpeed = 0.003f;

int worldMap[mapWidth][mapHeight] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

struct Player
{
    float x, y;
    float dirX, dirY;
    float planeX, planeY;
};

void movePlayer(Player &player, sf::Keyboard::Key key) // this class moves the plyer
{
    if (key == sf::Keyboard::W)
    {
        if (worldMap[int(player.x + player.dirX * playerSpeed)][int(player.y)] == 0)
            player.x += player.dirX * playerSpeed;
        if (worldMap[int(player.x)][int(player.y + player.dirY * playerSpeed)] == 0)
            player.y += player.dirY * playerSpeed;
    }
    if (key == sf::Keyboard::S)
    {
        if (worldMap[int(player.x - player.dirX * playerSpeed)][int(player.y)] == 0)
            player.x -= player.dirX * playerSpeed;
        if (worldMap[int(player.x)][int(player.y - player.dirY * playerSpeed)] == 0)
            player.y -= player.dirY * playerSpeed;
    }
    if (key == sf::Keyboard::A)
    {
        float oldDirX = player.dirX;
        player.dirX = player.dirX * cos(rotationSpeed) - player.dirY * sin(rotationSpeed);
        player.dirY = oldDirX * sin(rotationSpeed) + player.dirY * cos(rotationSpeed);
        float oldPlaneX = player.planeX;
        player.planeX = player.planeX * cos(rotationSpeed) - player.planeY * sin(rotationSpeed);
        player.planeY = oldPlaneX * sin(rotationSpeed) + player.planeY * cos(rotationSpeed);
    }
    if (key == sf::Keyboard::D)
    {
        float oldDirX = player.dirX;
        player.dirX = player.dirX * cos(-rotationSpeed) - player.dirY * sin(-rotationSpeed);
        player.dirY = oldDirX * sin(-rotationSpeed) + player.dirY * cos(-rotationSpeed);
        float oldPlaneX = player.planeX;
        player.planeX = player.planeX * cos(-rotationSpeed) - player.planeY * sin(-rotationSpeed);
        player.planeY = oldPlaneX * sin(-rotationSpeed) + player.planeY * cos(-rotationSpeed);
    }

    std::cout<< "x" << " " << player.x << " " << "y" << " " << player.y << " " << player.x + player.y << std::endl;
    std::cout<< "dirX" << " " << player.dirX << " " << "dirY"  << " " << player.dirY << " " << player.dirX + player.dirY << std::endl;
    std::cout<< "planeX" << " " << player.planeX << " " << "planeY" << " " << player.planeY << " " << player.planeX + player.planeY << std::endl;
}

void renderScene(sf::RenderWindow &window, Player &player)
{
    for (int x = 0; x < screenWidth; x++)
    {
        float cameraX = 2 * x / float(screenWidth) - 1;
        float rayDirX = player.dirX + player.planeX * cameraX;
        float rayDirY = player.dirY + player.planeY * cameraX;

        int mapX = int(player.x);
        int mapY = int(player.y);

        float sideDistX, sideDistY;

        float deltaDistX = std::abs(1 / rayDirX);
        float deltaDistY = std::abs(1 / rayDirY);
        float perpWallDist;

        int stepX, stepY;

        bool hit = false;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (player.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player.x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (player.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player.y) * deltaDistY;
        }

        while (!hit)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (worldMap[mapX][mapY] > 0)
                hit = true;
        }

        if (side == 0)
            perpWallDist = (mapX - player.x + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - player.y + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(screenHeight / perpWallDist);

        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight)
            drawEnd = screenHeight - 1;

        sf::Color color;
        switch (worldMap[mapX][mapY])
        {
        case 1:
            color = sf::Color::Red;
            break;
        case 2:
            color = sf::Color::Green;
            break;
        case 3:
            color = sf::Color::Blue;
            break;
        case 4:
            color = sf::Color::White;
            break;
        default:
            color = sf::Color::Yellow;
            break;
        }

        if (side == 1)
            color = sf::Color(color.r / 2, color.g / 2, color.b / 2);

        sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(x, drawStart), color),
                sf::Vertex(sf::Vector2f(x, drawEnd), color)};
        window.draw(line, 2, sf::Lines);
  
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Raycaster");

    Player player = {22.0f, 12.0f, -1.0f, 0.0f, 0.0f, 0.66f};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            movePlayer(player, sf::Keyboard::W);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            movePlayer(player, sf::Keyboard::S);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            movePlayer(player, sf::Keyboard::A);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            movePlayer(player, sf::Keyboard::D);

        window.clear();
        renderScene(window, player);     
        window.display();
    }

    return 0;
}
