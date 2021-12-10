# Sudoku-Assistant
A sudoku assistant that helps people to solve simple 9x9 sudoku puzzles\
Project based on COMP10002 2021 semester 2 Assignment 2

## Stage 1 - Reading and Printing 
Read the input puzzle, print out the formatted sudoku, and the number of unknown cells

## Stage 2 - Grid Checking 
Checks the input grid for mistakes, to ensure that none of the 27 sets in the supplied puzzle have duplicate elements.\
Errors are to be reported according to their set number, from 0 to 26, and also by the set type ("row": 0-8, "col": 9-17, or "sqr": 18-26) and the ordinal number of that set.

## Stage 3 - Implementing Strategy One 
For a valid puzzle, strategy 1 is implemented:\
The three sets that cell is a member of should be examined, accumulating label counts from the 24 labeled cells in those three sets. Each of those labels is a number between 1 and 9. Hence, if there is only on of those nine possible numbers that does not yet occur anywhere in c's three sets, then it must be the label for the empty cell.
