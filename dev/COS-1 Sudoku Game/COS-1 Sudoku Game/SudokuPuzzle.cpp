#include "SudokuPuzzle.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>



void SudokuPuzzle::createPuzzle(SudokuBoard& board, int puzzleChoice)
{
	int puzzle[9][9] =
	{
		{ 5,3,0,0,7,0,0,0,0 },
		{ 6,0,0,1,9,5,0,0,0 },
		{ 0,9,8,0,0,0,0,6,0 },
		{ 8,0,0,0,6,0,0,0,3 },
		{ 4,0,0,8,0,3,0,0,1 },
		{ 7,0,0,0,2,0,0,0,6 },
		{ 0,6,0,0,0,0,2,8,0 },		
		{ 0,0,0,4,1,9,0,0,5 },
		{ 0,0,0,0,8,0,0,7,9 }
	};

	int puzzle2[9][9] =
	{
		{ 0,2,0,6,0,8,0,0,0 },
		{ 5,8,0,0,0,9,7,0,0 },
		{ 0,0,0,0,4,0,0,0,0 },
		{ 3,7,0,0,0,0,5,0,0 },
		{ 6,0,0,0,0,0,0,0,4 },
		{ 0,0,8,0,0,0,0,1,3 },
		{ 0,0,0,0,2,0,0,0,0 },
		{ 0,0,9,8,0,0,0,3,6 },
		{ 0,0,0,3,0,6,0,9,0 }
	};

	int puzzle3[9][9] =
	{
		{ 0,0,0,2,6,0,7,0,1 },
		{ 6,8,0,0,7,0,0,9,0 },
		{ 1,9,0,0,0,4,5,0,0 },
		{ 8,2,0,1,0,0,0,4,0 },
		{ 0,0,4,6,0,2,9,0,0 },
		{ 0,5,0,0,0,3,0,2,8 },
		{ 0,0,9,3,0,0,0,7,4 },
		{ 0,4,0,0,5,0,0,3,6 },
		{ 7,0,3,0,1,8,0,0,0 }
	};

	fixedCells = std::vector<std::vector<bool>>(9, std::vector<bool>(9, false));

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			int number;

			if (puzzleChoice == 0)
			{
				number = puzzle[row][col];
			}

			else if (puzzleChoice == 1)
			{
				number = puzzle2[row][col];
			}

			else
			{
				number = puzzle3[row][col];
			}

			board.setCell(row, col, number);
			fixedCells[row][col] = (number != 0);
		}
	}
}

bool SudokuPuzzle::generateCompleteBoard(SudokuBoard& board, int puzzleChoice)
{
	fixedCells = std::vector<std::vector<bool>>(9, std::vector<bool>(9, false));

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			board.setCell(row, col, 0);
		}
	}

	return fillBoard(board);
}

void SudokuPuzzle::removeNumbers(SudokuBoard& board, int puzzleChoice)
{
	int numbersToRemove = 0;

	if (puzzleChoice == 0)
	{
		numbersToRemove = 25;
	}
	
	else if (puzzleChoice == 1)
	{
		numbersToRemove = 45;
	}

	else if (puzzleChoice == 2)
	{
		numbersToRemove = 55;
	}

	static std::mt19937 rng(std::random_device{}());

	std::vector<int> positions(81);

	for (int i = 0; i < 81; i++)
	{
		positions[i] = i;
	}

	std::shuffle(positions.begin(), positions.end(), rng);

	for (int i = 0; i < numbersToRemove; i++)
	{
		int row = positions[i] / 9;
		int col = positions[i] % 9;

		board.setCell(row, col, 0);
	}

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			fixedCells[row][col] = (board.getCell(row, col) != 0);
		}
	}
}



bool SudokuPuzzle::isFixed(int row, int col) const
{
	return fixedCells[row][col];
}

bool SudokuPuzzle::isPuzzleCompleted(const SudokuBoard& board, const SudokuChecker& checker)
{
	return checker.isBoardCompleted(board);
}

void SudokuPuzzle::savePuzzle(const SudokuBoard& board, const SudokuBoard& startingBoard, int puzzleChoice) const
{
	std::ofstream file("sudoku_save.txt");

	if (!file)
	{
		std::cout << "Unable to save puzzle.\n";
		return;
	}

	file << puzzleChoice << "\n";

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			file << startingBoard.getCell(row, col) << " ";
		}

		file << "\n";
	}

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			file << board.getCell(row, col) << " ";
		}

		file << "\n";
	}

	if (file)
	{
		std::cout << "Puzzle saved successfully.\n";
	}

	else
	{
		std::cout << "Error while saving puzzle.\n";
	}
}

bool SudokuPuzzle::loadPuzzle(SudokuBoard& board, SudokuBoard& startingBoard, int& puzzleChoice)
{
	std::ifstream file("sudoku_save.txt");

	if (!file)
	{
		return false;
	}

	int savedChoice;
	file >> savedChoice;

	if (!file || savedChoice < 0 || savedChoice > 2)
	{
		return false;
	}

	int savedGrid[9][9];

	int savedStartingGrid[9][9];

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			int number;

			if (!(file >> number))
			{
				return false;
			}

			if (number < 0 || number > 9)
			{
				return false;
			}

			savedStartingGrid[row][col] = number;
		}
	}

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			int number;

			if (!(file >> number))
			{
				return false;
			}

			if (number < 0 || number > 9)
			{
				return false;
			}

			if (savedStartingGrid[row][col] != 0 &&
				number != savedStartingGrid[row][col])
			{
				return false;
			}
						
			savedGrid[row][col] = number;
		}
	}

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			startingBoard.setCell(row, col, savedStartingGrid[row][col]);

			fixedCells[row][col] = (savedStartingGrid[row][col] != 0);
		}
	}

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			board.setCell(row, col, savedGrid[row][col]);
		}
	}

	puzzleChoice = savedChoice;
	return true;
}

bool isSafe(SudokuBoard& board, int row, int col, int number)
{
	for (int i = 0; i < 9; i++)
	{
		if (board.getCell(row, i) == number)
			return false;

		if (board.getCell(i, col) == number)
			return false;
	}

	int startRow = row - row % 3;
	int startCol = col - col % 3;

	for (int r = startRow; r < startRow + 3; r++)
	{
		for (int c = startCol; c < startCol + 3; c++)
		{
			if (board.getCell(r, c) == number)
				return false;
		}
	}

	return true;
}

bool SudokuPuzzle::fillBoard(SudokuBoard& board)
{
	static std::mt19937 rng(std::random_device{}());

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (board.getCell(row, col) == 0)
			{
				std::vector<int> numbers = { 1,2,3,4,5,6,7,8,9 };

				std::shuffle(numbers.begin(), numbers.end(), rng);

				for (int number : numbers)
				{
					if (isSafe(board, row, col, number))
					{
						board.setCell(row, col, number);

						if (fillBoard(board))
						{
							return true;
						}

						board.setCell(row, col, 0);
					}
				}

				return false;
			}
		}
	}

	return true;
}