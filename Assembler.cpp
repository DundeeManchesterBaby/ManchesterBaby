#include "Assembler.h"
#include <string>

using namespace std;

Assembler::Assembler(){
  symbolTable = {"", "", "", "", ""};
}

bitset<8> Assembler::decimalToBinary(int number){
  bitset<8> binary;
  binary.reset();
  //array to store 1s + 0s, currently 8bit number
  int rem;
  int num = number;
  
  for(int i=0; i<8; i++){
    if(num == 1){
      *binary[p+i]=1;
      return binary;
    }
    else if(num == 0){
      return binary;
    }
    rem = num%2;
    *binary[p+i] = rem;
    num = num/2;
  }
}

int binaryToDecimal(bitset<3>){
  return NULL;
}

void convertLine();

void Assembler::read(string fileName){
  string currentLine;
  ifstream fileStream;
  fileStream.open(fileName);
  
  while(getline(fileStream,currentLine){
      //loop through the file, storing lines to be implemented
	}
    }
  
  void Assembler::write(string fileName){
    ofstream fileStream;
    // fileStream.open(fileName);
    
    // for(//number of iterations){
    //   fileStream << "Output data" << endl;
    //}
  }
  
