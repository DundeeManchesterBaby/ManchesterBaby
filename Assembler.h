#include <vector>
#include <iostream>
#include <ifstream>

using namespace std;

class Assembler{
 private:
  //Remember all Binary numbers are Big-Endian (100 = 1, 110 = 2)
  int* decimalToBinary(int number);
  void binaryToDecimal();
  
  //Binary value of operator is equal to the index of the string in the vector.
  vector<string> symbolTable;

  //convert assembly to machine code
    void convertLine();
  
 public:
  //Initialise the symbolTable with our default operators.
  Assembler();

  //read input from text file
  void read(string fileName);
  
  //write output to text file
  void write(string fileName);  
};
