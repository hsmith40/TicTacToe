#include <iostream>
#include <ctime>
#include <chrono>
#include <ratio>
using namespace std::chrono;

using namespace std;

// This TicTacToe is scalable

const int X = 3;
const int Y = 3;

//const int X = 4;
//const int Y = 4;

//const int X = 5;
//const int Y = 5;

class TicTacToe
{
public:
	TicTacToe()
	{
		resetBoard();
	}
	
	// makeMove() make a move on the board
	// parms: char player - player number, only valid chars are 'X' and 'O'
	//        int x - x position, only valid numbers 0,1,2
	//        int y - y position, only valid numbers are 0,1,2
	// returns: 0 - ok
	//          'M' - invalid move
	//          'P' - invalid player
	//          ' ' - valid move, no winner
	//          'X' - valid move X is winner
	//          'O' - valid move O is winner
	
	char makeMove(char player, int x, int y)
	{
		if (!(player == 'X' || player == 'O')) // test invalid player
			return 'P';
		if (board[x][y] != ' ')
			return 'M'; // invalid move
		board [x][y] = player;
		return isWinnah();  // Test if winner yet
	}
	
	// showBoard() shows the board
	
	void showBoard()
	{
		int i, j;
    	for (i = 0; i < X; i++)
    	{
      		for (j = 0; j < Y; j++)
      			printf("[%d][%d]=%c ",i,j,board[i][j]);
      		cout << endl;
      	} 
	}
	
	// horzCombos() tests for a horizontal winner
	// parms - none
	// returns - winner or ' ' if none
	
	char horzCombos()
	{
		char winner = ' ';
		int z=0;
		for (int x=0; x< X; x++)
		{
			// for each horz, get the first element
				for (int y=0; y<Y; y++)
				{
					if ((y == 0) && (board[x][y] != ' '))
					{
						winner = board[x][y];
						z = 0;
					}
					if ((winner != ' ') && (board[x][y] == winner))
					{
						z = z + 1;
						if (z == Y)
							return winner;
					}
					else
						break;
				}
		}
		return ' ';
	}
	
	// vertCombos() tests for vertical winner
	// parms - none
	// returns - winner or ' ' if none
	
	char vertCombos()
	{
		char winner = ' ';
		int z=0;
		for (int y=0; y< Y; y++)
		{
			// for each horz, get the first element
				for (int x=0; x<X; x++)
				{
					if ((x == 0) && (board[x][y] != ' '))
					{
						winner = board[x][y];
						z = 0;
					}
					if ((winner != ' ') && (board[x][y] == winner))
					{
						z = z + 1;
						if (z == X)
							return winner;
					}
					else
						break;
				}
		}
		return ' ';
	}
	
	// diagCombos() test for diagonal winner
	// parms - none
	// returns - winner or ' ' if none
	
	char diagCombos()
	{
		char winner;
		int z;
		
		if (board[0][0] != ' ')		
			for (int x=0, y=0; x<X; x++, y++)
			{
				if ((x==0) && (board[x][y] != ' '))
				{
					winner = board[x][y];
					z = 0;
				}
				if ((winner != ' ') && (board[x][y]) == winner)
				{
					z = z + 1;
					if (z == X)
						return winner;
				}
			}
		else if ((board[0][Y-1]) != ' ')
		{
			for (int x = X-1, y=0; y<Y; x--, y++)
			{
				if ((y==0) && (board[x][y] != ' '))
				{
					winner = board[x][y];
					z = 0;
				}
				if ((winner != ' ') && (board[x][y] == winner))
				{
					z = z + 1;
					if (z == X)
						return winner;
				}
			}
		}
		return ' ';
	}
	
	// isWinnah() checks for a winner
	// parms - none
	// returns - winner or ' ' if none
	
	char isWinnah()
	{
		char player;
		if ((player=horzCombos()) == ' ')
			if ((player=vertCombos()) == ' ')
				player = diagCombos();
		return player;
	}

	// reset Board() resets the board
	// parms - none
	// returns - none
	
	void resetBoard()
	{
		int x = 0;
		int i, j;
    	for (i = 0; i < X; i++)
      		for (j = 0; j < Y; j++)
        		board[i][j] = ' '; 
	}
private:
	char board[X][Y];
	
/* Winning combos horizontal
	0,0 0,1 0,2
	1,0 1,1 1,2
	2,0 2,1 2,2
	
   Winning combos vertical
	0,0 1,0 2,0
	0,1 1,1 2,1 
	0,2 1,2 2,2
	
   Winning combos diagonal
   1,1 plus
   0,0 2,2
   2,0 0,2
*/
}; // end TicTacToe class


// TicTacToeTestSuite - a class to test function in TicTacToe

class TicTacToeTestSuite
{
TicTacToe tic;

public:
	TicTacToeTestSuite()
	{}
	
	// testMove() test moves
	// parms - TicTacToe *t - a pointer to a TicTacToe object
	// player - char player - a player, 'X' or 'O'
	// x      - int x - x position in the board
	// y      - int y - y position in the board
	// returns - none
	void testMove(TicTacToe *t, char player, int x, int y) 
	{
		char rc;
		rc = t->makeMove(player, x, y);
		if (rc == 'M' ) 
			cout << "invalid move" << endl;
		else if (rc == 'P')
	 		cout << "invalid player" << endl;
		else
			cout << "good move" << endl;	
		
		return;
	}
	
	// testValidMoves() Test various moves. Calls testMove()
	// parms - none
	// return - none
	
	void testValidMoves()
	{
		cout << endl;
		cout << "Test invalid player" << endl;

		tic.resetBoard();
		testMove(&tic, 'b', 0, 0); // invalid player
	
		cout << "\nTest valid move" << endl;
		testMove(&tic, 'X', 0, 0); // X to 0,0
		tic.showBoard();

	
		cout <<  "\nTest invalid move" << endl;
		testMove(&tic, 'O', 0, 0); // O to 0,0 invalid move
		tic.showBoard();

		return;
	}
	
	// testIt() - the big tester, test moves and winners
	// parms - none
	// returns - none
	
	void testIt()
	{
		char winnah = ' ';
		
		// Test Valid Moves
		
		testValidMoves();
				
		// Test Horizontal Winners
		
		cout << "\n Test winner horz" << endl;
		tic.resetBoard();
		
		// this is a test, assume that the makeMove() calls are all valid, we just want
		// to test if there is a winner
		
		for (int x=0; x<X; x++)
		{
			tic.resetBoard();
			for (int y=0; y < Y; y++)	
				winnah = tic.makeMove('X', x, y);

			tic.showBoard();
			if (winnah != ' ')
				cout << "Winner is " << winnah << endl;
			else
				cout << "No Winner"<< endl;
		}
		cout << "\n Test no winner horz" << endl;
		tic.resetBoard();
		winnah = tic.makeMove('X', 2, 0);
		winnah = tic.makeMove(' ', 2, 1);
		winnah = tic.makeMove('X', 2, 2);
		tic.showBoard();
		if (winnah != ' ')
			cout << "Winner is " << winnah << endl;
		else
			cout << "No Winner"<< endl;

//		Test Vertical winners

		cout << endl;
		cout << " Test winner Vert" << endl;
		for (int y=0; y<Y; y++)
		{
			tic.resetBoard();
			for (int x=0; x < X; x++)	
				winnah = tic.makeMove('X', x, y);
			
			tic.showBoard();
			if (winnah != ' ')
				cout << "Winner is " << winnah << endl;
			else
				cout << "No Winner"<< endl;
		}

		cout << "\n Test no winner vert" << endl;
		tic.resetBoard();
		winnah = tic.makeMove('X', 0, 2);
		winnah = tic.makeMove('O', 1, 2);		
		winnah = tic.makeMove('X', 2, 2);
		tic.showBoard();
		if (winnah != ' ')
			cout << "Winner is " << winnah << endl;
		else
			cout << "No Winner"<< endl;

// Test Diagonal winners

		cout << endl;
		cout << " Test winner Diag" << endl;
		tic.resetBoard();
		for (int x=0, y=0; x<X; x++, y++)
			winnah = tic.makeMove('O', x, y);
			
		tic.showBoard();
		if (winnah != ' ')
			cout << "Winner is " << winnah << endl;
		else
			cout << "No Winner"<< endl;

		tic.resetBoard();
		for (int x = X-1, y=0; y<Y; x--, y++)
			winnah = tic.makeMove('X', x, y);

		tic.showBoard();
		if (winnah != ' ')
			cout << "Winner is " << winnah << endl;
		else
			cout << "No Winner"<< endl;
		
		
		cout << "\n Test no winner diag" << endl;
		tic.resetBoard();
		winnah = tic.makeMove('X', 0, 2);
		winnah = tic.makeMove('O', 1, 2);
		winnah = tic.makeMove('X', 2, 2);
		tic.showBoard();
		if (winnah != ' ')
			cout << "Winner is " << winnah << endl;
		else
			cout << "No Winner"<< endl;
		return;
	}
}; // end TicTacToeTestSuite class

int main()
{
	high_resolution_clock::time_point t1 = high_resolution_clock::now();


	cout << "\n\n **** Start Tic Tac Toe ****\n";
	TicTacToeTestSuite testTic; // Instantiate a TicTacToeTestSuite object (points for big words)

	testTic.testIt();	
	
	printf("\n\n");
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double, std::milli> time_span = t2 - t1;
  	cout << "This program took " << time_span.count() << " milliseconds." << endl;	
  	
	cout << "**** End ****" <<endl;
	
	
    return 0;
}
