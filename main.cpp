#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

const int gridHeight = 30; // y cordinate of display
const int gridWidth = 40;  // x cordinate of display
const int cellSize = 18;

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Grid Raycaster", sf::Style::Close);

    // Vector of storing color
    // Vector<vector<Color>> Map (gridHeight, vector<Color>(gridWidth, Color::White));

    int gridY;
    int gridX;

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

    while (window.isOpen())
    {
        Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == Event::Closed)
            {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::R))
        {
            for (int y = 0; y < gridHeight; y++)
            {
                for (int x = 0; x < gridWidth; x++)
                    shape[y][x].setFillColor(Color::Black);
            }
        }

        Vector2i mousePos = Mouse::getPosition(window);

        if (Mouse::isButtonPressed(Mouse::Left) &&  0 < mousePos.x && 0 < mousePos.y)
        {
            gridX = mousePos.x / cellSize;
            gridY = mousePos.y / cellSize;

            if (gridX < gridWidth && gridY < gridHeight)
                shape[gridY][gridX].setFillColor(Color::Cyan);
        }

        window.clear(Color::Black);
        for (int y = 0; y < gridHeight; y++)
        {
            for (int x = 0; x < gridWidth; x++)
                window.draw(shape[y][x]);
        }


        elapsedTime = elapsedTime + clock.restart();
        float fps = 1.f / elapsedTime.asSeconds();
        elapsedTime = Time::Zero;
        cout << "FPS: " << fps << endl;
        
        window.display();
    }
    return 0;
}