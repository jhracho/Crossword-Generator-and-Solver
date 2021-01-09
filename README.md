# Crossword-Generator-and-Solver
### Developed in Fall 2019

### Overview
This code, given a set of words, will generate an empty crossword puzzle to fit all of the words. It will also present the user with a solved version of the board, this serving as the answer key. Finally, it will present a list of clues in the form of anagrams in addition to the position of the first letter of each word and whether it goes across or down. If a word cannot fit in the crossword, the code will display that to the user (this is rare).

### Running the code
To compile the code in a bash terminal, simply execute the included Makefile with the following command:
```bash
make
```
There are three different ways this code can be run. 
- First, the user can add words via a manual input. By simply running the following code, the user can follow the prompts on screen and enter the words themselves:
```bash
./crossword
```
- Second, the user can add words via a text file. Run the following code to do so:
```bash
./crossword input.txt
```
- Third, the user can export the clues and empty board to another text file. However, this can only be done when the input words are supplied by a text file:
```bash
./crossword input.txt output.txt
```

### Further developments
I can explore more options for the presentation of word clues. Perhaps I can establish connectivitity with some sort of API that supplies crossword clues when a word is passed in the request body. 
