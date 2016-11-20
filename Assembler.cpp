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
      *(binary+i) = 1;
      return binary;
    }
    else if(num == 0){
      return binary;
    }
    rem = num%2;
    *(binary+i) = rem;
    num = num/2;
  }
}

char* Assembler::convertLine(string* line){
  string instructions[7] = {"JMP", "JRP", "LDN", "STO", "SUB", "CMP", "STP"};
  int pos = 0;
  int counter = 0;
  int iValue = 0;
  int writePos = 0;
  char* codeReturn = new char[/*size of max instructions in 1s + 0s*/];
  while(pos < line.length()-3){
    for(counter=0; counter<7; counter++){
      pos = line.find(instructions[counter], pos);
      if(pos != -1){
        iValue = counter;
        counter = 7;
      }
    }
    if(iValue == 0){
      *(codeReturn+writePos) = 0;
      writePos++;
      *(codeReturn+writePos) = 0;
      writePos++;
      *(codeReturn+writePos) = 0;
      writePos++;
    }
    else if(iValue == 1){
      *(codeReturn+writePos) = 1;
      writePos++;
      *(codeReturn+writePos) = 0;
      writePos++;
      *(codeReturn+writePos) = 0;
      writePos++;
    }
    else if(iValue == 2){
      *(codeReturn+writePos) = 0;
      writePos++;
      *(codeReturn+writePos) = 1;
      writePos++;
      *(codeReturn+writePos) = 0;
      writePos++;
    }
    else if(iValue == 3){
      *(codeReturn+writePos) = 1;
      writePos++;
      *(codeReturn+writePos) = 1;
      writePos++;
      *(codeReturn+writePos) = 0;
      writePos++;
    }
    else if(iValue == 4){
      *(codeReturn+writePos) = 0;
      writePos++;
      *(codeReturn+writePos) = 0;
      writePos++;
      *(codeReturn+writePos) = 1;
      writePos++;
    }
    else if(iValue == 5){
      *(codeReturn+writePos) = 0;
      writePos++;
      *(codeReturn+writePos) = 1;
      writePos++;
      *(codeReturn+writePos) = 1;
      writePos++;
    }
    else if(iValue == 6){
      *(codeReturn+writePos) = 1;
      writePos++;
      *(codeReturn+writePos) = 1;
      writePos++;
      *(codeReturn+writePos) = 1;
      writePos++;
    }
  }
  return codeReturn;
}

>>>>>>> 82462f87cb9d9454f3b05c5eb3e34889fdee8614
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
  
