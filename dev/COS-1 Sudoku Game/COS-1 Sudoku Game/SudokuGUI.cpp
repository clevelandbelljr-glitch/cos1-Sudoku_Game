#include <SFML/Graphics.hpp>
#include <optional>
#include <cstdlib>
#include <string>
#include <ctime>
#include <random>
#include <vector>
#include "SudokuBoard.h"
#include "SudokuChecker.h"
#include "SudokuPuzzle.h"


int main()
{
	SudokuBoard board;
	SudokuChecker checker;
	SudokuPuzzle puzzle;

	sf::Color backgroundColor(240, 240, 240);

	std::random_device rd;
	std::mt19937 colorGenerator(rd());
	std::uniform_int_distribution<int> colorValue(80, 230);

	std::vector<SudokuBoard> boardHistory;

	auto setRandomBackgroundColor = [&]()
	{
		backgroundColor = sf::Color(colorValue(colorGenerator), colorValue(colorGenerator), colorValue(colorGenerator));
	};

	int puzzleChoice = -1;

	bool showDifficultyScreen = true;

	SudokuBoard startingBoard = board;

	sf::Font font;

	if (!font.openFromFile("arial.ttf"))
	{
		return -1;
	}

	sf::RenderWindow window(sf::VideoMode({ 800u, 900u }), "Sudoku Game");

	sf::View gameView(sf::FloatRect({ 0.f, 0.f }, { 800.f, 900.f }));
	window.setView(gameView);

	sf::RectangleShape easyButton(sf::Vector2f(180.f, 60.f));
	easyButton.setPosition({ 100.f, 500.f });
	easyButton.setFillColor(sf::Color(100, 180, 100));

	sf::RectangleShape mediumButton(sf::Vector2f(180.f, 60.f));
	mediumButton.setPosition({ 310.f, 500.f });
	mediumButton.setFillColor(sf::Color(100, 149, 237));

	sf::RectangleShape hardButton(sf::Vector2f(180.f, 60.f));
	hardButton.setPosition({ 520.f, 500.f });
	hardButton.setFillColor(sf::Color(220, 100, 100));

	sf::Text easyText(font, "Easy", 24);
	easyText.setFillColor(sf::Color::White);
	easyText.setPosition({ 160.f, 515.f });

	sf::Text mediumText(font, "Medium", 24);
	mediumText.setFillColor(sf::Color::White);
	mediumText.setPosition({ 345.f, 515.f });

	sf::Text hardText(font, "Hard", 24);
	hardText.setFillColor(sf::Color::White);
	hardText.setPosition({ 580.f, 515.f });

	float cellSize = 70.0f;
	float boardSize = cellSize * 9;

	float startX = (800.0f - boardSize) / 2;
	float startY = (800.0f - boardSize) / 2;

	int selectedRow = -1;
	int selectedCol = -1;

	std::string gameMessage = "Select a cell and enter a number.";


	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (const auto* resized = event->getIf<sf::Event::Resized>())
			{
				float windowWidth = static_cast<float>(resized->size.x);
				float windowHeight = static_cast<float>(resized->size.y);

				gameView.setSize({ windowWidth, windowHeight });
				gameView.setCenter({windowWidth / 2.0f, windowHeight / 2.0f});
				window.setView(gameView);

				cellSize = std::min(windowWidth / 11.0f, windowHeight / 13.0f);
				boardSize = cellSize * 9;

				startX = (windowWidth - boardSize) / 2;
				startY = (windowHeight - boardSize) / 2;
			}

			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}

			if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				sf::Vector2i mousePosition = mousePressed->position;

				sf::Vector2f worldPosition =
					window.mapPixelToCoords(mousePosition);

				int mouseX = static_cast<int>(worldPosition.x);
				int mouseY = static_cast<int>(worldPosition.y);

				if (showDifficultyScreen)
				{
					sf::Vector2f mousePosition(static_cast<float>(mouseX), static_cast<float>(mouseY));

					if (easyButton.getGlobalBounds().contains(mousePosition))
					{
						puzzleChoice = 0;
					}
					else if (mediumButton.getGlobalBounds().contains(mousePosition))
					{
						puzzleChoice = 1;
					}
					else if (hardButton.getGlobalBounds().contains(mousePosition))
					{
						puzzleChoice = 2;
					}

					if (puzzleChoice != -1)
					{
						if (!puzzle.generateCompleteBoard(board, puzzleChoice))
						{
							return -1;
						}

						puzzle.removeNumbers(board, puzzleChoice);
						startingBoard = board;
						setRandomBackgroundColor();
						showDifficultyScreen = false;
						gameMessage = "Puzzle started!";
					}
				}
				else
				{
					selectedCol = static_cast<int>((mouseX - startX) / cellSize);
					selectedRow = static_cast<int>((mouseY - startY) / cellSize);

					if (selectedRow < 0 || selectedRow >= 9 || selectedCol < 0 || selectedCol >= 9)
					{
						selectedRow = -1;
						selectedCol = -1;
					}
				}
			}

			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (showDifficultyScreen)
				{
					if (keyPressed->code == sf::Keyboard::Key::Num1)
					{
						puzzleChoice = 0;
					}
					else if (keyPressed->code == sf::Keyboard::Key::Num2)
					{
						puzzleChoice = 1;
					}
					else if (keyPressed->code == sf::Keyboard::Key::Num3)
					{
						puzzleChoice = 2;
					}

					if (puzzleChoice != -1)
					{
						if (!puzzle.generateCompleteBoard(board, puzzleChoice))
						{
							return -1;
						}

						puzzle.removeNumbers(board, puzzleChoice);
						startingBoard = board;
						setRandomBackgroundColor();
						showDifficultyScreen = false;
						gameMessage = "Puzzle started.";
					}
				}

				if (!showDifficultyScreen)
				{
					if (keyPressed->code == sf::Keyboard::Key::R)
					{
						board = startingBoard;
						selectedRow = -1;
						selectedCol = -1;
						gameMessage = "Puzzle reset.";
					}

					if (keyPressed->code == sf::Keyboard::Key::S)
					{
						puzzle.savePuzzle(board, startingBoard, puzzleChoice);
						gameMessage = "Game saved successfully.";
					}

					if (keyPressed->code == sf::Keyboard::Key::L)
					{
						if (puzzle.loadPuzzle(board, startingBoard, puzzleChoice))
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

					if (keyPressed->code == sf::Keyboard::Key::U)
					{
						if (!boardHistory.empty())
						{
							board = boardHistory.back();
							boardHistory.pop_back();

							selectedRow = -1;
							selectedCol = -1;

							gameMessage = "Move undone.";
						}

						else
						{
							gameMessage = "No moves to undo.";
						}
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
						boardHistory.push_back(board);

						board.setCell(selectedRow, selectedCol, number);
						gameMessage = "Number entered.";

						if (!checker.isValidMove(board, selectedRow, selectedCol, number))
						{
							gameMessage = "The Checker Assistant found a conflict. You can change it.";
						}
						else if (checker.isBoardCompleted(board))
						{
							gameMessage = "You completed the game! Hip, Hip, Hurray!! You did it!!!!";
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
							boardHistory.push_back(board);

							board.setCell(selectedRow, selectedCol, 0);
							gameMessage = "Cell erased.";
						}
					}
					
				}

			}
		}

		window.clear(backgroundColor);

		if (showDifficultyScreen)
		{
			sf::Text titleText(font, "Sudoku Game", 40);
			titleText.setFillColor(sf::Color::Black);
			titleText.setOrigin(titleText.getLocalBounds().getCenter());
			titleText.setPosition({ 400.f, 250.f });
			window.draw(titleText);

			sf::Text difficultyText(font, "Choose Your Difficulty", 28);
			difficultyText.setFillColor(sf::Color::Black);
			difficultyText.setOrigin(difficultyText.getLocalBounds().getCenter());
			difficultyText.setPosition({ 400.f, 350.f });
			window.draw(difficultyText);

			sf::Text choicesText(font, "1 = Easy     2 = Medium     3 = Hard", 24);
			choicesText.setFillColor(sf::Color::Blue);
			choicesText.setOrigin(choicesText.getLocalBounds().getCenter());
			choicesText.setPosition({ 400.f, 450.f });
			window.draw(choicesText);

			window.draw(easyButton);
			window.draw(mediumButton);
			window.draw(hardButton);

			window.draw(easyText);
			window.draw(mediumText);
			window.draw(hardText);

		}

		if (selectedRow != -1 && selectedCol != -1)
		{
			sf::RectangleShape rowHighlight(sf::Vector2f(boardSize, cellSize));

			rowHighlight.setPosition(sf::Vector2f(startX, startY + selectedRow * cellSize));

			rowHighlight.setFillColor(sf::Color(220, 235, 255));

			window.draw(rowHighlight);

			sf::RectangleShape colHighlight(sf::Vector2f(cellSize, boardSize));

			colHighlight.setPosition(sf::Vector2f(startX + selectedCol * cellSize, startY));

			colHighlight.setFillColor(sf::Color(220, 235, 255));

			window.draw(colHighlight);


			sf::RectangleShape highlight(sf::Vector2f(cellSize, cellSize));

			highlight.setPosition(sf::Vector2f(startX + selectedCol * cellSize, startY + selectedRow * cellSize));

			highlight.setFillColor(sf::Color(100, 149, 237));

			window.draw(highlight);
		}

		if (!showDifficultyScreen)
		{
			for (int row = 0; row < 9; row++)
			{
				for (int col = 0; col < 9; col++)
				{
					int number = board.getCell(row, col);

					if (number != 0)
					{
						unsigned int numberFontSize = static_cast<unsigned int>(cellSize * 0.55f);

						sf::Text text(font, std::to_string(number), numberFontSize);

						if (puzzle.isFixed(row, col))
						{
							text.setFillColor(sf::Color::Black);
						}
						else
						{
							text.setFillColor(sf::Color::Blue);
						}

						text.setOrigin(text.getLocalBounds().getCenter());

						text.setPosition({
							startX + col * cellSize + cellSize / 2.0f,
							startY + row * cellSize + cellSize / 2.0f
							});

						window.draw(text);
					}

				}

			}
		}

		for (int i = 0; i <= 9; i++)
		{
			float position = i * cellSize;
			
			sf::RectangleShape verticalLine(sf::Vector2f(i % 3 == 0 ? 6.0f : 1.5f, boardSize));

			verticalLine.setPosition(sf::Vector2f(startX + position, startY));

			verticalLine.setFillColor(sf::Color::Black);
			window.draw(verticalLine);

			sf::RectangleShape horizontalLine(sf::Vector2f(boardSize, i % 3 == 0 ? 6.0f : 1.5f));

			horizontalLine.setPosition(sf::Vector2f(startX, startY + position));

			horizontalLine.setFillColor(sf::Color::Black);
			window.draw(horizontalLine);
		}

		unsigned int messageFontSize = static_cast<unsigned int>(cellSize * 0.30f);

		sf::Text messageText(font, gameMessage, messageFontSize);

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
