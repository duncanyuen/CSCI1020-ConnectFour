/***********************************************************************
CSCI1020 Hands-on Introduction to C++

I declare that the source code here submitted is original except for source
material explicitly acknowledged. I also acknowledge that I am aware of
University policy and regulations on honesty in academic work, and of the
disciplinary guidelines and procedures applicable to breaches of such
policy and regulations, as contained in the following University website:
https://www.cuhk.edu.hk/policy/academichonesty/

Student Name: YUEN Yu Ching
Student ID: 1155143580
Date: 26/4/2021
***********************************************************************/

/*
 * Features:
 *  - Colored marks
 *  - Different game modes
 *  - Custom names
 *  - Error checking
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>

using namespace std;

/* Represent the game board */
class GameBoard {
private:
	char board[6][7];

public:
	/* Constructor: initialize the member variable */
	GameBoard() {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				board[i][j] = ' ';
			}
		}
	}

	/* Display the game board with column labels from 1 to 7
	   In Part 1, you are required to follow the output format in the sample run
	   You are welcome to design and implement a better one in Part 2 */
	void display() {
		cout << "=====================" << endl;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				cout << "|";
				HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
				if (board[i][j] == 'O') {
					SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY);
					SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
					//cout << "\0x1B[34m";
				} else if (board[i][j] == 'X') {
					SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY);
					SetConsoleTextAttribute(hOut, FOREGROUND_RED);
					//cout << "\0x1B[31m";
				}
				cout << board[i][j];
				if ((board[i][j] == 'O') || (board[i][j] == 'X')) {
					SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				}
				//cout << "\0x1B[37m";
				cout << "|";
			}
			cout << endl;
		}
		cout << "=====================" << endl;
		for (int i = 1; i < 8; i++) {
			cout << " " << i << " ";
		}
		cout << endl;
	}

	/* Place the given mark in the given column
	   If the column is not full and the mark can be placed, return true
	   If the column is full already and the mark cannot be placed, return false
	   Hint: the return value is useful for the computer's naive strategy in Part 1 */
	bool placeMark(int column, char mark) {
		for (int i = 6; i > -1; i--) {
			if (board[i][column] == ' ') {
				board[i][column] = mark;
				return true;
			}
		}
		return false;
	}

	bool colIsFull(int column) {
		if ((board[0][column] == 'X') || (board[0][column] == 'O')){
			return true;
		}
		return false;
	}

	/* Return true if there is a winner; otherwise return false
	   The winning message is not printed by this function
	   Hint: The winner must be the current player who just placed the mark */
	bool hasWinner() {
		char current;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				current = board[i][j];
				if (current == ' ') {
					continue;
				}
				if ((j + 3) < 7) {
					for (int k = 1; k < 4; k++) {
						if (board[i][j + k] == current) {
							if (k == 3) {
								return true;
							}
							continue;
						}
						else {
							break;
						}
					}
				}
				if (((i + 3) < 6) && ((j + 3) < 7)) {
					for (int k = 1; k < 4; k++) {
						if (board[i + k][j + k] == current) {
							if (k == 3) {
								return true;
							}
							continue;
						}
						else {
							break;
						}
					}
				}
				if ((i + 3) < 6) {
					for (int k = 1; k < 4; k++) {
						if (board[i + k][j] == current) {
							if (k == 3) {
								return true;
							}
							continue;
						}
						else {
							break;
						}
					}
				}
				if (((i + 3) < 6) && ((j - 3) > -1)) {
					for (int k = 1; k < 4; k++) {
						if (board[i + k][j - k] == current) {
							if (k == 3) {
								return true;
							}
							continue;
						}
						else {
							break;
						}
					}
				}
			}
		}
		return false;
	}

	/* Return true if the game board is full; otherwise return false
	   The draw game message is not printed by this function */
	bool isFull() {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				if (board[i][j] == ' ') {
					return false;
				}
			}
		}
		return true;
	}

	GameBoard* cloneBoard() {
		return new GameBoard(*this);
	}
};

int Win(GameBoard board) {
	GameBoard* fakeboardX[7];
	for (int i = 0; i < 7; i++) {
		fakeboardX[i] = board.cloneBoard();
		(*fakeboardX[i]).placeMark(i, 'X');
		if ((*fakeboardX[i]).hasWinner()) {
			return i;
		}
	}
	return -1;
}

int Lose(GameBoard board) {
	GameBoard* fakeboardO[7];
	for (int i = 0; i < 7; i++) {
		fakeboardO[i] = board.cloneBoard();
		(*fakeboardO[i]).placeMark(i, 'O');
		if ((*fakeboardO[i]).hasWinner()) {
			return i;
		}
	}
	return -1;
}

/* Define classes for players here */

/* You can assume that the input of the human player must be valid in Part 1
   (i.e, an integer between 1 to 7 inclusively and the target column is not full)
   You are welcome to handle invalid inputs in Part 2 */

   /* You are required to implement the following naive strategy for the computer player in Part 1:
	  place the mark in the first column that is not full scanning from 1 To 7.
	  You are welcome to design and implement better strategies in Part 2.
	  Hint: call placeMark() of the GameBoard object */
class Player {
protected:
	string name;
	char mark;

public:
	Player() {
		name = "Player";
		mark = 'K';
	}

	virtual void place(GameBoard& board1) {
		int column;
		cout << name << ", your turn: ";
		cin >> column;
		while ((board1.colIsFull(column-1)) || (column < 1) || (column > 7)) {
			cout << "Invalid input: Column " << column;
			if (column < 1){
				cout << " is too small and does not exist";
			} else if (column > 7){
				cout << " is too big and does not exist";
			} else if (board1.colIsFull(column-1)){
				cout << " is full";
			}
			cout << endl;
			cout << "Please enter another column:";
			cin >> column;
		}
		(board1.placeMark(column - 1, mark));
		return;
	}

	string getName() {
		return name;
	}
};

class HumanPlayer : public Player {
public:
	HumanPlayer(string inname, char inmark) {
		name = inname;
		mark = inmark;
	}
};

class ComputerPlayer : public Player {
private:
	int hardness;

public:
	ComputerPlayer(string inname, char inmark, int inhardness) {
		name = inname;
		mark = inmark;
		hardness = inhardness;
	}
	virtual void place(GameBoard& board) {
		int markColumn = -1;
		if (hardness == 0) {
			for (int i = 0; (board.colIsFull(i)); i++) {
				markColumn = i;
			}
			markColumn++;
		}
		else if (hardness == 1) {
			markColumn = rand() % 7;
			while (board.colIsFull(markColumn)) {
				markColumn = rand() % 7;
			}
		}
		else if (hardness == 2) {
			markColumn = Win(board);
			if (markColumn == -1) {
				markColumn = rand() % 7;
				while (board.colIsFull(markColumn)){
					markColumn = rand() % 7;
				}
			}
		}
		else if (hardness == 3) {
			markColumn = Lose(board);
			if (markColumn == -1) {
				markColumn = rand() % 7;
				while (board.colIsFull(markColumn)) {
					markColumn = rand() % 7;
				}
			}
		}
		board.placeMark(markColumn, mark);
		cout << name << "'s turn: " << markColumn + 1 << endl;
	}
};

/* Represent the game */
class ConnectFourGame {
private:
	/* Declare member variables */
	int currentPlayer;
	GameBoard board;
	Player* player0;
	Player* player1;


public:
	/* Constructor: create the player objects and the board object
	   If there is only one human player, he/she is named "Player 1" and the computer player is named "Computer"
	   If there are two human players, they are named "Player 1" and "Player 2"
	   The marks used by player 1 and player 2 are 'O' and 'X' respectively. */
	ConnectFourGame(int numOfPlayers) {
		if (numOfPlayers == 2) {
			string player1name;
			string player2name;
			cout << "Player 1's name [default: \"Player 1\"]: ";
			getline(cin, player1name);
			if (player1name.empty()) {
				player1name = "Player 1";
			}
			cout << "Player 2's name [default: \"Player 2\"]: ";
			getline(cin, player2name);
			if (player2name.empty()) {
				player2name = "Player 2";
			}
			player0 = new HumanPlayer(player1name, 'O');
			player1 = new HumanPlayer(player2name, 'X');
		}
		else {
			string player1name;
			string input;
			int difficulty = -1;
			cout << "Player \'s name [default: \"Player\"]: ";
			getline(cin, player1name);
			if (player1name.empty()) {
				player1name = "Player";
			}
			while ((difficulty < 0) || (difficulty > 3)) {
				cout << "Difficulty level [0-3, default 0] :";
				getline(cin,input);
				if (input.empty()) {
					difficulty = 0;
				}
				else {
					difficulty = stoi(input);
				}
				if ((difficulty < 0) || (difficulty > 3)) {
					cout << "Invalid difficulty, please try again..." << endl;
				}
			}
			player0 = new HumanPlayer(player1name, 'O');
			player1 = new ComputerPlayer("Computer", 'X', difficulty);
		}
		currentPlayer = 0;
	}

	/* Called once in main()
	   Player 1 moves first */
	void start() {
		int markColumn;
		string name;
		currentPlayer = 0;
		board.display();
		while ((board.hasWinner() == false) && (board.isFull() == false)) {
			if (currentPlayer == 0) {
				name = player0->getName();
				player0->place(board);
			}
			else {
				name = player1->getName();
				player1->place(board);
			}
			board.display();
			if (board.hasWinner()) {
				cout << name << " wins!" << endl;
				return;
			}
			else if (board.isFull()) {
				cout << "Draw game!" << endl;
				return;
			}
			else {
				currentPlayer = !currentPlayer;
				markColumn = 0;
			}
		}
	}
};

/* The main function */
int main() {
	int numOfPlayers;
	cout << "How many players (1 or 2)?" << endl;
	cin >> numOfPlayers;
	cin.ignore();
	ConnectFourGame game(numOfPlayers);
	game.start();
	return 0;
}
