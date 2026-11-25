#include <iostream>
#include <array>
#include <limits>
using namespace std;

// Declare Functions
void displaySeating(const array<array<bool, 30>, 15>& seats);
void getSeatSelection(int& row, int& seat);
bool reserveSeat(array<array<bool, 30>, 15>& seats, int row, int seat);
double calculateSales(const array<array<bool, 30>, 15>& seats, double ticketPrice);

int main() {
    // Create a 2D array of seats. All seats start as available (false)
    array<array<bool, 30>, 15> seats = {};

    const double ticketPrice = 11.75;
    char choice = 'Y'; // Default choice to 'Y' to enter the loop

    while (choice == 'Y' || choice == 'y') {
        // Show the seating chart
        displaySeating(seats);

        // Ask the user which seat they want
        int row = 0;
        int seat = 0;
        getSeatSelection(row, seat);

        // Try to reserve the seat
        bool success = reserveSeat(seats, row, seat);

        if (success) {
            cout << "Seat " << (row + 1) << "-" << (seat + 1) << " successfully reserved." << endl;
        } else {
            cout << "Sorry, that seat is already taken." << endl;
        }

        // Show how much money has been made so far
        double total = calculateSales(seats, ticketPrice);
        cout << "Current sales: $" << total << endl;
        cout << endl;

        // Ask if they want to reserve another seat
        cout << "Would you like to reserve another seat? (Y/N): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    }

    // After user is done, show the final sales
    double finalTotal = calculateSales(seats, ticketPrice);
    cout << "Thank you! Final sales: $" << finalTotal << endl;

    // Show the final seating chart
    cout << "\nFinal Seating Chart:\n";
    displaySeating(seats);

    return 0;
}

// Function to show all seats with row and seat labels
void displaySeating(const array<array<bool, 30>, 15>& seats) {
    cout << "\nSeats (\"#\" = available, \"*\" = taken):" << endl;
    cout << "        Seats -->" << endl;  // Seats label at the top

    // Print seat numbers
    cout << "     ";
    for (int seatNumber = 1; seatNumber <= 30; seatNumber++) {
        if (seatNumber < 10) {
            cout << " ";
        }
        cout << seatNumber << " ";
    }
    cout << endl;

    // Print seating chart
    cout << "Rows ↓" << endl;
    for (int row = 0; row < 15; row++) {
        if (row + 1 < 10) {
            cout << " ";
        }
        cout << " " << row + 1 << " | ";
        for (int seat = 0; seat < 30; seat++) {
            if (seats[row][seat] == true) {
                cout << "*  ";
            } else {
                cout << "#  ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

// Function to get a seat selection from the user
void getSeatSelection(int& row, int& seat) {
    bool validInput = false;

    while (!validInput) {
        cout << "Enter the row number (1-15): ";
        cin >> row;
        
        if (!cin || row < 1 || row > 15) {
            cout << "Invalid row number. Please try again." << endl;
            cin.clear(); // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard input
            continue;
        }

        cout << "Enter the seat number (1-30): ";
        cin >> seat;

        if (!cin || seat < 1 || seat > 30) {
            cout << "Invalid seat number. Please try again." << endl;
            cin.clear(); // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        validInput = true; // valid input received
    }

    row = row - 1;  // make it zero-based for array
    seat = seat - 1; 
}

// Function to try and reserve a seat
bool reserveSeat(array<array<bool, 30>, 15>& seats, int row, int seat) {
    if (seats[row][seat] == false) {
        seats[row][seat] = true;
        return true;
    } else {
        return false;
    }
}

// Function to calculate the total sales
double calculateSales(const array<array<bool, 30>, 15>& seats, double ticketPrice) {
    int soldSeats = 0;

    for (int row = 0; row < 15; row++) {
        for (int seat = 0; seat < 30; seat++) {
            if (seats[row][seat] == true) {
                soldSeats++;
            }
        }
    }

    double totalSales = soldSeats * ticketPrice;
    return totalSales;
}
