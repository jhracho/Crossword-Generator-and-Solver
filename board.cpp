// Implementation of board.h
// Jake Hracho
// board.cpp

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;
#include "board.h"

Board::Board()
{
  for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++){
			blankBoard[i][j] =  noFillBlank;
			solvedBoard[i][j] = noFillSol;
		}
}

// Deconstructor
Board::~Board()
{}

// Constructs the Blank Board based on the solved board
void Board::constructBlank()
{
  for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			if (solvedBoard[i][j] == '.')
				blankBoard[i][j] = noFillBlank;
			else
				blankBoard[i][j] = fillBlank;
		}
	}
}
// Displays the board to be solved
void Board::displayBlank()
{
	cout << "Crossword Puzzle:" << endl;
  	cout << "+" << setfill('-') << setw(SIZE + 1) << "+" << endl;
	for (int i = 0; i < SIZE; i++){
		cout << "|";
		for (int j = 0; j < SIZE; j++){
			cout << blankBoard[i][j];
		}
		cout << "|";
		cout << endl;
	}
	cout << "+" << setfill('-') << setw(SIZE + 1) << "+" << endl;
	cout << endl;
}

void Board::displaySolved()
{
	cout << "Solution:" << endl;
  	cout << "+" << setfill('-') << setw(SIZE + 1) << "+" << endl;
	for (int i = 0; i < SIZE; i++){
		cout << "|";
		for (int j = 0; j < SIZE; j++)
			cout << solvedBoard[i][j];
		cout << "|";
		cout << endl;
	}
	cout << "+" << setfill('-') << setw(SIZE + 1) << "+" << endl;
	cout << endl;
}

void Board::placeLargest(Word &w)
{
	int y = (SIZE - (w.name).size()) / 2;
  	setWordY(w,y);
	setWordX(w,7);
	for (int i = 0; i < (w.name).size(); i++){
    solvedBoard[7][y] = w.name[i];
		y++;
	}

}

void Board::setWordY(Word &w, int y)
{w.yCord = y;}

void Board::setWordX(Word &w, int x)
{w.xCord = x;}

bool Board::hitBorder(Word w, int start)
{
	if (start + w.name.size() - 1 > 40)
		return false;
  return true;	 
}

// Places the word on the board assuming it can be placed
void Board::placeWord(Word &placed, int xInt, int yInt, int wInt)
{
	int x = 0;
	int y = 0;
 	
// Option for each type of placement
	if (placed.direction == down){
	  y = yInt;
		x = xInt - wInt;
		placed.direction = down;
		placed.xCord = x;
		placed.yCord = y;

		for (int i = 0; i < placed.name.size(); i++){
			solvedBoard[x][y] = placed.name[i];
			x++;
		}
	}

	else if (placed.direction == across){
		y = yInt - wInt;
		x = xInt;
		placed.direction = across;
		placed.xCord = x;
		placed.yCord = y;

		for (int i = 0; i < placed.name.size(); i++){
			solvedBoard[x][y] = placed.name[i];
			y++;
		}
	}
}

// Little method that initializes the struct vector in crossword.cpp
Word Board::initializeWord(string s, string c)
{
	Word w;
  w.name = s;
	w.clue = c;
  w.xCord = 0;
	w.yCord = 0;
	w.direction = across;
	return w;
}


// Pushes blank puzzle to the file
void Board::pushBlank(string newFile, vector<Word> words)
{
	ofstream outFile(newFile);
	outFile << "Crossword Puzzle:" << endl;
	outFile << "+" << setfill('-') << setw(SIZE + 1) << "+" << endl;
	for (int i = 0; i < SIZE; i++){
		outFile << "|";
		for (int j = 0; j < SIZE; j++){
			outFile << blankBoard[i][j];
		}
		outFile << "|";
		outFile << endl;
	}
	outFile << "+" << setfill('-') << setw(SIZE + 1) << "+" << endl;
	outFile << endl;

	for (auto it = words.begin(); it != words.end(); it++){
		outFile << setfill(' ') << setw(2) << (*it).xCord << " " << setfill(' ') << setw(3) << (*it).yCord << "    " << setfill(' ') << setw(6) << (*it).direction;
		outFile << "   " << (*it).clue << endl;
	}
}

// Runs through the board to find a possible index point
void Board::getWordIntersect(Word &placed, int& x, int& y, int &w)
{
  for (int i = 0; i < placed.name.size(); i++){
		for (int xRow = 0; xRow < SIZE; xRow++){
			for (int yCol = 0; yCol < SIZE; yCol++){
			  if (placed.name[i] == solvedBoard[xRow][yCol]){
			  	x = xRow;
					y = yCol;
					w = i;
		      if (validPlacement(placed, x, y, w)){
            placeWord(placed, x, y, w);
						return;
					}      
				}
			}
		}
	}
	cout << "Could not place word: " << placed.name << endl;
}

// Checks if the word runs into any words
bool Board::validPlacement(Word &placed, int xInt, int yInt, int wInt){
  
// Gets orientation	
	if (solvedBoard[xInt][yInt+1] != '.' || solvedBoard[xInt][yInt-1] != '.')
		placed.direction = down;
	else if (solvedBoard[xInt+1][yInt] != '.' || solvedBoard[xInt+1][yInt] != '.')
		placed.direction = across;

// Cases to check word validity
	if (placed.direction == down){
    for (int i = 1; i <= wInt; i++){  // Checks left of intersection
			if (solvedBoard[xInt-i][yInt] != '.'){
        cout << "error1";
				return false;
			}
			else if (solvedBoard[xInt-i][yInt+1] != '.'){
        cout << "error2";
				return false;
			}
			else if (solvedBoard[xInt-i][yInt-1] != '.'){
        cout << "error3";
				return false;
		  }
		}
			
    if (solvedBoard[xInt-wInt-1][yInt] != '.'){
			cout << "error4";
			return false;
		}

		for (int i = 1; i <= placed.name.size() - wInt - 1; i++){
			if (solvedBoard[xInt+i][yInt] != '.'){
				cout << "error5";
				return false;
			}
			else if (solvedBoard[xInt+i][yInt+1] != '.'){
				cout << "error6";
				return false;
			}
			else if (solvedBoard[xInt+i][yInt-1] != '.'){
				cout << "error7" << endl;
				cout << solvedBoard[xInt+i][yInt-1] << endl;
				return false;
			}
		}
    if (solvedBoard[xInt + placed.name.size()-wInt][yInt] != '.'){
			cout << "error8";
			cout << solvedBoard[placed.name.size()-wInt][yInt];
			return false;
		}
   
	}

	else if (placed.direction == across){
     for (int i = 1; i <= wInt; i++){  // Checks left of intersection
			if (solvedBoard[xInt][yInt-i] != '.')
				return false;
			else if (solvedBoard[xInt+1][yInt-i] != '.')
				return false;
			else if (solvedBoard[xInt-1][yInt-i] != '.')
				return false;
		}
			
    if (solvedBoard[xInt][yInt-wInt-1] != '.')
			return false;

		for (int i = 1; i <= placed.name.size() - wInt - 1; i++){
			if (solvedBoard[xInt][yInt+i] != '.')
				return false;
			else if (solvedBoard[xInt+1][yInt+i] != '.')
				return false;
			else if (solvedBoard[xInt-1][yInt+i] != '.')
				return false;
		}
    if (solvedBoard[xInt][yInt + placed.name.size()-wInt] != '.')
			return false;
	}

  return true;
}

bool hitBorder(Word placed, int x){

}
