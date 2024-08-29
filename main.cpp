/*
* just making a new brach named "harry" for checking the branch system
*
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

const int gridHeight = 24; // y cordinate of display
const int gridWidth = 34;  // x cordinate of display
const int cellSize = 26;

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Grid Raycaster", sf::Style::Close);

    sf::CircleShape red;
    sf::CircleShape blue;
    float radius = 7;

    red.setFillColor(Color::Red);
    red.setRadius(radius);
    red.setOrigin(radius, radius);

    
    blue.setFillColor(Color::Green);
    blue.setRadius(radius);
    blue.setOrigin(radius, radius);

    int gridY;
    int gridX;

    sf::Vertex line[12];

    // vector for Rectangle shape
    vector<vector<RectangleShape>> shape(gridHeight, vector<RectangleShape>(gridWidth));

    for (int y = 0; y < gridHeight; y++)
    {
        for (int x = 0; x < gridWidth; x++)
        {
            shape[y][x].setSize(Vector2f(cellSize, cellSize));
            shape[y][x].setFillColor(Color::Black);
            shape[y][x].setOutlineColor(Color::White);
            shape[y][x].setOutlineThickness(1);
            shape[y][x].setPosition(x * cellSize, y * cellSize);
        }
    }

    // window.setFramerateLimit(120);

    Clock clock;
    
    Time elapsedTime;
    

    float speed = 400.f;

    while (window.isOpen())
    {
        elapsedTime = clock.restart();
        float deltaTime = elapsedTime.asSeconds();

        Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == Event::Closed)
            {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::R))
            {
                for (int y = 0; y < gridHeight; y++)
                {
                    for (int x = 0; x < gridWidth; x++)
                    shape[y][x].setFillColor(Color::Black);
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            red.move(0, -speed * deltaTime);
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            red.move(0, speed * deltaTime);
        }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            red.move(-speed * deltaTime, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            red.move(speed * deltaTime, 0);
        }

        
        

        Vector2i mousePos = Mouse::getPosition(window);
        blue.setPosition(mousePos.x, mousePos.y);

        if (Mouse::isButtonPressed(Mouse::Right) &&  0 < mousePos.x && 0 < mousePos.y)
        {
            gridX = mousePos.x / cellSize;
            gridY = mousePos.y / cellSize;

            if (gridX < gridWidth && gridY < gridHeight)
                shape[gridY][gridX].setFillColor(Color::Cyan);
        }
        if (Mouse::isButtonPressed(Mouse::Left) && 0 < mousePos.x && 0 < mousePos.y)
        {
            sf::Vector2f pointA(100, 100);
            sf::Vector2f pointB(700, 700);

            sf::Vertex line [] = 
            {
               sf::Vertex (pointA, sf::Color::Red), 
               sf::Vertex (pointB, sf::Color::Green)
            };
        }

        window.clear(Color::Black);

        for (int y = 0; y < gridHeight; y++)
        {
            for (int x = 0; x < gridWidth; x++)
                window.draw(shape[y][x]);
        }


        // elapsedTime = elapsedTime + clock.restart();
        float fps = 1.f / deltaTime;
        // elapsedTime = Time::Zero;
        cout << "FPS: " << fps << endl;
        
        window.draw(red);
        window.draw(blue);
        window.draw(line, 2, sf::Lines);
        window.display();
    }
    return 0;
}
