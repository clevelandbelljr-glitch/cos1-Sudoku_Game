#pragma once

#include "SudokuBoard.h"
#include "SudokuChecker.h"
#include <vector>

class SudokuPuzzle
{
private:
	std::vector<std::vector<bool>> fixedCells;

public:
	void createPuzzle(SudokuBoard& board, int puzzleChoice);
	bool generateCompleteBoard(SudokuBoard& board, int puzzleChoice);
	void removeNumbers(SudokuBoard& board, int puzzleChoice);
	void savePuzzle(const SudokuBoard& board, const SudokuBoard& startingBoard, int puzzleChoice) const;
	bool loadPuzzle(SudokuBoard& board, SudokuBoard& startingBoard, int& puzzleChoice);
	bool isFixed(int row, int col) const;
	bool isPuzzleCompleted(const SudokuBoard& board, const SudokuChecker& checker);
	bool fillBoard(SudokuBoard& board);
};