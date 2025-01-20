// Lucia Raciti
// Fund Comp
// 11/17/24
// crossword.c is main file for crossword puzzle that determines the amount of arguments int he command line and displays the proper outputs based on these arguments


#include <stdio.h>
#include "crossfunc.h"
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {

  char solBoard[SIZE][SIZE];
  char puzBoard[SIZE][SIZE];
  char words[20][SIZE];
  char mixedWords[20][SIZE];
  int count;
  Place wordPlacement[20];

  // create initial boards
  initialBoards(solBoard, puzBoard);

  // if no file entered after executable
  if (argc == 1) {
    printf("Anagram Crossword Puzzle Generator\n");
    printf("----------------------------------\n");
    count = readWordsInput(words);
  }
  // if file is read after executable, read from file
  else if (argc == 2 || argc == 3) {
    count = readWordsFile(words, argv[1]);
    if (count == 0) return 0;
  }
  else {
  // if too many arguments entered
    printf("Too many arguments\n");
    return 0;
  }

  // adds first word to puzzle
  addFirstWord(solBoard, words, wordPlacement);

  // runs simulation until all words accounted for a word is not possible on crossword
  count = RunSimulation(solBoard, words, count, wordPlacement);

  // changes the boards to the new characters
  ChangeCrossword(solBoard, puzBoard);

  // if only executable or one filename entered in command line
  if (argc == 1 || argc == 2) DisplayCommandWin(solBoard, puzBoard, wordPlacement, count);
  // if two files entered in command line along with exectuable
  else DisplayFile(solBoard, puzBoard, wordPlacement, count, argv[2]);

  return 0;
}
