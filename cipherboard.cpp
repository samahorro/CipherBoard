// Samantha Ahorro
// Project 1 (CPSC-253)

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

const int GRID_SIZE = 3;  // 3x3 grid board

void displayGrid() {
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      cout << "[" << i << "," << j << "] ";
    }

    std::cout << "\n";
  }
}

// Function to read message from the file
string readMessage(string filename) {
  ifstream file(filename);
  if (!file) {
    return "ERROR: File not Found!";
  }
  string message, line;
  while (getline(file, line)) {
    message.append(line);  // reads the entire file content
  }
  file.close();
  return message;
}

// Function to get user-selected grid positions
void getUserSelection(vector<pair<int, int>>& positions) {
  cout << "\n-------------------------------------------------\n";
  cout << "Select 3 grid positions in the format: \n";
  cout << "Example Input:\n1 2\n2 2\n0 1\n\n";

  int i = 0;
  while (i < 3) {
    int pos1, pos2;
    cin >> pos1 >> pos2;

    if (pos1 < 0 || pos1 > 2 || pos2 < 0 || pos2 > 2) {
      fprintf(stderr,
              "Invalid Row and Column Number. Choose from the boxes above!\n");
    } else {
      positions.push_back(
          {pos1, pos2});  // stores each position the user selects

      i++;
    }
  }

  // shows selected positions
  cout << "\n";
  cout << "Selected Positions: " << endl;
  for (int i = 0; i < positions.size(); i++) {
    cout << "(" << positions[i].first << ", " << positions[i].second << ") "
         << endl;
  }
  cout << endl;
}

// decryption method

string decryptMessage(string encryptedMessage,
                      vector<pair<int, int>>& positions) {
  for (int i = 0; i < encryptedMessage.size(); i++) {
    // input (1,2)
    int new_row = positions[i % 3].first;
    int new_col = positions[i % 3].second;

    // (1 *2)
    int shift = (new_row * new_col) + (new_row + new_col) - (new_row ^ new_col);

    // Decryption Method:
    if (i % 2 == 0) {
      encryptedMessage[i] = encryptedMessage[i] - shift;
    } else {
      encryptedMessage[i] = encryptedMessage[i] + shift;
    }
  }
  return encryptedMessage;
}

string encryptMessage(string message, vector<pair<int, int>>& positions) {
  if (positions.size() != 3) {
    return "ERROR: Select exactly 3 grid positions.";
  }
  for (int i = 0; i < message.size(); i++) {
    // gets first and second so, (1,2)
    int row = positions[i % 3].first;
    int col = positions[i % 3].second;

    int shift = (row * col) + (row + col) - (row ^ col);

    // Apply encryption
    // if index is even
    if (i % 2 == 0) {
      message[i] = (message[i] + shift);
    } else {
      message[i] = (message[i] - shift);
    }
  }

  return message;
}

int main() {
  int choice;
  string fileName;
  vector<pair<int, int>> positions;

  // Simple user interface
  while (true) {
    cout << "\n-------------------------------------------------\n";
    cout << "\n⋆｡°✩ Welcome to the CipherBoard⋆｡°✩\n";
    cout << "\n-------------------------------------------------\n";
    cout << "\n";
    displayGrid();
    cout << "\n";
    cout << "1. Encrypt a file\n";
    cout << "2. Decrypt a file\n";
    cout << "3. Exit\n";
    cout << "\n-------------------------------------------------\n";
    cout << "Enter your choice: ";
    cin >> choice;

    // Enter text file to encrypt
    if (choice == 1) {  // Encrypt file
      cout << "Enter the file you want to encrypt: ";
      cin >> fileName;

      string message = readMessage(fileName);
      if (message == "ERROR: File not Found!") {
        cerr << message << endl;
        continue;  // Restart loop if file is not found
      }

      getUserSelection(positions);

      string encrypted = encryptMessage(message, positions);

      positions.clear();

      // saves to output file

      ofstream outFile("encrypted.txt");
      outFile << encrypted;
      outFile.close();
      cout << "Encrypted file saved!\n";
    }

    // choice to decrypt the file
    else if (choice == 2) {
      cout << "Enter the encrypted file to decrypt: ";
      cin >> fileName;
      string encryptMessage = readMessage(fileName);
      if (encryptMessage == "ERROR: File not Found!") {
        cerr << encryptMessage << endl;
        continue;
      }
      getUserSelection(positions);
      string decrypted = decryptMessage(encryptMessage, positions);
      ofstream new_outFile("decrypted.txt");
      new_outFile << decrypted;
      new_outFile.close();
      cout << "Decrypted file saved as 'decrypted.txt'!\n";
    }

    // exits the board
    else if (choice == 3) {
      cout << "Exiting CipherBoard.\n";
      break;
    } else {
      cout << "Invalid Choice. Please choose 1,2, or 3. \n";
    }

    return 0;
  }
}
