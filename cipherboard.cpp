// Samantha Ahorro
// Project 1 (CPSC-253)

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

const int GRID_SIZE = 3;  // 3x3 grid board

void displayGrid() {
  cout << " Welcome to the Cipher Board " << "\n";

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
void getUserSelection(vector<pair<int, int>> &positions) {
  cout << "Select 3 grid positions in the format: \n";
  cout << "Example Input:\n1 2\n2 3\n3 1\n\n";

  for (int i = 0; i < 3; i++) {
    int pos1, pos2;
    cin >> pos1 >> pos2;
    positions.push_back({pos1, pos2});  // stores each position the user selects
  }

  // shows selected positions
  cout << "Selected Positions: ";
  for (int i = 0; i < positions.size(); i++) {
    cout << "(" << positions[i].first << ", " << positions[i].second << ") ";
  }
  cout << endl;
}

// Encryption Method
string encryptMessage(string message, vector<pair<int, int>> &positions) {
  if (positions.size() != 3) {
    return "ERROR: Select exactly 3 grid positions.";
  }
  // Encrypt each character cycling through
  for (size_t i = 0; i < message.size(); i++) {
    int shift = positions[i % 3].first * positions[i % 3].second;

    message[i] += shift;
  }
  return message;
}

int main() {
  // Enter text file to encrypt
  string fileName;
  cout << "Enter the file you want to encrypt: ";
  cin >> fileName;
  string message = readMessage(fileName);

  cout << "Message Loaded: \n" << message << endl;

  // stores user selections
  vector<pair<int, int>> positions;
  getUserSelection(positions);

  string encrypted = encryptMessage(fileName, positions);

  cout << "Encrypted Message: \n" << encrypted << endl;

  // saves to output file

  ofstream outFile("encrypted.txt");
  outFile << encrypted;
  outFile.close();
  cout << "Encrypted file saved!\n";

  return 0;
}
