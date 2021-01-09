// Main Driver for Crossword
// Jake Hracho
// crossword.cpp

#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <vector>
#include <cctype>
#include <fstream>
#include "board.h"
using namespace std;

// Prototypes
string stringShuffle(string);
bool wordValid(string);
void generateClues(vector<string>, vector<string> &);
void displayClues(vector<Word>);
void sortSolutions(vector<string> &);
void createStrucVec(vector<Word> &, vector<string> &, vector<string> &);
void makeUpper(string &);

//Global Variable declarations
vector<string> solutions;
vector<string> clues;
int totalWords = 0;

// Global Variable Declarations
Board crossword;

int main(int argc, char *argv[]){		
// Initializaiton
  	cout << "Anagram Crossword Puzzle Generator" << endl;
	cout << "----------------------------------" << endl;
	cout << endl;

 	if (argc == 1){
    	cout << "Enter a list of words. Type '.' to finish:" << endl;
    	string temp;
			cin >> temp;
			makeUpper(temp);

			while (temp != "."){
				if (solutions.size() == 20){
					cout << "20 words reached, ending list." << endl;
					break;
				}
			if (wordValid(temp)){
        		solutions.push_back(temp);
				totalWords++;
			}
			else{
				cout << "Invalid word. Ensure each word is only letters and between";
				cout << " 2 and 15 characters." << endl;
			}
			cin >> temp;
			makeUpper(temp);	
		}
		cout << "Input complete. Initializing..." << endl;
		
// Sorts the words by Bubble Sort
		sortSolutions(solutions);
		generateClues(solutions, clues);

// Initializes a struct Word vector with the same size as the input length
    	vector<Word> words(totalWords);
		createStrucVec(words, solutions, clues);
		crossword.placeLargest(words[0]);
      
		for (int i = 1; i < words.size(); i++){
			int xIntersect = 0;
			int yIntersect = 0;
			int wIntersect = 0;
      		crossword.getWordIntersect(words[i],xIntersect, yIntersect, wIntersect);
		}

// Displays the solved board, blank board to be solved, and clues
		crossword.displaySolved();
		crossword.constructBlank();
		crossword.displayBlank();
		displayClues(words);
  }

// Input File Type
	else if(argc == 2 || argc == 3){
    	ifstream file;
		string textFile = argv[1];
		file.open(textFile);
		string tempWord;

		while (!file){
      		cout << "Error opening file, enter valid name: ";
			cin >> textFile;
			file.open(textFile);
		}

		while(file.peek() != EOF){
      		getline(file, tempWord);
			totalWords++;
			makeUpper(tempWord);
      		solutions.push_back(tempWord);
		}
	  
// Sorts the words by Bubble Sort
		sortSolutions(solutions);
		generateClues(solutions, clues);

// Initializes a struct Word vector with the same size as the input length
    	vector<Word> words(totalWords);
		createStrucVec(words, solutions, clues);
		crossword.placeLargest(words[0]);
      
		for (int i = 1; i < words.size(); i++){
			int xIntersect = 0;
			int yIntersect = 0;
			int wIntersect = 0;
      		crossword.getWordIntersect(words[i],xIntersect, yIntersect, wIntersect);
		}

// Displays the solved board, blank board to be solved, and clues
		crossword.constructBlank();
		
		if (argc == 2){
	  		crossword.displaySolved();
			crossword.displayBlank();
	  		displayClues(words);
		}

// Input and Output File Type
		
    	if (argc == 3){
      		string newFile = argv[2];
			ofstream outFile(newFile);
			crossword.pushBlank(newFile, words);
			cout << "Puzzle generated in " << newFile << "... Good luck!" << endl;
    	} 
  
  }

	else{
		cout << "Invalid initialization. Please try again." << endl;
		return 1;
	}

	return 0;
}

string stringShuffle(string x){
	random_shuffle(x.begin(), x.end());
  return x;
}


// Checks validity using ASCII values
bool wordValid(string x){
	if (x.size() > 15 || x.size() < 2)
		return false;
  	for (auto it = x.begin(); it != x.end(); it++){
    	if ((*it) < 65 || (*it) > 122 || ((*it) > 90 && (*it) < 97))
			return false;
	}
	return true;
}

// Generates the vector of anagrams for the clues
void generateClues(vector<string> s, vector<string> &c){
	string temp;
	for (auto it = s.begin(); it != s.end(); it++){
    	temp = stringShuffle((*it));
		c.push_back(temp);
	}
}

// Displays the clues and coordinates under the board
void displayClues(vector<Word> w){
  	cout << "Clues:" << endl;
	cout << endl;
	cout << "Row  Col  Direction  Clue" << endl;
	for (auto it = w.begin(); it != w.end(); it++){
    	cout << setfill(' ') << setw(2) << (*it).xCord << " " << setfill(' ') <<  setw(3) << (*it).yCord << "     " << setfill(' ') << setw(6) << (*it).direction;
		cout << "    " << (*it).clue << endl;  
	}
}


// Bubble sort
void sortSolutions(vector<string> &s){
  	string temp;
	for (int i = 0; i < s.size() - 1; i++){
		for (int j = 0; j < s.size() - i - 1; j++){
			if (s[j].size() < s[j+1].size()){
				temp = s[j];
				s[j] = s[j+1];
				s[j+1] = temp;
			}
		}
	}
}

// Initializes the struct Word vector for simplicity
void createStrucVec(vector<Word> &w, vector<string> &s, vector<string> &c){
	 Word temp;
	 for (int i = 0; i < s.size(); i++){
     temp = crossword.initializeWord(s.at(i), c.at(i));
		 w.at(i) = temp;
	 }
}

void makeUpper (string& s)
{
  for (int i = 0; i < s.size(); i++)
	s[i] = toupper(s[i]);
}
