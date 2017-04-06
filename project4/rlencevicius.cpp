#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

char board[3][3];
char player, opponent;

int row = 0, col = 0, dia = 0;

int empty_r( int c );
int empty_c( int r );
bool losing( char[3][3] );
bool winning( char[3][3] );
bool finished( char[3][3] );
char check();
void move();
void display();


int main( int argc, char* argsv[] ) {
	string boardfile = argsv[ 1 ];
	player = *argsv[ 2 ];
	if ( player == 'x' || player == 'X' ) {
		player = 'X';
		opponent = 'O';
	} else {
		player = 'O';
		opponent = 'X';
	}

	ifstream readfile( boardfile.c_str() );
	char c;
	int i = 0, j = 0;
	while ( readfile.get(c) && i < 3 ) {
		if ( c != '\n' ) {
			board[i][j] = c;
			j++;
		} else if ( c == '\n' ) {
			i++;
			j = 0;
		}
	}
	readfile.close();

	move();

	ofstream writefile( boardfile.c_str() );
	i = 0, j = 0;
	while ( i < 3 ) {
		if ( j < 3 ) {
			writefile << board[i][j];
			j++;
		}

		if ( j == 3 ) {
			writefile << '\n';
			j = 0;
			i++;
		}
	}
	writefile.close();

	display();
	c = check();
	if ( finished( board ) )
		cout << "Tie" << endl;
	else if ( c == 'X' )
		cout << "X Wins!" << endl;
	else if ( c == 'O' )
		cout << "O Wins!" << endl;
}

int empty_c( int r ) {
	for ( int i = 0; i < 3; i++) {
		if ( board[r][i] == ' ') {
			return i;
		}
	}
}

int empty_r( int c ) {
	for ( int i = 0; i < 3; i++) {
		if ( board[i][c] == ' ') {
			return i;
		}
	}
}

bool losing( char board[3][3] ) {
	char a, b, c, d, e, f, g, h, i;
	a = board[0][0], b = board[0][1], c = board[0][2];
	d = board[1][0], e = board[1][1], f = board[1][2];
	g = board[2][0], h = board[2][1], i = board[2][2];

	if ( ( a == opponent && b == opponent && c != player   ) ||
		( a == opponent && b != player   && c == opponent ) ||
		( a != player   && b == opponent && c == opponent ) ) {
		row = 1;
		return true;
	} else if ( ( d == opponent && e == opponent && f != player   ) ||
			  ( d == opponent && e != player   && f == opponent ) ||
			  ( d != player   && e == opponent && f == opponent ) ) {
		row = 2;
		return true;
	} else if ( ( g == opponent && h == opponent && i != player   ) ||
			  ( g == opponent && h != player   && i == opponent ) ||
			  ( g != player   && h == opponent && i == opponent ) ) {
		row = 3;
		return true;
	}

	if ( ( a == opponent && d == opponent && g != player   ) ||
		( a == opponent && d != player   && g == opponent ) ||
		( a != player   && d == opponent && g == opponent ) ) {
		col = 1;
		return true;
	} else if ( ( b == opponent && e == opponent && h != player   ) ||
			  ( b == opponent && e != player   && h == opponent ) ||
			  ( b != player   && e == opponent && h == opponent ) ) {
		col = 2;
		return true;
	} else if ( ( c == opponent && f == opponent && i != player   ) ||
			  ( c == opponent && f != player   && i == opponent ) ||
			  ( c != player   && f == opponent && i == opponent ) ) {
		col = 3;
		return true;
	}

	if ( ( a == opponent && e == opponent && i != player   ) ||
		( a == opponent && e != player   && i == opponent ) ||
		( a != player   && e == opponent && i == opponent ) ) {
		dia = 1;
		return true;
	} else if ( ( g == opponent && e == opponent && c != player   ) ||
			  ( g == opponent && e != player   && c == opponent ) ||
			  ( g != player   && e == opponent && c == opponent ) ) {
		dia = 2;
		return true;
	}

	return false;
}

bool winning( char board[3][3] ) {
	char a, b, c, d, e, f, g, h, i;
	a = board[0][0], b = board[0][1], c = board[0][2];
	d = board[1][0], e = board[1][1], f = board[1][2];
	g = board[2][0], h = board[2][1], i = board[2][2];

	if ( ( a == player   && b == player   && c != opponent ) ||
		( a == player   && b != opponent && c == player   ) ||
		( a != opponent && b == player   && c == player   ) ) {
		row = 1;
		return true;
	} else if ( ( d == player   && e == player   && f != opponent ) ||
			  ( d == player   && e != opponent && f == player   ) ||
			  ( d != opponent && e == player   && f == player   ) ) {
		row = 2;
		return true;
	} else if ( ( g == player   && h == player   && i != opponent ) ||
			  ( g == player   && h != opponent && i == player   ) ||
			  ( g != opponent && h == player   && i == player   ) ) {
		row = 3;
		return true;
	}

	if ( ( a == player   && d == player   && g != opponent ) ||
		( a == player   && d != opponent && g == player   ) ||
		( a != opponent && d == player   && g == player   ) ) {
		col = 1;
		return true;
	} else if ( ( b == player   && e == player   && h != opponent ) ||
			  ( b == player   && e != opponent && h == player   ) ||
			  ( b != opponent && e == player   && h == player   ) ) {
		col = 2;
		return true;
	} else if ( ( c == player   && f == player   && i != opponent ) ||
			  ( c == player   && f != opponent && i == player   ) ||
			  ( c != opponent && f == player   && i == player   ) ) {
		col = 3;
		return true;
	}

	if ( ( a == player   && e == player   && i != opponent ) ||
		( a == player   && e != opponent && i == player   ) ||
		( a != opponent && e == player   && i == player   ) ) {
		dia = 1;
		return true;
	} else if ( ( g == player   && e == player   && c != opponent ) ||
			  ( g == player   && e != opponent && c == player   ) ||
			  ( g != opponent && e == player   && c == player   ) ) {
		dia = 2;
		return true;
	}

	return false;
}

bool finished( char board[3][3] ) {
	for ( int i = 0; i < 3; i++) {
		for ( int j = 0; j < 3; j++) {
			if (board[i][j] == ' ')
				return false;
		}
	}
	return true;
}

char check() {
	int i;

	for ( i = 0; i < 3; i++) {
		if ( board[i][0] == board[i][1] && board[i][0] == board[i][2] )
			return board[i][0];
	}

	for ( i = 0; i < 3; i++) {
		if ( board[0][i] == board[1][i] && board[0][i] == board[2][i] )
			return board[0][i];
	}

	if ( board[0][0] == board[1][1] && board[0][0] == board[3][3] )
		return board[0][0];

	if ( board[0][2] == board[1][1] && board[1][1] == board[2][0] )
		return board[0][2];

	return ' ';
}

void move() {
	char temp;
	char test[3][3];
	for ( int i = 0; i < 3; i++ ) {
		for ( int j = 0; j < 3; j++ ) {
			test[i][j] = board[i][j];
		}
	}

	//==================ATTACK==================
	for ( int i = 0; i < 3; i++ ) {
		for ( int j = 0; j < 3; j++ ) {
			if ( board[i][j] == ' ' ) {
				temp = board[i][j];
				test[i][j] = 'T';
				if ( winning(test) ) {
					break;
				}
			}
		}
	}

	if ( row > 0 ) {
		if ( board[row - 1][empty_c(row-1)] != opponent )
			board[row - 1][empty_c(row-1)] = player;
		return;
	} else if ( col > 0 ) {
		if ( board[empty_r(col - 1)][col - 1] != opponent )
			board[empty_r(col - 1)][col - 1] = player;
		return;
	} else if ( dia == 1 ) {
		if ( board[0][0] != opponent )
			board[0][0] = player;
		else if ( board[1][1] != opponent )
				board[1][1] = player;
		else if ( board[2][2] != opponent )
				board[2][2] = player;
		return;
	} else if ( dia == 2 ) {
		if ( board[0][2] != opponent )
			board[0][2] = player;
		else if ( board[1][1] != opponent )
				board[1][1] = player;
		else if ( board[2][0] != opponent )
				board[2][0] = player;
		return;
	}

	//==================DEFENCE==================
	for ( int i = 0; i < 3; i++ ) {
		for ( int j = 0; j < 3; j++ ) {
			if ( board[i][j] == ' ' ) {
				temp = board[i][j];
				test[i][j] = 'T';
				if ( losing(test) )
					break;
			}
		}
	}

	if ( row > 0 ) {
		if ( board[row - 1][empty_c(row-1)] != opponent )
			board[row - 1][empty_c(row-1)] = player;
		return;
	} else if ( col > 0 ) {
		if ( board[empty_r(col - 1)][col - 1] != opponent )
			board[empty_r(col - 1)][col - 1] = player;
		return;
	} else if ( dia == 1 ) {
		if ( board[0][0] != opponent )
			board[0][0] = player;
		else if ( board[1][1] != opponent )
				board[1][1] = player;
		else if ( board[2][2] != opponent )
				board[2][2] = player;
		return;
	} else if ( dia == 2 ) {
		if ( board[0][2] != opponent )
			board[0][2] = player;
		else if ( board[1][1] != opponent )
				board[1][1] = player;
		else if ( board[2][0] != opponent )
				board[2][0] = player;
		return;
	}

	srand(time(NULL));
	int i, j;
	bool condition = false;
	i = rand() % 3;
	j = rand() % 3;

	while ( condition == false ) {
		if ( finished( board ) ) {
			condition = true;
		} else if ( board[i][j] != ' ' ) {
			i = rand() % 3;
			j = rand() % 3;
		} else {
			board[i][j] = player;
			condition = true;
		}
	}
}

void display() {
	for ( int i = 0; i < 3; i++) {
		cout << board[i][0] << board[i][1] << board[i][2] << endl;
	}
}
