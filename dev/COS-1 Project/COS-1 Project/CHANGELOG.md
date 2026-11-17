Sudoku Game with Checker Assistant - Changelog

Week 1 - Project Foundation
	Created the initial C++ Sudoku project.
	Built 9x9 Sudoku board using vectors.
	Created the SudokuBoard, SudokuChecker, and SudokuPuzzle classes.
	Added board display functionality.
	Added checks for duplicate numbers in rows, columns, and 3x3 boxes.
	Created a menu-driven game.
	Added basic player input and validation.
	Protected original puzzle numbers.

Week 2 - Usability  and Improvements
	Improved the Sudoku board display with clearer 3x3 box boarders.
	Allowed players to change their own entries.
	Kept original puzzle numbers protected.
	Improved input error handling for letters entered instead of numbers.
	Added a welcome message and basic Sudoku instructions.
	Improved menu wording and added reminders for players.
	Built and tested the program after these changes.

Week 3 - Testing and Improvements
	Tested Sudoku puzzle completion detection.
	Tested duplicate number detection in rows, columns, and 3x3 boxes.
	Tested invalid letter input.
	Tested invalid row, column, and number ranges.
	Tested entering and erasing player numbers.
	Tested that original puzzle clues remain protected.
	Tested the Reset feature.
	Tested saving and loading a game.
	Tested the menu options and game flow.
	Captured screenshots of program features and test results.
	Removed temporary testing code after testing.
	Rebuilt the project successfully after cleanup.
	Refactored the createPuzzle() function to reduce repeated code when loading puzzle values and identifying original clues.
	Tested both Sudoku puzzles after refactoring to confirm they still display correctly.
	
Week 4 - Final Development and Review
	Added a third Sudoku puzzle to give players more variety.
	Updated random puzzle selection to choose from three puzzles.
	Updated Save and Load validation to support the third puzzle.
	Tested the third puzzle, including Reset, Save, and Load.
	Improved loadPuzzle() to verify saved values against original puzzle clues.
	Added protection against modified save files that attempt to change original clues.
	Tested the protection by modifying an original clue in the save file and confirming that the game rejected it.
	Verified that Option 3 uses isBoardCompleted() to check whether the Sudoku puzzle is solved.
	Updated loadPuzzle() to validate all saved values before changing the active board or locked cells.
	Tested that an invalid save file is rejected without disrupting the active game.
	Verified that normal Save and Load functionality still works after the changes.
	Created three final development issues on the GitHub project board.
	Updated issue statuses to track final testing and code review.
	Reviewed the organization and responsibilities of the Sudoku classes.
	Continued final testing of game features and input validation.
	Updated the README with the Week 4 final project stand-up.

		