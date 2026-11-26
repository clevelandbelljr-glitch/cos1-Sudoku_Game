#include <SFML/Graphics.hpp>
#include <optional>
#include <cstdlib>
#include <string>
#include <ctime>
#include "SudokuBoard.h"
#include "SudokuChecker.h"
#include "SudokuPuzzle.h"

int main()
{
	SudokuBoard board;
	SudokuChecker checker;
	SudokuPuzzle puzzle;

	srand(static_cast<unsigned int>(time(nullptr)));

	int puzzleChoice = rand() % 3;
	puzzle.createPuzzle(board, puzzleChoice);
	
	sf::Font font;
	
	if (!font.openFromFile("arial.ttf"))
	{
		return -1;
	}

	sf::RenderWindow window(sf::VideoMode({ 800u, 900u }), "Sudoku Game");

	const float cellSize = 70.0f;
	const float boardSize = cellSize * 9;

	const float startX = (800.0f - boardSize) / 2;
	const float startY = (800.0f - boardSize) / 2;

	int selectedRow = -1;
	int selectedCol = -1;

	std::string gameMessage = "Select a cell and enter a number.";
	

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

			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->code == sf::Keyboard::Key::R)
				{
					puzzle.createPuzzle(board, puzzleChoice);
					selectedRow = -1;
					selectedCol = -1;
					gameMessage = "Puzzle reset.";
				}

				if (keyPressed->code == sf::Keyboard::Key::S)
				{
					puzzle.savePuzzle(board, puzzleChoice);
					gameMessage = "Game saved successfully.";
				}

				if (keyPressed->code == sf::Keyboard::Key::L)
				{
					if (puzzle.loadPuzzle(board, puzzleChoice))
					{
						gameMessage = "Game loaded successfully.";
						selectedRow = -1;
						selectedCol = -1;
					}

					else
					{
						gameMessage = "No saved game found or fail to load game.";
					}
					
				}

				int number = -1;

				if (keyPressed->code >= sf::Keyboard::Key::Num1 && keyPressed->code <= sf::Keyboard::Key::Num9)
				{
					number = static_cast<int>(keyPressed->code) - static_cast<int>(sf::Keyboard::Key::Num1) + 1;
				}

				if (number != -1 && selectedRow != -1 && selectedCol != -1)
				{
					if (!puzzle.isFixed(selectedRow, selectedCol))
					{
						if (checker.isValidMove(board, selectedRow, selectedCol, number))
						{
							board.setCell(selectedRow, selectedCol, number);
							gameMessage = "Move accepted.";

							if (checker.isBoardCompleted(board))
							{
								gameMessage = "You completed the game! Hip, Hip, Hurray!! You did it!!!!";
							}
						}

						else
						{
							gameMessage = "Invalid move. Pick another number.";
						}
					}

					else
					{
						gameMessage = "Original clue cannot be changed.";
					}
				}

				if (keyPressed->code == sf::Keyboard::Key::Delete || keyPressed->code == sf::Keyboard::Key::Backspace)
				{
					if (selectedRow != -1 && selectedCol != -1)
					{
						if (!puzzle.isFixed(selectedRow, selectedCol))
						{
							board.setCell(selectedRow, selectedCol, 0);
							gameMessage = "Cell erased.";
						}
					}
					
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

					if (puzzle.isFixed(row, col))
					{
						text.setFillColor(sf::Color::Black);
					}
					else
					{
						text.setFillColor(sf::Color::Blue);
					}
					

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

		sf::Text messageText(font, gameMessage, 20);

		messageText.setFillColor(sf::Color::Black);

		messageText.setOrigin(messageText.getLocalBounds().getCenter());

		messageText.setPosition(sf::Vector2f(400, 790));

		window.draw(messageText);

		sf::Text controlsText(font, "R = Reset | S = Save | L = Load | Delete = Erase", 20);
		controlsText.setOrigin(controlsText.getLocalBounds().getCenter());
		controlsText.setPosition({ 400.f, 830.f });
		controlsText.setFillColor(sf::Color::Blue);

		window.draw(controlsText);
		window.display();
	}
	return 0;
}
