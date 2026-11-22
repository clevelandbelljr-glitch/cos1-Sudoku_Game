#include <SFML/Graphics.hpp>
#include <optional>
#include <cstdlib>
#include <string>
#include "SudokuBoard.h"
#include "SudokuChecker.h"
#include "SudokuPuzzle.h"

int main()
{
	SudokuBoard board;
	SudokuChecker checker;
	SudokuPuzzle puzzle;

	int puzzleChoice = rand() % 3;
	puzzle.createPuzzle(board, puzzleChoice);
	
	sf::Font font;
	
	if (!font.openFromFile("arial.ttf"))
	{
		return -1;
	}

	sf::RenderWindow window(sf::VideoMode({ 800u, 800u }), "Sudoku Game");

	const float cellSize = 70.0f;
	const float boardSize = cellSize * 9;

	const float startX = (800.0f - boardSize) / 2;
	const float startY = (800.0f - boardSize) / 2;

	int selectedRow = -1;
	int selectedCol = -1;

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}

			if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				int mouseX = mousePressed->position.x;
				int mouseY = mousePressed->position.y;

				selectedCol = static_cast<int>((mouseX - startX) / cellSize);
				selectedRow = static_cast<int>((mouseY - startY) / cellSize);

				if (selectedRow < 0 || selectedRow >= 9 || selectedCol < 0 || selectedCol >= 9)
				{
					selectedRow = -1;
					selectedCol = -1;
				}
			}
		}

		window.clear(sf::Color(240, 240, 240));

		if (selectedRow != -1 && selectedCol != -1)
		{
			sf::RectangleShape highlight(sf::Vector2f(cellSize, cellSize));

			highlight.setPosition(sf::Vector2f(startX + selectedCol * cellSize, startY + selectedRow * cellSize));

			highlight.setFillColor(sf::Color(173, 216, 239));

			window.draw(highlight);
		}

		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				int number = board.getCell(row, col);

				if (number != 0)
				{
					sf::Text text(font, std::to_string(number), 32);

					text.setFillColor(sf::Color::Black);

					text.setPosition(sf::Vector2f(startX + col * cellSize + 24, startY + row * cellSize + 16));

					window.draw(text);
				}
				
			}
			
		}

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
