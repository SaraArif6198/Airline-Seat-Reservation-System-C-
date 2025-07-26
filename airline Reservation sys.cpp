#include <iostream>
#include <string>
#include <ctime> // For sleep functionality
#include <windows.h> // For clearing the screen
using namespace std;

const int ROWS = 8;
const int COLS = 4;

// Function prototypes
void printSeats(char layout[ROWS][COLS]);
bool reserveSeat(char layout[ROWS][COLS], const string& seatNumber);
bool cancelSeat(char layout[ROWS][COLS], const string& seatNumber);
void sleepForSeconds(int seconds);

int main() {
    // Display the initial screen
    cout << "========================================" << endl;
    cout << "       AIRLINE RESERVATION SYSTEM BY:   " << endl;
    cout << "           SARA ARIF                    " << endl;
    cout << "========================================" << endl;

    // Pause for 3 seconds to display the intro screen
    sleepForSeconds(3);

    // Clear the console
    system("cls");

    char layout[ROWS][COLS];
    int filled = 0;
    const int totalSeats = ROWS * COLS;

    // Initialize seating layout
    for (int i = 0; i < ROWS; i++) {
        layout[i][0] = 'A';
        layout[i][1] = 'B';
        layout[i][2] = 'C';
        layout[i][3] = 'D';
    }

    cout << "Welcome to the Airline Seat Allocation System." << endl;
    cout << "You can: " << endl
         << "1. Reserve a seat by entering the seat number (e.g., 1A)." << endl
         << "2. Cancel a reservation by entering C followed by the seat number (e.g., C1A)." << endl
         << "3. Exit by typing -1." << endl << endl;

    printSeats(layout);

    string input;

    while (filled < totalSeats) {
        cout << "Enter your choice: ";
        cin >> input;

        if (input == "-1") {
            cout << "Program ended." << endl;
            break;
        }

        if (input[0] == 'C') {
            // Handle cancellation
            string seatNumber = input.substr(1);
            if (cancelSeat(layout, seatNumber)) {
                filled--;
                cout << "Cancellation successful for seat " << seatNumber << "." << endl;
            } else {
                cout << "Invalid cancellation request for seat " << seatNumber << "." << endl;
            }
        } else {                                                                                                             
            // Handle reservation
            if (reserveSeat(layout, input)) {
                filled++;
                cout << "Reservation successful for seat " << input << "." << endl;
            } else {
                cout << "Invalid reservation request or seat already reserved." << endl;
            }
        }

        printSeats(layout);

        if (filled == totalSeats) {
            cout << "All seats are now reserved." << endl;
        }
    }

    cout << "Final seat assignments:" << endl;
    printSeats(layout);
    return 0;
}

void printSeats(char layout[ROWS][COLS]) {
    cout << "Seating Chart:" << endl;
    for (int i = 0; i < ROWS; i++) {
        cout << "Row " << (i + 1) << "  ";
        for (int j = 0; j < COLS; j++) {
            cout << layout[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool reserveSeat(char layout[ROWS][COLS], const string& seatNumber) {
    int row = 0, i = 0;
    while (isdigit(seatNumber[i])) {
        row = row * 10 + (seatNumber[i] - '0');
        i++;
    }
    row--;
    char column = seatNumber[i];
    
    if (row < 0 || row >= ROWS || column < 'A' || column >= ('A' + COLS)) return false;
    int col = column - 'A';
    if (layout[row][col] == 'X') return false;
    layout[row][col] = 'X';
    return true;
}

bool cancelSeat(char layout[ROWS][COLS], const string& seatNumber) {
    int row = 0, i = 0;
    while (isdigit(seatNumber[i])) {
        row = row * 10 + (seatNumber[i] - '0');
        i++;
    }
    row--;
    char column = seatNumber[i];
    
    if (row < 0 || row >= ROWS || column < 'A' || column >= ('A' + COLS)) return false;
    int col = column - 'A';
    if (layout[row][col] != 'X') return false;
    layout[row][col] = column;
    return true;
}

void sleepForSeconds(int seconds) {
    clock_t end_time = clock() + seconds * CLOCKS_PER_SEC;
    while (clock() < end_time);
}
