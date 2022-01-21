// Clocks Application for Chada Tech
// Written by: Gregory Eglen
// Date: 01/20/2022

#define _CRT_SECURE_NO_WARNINGS                                        // Needed to add this to prevent compiler errors while using localtime()
#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include <stdexcept>                                                  // For error checking user input

using namespace std;

// This function is responsible for adding one hour to the clock using a pass by reference parameter
void AddHour(int& currentHour) {
		currentHour += 1;
}

// This function is responsible for adding one minute to the clock using a pass by reference parameter
void AddMinute(int& currentHour, int& currentMinute) {
	currentMinute += 1;
	
	// A check to see if the minutes become 60, to increase the hour and reset minutes to 0
	if (currentMinute >= 60) {
		AddHour(currentHour);
		currentMinute = 0;
	}
}

// This function is responsible for adding one second to the clock using a pass by reference parameter
void AddSecond(int& currentHour, int& currentMinute, int& currentSecond) {
	currentSecond += 1;

	// A check to see if current seconds became 60, to increase the minutes by one and reset seconds to 0
	if (currentSecond >= 60) {
		AddMinute(currentHour, currentMinute);
		currentSecond = 0;
	}
}

// This function prints 100 new lines to clear the console screen
void ClearScreen() {                                                
	for (int n = 0; n < 10; ++n) {
		cout << "\n\n\n\n\n\n\n\n\n\n";
	}
}

// This function prints a formatted line with astericks and a space between the two clocks
void DisplayLine(int option = 0) {
	if (option == 0) {
		cout << setfill('*') << setw(26) << "";
		cout << setfill(' ') << setw(10) << "";
		cout << setfill('*') << setw(26) << "" << endl;
	}
	else if (option == 1) {
		cout << setfill(' ') << setw(18) << "";
		cout << setfill('*') << setw(26) << "";
		cout << setfill(' ') << setw(18) << "" << endl;
	}
	else {
		cout << "Error: This line has not been implemented yet";
	}
}

// This function displays the 12 and 24 hour clocks
void DisplayTime(int clockHours, int clockMinutes, int clockSeconds) {
	string timePeriod;                       // String variable to store AM or PM for the clock
	int clockModifier;                       // Integer variable to modify the 12 hour clock when it is PM
	int menuSelection = 0;                   // Integer variable that stores the user's menu selection

	// While loop to keep displaying the clock until the user enters 4 to exit the program
	while (menuSelection != 4) {             
		if (clockHours == 0) {               // Branch to select if it is AM or PM and modify the 12 hour clock into displaying correctly
			timePeriod = " AM";
			clockModifier = -12;
		}
		else if (clockHours < 12) {       
			timePeriod = " AM";
			clockModifier = 0;
		}
		else if (clockHours == 12) {
			timePeriod = " PM";
			clockModifier = 0;
		}
		else if (clockHours >= 24) {
			timePeriod = " AM";
			clockHours = 0;
			clockModifier = -12;
		}
		else {
			timePeriod = " PM";
			clockModifier = 12;
		}

		// These lines are the formatted output of the clocks and menu
		DisplayLine(0);
		cout << setfill(' ') << "*" << setw(19) << "12-Hour Clock" << setw(6) << "*";
		cout << setw(10) << "";
		cout << "*" << setw(19) << "24-Hour Clock" << setw(6) << "*" << endl;
		cout << "*" << setw(7) << "" << setfill('0') << setw(2) << clockHours - clockModifier << ":" << setw(2) << clockMinutes << ":" << setw(2) << clockSeconds << setfill(' ') << timePeriod << setw(7) << "*";
		cout << setw(10) << "";
		cout << "*" << setw(8) << "" << setfill('0') << setw(2) << clockHours << ":" << setw(2) << clockMinutes << ":" << setw(2) << clockSeconds << setfill(' ') << setw(9) << "*" << endl;
		DisplayLine(0);
		cout << "\n";
		DisplayLine(1);
		cout << setw(19) << "*" << setw(18) << "1 - Add One Hour" << setw(7) << "*" << endl;
		cout << setw(19) << "*" << setw(20) << "2 - Add One Minute" << setw(5) << "*" << endl;
		cout << setw(19) << "*" << setw(20) << "3 - Add One Second" << setw(5) << "*" << endl;
		cout << setw(19) << "*" << setw(18) << "4 - Exit Program" << setw(7) << "*" << endl;
		DisplayLine(1);

		cout << "\nMake a menu selection: " << endl;

		cin >> menuSelection;       // This takes user input for the menu selection

		// Check if the user entered an integer. (This knowledge was gained from this forum post: http://www.cplusplus.com/forum/beginner/40321/)
		if (cin.fail() == true) {
			break;
		}

		// This switch statement decides what action will be taken to the clock
		switch (menuSelection) {
			case 1:
				AddHour(clockHours);
				break;

			case 2:
				AddMinute(clockHours, clockMinutes);
				break;
			
			case 3:
				AddSecond(clockHours, clockMinutes, clockSeconds);
				break;
			
			case 4:
				break;

			default:
				break;
		}


		ClearScreen();
	}
}


// This function displays a goodbye message when the user exits the program
void EndProgram() {
	ClearScreen();

	// If the program reached this point because of a user entering a bad input, print this statement
	if (cin.fail() == true) {
		cout << "You entered an invalid menu selection. Please run the program again." << endl;
	}

	// Prints Goodbye message
	cout << "Thank you for using this software. Goodbye!\n\n\n" << endl;
}

// This function is used to get the current time.
// timePosition has 3 options: 0 - Gets Hours, 1 - Gets Minutes, 2 - Gets Seconds
int GetTime(int timePosition) {
	time_t ttime = time(0);
	tm* local_time = localtime(&ttime);

	switch (timePosition) {
		case 0:
			return local_time->tm_hour;
			break;

		case 1:
			return local_time->tm_min;
			break;
		
		case 2:
			return local_time->tm_sec;
			break;

		default:
			cout << "Unable to retrieve time.";
			return 0;
			break;
	}

}


int main() {
	int timeHour = GetTime(0);            // Variable to store the hours of time
	int timeMinute = GetTime(1);          // Variable to store the minutes of time
	int timeSecond = GetTime(2);          // Variable to store the seconds of time

	DisplayTime(timeHour, timeMinute, timeSecond);
	EndProgram();
	return 0;
}