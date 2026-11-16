Milestone 4 - Final Development and Review

⚙️ Features Added
	Added a third Sudoku puzzle for more variety.
	Updated random puzzle selection to choose from three puzzles.
	Updated Save and Load to support all three puzzles.
	Tested Reset, Save, and Load with the third puzzle.
	Verified puzzle completion using isBoardCompleted().

🧱 Updates to Your System Design
	Continued using three separate classes:
		SudokuBoard: Stores and displays the Sudoku board.
		SudokuChecker: Checks moves, conflicts, and puzzle completion.
		SudokuPuzzle: Creates puzzles and handles saving, loading, and original number protection.

🧹 Refactoring Improvements
	Reviewed the organization and responsibilities of all three classes.
	Improved loadPuzzle() by validating saved values before updating the active board.
	Used a temporary SudokuPuzzle object to check original clues without changing the active puzzle.
	Cleaned up code formatting to improve readability.

🐛 Bugs Fixed
	Added protection against modified save files that attempt to change original puzzle clues.
	Fixed save validation so invalid or incomplete save files are rejected.
	Verified that invalid save files do not disrupt the active game.
	Confirmed normal Save and Load functionality still works.

🧪 Testing and Improvements
	Tested all three Sudoku puzzles.
	Tested puzzle completion and duplicate number detection.
	Tested invalid letter input and invalid row, column, and number ranges.
	Tested entering and erasing player numbers.
	Tested original number protection.
	Tested Reset, Save, and Load.
	Verified the program builds and runs successfully.

💭 What You Changed and Why
I added another puzzle to give players more variety and improved Save and Load to make the game more reliable. I also reviewed my code and tested different situations to make sure the game handles errors correctly. These changes helped improve the organization, reliability, and overall experience of my Sudoku game.