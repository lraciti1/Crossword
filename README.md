# Crossword

## Overview
This project is a C program called crossword.c that generates a crossword anagram puzzle. The game allows players to solve anagram-based crossword clues, with both interactive and command-line modes supported. It was developed as a lab assignment to demonstrate key concepts in C programming, including problem decomposition, 2D arrays, file I/O, and interactive gameplay.

## Features
Dual Modes:
Interactive Mode: Solve puzzles directly in the terminal.
Command-line Mode: Generate and display puzzles via terminal commands.
Puzzle Output:
Solution Puzzle: Displays the completed crossword.
Unsolved Puzzle: A blank puzzle with clues to solve.
Anagram Clues: Provides shuffled letters of the words as hints.
Word Validation: Accepts and validates user input against the constraints of the puzzle.
Word Sorting: Automatically stores words in descending order of length for better puzzle arrangement.

## Key Functionalities
1. Reading Input: Reads a text file containing words for the puzzle.
2. Word Storage: Stores words in descending order of length.
3. Puzzle Creation: Places words on the board and generates clues.
4. Clue Generation: Randomizes word letters to create anagrams.
5. Validation: Ensures proper input and logical placement of words.
