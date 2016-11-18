#include "Baby.h"
#include <iostream>

using namespace std;

Baby::Baby(){
  //Create our store of empty registers.
  bitset<32> initialRegister;
  store.resize(32, initialRegister);

  //This is only here for testing
  bitset<5> op;
  stopped = false;

  int x = 0;
  while(x<=7){
    ((*this).*symbolTable[x])(op);
    x++;
    }
}

int Baby::convertAddressToIndex(bitset<5> address){
  //reverse the bitset so that it is little endian, for use with to_ulong()
  bitset<5> reversed;
  for(int i = 4; i >= 0; i--){
    reversed[i] = address[4-i];
  }
  //return the converted decimal
  return reversed.to_ulong();
}

int Baby::convertOpcodeToIndex(bitset<3> opcode){
  bitset<3> reversed;
  for(int i = 2; i >= 0; i--){
    reversed[i] = opcode[2-i];
  }
  //return the converted decimal
  return reversed.to_ulong();
}

int Baby::convertBinaryToDecimal(bitset<32> convertThis){
  int x = 0;
  for(int i = 0; i <= 30; i++ ){
    convertThis[i] ? x += 2^i : false; 
      
    }
  return x;
  
}

bitset<32> Baby::incrementCI(){
  bitset<32> sum, increment;
  bool carry = false;
  for(int i = 0; i < 32; i++){
    sum[i] = (CI[i] ^ increment[i]) ^ carry;
    carry = ((CI[i] & increment[i]) | (CI[i] & carry)) | (increment[i] & carry);
  }
  return sum;
}


//Instruction Stubs, need to implement the functionality
void Baby::JMP(bitset<5> operand){
  cout << "JMP" << endl;  
  //CI = fetchFromStore(operand);
}

void Baby::JRP(bitset<5> operand){
  cout << "JRP" << endl;
  //CI += storeAddress;
}

void Baby::LDN(bitset<5> operand){
  cout << "LDN" << endl;
}

void Baby::STO(bitset<5> operand){
  cout << "STO" << endl;
}

void Baby::SUB(bitset<5> operand){
  cout << "SUB" << endl;
}

void Baby::CMP(bitset<5> operand){
  cout << "CMP" << endl;
}

void Baby::STOP(bitset<5> operand){
  cout << "STOP" << endl;
  stopped = true;
}


bitset<32> Baby::fetchFromStore(bitset<5> address){
  bitset<32> registerContents;

  //get the decimal value of the address that corresponds to the index of the register in the store
  unsigned int addressIndex = convertAddressToIndex(address);

  //get the register contents using the address index.
  registerContents = store[addressIndex];

  //return the register contents
  return registerContents;
}

void Baby::fetch(){
  //increment the address of the CI.
  incrementCI();

  //get the address of PI from CI's operand
  bitset<5> PIAddress = getOperandAddress(CI);
  
  //get the instruction to be executed from the address of CI and assign it to PI
  PI = fetchFromStore(PIAddress);

  //get the current opcode from PI
  bitset<3> opcode = getOperator(PI);

  //get the operand address as well
  bitset<5> operandAddress = getOperandAddress(PI);
  
  execute(opcode, operandAddress);  
}

void Baby::execute(bitset<3> opcode, bitset<5> operandAddress){
  int opcodeIndex = convertOpcodeToIndex(opcode);

  ((*this).*symbolTable[opcodeIndex])(operandAddress);

}

bitset<5> Baby::getOperandAddress(bitset<32> instruction){
  bitset<5> operand;
  
  for(int i = 0; i <= 4; i++){
    //extract bits one through five from the instruction and insert them into the operand
    operand[i] = instruction[i];
  }
  
  //return the extracted operand to the caller
   return operand;
}



bitset<3> Baby::getOperator(bitset<32> instruction){
  bitset<3> opcode;
  
  for(int i = 13; i <= 15; i++){
    //Extract the first, second and third bits of the opcode from the instruction
    opcode[i-13] = instruction[i];
  }
  
  //return the extracted opcode to the caller
  return opcode;
}
