#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

bool sudokuCheck(int sudoku[9][9]) {
    unordered_set<int> seen;

    // Check row
    for (int i = 0; i < 9; i++) {
        seen.clear();
        for (int j = 0; j < 9; j++) {
            seen.insert(sudoku[i][j]);
        }
        if (seen.size() != 9) {
            cout << "WRONG: Row" << endl;
            return 1;
        }
    }

    // Check column
    for (int i = 0; i < 9; i++) {
        seen.clear();
        for (int j = 0; j < 9; j++) {
            seen.insert(sudoku[j][i]);
        }
        if (seen.size() != 9) {
            cout << "WRONG: Column" << endl;
            return 1;
        }
    }

    // Check 3x3 box
    for (int boxRow = 0; boxRow < 9; boxRow += 3) {
        for (int boxCol = 0; boxCol < 9; boxCol += 3) {
            seen.clear();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    seen.insert(sudoku[boxRow + i][boxCol + j]);
                }
            }
            if (seen.size() != 9) {
                cout << "WRONG: 3x3 Box" << endl;
                return 1;
            }
        }
    }

    cout << "CORRECT" << endl;

    return 0;
}

int main(int argc, char* argv[]) {
    // Make sure a file path was provided
    if (argc != 2) {
        cout << "Incorrect arguments | Usage: sudoku SOLUTION" << endl<<"Where:\nSOLUTION is path to the text file with solution to examine.";
        return 1;
    }

    // Get the file path from the command line argument
    string file_path = argv[1];

    // Open the file
    ifstream file(file_path);

    // Make sure the file was opened successfully
    if (!file.is_open()) {
        cout << "ERROR: Could not open file '" << endl;
        return 1;
    }
    
    int sudoku[9][9];

    // Validation
    for (int i = 0; i < 9; i++) {
            
        for (int j = 0; j < 9; j++) {   
            
            char c;

            if (!(file >> c)) {
                cout << "ERROR: Sudoku too short" << endl;
                return 1;
            }
            
            if (!isdigit(c)) {
                cout << "ERROR: Invalid character " << c << endl;
                return 1;
            }
            else if(c == '0') {
                cout << "WRONG: Invalid character " << c << endl;
                return 1;
            }
            
            sudoku[i][j] = c - '0';
        }
    }

    if (file.get() != EOF) {
        cout << "ERROR: Extra characters at end of file" << endl;
        return false;
    }
     
    // Close the file
    file.close();
    
    return sudokuCheck(sudoku)==1? 1:0;
}

