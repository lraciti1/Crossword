// Lucia Raciti
// Fund Comp
// 11/17/24
// crossfunc.c is function file for crossword puzzle that creates boards of a crossword puzzle and from words given, creates a crossword puzzle and solution puzzle that uses anagrams as clues

#include <stdio.h>
#include "crossfunc.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

///////// Initial Board Creation //////////
void initialBoards(char solBoard[SIZE][SIZE], char puzBoard[SIZE][SIZE])
{
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      solBoard[i][j] = '.';
      puzBoard[i][j] = '#';
    }
  }
}

///////// display boards to stdout ///////////
void displayCommand(char board[SIZE][SIZE]) {
  // top row
  for (int i = 0; i <= SIZE+1; i++)
    printf("-");
  printf("\n");
  
  // interior of display
  for (int i = 0; i < SIZE; i++) {
    printf("|");
    for (int j = 0; j < SIZE; j++) {
      printf("%c", board[i][j]);
    }
    printf("|\n");
  }

  // bottom row
  for (int i = 0; i <= SIZE+1; i++)
    printf("-");
  printf("\n");
}

//////// display baords to file //////////
void displayFile(char board[SIZE][SIZE], FILE *fpOutput) {

  // top row
  for (int i = 0; i <= SIZE+1; i++)
    fprintf(fpOutput, "-");
  fprintf(fpOutput, "\n");
  
  // interior of display
  for (int i = 0; i < SIZE; i++) {
    fprintf(fpOutput, "|");
    for (int j = 0; j < SIZE; j++) {
      fprintf(fpOutput, "%c", board[i][j]);
    }
    fprintf(fpOutput, "|\n");
  }

  // bottom row
  for (int i = 0; i <= SIZE+1; i++)
    fprintf(fpOutput, "-");
  fprintf(fpOutput, "\n");
}

/////// check word for length and characters //////////
int checkWord(char word[], char words[][SIZE]) {
  if (strlen(word) > SIZE) {  // too long of a word
    printf("Rejecting word. Too long\n");
    return 0;
  }
  else if (strlen(word) < 2) {
    printf("Rejecting word. Too short\n");  // too short of a word
    return 0;
  }
  for (int i = 0 ; i < strlen(word); i++) {
    if (!isalpha(word[i])|| isspace(word[i])) { // non alphabetical letters detected or multiple words entered
      printf("Rejecting Word. Non-alpha characters detected\n");
      return 0;
    }
  }
  toUpper(word); // converts to uppercase
  for (int i = 0; i < MaxWords; i++) {
    if (strcmp(words[i], word) == 0) { // makes sure there is no repeat of words
      printf("Already exists\n");
      return 0;
    }
  }
  return 1;
}

////// change word to all uppercase //////
void toUpper(char word[]) {
  for (int i = 0; i < strlen(word); i++)
    word[i] = toupper(word[i]);
}

/////// read words from command ////////
int readWordsInput(char words[][SIZE]) {
  char input[50]; // creates a string array to hold input
  int totalCount = 0; // keeps track of amount of words entered

  printf("Enter a list of words: \n");
  while (totalCount < MaxWords) {
    fgets(input, 50, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strcmp(input, ".") == 0) break;
    if (checkWord(input, words)) {
      toUpper(input); 
      strcpy(words[totalCount], input);
      totalCount++;
    }
  }
  sortWords(words, totalCount);  // sorts words in descending order
  return totalCount;
}

////// read words from file ////////
int readWordsFile(char words[][SIZE], char *filename) {
  FILE *fp = fopen(filename, "r");
  char input[50];
  int totalCount = 0;

  // if file does not exist
  if (!fp) {
    printf("Error: Could not open file\n");
    return 0;
  }

  // reads input into file and sorts it
  while (!feof(fp) && totalCount < MaxWords) {
    fgets(input, 50, fp);
    input[strcspn(input, "\n")] = '\0';
    if (feof(fp)) break;
    if (totalCount >= MaxWords) break;
    if (strcmp(input, ".") == 0) break;
    toUpper(input);
    strcpy(words[totalCount], input);
    totalCount++;
  } 
  sortWords(words, totalCount);
  fclose(fp);

  return totalCount;
} 

///////// sort words in the list //////////
void sortWords(char words[][SIZE], int count) {
  int swapped = 1;
  char temp[SIZE]; // temporary variable to store word

  while (swapped != 0) {
    swapped = 0;
    for (int i = 0; i < count-1; i++) {
      if (strlen(words[i]) < strlen(words[i+1])) { 
        swapped++; // increments the amount of swapped until none can be swapped
        strcpy(temp, words[i]);
        strcpy(words[i], words[i+1]);
        strcpy(words[i+1], temp);
        }
    }        
  }
}

///////// shuffles letters within each word in array //////////
void shuffle(char word[SIZE]) {
  srand(time(0)); // seed number
  int random_int = 0;
  char tempLetter;

  for (int i = 0; i < strlen(word); i++) {
    random_int = rand() % strlen(word); // random integer to shuffle letter
    tempLetter = word[random_int]; // stores random letter in string to variable
    word[random_int] = word[i];
    word[i] = tempLetter; // flips around the letters
  }
}

//////// first word in puzzle ////////
void addFirstWord(char solboard[SIZE][SIZE], char words[][SIZE], Place wordPlacement[MaxWords]) {
  char word[SIZE];
  char swappedword[SIZE];
  strcpy(word, words[0]);
  strcpy(swappedword, word);
  shuffle(swappedword);

  int length = strlen(word); // length of word
  int row = 7; // middle of board
  int count = 0; // keeps track of letters
  int col1 = (SIZE - length)/2; // where to start the first letter

  for (int j = col1; j < length+col1; j++) {
    solboard[row][j] = word[count];
    count++;
  }
  // adds to the struct array in first position
  strcpy(wordPlacement[0].word, word);
  wordPlacement[0].x = col1;
  wordPlacement[0].y = row;
  wordPlacement[0].horizontal = 1;
  wordPlacement[0].used = 1;
  strcpy(wordPlacement[0].anagram, swappedword);
}


////// Run until all words used or no possibilites //////
int RunSimulation(char solboard[SIZE][SIZE], char words[][SIZE], int count, Place wordPlacement[MaxWords]) {
  int amountUsed = 1; // first word added
  while (amountUsed < count) {
    wordPlacement[amountUsed] = addWord(solboard, words, count, wordPlacement[amountUsed], amountUsed, wordPlacement);
    
    // stops if word cannot be placed by having initial condition of amount.used == 0
    if (wordPlacement[amountUsed].used == 0) {
      printf("\n");
      printf("Unable to place a word!\n");
      return amountUsed;
    }
    amountUsed++;
  }
  return amountUsed;
}


///////// add word //////////
Place addWord(char solboard[SIZE][SIZE], char words[][SIZE], int count, Place wordPlaced, int amountUsed, Place wordPlacement[MaxWords]) {
  wordPlaced = intersection(solboard, words, count, wordPlacement, amountUsed);
  if (wordPlaced.used == 0) return wordPlaced;  // return if word is not in crossword

  char word[SIZE];
  strcpy(word, wordPlaced.word);

  // places word on board one letter at a time and returns struct
  for (int i = 0; i < strlen(word); i++) {
    if (wordPlaced.horizontal == 1)
      solboard[wordPlaced.y][wordPlaced.x + i] = word[i];
    else
      solboard[wordPlaced.y + i][wordPlaced.x] = word[i];
  }
  return wordPlaced;
}


////// Find intersection of a word /////////
Place intersection(char solboard[SIZE][SIZE], char words[][SIZE], int count, Place wordPlacement[MaxWords], int amountUsed) {
  char word[SIZE];
  char swappedWord[SIZE];
  Place placement;
  placement.used = 0; // initialize the used variable
  int counter = 1; // second word in list, first used

  // increment word
  while (counter < count) {
    strcpy(word, words[counter]);

    int countLetter = 0;

    // read through each letter of word
    while (countLetter < strlen(word)) { 
      for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
          if (solboard[i][j] == word[countLetter]) {
            if (validPlacement(solboard, word, i, j, countLetter) && !(isUsed(word, wordPlacement, count))) {
              placement.horizontal = isHorizontal(solboard, i, j); // check if horizontal
              strcpy(swappedWord, word);
 	      shuffle(swappedWord);  // shuffle word to get anagram
	      placement.used = 1; // determines word as used
              strcpy(placement.word, word);
              strcpy(placement.anagram, swappedWord); 
              // horizontal word
              if (placement.horizontal == 1) {
                placement.y = i;
                placement.x = j-countLetter;
                return placement;
              }
              // vertical word
              else {
                placement.y = i-countLetter;
                placement.x = j;
                return placement;
              }
            }
          }
        }
      }
      countLetter++; // increase letter count
    }
    counter++; // increase word cound
  }
  return placement;
}

///// Not used yet? //////
int isUsed(char word[SIZE], Place wordPlacement[MaxWords], int amountUsed) {
  for (int i = 0 ; i < amountUsed; i++) {
    if (strcmp(wordPlacement[i].word, word) == 0) return 1; // is used
  }
  return 0;
}


/////// Horizontal Placement? ////////
int isHorizontal(char solboard[SIZE][SIZE], int row, int col) {
  if (solboard[row][col+1] == '.' || solboard[row][col-1] == '.')
    return 1;
  else
    return 0;
}


///////// Is it valid placement? //////////
int validPlacement(char solboard[SIZE][SIZE], char word[SIZE], int row, int col, int countLetter) {

  int length = strlen(word);

  // horizontal check
  if (isHorizontal(solboard, row, col) == 1) {
    for (int i = col-countLetter; i < col+length-countLetter; i++) {
      if (i == col) continue;
      if (i >= SIZE || i < 0) return 0; // not valid placement 
      if (solboard[row-1][i] != '.') return 0;
      if (solboard[row+1][i] != '.') return 0;
      if (solboard[row][i] != '.' && solboard[row][i] != word[i-(col-countLetter)]) return 0;
    }
    if (solboard[row][(col-countLetter-1)] != '.') return 0;
    if (solboard[row][(col+length-countLetter)] != '.') return 0;
    return 1;
  }
  
  // vertical check
  else {
    for (int i = row-countLetter; i < row+length-countLetter; i++) {
      if (i == row) continue;
      if (i >= SIZE || i < 0) return 0;
      if (solboard[i][col-1] != '.') return 0;
      if (solboard[i][col+1] != '.') return 0;
      if (solboard[i][col] != '.' && solboard[i][col] != word[i-(row-countLetter)]) return 0;
    }
    if (solboard[row-countLetter-1][col] != '.') return 0;
    if (solboard[row+length-countLetter][col] != '.') return 0;
    return 1;
  }
}

////// display clues for command window /////////
void displayClues(Place wordPlacement[MaxWords], int count) {
  char direction[10];
  printf("Clues: \n");
  printf("\n");
  for (int i = 0; i < count; i++) {
    if (wordPlacement[i].horizontal == 1) strcpy(direction, "Across");
    else strcpy(direction, "Down");
    printf("%-2d, %-4d %-7s %s\n", wordPlacement[i].x, wordPlacement[i].y, direction, wordPlacement[i].anagram);
  }
}

//////// display clues to file ///////////
void displayCluesFile(Place wordPlacement[MaxWords], int count, FILE *fpOutput) {
  char direction[10];
  fprintf(fpOutput, "Clues: \n");
  fprintf(fpOutput, "\n");
  for (int i = 0; i < count; i++) {
    if (wordPlacement[i].horizontal == 1) strcpy(direction, "Across");
    else strcpy(direction, "Down");
    fprintf(fpOutput, "%-2d, %-4d %-7s %s\n", wordPlacement[i].x, wordPlacement[i].y, direction, wordPlacement[i].anagram);
  }
}


///////// Change Crossword Puzzle to match Solution //////////
void ChangeCrossword(char solboard[SIZE][SIZE], char puzboard[SIZE][SIZE]) 
{
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (solboard[i][j] != '.') puzboard[i][j] = ' ';
    }
  }
}

///////// output to command window ///////////
void DisplayCommandWin(char solboard[SIZE][SIZE], char puzboard[SIZE][SIZE], Place wordPlacement[MaxWords], int count) {
  printf("\n");
  printf("Solution: \n");
  displayCommand(solboard);
  printf("\n");
  printf("Crossword puzzle: \n");
  displayCommand(puzboard);
  displayClues(wordPlacement, count);
}

/////////// output to another file option ////////////
int DisplayFile(char solboard[SIZE][SIZE], char puzboard[SIZE][SIZE], Place wordPlacement[MaxWords], int count, char *filename) { 
  FILE *fpOutput = fopen(filename, "w");
  if (!fpOutput) {
    printf("Error opening file to add crossword to: %s\n", filename);
    return 1;
  }

  fprintf(fpOutput, "Anagram Crossword Puzzle Generator\n");
  fprintf(fpOutput, "----------------------------------\n");

  fprintf(fpOutput, "\n");
  fprintf(fpOutput, "Solution: \n");
  displayFile(solboard, fpOutput);
  fprintf(fpOutput, "\n");
  fprintf(fpOutput, "Crossword puzzle:\n");
  displayFile(puzboard, fpOutput);
  displayCluesFile(wordPlacement, count, fpOutput);
  printf("Ouput went to file: %s\n", filename);
  return 0;  
}
