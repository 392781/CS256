#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

int speed = 300;
string terminal[25][80];
string moved[25][80];

void clear();
void setms( int );
void setfg( int );
void setbg( int );
void pause();
void slow();
void fast();
void plot( int , int , char );
void hplot( int , int , char , int );
void vplot( int , int , char , int );
void text( int , int , string );
void move( int , int , int , int , int , int );
void copy( int , int , int , int , int , int );
int quit();

int main ( int argc, char* argsv[] ) {
	string command_file = argsv[ 1 ];
	int col, row, height, width, new_col, new_row, count;
	int milliseconds, fg, bg;
	int line_counter = 0;
	char c;
	string string1;
	string command;

	ifstream myfile;
	ofstream logfile;
	myfile.open( command_file.c_str() );
	logfile.open( "project2.log" );

	while ( !myfile.eof() ) {
		myfile >> command;
		line_counter++;
		if ( command == "clear" ) {
			clear();
		} else if ( command == "setms") {
			myfile >> milliseconds;
			setms( milliseconds );
		} else if ( command == "setfg") {
			myfile >> fg;
			if (fg >= 30 && fg <= 39) {
				setfg(fg);
			} else {
				logfile << "Error: Line " << line_counter << " - bad FG value "
					   << fg << ", skipping." << endl;
			}
		} else if ( command == "setbg") {
			myfile >> bg;
			if (bg >= 40 && bg <= 49) {
				setbg(bg);
			} else {
				logfile << "Error: Line " << line_counter << " - bad BG value "
					   << bg << ", skipping." << endl;
			}
		} else if ( command == "pause") {
			pause();
		} else if ( command == "slow") {
			slow();
		} else if ( command == "fast") {
			fast();
		} else if ( command == "plot") {
			myfile >> row >> col >> c;
			plot( row, col, c);
		} else if ( command == "hplot") {
			myfile >> row >> col >> c >> count;
			hplot( row , col , c , count);
		} else if ( command == "vplot") {
			myfile >> row >> col >> c >> count;
			vplot( row , col , c , count);
		} else if ( command == "text") {
			myfile >> row >> col >> string1;
			text( row , col , string1 );
		} else if ( command == "move") {
			myfile >> row >> col >> height >> width >> new_row >> new_col;
			move( row , col , height , width , new_row , new_col);
		} else if ( command == "copy") {
			myfile >> row >> col >> height >> width >> new_row >> new_col;
			copy( row , col , height , width , new_row , new_col);
		} else if ( command == "//") {

		} else if ( command == "quit") {
			myfile.close();
			logfile.close();
			quit();
		}
		else {
			logfile << "Error: Line " << line_counter << " - bad command "
				   << "'" << command << "'" << ", skipping." << endl;
		}
	}

	myfile.close();
	logfile.close();

}

void clear() {
	char ESC = 27;
	cout << ESC << "[2J" << ESC << "[0;0f" << flush;
}

void setms( int milliseconds ) {
	speed = milliseconds;
}

void setfg( int color ) {
	char ESC = 27;
	if ( color >= 30 && color <= 39 )
		cout << ESC << "[" << color << "m";

}

void setbg( int color ) {
	char ESC = 27;
	cout << ESC << "[" << color << "m";
}

void pause() {
	int limit = clock() + speed * CLOCKS_PER_SEC / 1000;
	while ( clock() < limit ) {}
}

void slow() {
	setms(300);
}

void fast() {
	setms(100);
}

void plot( int row , int col , char c ) {
	terminal[row][col] = c;
	char ESC = 27;
	cout << ESC << "[" << row << ";" << col << "f";
	cout << c << flush;
	cout << ESC << "[0;0f";
}

void hplot( int row , int col , char c , int count ) {
	char ESC = 27;
	for ( int i = 0 ; i < count ; i++ ) {
		terminal[row][col + i] = c;
		cout << ESC << "[" << row << ";" << col << "f";
		cout << c << flush;
		col++;
	}

	cout << ESC << "[0;0f";
}

void vplot( int row , int col , char c , int count ) {
	char ESC = 27;
	for ( int i = 0 ; i < count ; i++ ) {
		terminal[row + i][col] = c;
		cout << ESC << "[" << row << ";" << col << "f";
		cout << c << flush;
		row++;
	}

	cout << ESC << "[0;0f";
}

void text( int row , int col , string text ) {
	for ( int i = 0 ; i < text.length() ; i++ ){
		terminal[row][col + i] = text[i];
	}

	char ESC = 27;
	cout << ESC << "[" << row << ";" << col << "f";
	cout << text << flush;
	cout << ESC << "[0;0f";
}

void move( int row , int col , int height , int width , int new_row , int new_col ) {
	for ( int i = 0 ; i < height ; i++ ) {
		for ( int j = 0 ; j < width ; j++ ) {
			moved[row + new_row + i][col + new_col + j] = terminal[row + i][col + j];
			terminal[row + new_row + i][col + new_col + j] = moved[row + new_row + i][col + new_col + j];
			terminal[row + i][col + j] = "";
		}
	}

	char ESC = 27;
	cout << ESC << "[2J";
	for( int i = 0 ; i < 25; i++ ) {
		for ( int j = 0 ; j < 80 ; j++ ) {
			cout << ESC << "[" << i << ";" << j << "f" << terminal[i][j];
		}
	}
	cout << ESC << "[0;0f";
}

void copy( int row , int col , int height , int width , int new_row , int new_col ) {
	for ( int i = 0 ; i < height ; i++ ) {
		for ( int j = 0 ; j < width ; j++) {
			moved[row + new_row + i][col + new_col + j] = terminal[row + i][col + j];
			terminal[row + new_row + i][col + new_col + j] = moved[row + new_row + i][col + new_col + j];
		}
	}

	char ESC = 27;
	for ( int i = 0 ; i < height ; i++ ) {
		for ( int j = 0 ; j < width ; j++) {
			cout << ESC << "[" << (row + new_row + i) << ";" << (col + new_col + j) << "f"
				<< terminal[row + new_row + i][col + new_col + j] << flush;
			terminal[row + new_row + i][col + new_col + j] = moved[row + new_row + i][col + new_col + j];
		}
	}

	cout << ESC << "[0;0f";
}

int quit() {
	return(0);
}
