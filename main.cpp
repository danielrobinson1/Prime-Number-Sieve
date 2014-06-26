///////////////////////////////////////////////////////////////////////////////////////////////////
// Prime Number Sieve
//
// Program Description:
// User enters a number and the program calculates all primes less than or equal to that number.
//
// Details of the Algorithm:
// Sieve of Eratosthenes. For a given input x, write out all integers from 2 up to x. 2 is prime but
// all other multiples of 2 are not, so delete them to obtain a new list of integers. The smallest integer
// in this new list, after 2, is prime, (i.e 3). Keep 3 but delete all other multiples of 3 from the list.
// Continue this process until we get to the square root of x. What is left is the list of all primes up to x.
//
// Version 4:
// *In this version all intermediate steps are printed.
// *Introduced strings in place of char arrays.
//
// Improvements:
// *Modify the PrintList function to take an input.
// *Is atoi the most efficient way to convert a string to an integer?
// *Understand the difference between "cin >>" and "getline(cin, )".
//  Experienced problems with "cin >> " where old user input was remaining in the stream and when
//  the user was next asked to enter input, the old input was being read automatically. There was
//  no such problem with "getline(cin, )". This is something to do with the fact that one of these
//  reads the end of string character and the other doesn't.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>    // Vectors are like arrays but it's easier to delete and change entries.
#include <cmath>     // Includes function sqrt().
#include <algorithm> // required for function "remove_if".
#include <string>
#include <windows.h> // Neede for clrscr function.

using namespace std;

// Global variables
bool validinput = false;
int input;
int sqrtinput;
int pivot;
vector<int> numbers;
string again;

// Function protoypes
void Clrscr();
void PrintProgDetails();
void Validate(int x);
void GenerateList(int x);
void PrintList();
void EnterToContinue();
void ZeroNonPrimes();
void ZeroMultiples();
bool IsZero(int x);
void DeleteZeroes();

// Main program
int main()
{
    while(1)
    {
    Clrscr();
    PrintProgDetails();
    validinput = false;         // Reset bool var "validinput".
    numbers.clear();            // Reset vector "numbers".
    while (validinput == false) {
        cout << "Enter an integer greater than 1: ";
        string line;
        getline(cin,line);
        cout << line;
        cout << line.c_str();
        input = atoi(line.c_str()); // atoi converts a string to an integer. Returns 0 if
                                    // original string was not an integer.
                                    // Is there a better way to convert strings to integers?
        cout << input;
        Validate(input);
    }
    GenerateList(input);
    cout << endl << "Numbers up to " << input << ": " << endl << endl;
    PrintList();
    EnterToContinue();
    cout << endl << endl;
    ZeroNonPrimes();
    DeleteZeroes();
    cout << endl << "There are " << numbers.size()-2 << " primes up to " << input << ": ";
    cout << endl << endl;
    PrintList();

    // Do another calculation, or exit?
    while(1)
    {
    cout << "Go again? (y/n)";
    getline(cin,again);
    if ((again == "N") || (again == "n")) {
        break;  // Exit while loop
    }
    else if ((again == "Y") || (again == "y")) {
        break;
    }
    else cout << "Invalid response." << endl;
    }

    if ((again == "N") || (again == "n")) {
        break;  // Exit while loop
    }
    else if ((again == "Y") || (again == "y")) {
        continue;
    }
    }
return(0);
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Clrscr
//
// clears the console window
//
// Thanks go to sunlight @ cprogramming.com
//
//////////////////////////////////////////////////////////////////////////////////////////////
void Clrscr()
{
   COORD coordScreen = { 0, 0 };
   DWORD cCharsWritten;
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   DWORD dwConSize;
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   GetConsoleScreenBufferInfo(hConsole, &csbi);
   dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
   FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
   GetConsoleScreenBufferInfo(hConsole, &csbi);
   FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
   SetConsoleCursorPosition(hConsole, coordScreen);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// PrintProgDetails
//
// Prints details and desription of the program.
///////////////////////////////////////////////////////////////////////////////////////////////////
void PrintProgDetails() {
    cout << endl;
    cout << "** PRIME NUMBER SIEVE (v4)" << endl;
    cout << "** A C++ program by Daniel Robinson." << endl;
    cout << "** Calculates all prime numbers up to a given integer entered by the user.";
    cout << endl << endl << endl << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Validate
//
// Checks whether input entered by user is an integer greater than 1.
//
// Currently the function allows a mix of integers and letters. E.g 12s is treated as 12/
///////////////////////////////////////////////////////////////////////////////////////////////////
void Validate(int x) {
    if (x <= 1) {
        cout << "Invalid entry." << endl << endl;
        validinput = false;
    }
    else validinput = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// GenerateList
//
// Generatates a list of integers 0,0,2,...,x and stores in vector "numbers".
///////////////////////////////////////////////////////////////////////////////////////////////////
void GenerateList(int x) {
    numbers.push_back(0);
    numbers.push_back(0);
    for(int i = 2; i <= x; i++) {
        numbers.push_back(i);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// PrintList
//
// Prints out the vector "numbers".
///////////////////////////////////////////////////////////////////////////////////////////////////
void PrintList() {
    for(vector<int>::iterator i = numbers.begin()+2; i != numbers.end(); i++) {
        cout << *i << " ";
    }
    cout << endl << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// EnterToContinue
//
// User prompted to hit return before the program can continue.
///////////////////////////////////////////////////////////////////////////////////////////////////
void EnterToContinue() {
    cout << "Press return to continue";
    cin.get();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// ZeroNonPrimes
//
// Set all non-primes in the vector "numbers" to zero, ready to be deleted.
///////////////////////////////////////////////////////////////////////////////////////////////////
void ZeroNonPrimes() {
    sqrtinput = sqrt(input);
    for(int x = 2; x <= sqrtinput; x++){
        if(numbers[x] == 0){
            continue;
        }
        else{
            pivot = numbers[x];
            cout << endl << "New pivot = " << pivot << "." << endl;
            cout << "Delete all multiples of " << pivot << ": " << endl << endl;
            ZeroMultiples();
        }
        PrintList();
        EnterToContinue();
        cout << endl << endl << endl;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// ZeroMultiples
//
// Sets all multiples of the variable "pivot" to zero.
///////////////////////////////////////////////////////////////////////////////////////////////////
void ZeroMultiples() {
    int ratio = input/pivot;

    for(int x = 2; x <= ratio; ++x){
        int product = pivot*x;
        numbers[product] = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// IsZero
//
// Predicate function to check whether x is equal to zero.
///////////////////////////////////////////////////////////////////////////////////////////////////
bool IsZero(int x) {
    return(x == 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// DeleteZeroes
//
// Delete all entries of the vector "numbers" which have value zero.
//
// Return value of the function "remove_if" is an iterator pointing to the new end of the vector "numbers".
//
// Not sure why +1 and -1 are needed for numbers.end and newEnd resp, but it works.
///////////////////////////////////////////////////////////////////////////////////////////////////
void DeleteZeroes() {
    vector<int>::iterator newEnd =
    remove_if(numbers.begin()+2, numbers.end()+1, IsZero);
    numbers.erase(newEnd-1, numbers.end());
}
