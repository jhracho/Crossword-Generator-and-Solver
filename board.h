// Class for the board itself
// Jake Hracho
// board.h
#include <iostream>
#include <vector>
using namespace std;

// Const Global Variables
const int SIZE = 15;
const char noFillBlank = '#';
const char noFillSol = '.';
const char fillBlank = ' ';
const string across = "ACROSS";
const string down = "DOWN";

// Word Structure
struct Word{
  string name;
	int xCord;
	int yCord;
	string direction;
	string clue;
};

// Board Class
class Board{
  public:

// Regular Methods
	  	Board();
		~Board();
		void displayBlank();
		void displaySolved();
		void constructBlank();
		void placeLargest(Word &);
		void placeWord(Word &, int, int, int);

// Structure Methods
		void pushBlank(string, vector<Word>);
		void getWordIntersect(Word &, int &, int &, int &);
		void setWordName(Word, string);
		void setWordX(Word &, int);
		void setWordY(Word &, int);
		void setWordDown(Word &);
		bool hitBorder(Word, int);
		bool validPlacement(Word &, int, int, int);
		Word initializeWord(string, string);

// Private Stuff
  private:
    	char blankBoard[SIZE][SIZE];
		char solvedBoard[SIZE][SIZE];
};
