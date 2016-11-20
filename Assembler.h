#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

class Assembler{
 private:  
  //Binary value of operator is equal to the index of the string in the vector.
  vector<string> symbolTable;
  vector<string> fileContents; //vector that stores the lines of the text file

  //convert assembly to machine code
    bitset<16> convertLine(string* line);
  
 public:
  //Initialise the symbolTable with our default operators.
  Assembler();

  //Remember all Binary numbers are Big-Endian (100 = 1, 110 = 2)
  bitset<8> decimalToBinary(int number);
  
  int binaryToDecimal(bitset<32>);
  
  //read input from text file
  void read(string fileName);
  
  //write output to text file
  void write(string fileName);  
};
