// Lucia Raciti
// Fund Comp
// 11/17/24
// crossfunc.h is function header file for crossword puzzle that calls all the functions from crossfunc.c and defines the global variables of SIZE and MaxWords and creates a struct to store the word, position, direction, and anagram

#define SIZE 15
#define MaxWords 20

typedef struct {
  char word[SIZE];
  int x;
  int y;
  int horizontal;
  char anagram[SIZE];
  int used; 
} Place;

void initialBoards(char [SIZE][SIZE], char [SIZE][SIZE]);
void displayCommand(char [SIZE][SIZE]);
void displayFile(char [SIZE][SIZE], FILE *);
int checkWord(char [SIZE], char [][SIZE]);
void toUpper(char [SIZE]);
int readWordsInput(char [][SIZE]);
int readWordsFile(char [][SIZE], char *);
void sortWords(char [][SIZE], int);
void shuffle(char [SIZE]);
void addFirstWord(char [SIZE][SIZE], char [][SIZE], Place [MaxWords]);

// experimenting
int RunSimulation(char [SIZE][SIZE], char [][SIZE], int, Place [MaxWords]);
Place addWord(char [SIZE][SIZE], char [][SIZE], int, Place, int, Place [MaxWords]);
Place intersection(char [SIZE][SIZE], char [][SIZE], int, Place [MaxWords], int);
int isUsed(char [SIZE], Place [MaxWords], int);
int isHorizontal(char [SIZE][SIZE], int, int);
int validPlacement(char [SIZE][SIZE], char [SIZE], int, int, int);
void displayClues(Place [MaxWords], int);
void displayCluesFile(Place [MaxWords], int, FILE *);
void ChangeCrossword(char [SIZE][SIZE], char [SIZE][SIZE]);
void DisplayCommandWin(char [SIZE][SIZE], char [SIZE][SIZE], Place [MaxWords], int);
int DisplayFile(char [SIZE][SIZE], char [SIZE][SIZE], Place [MaxWords], int, char *);
