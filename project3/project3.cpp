#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

struct KDA {
	char WL;
	int kill;
	int death;
	int assist;
};

int counter;
KDA list[1000];

void add_match( char , int , int , int );
void delete_match( int );
void display();
double calculate_WL();
double calculate_KD( int );
double calculate_total_KD();
void reset_db();

int main() {
	counter = 0;
	char WL;
	int kill, death, assist, position;
	double KDR, WLR;
	string command;
	string line;

	ifstream readfile( "datafile.log" );

	while ( readfile >> WL ) {
		readfile >> kill >> death >> assist;
		list[counter].WL = WL;
		list[counter].kill = kill;
		list[counter].death = death;
		list[counter].assist = assist;
		counter++;
	}
	readfile.close();

	cin >> command;

	if (command == "add") {
		cin >> WL >> kill >> death >> assist;

		add_match( WL , kill , death , assist );

          ofstream writefile( "datafile.log" , ios::app );
		writefile << list[counter].WL << " " << list[counter].kill << " "
				<< list[counter].death << " " << list[counter].assist << endl;
		cout << "Match added" << endl;
		writefile.close();

	} else if (command == "delete") {
		cin >> position;
		delete_match( position );
		cout << "Match deleted" << endl;

	} else if (command == "list") {
		display();

	} else if (command == "kdr") {
		KDR = calculate_total_KD();
		cout << "Overall KDR: " << setprecision( 2 ) << fixed << KDR << endl;

	} else if (command == "wlr") {
		WLR = calculate_WL();
		cout << "W/L Ratio: " << setprecision( 2 ) << fixed << WLR << endl;

	} else if (command == "reset"){
		reset_db();

	} else if (command == "quit"){

	} else {
		cout << "Bad command" << endl;
	}

	return 0;
}

void add_match( char WL , int kill , int death , int assist ) {
	if (counter < 1000) {
		list[counter].WL = WL;
		list[counter].kill = kill;
		list[counter].death = death;
		list[counter].assist = assist;
	} else if (counter >= 1000) {
		cout << "List full! Reset log file to add more games.";
	}
}

void delete_match( int position ) {
	string line;
	ifstream readfile( "datafile.log" );
	ofstream writefile( "datafile.txt" );
	for (int i = 0; i < counter; i++) {
		if (i == position - 1) {
			getline( readfile, line);
			getline( readfile, line );
			writefile << line << endl;
		} else if ( i == counter - 1 ) {
			continue;
		} else {
			getline( readfile, line );
			writefile << line << endl;
		}
	}
	readfile.close();
	writefile.close();
	counter--;

	reset_db();

	ifstream read( "datafile.txt" );
	ofstream write( "datafile.log" );
	for (int i = 0; i < counter; i++) {
		getline( read, line);
		write << line << endl;
	}
	read.close();
	write.close();
}

void display() {
	char result;
	int kill;
	int death;
	int assist;
	double KD;
	double tot_KD = calculate_total_KD();
	double WL_Ratio = calculate_WL();

	cout << "Game # | " << "W/L | " << "Kills | " << "Deaths | " << "Assists | "
		<< "  KDR   " << endl << flush;
	cout << "-----------------------------------------------" << endl;

	for ( int i = 0; i < counter ; i++) {
		if (list[i].WL == 'W')
			result = 'W';
		else if (list[i].WL == 'L')
			result = 'L';
		kill = list[i].kill;
		death = list[i].death;
		assist = list[i].assist;
		KD = calculate_KD(i);

		cout << setw( 3 ) << i + 1 << ".     " << setw( 2 ) << result
			<< setw( 9 ) << kill << setw( 9 ) << death << setw( 10 )
			<< assist << setw( 8 ) << setprecision( 2 ) << fixed
		 	<< KD << endl;
	}

	cout << "-----------------------------------------------" << endl;
	cout << "Overall KDR: " << tot_KD << endl;
	cout << "W/L Ratio:   " << WL_Ratio << endl;
}

double calculate_WL() {
	int win = 0;
	int loss = 0;
	double WL_Ratio;

	for ( int i = 0; i < counter; i++ ) {
		if ( list[i].WL == 'W' )
			win++;
		else if ( list[i].WL == 'L')
			loss++;
	}

	WL_Ratio = win / (double)loss;

	return WL_Ratio;
}

double calculate_KD( int position ) {
	int kill = list[position].kill;
	int death = list[position].death;
	int assist = list[position].assist;
	double KD = (kill + assist) / (double)death;

	return KD;
}

double calculate_total_KD() {
	int kill = 0;
	int death = 0;
	int assist = 0;
	double KD;

	for ( int i = 0; i < counter; i++ ) {
		kill += list[i].kill;
		death += list[i].death;
		assist += list[i].assist;
	}

	KD = (kill + assist) / (double)death;

	return KD;
}

void reset_db() {
	if ( remove( "datafile.log" ) != 0 )
		perror( "Reset unsuccessful" );
	else
		puts( "Reset successful" );
		ofstream writefile( "datafile.log" );
		writefile.close();
}
