#include <iostream>
#include <time.h>
using namespace std;

void pause( int milliseconds ) {
	int limit = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
	while( clock() < limit ) {}
}

int main() {
	char ESC 		= 27;
	int N 			= 30;
	int col_counter 	= 0;
	int time		= 50;

	cout << ESC << "[2J" << ESC << "[13;" << col_counter << "f";

	while ( N < 38 ) {
		while ( col_counter < 80 ) {
			for ( int i = 0; i < 80; i++ ) {
				cout << "o";
			}

			cout << ESC << "[13;" << col_counter << "f";
			cout << ESC << "[" << N << "m" << "O"; 
			cout << ESC << "[37m" << flush;
			pause(time);
			cout << ESC << "[2J" << ESC << "[13;0f";
			col_counter++;
		}

		col_counter--;
		
		do {
			for ( int i = 0; i < 80; i++ ) {
				cout << "o";
			}

			col_counter--;
			cout << ESC << "[13;" << col_counter << "f";
			cout << ESC << "[" << N << "m" << "O"; 
			cout << ESC << "[37m" << flush;
			pause(time);
			cout << ESC << "[2J" << ESC << "[13;0f";
		} while ( col_counter > 0 );

		if ( col_counter == 0 )
			N++;
	}

	cout << endl;
}
