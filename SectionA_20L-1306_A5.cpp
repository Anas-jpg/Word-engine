#include <iostream>
#include <fstream>
#include <string>
#include<time.h>
#include <locale>
#include <climits>
#include <windows.h>
using namespace std;
bool placed = true;
enum direction { LEFT_RIGHT, RIGHT_LEFT, DOWN, UP, RIGHT_DOWN, RIGHT_UP, LEFT_DOWN, LEFT_UP };
const int Max = 50;
struct wordPuzzle
{
	
	int version;
	int totalRows;
	int totalColumns;
	char puzzle[Max][Max];

};

struct wordFind
{
	string word;
	bool found;
	int row;
	int column;
	direction target;
	int foundCount;
};
void findWord(wordPuzzle& game, wordFind& Finder);

// read the puzzle from the input file
bool readPuzzle(wordPuzzle& game, string inputFileName);

// display the Grid of THe Puzzle
void displayPuzzle(wordPuzzle& game);
void ReadColRows(wordPuzzle& game, string inputwordList)
{
	ifstream file;
	file.open(inputwordList);
	if (!file)
	{
		return;
	}
	file >> game.totalRows;
	file >> game.totalColumns;
}
bool readPuzzle(wordPuzzle& game, string inputwordList)
{

	ifstream file;
	string text;
	int i = 0;
	int nums = 0;
	game.version = 2;
	file.open(inputwordList);
	if (!file)
	{
		return false;
	}
	while (file >> text)
	{



		for (int k = 0; k < game.totalColumns; k++)
		{
			game.puzzle[i][k] = toupper(text[k]);
			nums += 1;
		}

		i += 1;
	}

	//To check that the all entries are present in the Grid
	if (nums != (game.totalRows * game.totalColumns))
	{
		return false;
	}
	file.close();
	return true;
}
void displayPuzzle(wordPuzzle& game)
{
	//Display the Grid On Console
	for (int i = 0; i < game.totalRows; i++)
	{
		for (int k = 0; k < game.totalColumns; k++)
		{
			cout << game.puzzle[i][k];
		}
		cout << endl;
	}
}
void findWord(wordPuzzle& game, wordFind& Finder)
{
	Finder.foundCount = 0;
	for (int i = 0; i < game.totalRows; i++)
	{
		for (int k = 0; k < game.totalColumns; k++)
		{
			if (game.puzzle[i][k] == Finder.word[0])
			{
				//  To keep record of how many letters in a direction Existing with the appropriate letter in the game word
				int tracker = 0;
				int Tmpi = i;
				int Tmpk = k;
				bool a = true;
				if (game.puzzle[i - 1][k] == Finder.word[1] && (i >= static_cast<int>(Finder.word.length()) - 1))
				{
					while (a && tracker < static_cast<int>(Finder.word.length() - 1))
					{
						if (game.puzzle[Tmpi - 1][Tmpk] == Finder.word[tracker + 1])
						{
							Tmpi--;
							tracker++;
						}
						else
						{
							a = false;
						}

					}
					if ((tracker + 1) == static_cast<int>(Finder.word.length()))
					{
						Finder.target = UP;
						Finder.foundCount += 1;
						Finder.row = i;
						Finder.column = k;
						Finder.found = true;
					}
					tracker = 0;
				}
				Tmpi = i;
				Tmpk = k;
				a = true;
				if ((game.puzzle[i - 1][k - 1] == Finder.word[1]) && (k >= static_cast<int>(Finder.word.length() - 1)) && (static_cast<int>(Finder.word.length()) - 1 <= i))
				{
					while (a && tracker < static_cast<int>(Finder.word.length() - 1))
					{
						if (game.puzzle[Tmpi - 1][Tmpk - 1] == Finder.word[tracker + 1])
						{
							Tmpk--;
							Tmpi--;
							tracker++;
						}
						else
						{
							a = false;
						}
					}
					if ((tracker + 1) == static_cast<int>(Finder.word.length()))
					{
						Finder.target = LEFT_UP;
						Finder.foundCount += 1;
						Finder.row = i;
						Finder.column = k;
						Finder.found = true;

					}
					tracker = 0;
				}
				a = true;
				Tmpi = i;
				Tmpk = k;
				if (game.puzzle[i - 1][k + 1] == Finder.word[1] && (static_cast<int>(Finder.word.length()) - 1 <= i) && ((game.totalColumns - k - 1) >= static_cast<int>(Finder.word.length() - 1)))
				{
					while (a && tracker < static_cast<int>(Finder.word.length()) - 1)
					{
						if (game.puzzle[Tmpi - 1][Tmpk + 1] == Finder.word[tracker + 1])
						{
							Tmpk++;
							Tmpi--;
							tracker++;
						}
						else
						{
							a = false;
						}
					}
					if ((tracker + 1) == static_cast<int>(Finder.word.length()))
					{
						Finder.target = RIGHT_UP;
						Finder.foundCount += 1;
						Finder.row = i;
						Finder.column = k;
						Finder.found = true;
					}
					tracker = 0;

				}
				Tmpi = i;
				Tmpk = k;
				a = true;
				if (game.puzzle[i][k + 1] == Finder.word[1] && game.totalColumns - k >= static_cast<int>(Finder.word.length()))
				{
					while (a && tracker < static_cast<int>(Finder.word.length() - 1))
					{
						if (game.puzzle[Tmpi][Tmpk + 1] == Finder.word[tracker + 1])
						{
							Tmpk++;
							tracker++;
						}
						else
						{
							a = false;
						}
					}
					if ((tracker + 1) == static_cast<int>(Finder.word.length()))
					{
						Finder.target = LEFT_RIGHT;
						Finder.foundCount += 1;
						Finder.row = i;
						Finder.column = k;
						Finder.found = true;
					}
					tracker = 0;
				}
				a = true;
				Tmpi = i;
				Tmpk = k;
				if (game.puzzle[i][k - 1] == Finder.word[1] && (k >= static_cast<int>(Finder.word.length() - 1)))
				{
					while (a && (tracker < static_cast<int>(Finder.word.length() - 1)))
					{
						if (game.puzzle[Tmpi][Tmpk - 1] == Finder.word[tracker + 1])
						{
							Tmpk--;
							tracker++;
						}
						else
						{
							a = false;
						}

					}
					if (((tracker + 1) == static_cast<int>(Finder.word.length())))
					{
						Finder.foundCount += 1;
						Finder.target = RIGHT_LEFT;
						Finder.row = i;
						Finder.column = k;
						Finder.found = true;

					}
					tracker = 0;
				}
				a = true;
				Tmpi = i;
				Tmpk = k;
				if ((game.puzzle[i + 1][k + 1] == Finder.word[1] && game.totalColumns - k >= static_cast<int>(Finder.word.length()) && game.totalRows >= static_cast<int>(Finder.word.length())))
				{
					while (a && tracker < static_cast<int>(Finder.word.length() - 1))
					{
						if (game.puzzle[Tmpi + 1][Tmpk + 1] == Finder.word[tracker + 1])
						{
							Tmpk++;
							Tmpi++;
							tracker++;
						}
						else
						{
							a = false;
						}
					}
					if ((tracker + 1) == static_cast<int>(Finder.word.length()))
					{
						Finder.foundCount += 1;
						Finder.target = RIGHT_DOWN;
						Finder.row = i;
						Finder.column = k;
						Finder.found = true;

					}
					tracker = 0;
				}
				a = true;
				Tmpi = i;
				Tmpk = k;
				if (game.puzzle[i + 1][k] == Finder.word[1] && game.totalRows >= static_cast<int>(Finder.word.length()))
				{
					while (a && tracker < static_cast<int>(Finder.word.length() - 1))
					{
						if (game.puzzle[Tmpi + 1][Tmpk] == Finder.word[tracker + 1])
						{
							Tmpi++;
							tracker++;
						}
						else
						{
							a = false;
						}
					}
					if ((tracker + 1) == static_cast<int>(Finder.word.length()))
					{
						Finder.target = DOWN;
						Finder.foundCount += 1;
						Finder.row = i;
						Finder.column = k;
						Finder.found = true;
					}
					tracker = 0;
				}
				a = true;
				Tmpi = i;
				Tmpk = k;
				if (game.puzzle[i + 1][k - 1] == Finder.word[1] && game.totalRows >= static_cast<int>(Finder.word.length() && (tracker < static_cast<int>(Finder.word.length() - 1))))
				{
					while (a && tracker < static_cast<int>(Finder.word.length()) - 1)
					{
						if (game.puzzle[Tmpi + 1][Tmpk - 1] == Finder.word[tracker + 1])
						{
							Tmpk--;
							Tmpi++;
							tracker++;
						}
						else
						{
							a = false;
						}
					}
					if ((tracker + 1) == static_cast<int>(Finder.word.length()))
					{
						Finder.target = LEFT_DOWN;
						Finder.foundCount += 1;
						Finder.row = i;
						Finder.column = k;
						Finder.found = true;
					}
					tracker = 0;

				}
				Tmpi = i;
				Tmpk = k;
				a = true;

			}
		}
	}
}
int main()
{
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 3);
	cout << "\n";
	cout << "\t\t\t-------------------------------------------\n";
	cout << "\t\t\t| WORD SEARCH GENERATOR - BY Muhammad Anas|\n";
	cout << "\t\t\t-------------------------------------------\n\n";
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 11);
	cout << "\n\n1) Create Grid\n2) Search Words from Grid\n3) Quit" << endl << endl << endl;
	char choice = 'a';
	cout << "-----Enter S to search words from grid-----\n-----Enter C to create grid-----\n-----Enter Q to quit-----" << endl;
	cin >> choice;

	/*this program takes the max 15 words from a file named input.txt and generate a grid of 15X15 of words randomly placed in it*/
	while (choice != 'Q' && choice != 'q')
	{
		switch (choice)
		{
		case 'c':
		case 'C':
		{
			string wordlist;
			int numWords = 0;
			cout << "\n";
			int cnt = 0;
			console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color, 15);
			cout << "Enter the Name of File which contain List of Words e.g(input1.txt)\n\n";
			cin >> wordlist;
			cout << "Enter Numbers of words to Search"<<endl;
			cin >> numWords;
			int tempWords = numWords;
			ifstream in(wordlist);
			string s;

			/*while (in >> s)
			{
				numWords++;

			}*/
			cout << "List of Words in the File\n";
			string* words = new string[numWords];
			ifstream inn(wordlist);
			while (inn >> s)
			{
				if (tempWords != 0)
				{
					*(words + cnt) = s;
					cout << *(words + cnt) << " ";
					cnt++;
					tempWords--;
				}
				else
					break;
				
			}
			cout << "\n";

			// converts all words to uppercase
			locale loc;
			for (int cnt = 0; cnt < numWords; cnt++) {
				for (int i = 0; i < (*(words + cnt)).length(); i++) {
					(*(words + cnt))[i] = toupper((*(words + cnt))[i], loc);
				}
			}

			// gets dimensions for grid from user
			int dimensions = 0;
			int newDimensions = 0;
			for (int cnt = 0; cnt < numWords; cnt++) {
				if ((*(words + cnt)).length() > newDimensions)
				{
					newDimensions = (*(words + cnt)).length();
				};
			}
			int Rows, Cols;
			//newDimensions += 4;
			
			{
				console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color, 6);
				cout << "\nHighest Word Length is: " << newDimensions ;
				cout << "\nPlease Enter the Rows and Columns\n\n";
				cout << "Enter Rows: \n";
				cin >> Rows;
				cout << "Enter Columns: \n";
				cin >> Cols;
				if (Cols < newDimensions || Rows < newDimensions)
				{
					console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color, 12);
					cout << "\nGrid is not formed due to invalid Dimension given\n";
					break;
				}
				else
				{
					dimensions = Cols;
				}
				
			}
			
			// makes sure dimensions are less than or equal to a reasonable length and that the input is an integer
			cout << "\n";

			// generates initial grid
			char** grid = new char* [dimensions];
			for (int count = 0; count < dimensions; count++) {
				grid[count] = new char[dimensions];
			}

			// initializes grid
			for (int i = 0; i < dimensions; i++) {
				for (int j = 0; j < dimensions; j++) {
					*((grid[i]) + j) = '?';
				}
			}

			// inserts each word into grid
			for (int cnt = 0; cnt < numWords; cnt++) {
				bool inGrid = false;
				string word = *(words + cnt);
				while (!inGrid) {
					// random row, column, and orientation are set
					int randomRow = rand() % dimensions;
					int randomCol = rand() % dimensions;
					int randomOrient = rand() % 8 + 1;
					// checks to see if word will fit based on orientation
					if (randomOrient == 1) { if (word.length() > (dimensions - randomCol)) { continue; }; };
					if (randomOrient == 2) { if (word.length() > (dimensions - randomRow)) { continue; }; };
					if (randomOrient == 3) { if (word.length() > (randomCol + 1)) { continue; }; };
					if (randomOrient == 4) { if (word.length() > (randomRow + 1)) { continue; }; };
					if (randomOrient == 5) { if ((word.length() > (dimensions - randomRow)) || (word.length() > (dimensions - randomCol))) { continue; }; };
					if (randomOrient == 6) { if ((word.length() > (dimensions - randomRow)) || (word.length() > (randomCol + 1))) { continue; }; };
					if (randomOrient == 7) { if ((word.length() > (randomRow + 1)) || (word.length() > (dimensions - randomCol))) { continue; }; };
					if (randomOrient == 8) { if ((word.length() > (randomRow + 1)) || (word.length() > (randomCol + 1))) { continue; }; };
					// variables for row and column increment coefficients
					int coefRow = 0;
					int coefCol = 0;
					if (randomOrient == 1) {
						coefRow = 0;
						coefCol = 1;
					};
					if (randomOrient == 2) {
						coefRow = 1;
						coefCol = 0;
					};
					if (randomOrient == 3) {
						coefRow = 0;
						coefCol = -1;
					};
					if (randomOrient == 4) {
						coefRow = -1;
						coefCol = 0;
					};
					if (randomOrient == 5) {
						coefRow = 1;
						coefCol = 1;
					};
					if (randomOrient == 6) {
						coefRow = 1;
						coefCol = -1;
					};
					if (randomOrient == 7) {
						coefRow = -1;
						coefCol = 1;
					};
					if (randomOrient == 8) {
						coefRow = -1;
						coefCol = -1;
					};
					// checks to see if word can be placed based in the randomly-generated spot
					bool canFit = true;
					for (int k = 0; k < word.length(); k++) {
						if ((*((grid[randomRow + (coefRow * k)]) + randomCol + (coefCol * k)) != '?') && (*((grid[randomRow + (coefRow * k)]) + randomCol + (coefCol * k)) != word[k])) {
							canFit = false;
							break;
						}
					}
					if (!canFit) { continue; };
					// at this point the word is confirmed to fit and not overwrite any existing letters on the grid
					for (int k = 0; k < word.length(); k++) {
						*((grid[randomRow + (coefRow * k)]) + randomCol + (coefCol * k)) = word[k];
					}
					inGrid = true;

				}
			}

			// fills in the rest of the grid with random letters
			for (int i = 0; i < dimensions; i++) {
				for (int j = 0; j < dimensions; j++) {
					if (*((grid[i]) + j) == '?') {
						*(grid[i] + j) = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 26];
					}
				}
			}

			cout << "-------------------------------------------\n\n";
			for (int i = 0; i < dimensions; i++) {
				for (int j = 0; j < dimensions; j++) {
					HANDLE console_color;
					console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color, 11);
					cout << *((grid[i]) + j)<<" ";
				}
				cout << "\n";
			}
			cout << "\n";

			cout << "-------------------------------------------\n\n";

			// asks the user if they want to save the grid to a file
			char saveGrid = 'y';
			if (saveGrid == 'y') {
				string gridName;
				HANDLE console_color;
				console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color, 15);
				cout << "-------------Enter the Name of File to Save the Grid-------------\n\t\t(with .txt extension) e.g(output.txt)\n\n";
				cin >> gridName;
				ofstream gridFile(gridName);
				for (int i = 0; i < dimensions; i++) {
					for (int j = 0; j < dimensions; j++) {
						gridFile << *((grid[i]) + j);
					}
					gridFile << "\n";
				}
				gridFile << "\n";
				gridFile.close();
				console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color, 14);
				cout << "\nGrid is Successfully Generated with named as "<<gridName<<" .......\n\n";

			};
			if (saveGrid == 'n') {
				cout << "\nGrid not saved.  Exiting program now...\n\n";
			};
			cout << "-------------------------------------------\n\n";
			break;
		}
		case 's':
		case 'S':

		{
			console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color, 11);
			cout << "------Enter Name of file which contain Words to be Searched e.g (wordlist.txt)------\n";
			int skipValues = 3;
			string puzzleGrid;
			string wordList;
			cin >> wordList;
			cout << "Enter File Name which contain the GRID e.g(input.txt)\n";
			cin >> puzzleGrid;
			ofstream myfile;
			myfile.open("tt.txt");
			wordPuzzle game;
			wordFind find;
			ifstream filer;
			cout << "Your Grid is Named as: " << puzzleGrid << endl;
			cout << "Your WordsList is named as: " << wordList << endl;
			ReadColRows(game, wordList);
			// Read Rows and Columns from File
			if (readPuzzle(game, puzzleGrid))
			{
				console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color, 10);
				cout << "File Load SuccessFully\n" << endl;
			}
			else
			{
				cerr << "The puzzle file \"" << puzzleGrid << "\" could not be opened or is invalid" << endl;
				abort();
			}
			displayPuzzle(game);

			//Reading the "WordList" to Find Specific Words .
			filer.open(wordList);
			if (!filer)
			{
				cerr << "The puzzle file \"" << wordList << "\" could not be opened or is invalid" << endl;
				abort();
			}
			while (filer >> wordList)
			{
				if (skipValues > 0)
				{
					skipValues--;
					continue;
				}

				for (int i = 0; i < static_cast<int>(wordList.length()); i++)
				{

					wordList[i] = toupper(wordList[i]);
				}
				find.word = (wordList);
				findWord(game, find);
				if (find.foundCount == 0)
				{
					

					console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color, 12);
					cout << "The word " << find.word << " was not found" << endl;
					myfile << "\nThe word " << find.word << " was not found" << endl;
				}


				//Checking All Eigth Directions and Update the file named as Output.txt
				else if (find.foundCount == 1)
				{

					console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color, 7);
					cout << "The word " << find.word << " was found at (" << find.row << ", " << find.column << ")";
					myfile << "The word " << find.word << " was found at (" << find.row << ", " << find.column << ")";

					switch (find.target) {
					case LEFT_RIGHT:
					{
						cout << " and end at (" << find.row << ", " << find.column + find.word.length() - 1 << ")" << endl;
						myfile << " and end at (" << find.row << ", " << find.column + find.word.length() - 1 << ")" << endl;
						break;
					}

					case RIGHT_LEFT:
					{
						myfile << " and end at (" << find.row << ", " << find.column - find.word.length() + 1 << ")" << endl;
						cout << " and end at (" << find.row << ", " << find.column - find.word.length() + 1 << ")" << endl;
						break;
					}

					case DOWN:
					{
						myfile << " and end at (" << find.row + find.word.length() - 1 << ", " << find.column << ")" << endl;
						cout << " and end at (" << find.row + find.word.length() - 1 << ", " << find.column << ")" << endl;
						break;
					}

					case UP:
					{
						myfile << " and end at (" << find.row - find.word.length() + 1 << ", " << find.column << ")" << endl;
						cout << " and end at (" << find.row - find.word.length() + 1 << ", " << find.column << ")" << endl;
						break;
					}

					case RIGHT_DOWN:
					{
						myfile << " and end at (" << find.row + find.word.length() - 1 << ", " << find.column - find.word.length() + 1 << ")" << endl;
						cout << " and end at (" << find.row + find.word.length() - 1 << ", " << find.column - find.word.length() + 1 << ")" << endl;
						break;
					}
					case RIGHT_UP:
					{
						myfile << " and end at (" << find.row + find.word.length() + 1 << ", " << find.column - find.word.length() + 1 << ")" << endl;
						cout << " and end at (" << find.row + find.word.length() + 1 << ", " << find.column - find.word.length() + 1 << ")" << endl;
						break;
					}
					case LEFT_DOWN:
					{
						myfile << " and end at (" << find.row + find.word.length() - 1 << ", " << find.column - find.word.length() + 1 << ")" << endl;
						cout << " and end at (" << find.row + find.word.length() - 1 << ", " << find.column - find.word.length() + 1 << ")" << endl;
						break;
					}
					case LEFT_UP:
					{
						myfile << " and end at (" << find.row - find.word.length() + 1 << ", " << find.column - find.word.length() + 1 << ")" << endl;
						cout << " and end at (" << find.row - find.word.length() + 1 << ", " << find.column - find.word.length() + 1 << ")" << endl;
						break;
					}

					}
				}
				else
				{
					myfile << "The word " << find.word << " was found " << find.foundCount << " times" << endl;
					cout << "The word " << find.word << " was found " << find.foundCount << " times" << endl;

				}
				find.foundCount = 0;

			}

		}
		default:
		{
			console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color, 3);
			if (choice != 'q' && choice != 'Q')
				cout << "\n\nSelect appropriate Option in Menu" << endl;
		}
		}
		console_color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console_color, 11);
		cout << "\n\n1) Create Grid\n2) Search Words from Grid\n3) Quit" << endl << endl << endl;
		cout << "-----Enter S to Search words from grid-----\n-----Enter C to create grid-----\n-----Enter Q to quit-----" << endl;
		cin >> choice;

	}

	if (choice == 'q' || choice == 'Q')
	{
		console_color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console_color, 6);
		cout << "It's  hard to leave....Bye! Bye!;)" << endl << endl << endl;
		
	}
	system("pause");
}