#include <SFML/Graphics.hpp>
#include <optional>

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800u, 800u }), "Sudoku Game");

	const float cellSize = 70.0f;
	const float boardSize = cellSize * 9;

	const float startX = (800.0f - boardSize) / 2;
	const float startY = (800.0f - boardSize) / 2;

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear(sf::Color(240, 240, 240));

		for (int i = 0; i <= 9; i++)
		{
			float position = i * cellSize;
			
			sf::RectangleShape verticalLine(sf::Vector2f(i % 3 == 0 ? 4.0f : 1.5f, boardSize));

			verticalLine.setPosition(sf::Vector2f(startX + position, startY));

			verticalLine.setFillColor(sf::Color::Black);
			window.draw(verticalLine);

			sf::RectangleShape horizontalLine(sf::Vector2f(boardSize, i % 3 == 0 ? 4.0f : 1.5f));

			horizontalLine.setPosition(sf::Vector2f(startX, startY + position));

			horizontalLine.setFillColor(sf::Color::Black);
			window.draw(horizontalLine);
		}

		window.display();
	}
	return 0;
}
