/* Authors: Ewan Mallinson - 150007735 Martin Learmont - */
/* Module: AC21009 Team 20*/

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
  
  for(int i=7; i>=0; i--){
    if(num == 1){
      binary[i] = 1;
      return binary;
    }
    else if(num == 0){
      return binary;
    }
    rem = num%2;
    binary[i] = rem;
    num = num/2;
  }
}

bitset<32> Assembler::convertLine(string line){
  string instructions[8] = {"JMP", "JRP", "LDN", "STO", "SUB", "CMP", "STP", "VAR"};
  int pos = 0;
  int counter = 0;
  int iValue = 0;
  int writePos = 31;
  int varCount = 0;
  bitset<32> codeReturn;
    for(counter=0; counter<8; counter++){
      pos = line.find(instructions[counter], pos); //line.find() returns -1 if an instruction is not found
      if(pos != -1){
        iValue = counter;
        counter = 8;
      }
    }
    if(iValue == 0){
      codeReturn[writePos] = 0;
      writePos--;
      codeReturn[writePos] = 0;
      writePos--;
      codeReturn[writePos] = 0;
      writePos--;
      pos = 4;
      string binaryAddress = getOperandAddress(line, pos);
      for(int i=0; i<7; i++, writePos--){
        codeReturn[writePos] = binaryAddress[i];
      }
    }
    else if(iValue == 1){
      codeReturn[writePos] = 1;
      writePos--;
      codeReturn[writePos] = 0;
      writePos--;
      codeReturn[writePos] = 0;
      writePos--;
      pos = 4;
      string binaryAddress = getOperandAddress(line, pos);
      for(int i=0; i<7; i++, writePos--){
        codeReturn[writePos] = binaryAddress[i];
      }
    }
    else if(iValue == 2){
      codeReturn[writePos] = 0;
      writePos--;
      codeReturn[writePos] = 1;
      writePos--;
      codeReturn[writePos] = 0;
      writePos--;
      string binaryAddress = getOperandAddress(line, pos);
      for(int i=0; i<7; i++, writePos--){
        codeReturn[writePos] = binaryAddress[i];
      }
    }
    else if(iValue == 3){
      codeReturn[writePos] = 1;
      writePos--;
      codeReturn[writePos] = 1;
      writePos--;
      codeReturn[writePos] = 0;
      writePos--;
      pos = 4;
      string binaryAddress = getOperandAddress(line, pos);
      for(int i=0; i<7; i++, writePos--){
        codeReturn[writePos] = binaryAddress[i];
      }
    }
    else if(iValue == 4){
      codeReturn[writePos] = 0;
      writePos--;
      codeReturn[writePos] = 0;
      writePos--;
      codeReturn[writePos] = 1;
      writePos--;
      pos = 4;
      string binaryAddress = getOperandAddress(line, pos);
      for(int i=0; i<7; i++, writePos--){
        codeReturn[writePos] = binaryAddress[i];
      }
    }
    else if(iValue == 5){
      codeReturn[writePos] = 0;
      writePos--;
      codeReturn[writePos] = 1;
      writePos--;
      codeReturn[writePos] = 1;
      writePos--;
      pos = 4;
      string binaryAddress = getOperandAddress(line, pos);
      for(int i=0; i<7; i++, writePos--){
        codeReturn[writePos] = binaryAddress[i];
      }
    }
    else if(iValue == 6){
      codeReturn[writePos] = 1;
      writePos--;
      codeReturn[writePos] = 1;
      writePos--;
      codeReturn[writePos] = 1;
      writePos--;
    }
    else if(iValue == 7){
      string tempString;
      int tempPos = pos;
      pos = (line.find(":", pos)-1);
      for(int t=0; pos>=0; pos--){
        tempString = tempString + line[pos];
      }
      tempString = tempString + ":" + to_string(varCount) + ":";
      pos = tempPos + 4;
      while(line[pos] != ' '){
        tempString = tempString + line[pos];
        pos++;
      }
      symbolTable.push_back(tempString);
    }
  return codeReturn;
}

void Assembler::read(string fileName){
  string currentLine;
  ifstream fileStream;
  fileStream.open(fileName);
  
  
  while(getline(fileStream,currentLine)){
    fileContents.push_back(currentLine);
  }
}

  string Assembler::getOperandAddress(string line, int pos){
    string opName;
    string tempString;
    while(line[pos] != ' '){
      opName = opName + line[pos];
      pos++;
    }
    for(int i=0; i<symbolTable.size(); i++){
      int z = 0;
      while(symbolTable[i][z] != ':'){
        tempString = tempString + symbolTable[i][z];
        z++;
      }
      if(opName.compare(tempString)){
        z++;
        string numString;
        while(symbolTable[i][z] != ':'){
          numString = numString + symbolTable[i][z];
        }
        int addressInt = stoi(numString);
        bitset<8> addressBinary = decimalToBinary(addressInt);
	string tempString = addressBinary.to_string();
        return tempString;
      }
    }
  }
        
  void Assembler::write(string fileName){
    ofstream fileStream;
    fileStream.open(fileName);
    
    for(int i=0; i<fileContents.size(); i++){
      fileStream << convertLine(fileContents[i]);
    }
    fileStream.close();
  }
  